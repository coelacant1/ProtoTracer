#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Objects\Background.h"
#include "..\Render\Scene.h"
#include "..\Signals\FunctionGenerator.h"
#include "..\Menu\Menu.h"
#include "..\Sensors\APDS9960.h"
#include "..\Sensors\HeadsUpDisplay.h"
#include "..\Sensors\MicrophoneFourier_MAX9814.h"
//#include "..\Sensors\MicrophoneFourier_DMA.h"
#include "..\Sensors\FanController.h"

#include "..\Materials\MaterialAnimator.h"
#include "..\Materials\Animated\FlowNoise.h"
#include "..\Materials\Animated\RainbowNoise.h"
#include "..\Materials\Animated\RainbowSpiral.h"
#include "..\Materials\Animated\SpectrumAnalyzer.h"
#include "..\Materials\Animated\AudioReactiveGradient.h"
#include "..\Materials\Animated\Oscilloscope.h"

#include "AnimationTracks\BlinkTrack.h"
#include "..\Signals\FFTVoiceDetection.h"
#include "..\Render\ObjectAlign.h"

//Default Animation base for Analog microphone, APDS9960 boop sensor, and button control
template<size_t numObjects>
class ProtogenAnimation : public Animation<numObjects + 1> {
private:
    Background background;
    EasyEaseAnimator<40> eEA = EasyEaseAnimator<40>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);

    Vector2D camMin = Vector2D(0.0f, 0.0f);
    Vector2D camMax = Vector2D(189.0f, 93.0f);
    
    bool isBooped = false;
    bool blinkSet = false;

    Vector2D cameraSize;
    float xOffset = 0.0f;
    float yOffset = 0.0f;

    uint8_t microphonePin = 0;
    uint8_t buttonPin = 0;
    uint8_t faceCount = 10;
    
    //Materials
    FlowNoise flowNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial orangeMaterial = SimpleMaterial(RGBColor(255, 165, 0));
    SimpleMaterial whiteMaterial = SimpleMaterial(RGBColor(255, 255, 255));
    SimpleMaterial greenMaterial = SimpleMaterial(RGBColor(0, 255, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    SimpleMaterial yellowMaterial = SimpleMaterial(RGBColor(255, 255, 0));
    SimpleMaterial purpleMaterial = SimpleMaterial(RGBColor(255, 0, 255));
    
    RGBColor gradientSpectrum[2] = {RGBColor(255, 0, 0), RGBColor(255, 0, 0)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);
    
    MaterialAnimator<11> materialAnimator;
    MaterialAnimator<4> backgroundMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(200, 100), Vector2D(100, 50), true, true); 
    AudioReactiveGradient aRG = AudioReactiveGradient(Vector2D(160, 160), Vector2D(0, 0), true, true); 
    Oscilloscope oSC = Oscilloscope(Vector2D(200, 100), Vector2D(0, 0));

    //Animation controllers
    BlinkTrack<1> blink;
    ObjectAlign objA = ObjectAlign(camMin, camMax, Quaternion());

    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 5.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 6.7f);

    FanController fanController = FanController(15);
    APDS9960 boop;
    FFTVoiceDetection<128> voiceDetection;
    
    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;

    void LinkParameters(){
        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
    }

    void SetBaseMaterial(Material* material){
        materialAnimator.SetBaseMaterial(Material::Add, material);
    }

    void SetMaterialLayers(){
        materialAnimator.SetBaseMaterial(Material::Add, &gradientMat);
        materialAnimator.AddMaterial(Material::Replace, &yellowMaterial, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &orangeMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &whiteMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Replace, &greenMaterial, 40, 0.0f, 1.0f);//layer 4
        materialAnimator.AddMaterial(Material::Replace, &purpleMaterial, 40, 0.0f, 1.0f);//layer 5
        materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 6
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 7
        materialAnimator.AddMaterial(Material::Replace, &flowNoise, 40, 0.15f, 1.0f);//layer 8
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 9

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            eEA.AddParameterFrame(Viseme::SS + 100, MicrophoneFourier::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourier::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourier::GetFourierFiltered(), MicrophoneFourier::GetSampleRate());
        
                eEA.AddParameterFrame(Viseme::EE + 100, voiceDetection.GetViseme(Viseme::EE));
                eEA.AddParameterFrame(Viseme::AH + 100, voiceDetection.GetViseme(Viseme::AH));
                eEA.AddParameterFrame(Viseme::UH + 100, voiceDetection.GetViseme(Viseme::UH));
                eEA.AddParameterFrame(Viseme::AR + 100, voiceDetection.GetViseme(Viseme::AR));
                eEA.AddParameterFrame(Viseme::ER + 100, voiceDetection.GetViseme(Viseme::ER));
                eEA.AddParameterFrame(Viseme::OO + 100, voiceDetection.GetViseme(Viseme::OO));
            }
        }
    }

    void SetMaterialColor(){
        switch(Menu::GetFaceColor()){
            case 1: materialAnimator.AddMaterialFrame(yellowMaterial, 0.8f); break;
            case 2: materialAnimator.AddMaterialFrame(orangeMaterial, 0.8f); break;
            case 3: materialAnimator.AddMaterialFrame(whiteMaterial, 0.8f); break;
            case 4: materialAnimator.AddMaterialFrame(greenMaterial, 0.8f); break;
            case 5: materialAnimator.AddMaterialFrame(purpleMaterial, 0.8f); break;
            case 6: materialAnimator.AddMaterialFrame(redMaterial, 0.8f); break;
            case 7: materialAnimator.AddMaterialFrame(blueMaterial, 0.8f); break;
            case 8: materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f); break;
            case 9: materialAnimator.AddMaterialFrame(flowNoise, 0.8f); break;
            default: break;
        }
    }

protected:
    enum Color{
        CBASE,
        CYELLOW,
        CORANGE,
        CWHITE, 
        CGREEN,
        CPURPLE,
        CRED,
        CBLUE,
        CRAINBOW,
        CRAINBOWNOISE
    };
    
    HeadsUpDisplay hud = HeadsUpDisplay(Vector2D(0.0f, 0.0f), Vector2D(192.0f, 96.0f));

    virtual void LinkControlParameters() = 0;

    void UpdateFace(float ratio) {        
        Menu::Update(ratio);

        fanController.SetPWM(Menu::GetFanSpeed() * 25);
        
        xOffset = fGenMatXMove.Update();
        yOffset = fGenMatYMove.Update();
        
        if (Menu::UseBoopSensor()) {
           isBooped = boop.isBooped();
        }

        hud.SetEffect(Menu::GetEffect());// Pull Effect from menu and store reference in hud for observing data
        hud.Update();
        this->scene.SetEffect(&hud);// Use HUD as effect for overlay/data extraction

        voiceDetection.SetThreshold(map(Menu::GetMicLevel(), 0, 10, 1000, 50));
        UpdateFFTVisemes();

        MicrophoneFourier::Update();

        sA.SetHueAngle(ratio * 360.0f * 4.0f);
        sA.SetMirrorYState(Menu::MirrorSpectrumAnalyzer());
        sA.SetFlipYState(!Menu::MirrorSpectrumAnalyzer());
        
        aRG.SetRadius((xOffset + 2.0f) * 2.0f + 25.0f);
        aRG.SetSize(Vector2D((xOffset + 2.0f) * 10.0f + 50.0f, (xOffset + 2.0f) * 10.0f + 50.0f));
        aRG.SetHueAngle(ratio * 360.0f * 8.0f);
        aRG.SetRotation(ratio * 360.0f * 2.0f);

        oSC.SetHueAngle(ratio * 360.0f * 8.0f);
        
        SetMaterialColor();
        RGBColor hueFront = RGBColor(255, 0, 0).HueShift(Menu::GetHueF() * 36);
        RGBColor hueBack  = RGBColor(255, 0, 0).HueShift(Menu::GetHueB() * 36);

        gradientSpectrum[0] = hueFront;
        gradientSpectrum[1] = hueBack;
        gradientMat.UpdateGradient(gradientSpectrum);

        flowNoise.SetGradient(hueFront, 0);
        flowNoise.SetGradient(hueBack, 1);

        UpdateKeyFrameTracks();

        eEA.Update();
        
        flowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();
        backgroundMaterial.Update();

        uint8_t faceSize = Menu::GetFaceSize();
        float scale = Menu::ShowMenu() * 0.6f + 0.4f;
        float faceSizeOffset = faceSize * (cameraSize.X / 20.0f);// /2 for min of half size, /10 for 10 face size options
        float faceSizeMaxX = cameraSize.X / 2.0f;

        float xMaxCamera = cameraSize.X - faceSizeMaxX + faceSizeOffset;
        
        aRG.SetPosition(Vector2D(xMaxCamera / 2.0f + xOffset * 4.0f, cameraSize.Y / 2.0f + yOffset * 4.0f));

        objA.SetCameraMax(Vector2D(xMaxCamera, cameraSize.Y - cameraSize.Y * offsetFace).Multiply(scale));
    }

    void AlignObject(Object3D* obj, float rotation = 0.0f, float margin = 2.0f){
        objA.SetPlaneOffsetAngle(rotation);
        objA.SetEdgeMargin(margin);
        objA.AlignObject(obj);
    }

    void AlignObjects(Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f){
        objA.SetPlaneOffsetAngle(rotation);
        objA.SetEdgeMargin(margin);
        objA.AlignObjects(objects, objectCount);
    }

    void AlignObjectNoScale(Object3D* obj, float rotation = 0.0f, float margin = 2.0f){
        objA.SetPlaneOffsetAngle(rotation);
        objA.SetEdgeMargin(margin);
        objA.AlignObjectNoScale(obj);
    }
    
    void AlignObjectsNoScale(Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f){
        objA.SetPlaneOffsetAngle(rotation);
        objA.SetEdgeMargin(margin);
        objA.AlignObjectsNoScale(objects, objectCount);
    }

    void AddParameter(uint8_t index, float* parameter, uint8_t transitionFrames, EasyEaseInterpolation::InterpolationMethod interpolationMethod = EasyEaseInterpolation::InterpolationMethod::Overshoot, bool invertDirection = false){
        if(invertDirection){
            eEA.AddParameter(parameter, index, transitionFrames, 1.0f, 0.0f);
        }
        else{
            eEA.AddParameter(parameter, index, transitionFrames, 0.0f, 1.0f);
        }

        eEA.SetInterpolationMethod(index, interpolationMethod);
    }

    void AddViseme(Viseme::MouthShape visemeName, float* parameter){
        eEA.AddParameter(parameter, visemeName + 100, 2, 0.0f, 1.0f);

        eEA.SetInterpolationMethod(visemeName + 100, EasyEaseInterpolation::Linear);
    }

    void AddBlinkParameter(float* blinkParameter){
        blink.AddParameter(blinkParameter);

        blinkSet = true;
    }

    void AddParameterFrame(uint16_t animationIndex, float target){
        eEA.AddParameterFrame(animationIndex, target);
    }

    void AddMaterialFrame(Color color){
        switch(color){
            case CYELLOW:
                materialAnimator.AddMaterialFrame(yellowMaterial, 0.8f);
                break;
            case CORANGE:
                materialAnimator.AddMaterialFrame(orangeMaterial, 0.8f);
                break;
            case CWHITE:
                materialAnimator.AddMaterialFrame(whiteMaterial, 0.8f);
                break;
            case CGREEN:
                materialAnimator.AddMaterialFrame(greenMaterial, 0.8f);
                break;
            case CPURPLE:
                materialAnimator.AddMaterialFrame(purpleMaterial, 0.8f);
                break;
            case CRED:
                materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
                break;
            case CBLUE:
                materialAnimator.AddMaterialFrame(blueMaterial, 0.8f);
                break;
            case CRAINBOW:
                materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
                break;
            case CRAINBOWNOISE:
                materialAnimator.AddMaterialFrame(flowNoise, 0.8f);
                break;
            default:
                break;
        }
    }

    void SpectrumAnalyzerFace(){
        sA.Update(MicrophoneFourier::GetFourierFiltered());

        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndSA, 1.0f);

        backgroundMaterial.AddMaterialFrame(sA, offsetFaceSA);
    }

    void AudioReactiveGradientFace(){
        aRG.Update(MicrophoneFourier::GetFourierFiltered());

        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndARG, 1.0f);

        backgroundMaterial.AddMaterialFrame(aRG, offsetFaceARG);
    }

    void OscilloscopeFace(){
        oSC.Update(MicrophoneFourier::GetSamples());

        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndOSC, 1.0f);

        backgroundMaterial.AddMaterialFrame(oSC, offsetFaceOSC);
    }

    void HideFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
    }

    void DisableBlinking(){
        blink.Pause();
        blink.Reset();
    }

    void EnableBlinking(){
        blink.Reset();
        blink.Play();
    }

    bool IsBooped(){
        return isBooped;
    }

    Vector3D GetWiggleOffset(){
        return Vector3D(fGenMatXMove.Update(), fGenMatYMove.Update(), 0);
    }

    void SetWiggleSpeed(float multiplier){
        fGenMatXMove.SetPeriod(5.3f / multiplier);
        fGenMatYMove.SetPeriod(6.7f / multiplier);
    }

    void SetMenuWiggleSpeed(float multiplierX, float multiplierY, float multiplierR){
        Menu::SetWiggleSpeed(multiplierX, multiplierY, multiplierR);
    }

    void SetMenuOffset(Vector2D offset){
        Menu::SetPositionOffset(offset);
    }

    void SetMenuSize(Vector2D size){
        Menu::SetSize(size);
    }

public:
    ProtogenAnimation(Vector2D camMin, Vector2D camMax, uint8_t microphonePin, uint8_t buttonPin, uint8_t faceCount) {
        this->camMin = camMin;
        this->camMax = camMax;
        this->microphonePin = microphonePin;
        this->buttonPin = buttonPin;
        this->faceCount = faceCount;

        this->scene.AddObject(background.GetObject());
        
        background.GetObject()->SetMaterial(&backgroundMaterial);

        LinkParameters();

        SetMaterialLayers();

        objA.SetCameraMax(camMax);
        objA.SetCameraMin(camMin);
        objA.SetJustification(ObjectAlign::Stretch);
        objA.SetMirrorX(true);
        
        this->scene.EnableEffect();

        cameraSize = camMax - camMin;

        sA.SetSize(cameraSize);
        sA.SetPosition(cameraSize / 2.0f);

        oSC.SetSize(cameraSize);
        oSC.SetPosition(cameraSize / 2.0f);

        hud.SetFaceMax(camMax);
        hud.SetFaceMin(camMin);
    }

    Material* GetFaceMaterial(){
        return &materialAnimator;
    }

    Material* GetBackgroundMaterial(){
        return &backgroundMaterial;
    }

    void Initialize() override {
        boop.Initialize(5);

        hud.Initialize();

        fanController.Initialize();

        MicrophoneFourier::Initialize(microphonePin, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
        
        #ifdef NEOTRELLISMENU
        Menu::Initialize(faceCount);//NeoTrellis
        #else
        Menu::Initialize(faceCount, buttonPin, 500);//7 is number of faces
        #endif
    }

    uint8_t GetAccentBrightness(){
        return Menu::GetAccentBrightness();
    };

    uint8_t GetBrightness(){
        return Menu::GetBrightness();
    };

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

};
