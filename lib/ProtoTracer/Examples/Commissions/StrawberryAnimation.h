#pragma once

#include "../Animation.h"
#include "../AnimationTracks/BlinkTrack.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Objects/LEDStripBackground.h"
#include "../../Morph/Commissions/StrawberryBlush.h"
#include "../../Morph/Commissions/StrawberryFace.h"
#include "../../Morph/Commissions/StrawberryStinky.h"
#include "../../Morph/Commissions/StrawberryTears.h"
#include "../../Render/Scene.h"
#include "../../Menu/Menu.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Signals/FFTVoiceDetection.h"
#include "../../Sensors/BoopSensor.h"
#include "../../Sensors/MicrophoneFourier_MAX9814.h"
#include "../../Render/ObjectAlign.h"

#include "../../Materials/Animated/RainbowNoise.h"
#include "../../Materials/Animated/RainbowSpiral.h"
#include "../../Materials/Animated/SpectrumAnalyzer.h"
#include "../../Materials/Animated/AudioReactiveGradient.h"
#include "../../Materials/Animated/Oscilloscope.h"
#include "../../Materials/MaterialAnimator.h"
#include "../../Materials/MaterialMask.h"

#include "../../Shapes/Circle.h"
#include "../../Shapes/Ellipse.h"

class StrawberryAnimation : public Animation<6> {
private:
    StrawberryFace pM;
    StrawberryBlush pMBlush;
    StrawberryStinky pMStinky;
    StrawberryTears pMTears;
    Background background;
    LEDStripBackground ledStripBackground;

    Ellipse tongue = Ellipse(Vector2D(100.0f, 5.0f), Vector2D(100.0f, 40.0f), 0.0f);
    Circle eye = Circle(Vector2D(125.0f, 100.0f), 60.0f);
    
    EasyEaseAnimator<30> eEA = EasyEaseAnimator<30>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    
    //Materials
    RainbowNoise rainbowNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial orangeMaterial = SimpleMaterial(RGBColor(255, 165, 0));
    SimpleMaterial whiteMaterial = SimpleMaterial(RGBColor(255, 255, 255));
    SimpleMaterial greenMaterial = SimpleMaterial(RGBColor(0, 255, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    SimpleMaterial yellowMaterial = SimpleMaterial(RGBColor(255, 255, 0));
    SimpleMaterial purpleMaterial = SimpleMaterial(RGBColor(255, 0, 255));
    SimpleMaterial lightPinkMaterial = SimpleMaterial(RGBColor(251, 50, 219));
    
    RGBColor gradientSpectrum[2] = {RGBColor(100, 0, 80), RGBColor(80, 0, 60)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 200.0f, false);

    MaterialMask tongueMask = MaterialMask(&lightPinkMaterial, &gradientMat, &tongue);
    MaterialMask eyeMask = MaterialMask(&redMaterial, &tongueMask, &eye);
    
    MaterialAnimator<10> materialAnimator;
    MaterialAnimator<4> backgroundMaterial;

    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(200, 100), Vector2D(100, 50), true, true); 
    AudioReactiveGradient aRG = AudioReactiveGradient(Vector2D(160, 160), Vector2D(0, 0), true, true); 
    Oscilloscope oSC = Oscilloscope(Vector2D(200, 100), Vector2D(0, 0));

    //Animation controllers
    BlinkTrack<1> blink;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 2.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 2.7f);
    FunctionGenerator fGenMatHue = FunctionGenerator(FunctionGenerator::Triangle, 0.0f, 360.0f, 17.3f);

    FunctionGenerator fGenMatXMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 1.1f);
    FunctionGenerator fGenMatYMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 2.7f);
    FunctionGenerator fGenMatRMenu = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 1.7f);

    FunctionGenerator fGenMatStinkY = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 2.3f);
    FunctionGenerator fGenMatBlushY = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 2.7f);

    BoopSensor boop;

    FFTVoiceDetection<128> voiceDetection;

    ObjectAlign objA = ObjectAlign(Vector2D(0.0f, 0.0f), Vector2D(170.0f, 115.0f), Quaternion());

    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    float showTears = 0.0f;
    float showBlush = 0.0f;
    float showStink = 0.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;
    uint8_t showTearsInd = 54;
    uint8_t showBlushInd = 55;
    uint8_t showStinkInd = 56;
    uint8_t changeEyeColorInd = 57;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::Happy), StrawberryFace::Happy, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::Happy2), StrawberryFace::Happy2, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::HappyPog), StrawberryFace::HappyPog, 20, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::Happy3), StrawberryFace::Happy3, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::Content), StrawberryFace::Content, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::PogHeart), StrawberryFace::PogHeart, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::HappySurprised), StrawberryFace::HappySurprised, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::Nervous), StrawberryFace::Nervous, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::BlushHappy), StrawberryFace::BlushHappy, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::Stink), StrawberryFace::Stink, 30, 0.0f, 1.0f);

        //eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::Basis), StrawberryFace::Basis, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::TalkA), StrawberryFace::TalkA, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::TalkE), StrawberryFace::TalkE, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(StrawberryFace::TalkO), StrawberryFace::TalkO, 2, 0.0f, 1.0f);

        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
        eEA.AddParameter(&showTears, showTearsInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&showBlush, showBlushInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&showStink, showStinkInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(eyeMask.GetOpacityReference(), changeEyeColorInd, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(StrawberryFace::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(StrawberryFace::TalkA, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(StrawberryFace::TalkE, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(StrawberryFace::TalkO, EasyEaseInterpolation::Linear);
        
        eEA.SetInterpolationMethod(StrawberryFace::Stink, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(StrawberryFace::Nervous, EasyEaseInterpolation::Linear);
    }

    void SetMaterialLayers(){
        materialAnimator.SetBaseMaterial(Material::Add, &eyeMask);
        materialAnimator.AddMaterial(Material::Replace, &orangeMaterial, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &whiteMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &greenMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Replace, &yellowMaterial, 40, 0.0f, 1.0f);//layer 4
        materialAnimator.AddMaterial(Material::Replace, &purpleMaterial, 40, 0.0f, 1.0f);//layer 5
        materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 6
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 7
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 8
        materialAnimator.AddMaterial(Material::Lighten, &rainbowNoise, 40, 0.05f, 1.0f);//layer 9

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){//Default mouth
        eEA.AddParameterFrame(StrawberryFace::Happy, 1.0f);
        blink.Pause();
    }

    void HappyOpen(){
        eEA.AddParameterFrame(StrawberryFace::Happy2, 1.0f);
        blink.Pause();
    }

    void HappyPOG(){
        eEA.AddParameterFrame(StrawberryFace::HappyPog, 1.0f);
        blink.Pause();
    }

    void HappyTooth(){
        eEA.AddParameterFrame(StrawberryFace::Happy3, 1.0f);
        blink.Pause();
    }

    void HappyCalm(){
        eEA.AddParameterFrame(StrawberryFace::Content, 1.0f);
        blink.Play();
    }

    void HeartPOG(){
        eEA.AddParameterFrame(StrawberryFace::PogHeart, 1.0f);
        blink.Pause();
    }

    void HappyEyeOpen(){
        eEA.AddParameterFrame(StrawberryFace::HappySurprised, 1.0f);
        blink.Play();
    }
    
    void Nervous(){
        eEA.AddParameterFrame(StrawberryFace::Nervous, 1.0f);
        eEA.AddParameterFrame(showTearsInd, 1.0f);
        blink.Pause();
    }
    
    void Blush(){
        eEA.AddParameterFrame(StrawberryFace::BlushHappy, 1.0f);
        eEA.AddParameterFrame(showBlushInd, 1.0f);
        blink.Pause();
    }

    void Stinky(){
        eEA.AddParameterFrame(StrawberryFace::Stink, 1.0f);
        eEA.AddParameterFrame(showStinkInd, 1.0f);
        eEA.AddParameterFrame(changeEyeColorInd, 1.0f);
        blink.Pause();
    }

    void SpectrumAnalyzerFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndSA, 1.0f);

        backgroundMaterial.AddMaterialFrame(sA, offsetFaceSA);
    }

    void AudioReactiveGradientFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndARG, 1.0f);

        backgroundMaterial.AddMaterialFrame(aRG, offsetFaceARG);
    }

    void OscilloscopeFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndOSC, 1.0f);

        backgroundMaterial.AddMaterialFrame(oSC, offsetFaceOSC);
    }

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            eEA.AddParameterFrame(StrawberryFace::TalkA, MicrophoneFourierIT::GetCurrentMagnitude() * 0.5f);

            if(MicrophoneFourierIT::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourierIT::GetFourierFiltered(), MicrophoneFourierIT::GetSampleRate());
                
                eEA.AddParameterFrame(StrawberryFace::TalkE, voiceDetection.GetViseme(voiceDetection.EE) * 0.5f + voiceDetection.GetViseme(voiceDetection.ER) * 0.5f);
                eEA.AddParameterFrame(StrawberryFace::TalkO, voiceDetection.GetViseme(voiceDetection.UH) * 0.5f + voiceDetection.GetViseme(voiceDetection.OO) * 0.5f);
                //eEA.AddParameterFrame(StrawberryFace::TalkA, voiceDetection.GetViseme(voiceDetection.AR));
                //eEA.AddParameterFrame(StrawberryFace::TalkA, voiceDetection.GetViseme(voiceDetection.AH));
                //eEA.AddParameterFrame(StrawberryFace::TalkO, voiceDetection.GetViseme(voiceDetection.OO) / 0.75f);
            }
        }
    }

    void SetMaterialColor(){
        switch(Menu::GetFaceColor()){
            case 1: materialAnimator.AddMaterialFrame(redMaterial, 0.8f); break;
            case 2: materialAnimator.AddMaterialFrame(orangeMaterial, 0.8f); break;
            case 3: materialAnimator.AddMaterialFrame(whiteMaterial, 0.8f); break;
            case 4: materialAnimator.AddMaterialFrame(greenMaterial, 0.8f); break;
            case 5: materialAnimator.AddMaterialFrame(blueMaterial, 0.8f); break;
            case 6: materialAnimator.AddMaterialFrame(yellowMaterial, 0.8f); break;
            case 7: materialAnimator.AddMaterialFrame(purpleMaterial, 0.8f); break;
            case 8: materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f); break;
            case 9: materialAnimator.AddMaterialFrame(rainbowNoise, 0.8f); break;
            default: break;
        }
    }

public:
    StrawberryAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(pMBlush.GetObject());
        scene.AddObject(pMStinky.GetObject());
        scene.AddObject(pMTears.GetObject());
        scene.AddObject(background.GetObject());
        scene.AddObject(ledStripBackground.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        pM.GetObject()->SetMaterial(&materialAnimator);
        pMBlush.GetObject()->SetMaterial(&redMaterial);
        pMStinky.GetObject()->SetMaterial(&greenMaterial);
        pMTears.GetObject()->SetMaterial(&blueMaterial);
        background.GetObject()->SetMaterial(&backgroundMaterial);
        ledStripBackground.GetObject()->SetMaterial(&materialAnimator);

        boop.Initialize(5);

        MicrophoneFourierIT::Initialize(22, 8000, 30.0f, 100.0f);//8KHz sample rate, 50dB min, 120dB max
        Menu::Initialize(12, 0, 500);//13 is number of faces

        gradientMat.SetRotationAngle(90);

        objA.SetJustification(ObjectAlign::Stretch);
        objA.SetMirrorX(true);
        //objA.SetMirrorY(true);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    void Update(float ratio) override {
        pM.Reset();

        float xOffset = fGenMatXMove.Update();
        float yOffset = fGenMatYMove.Update();
        
        Menu::Update();

        SetMaterialColor();

        bool isBooped = Menu::UseBoopSensor() ? boop.isBooped() : 0;
        uint8_t mode = Menu::GetFaceState();//change by button press

        MicrophoneFourierIT::Update();
        sA.SetHueAngle(ratio * 360.0f * 4.0f);
        sA.SetMirrorYState(Menu::MirrorSpectrumAnalyzer());
        sA.SetFlipYState(!Menu::MirrorSpectrumAnalyzer());
        
        aRG.SetRadius((xOffset + 2.0f) * 2.0f + 25.0f);
        aRG.SetSize(Vector2D((xOffset + 2.0f) * 10.0f + 50.0f, (xOffset + 2.0f) * 10.0f + 50.0f));
        aRG.SetHueAngle(ratio * 360.0f * 8.0f);
        aRG.SetRotation(ratio * 360.0f * 2.0f);
        aRG.SetPosition(Vector2D(80.0f + xOffset * 4.0f, 48.0f + yOffset * 4.0f));

        oSC.SetSize(Vector2D(200.0f, 100.0f));
        oSC.SetHueAngle(ratio * 360.0f * 8.0f);
        oSC.SetPosition(Vector2D(100.0f, 50.0f));
        
        voiceDetection.SetThreshold(map(Menu::GetMicLevel(), 0, 10, 1000, 50));

        UpdateFFTVisemes();

        if (isBooped){
            Blush();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) HappyOpen();
            else if (mode == 2) HappyPOG();
            else if (mode == 3) HappyTooth();
            else if (mode == 4) HappyCalm();
            else if (mode == 5) HeartPOG();
            else if (mode == 6) HappyEyeOpen();
            else if (mode == 7) Nervous();
            else if (mode == 8) Stinky();
            else if (mode == 9) {
                aRG.Update(MicrophoneFourierIT::GetFourierFiltered());
                AudioReactiveGradientFace();
            }
            else if (mode == 10){
                oSC.Update(MicrophoneFourierIT::GetSamples());
                OscilloscopeFace();
            }
            else {
                sA.Update(MicrophoneFourierIT::GetFourierFiltered());
                SpectrumAnalyzerFace();
            }
        }

        UpdateKeyFrameTracks();

        eEA.Update();
        pM.Update();
        pMBlush.Update();
        pMTears.Update();
        pMStinky.Update();
        
        float menuRatio = Menu::ShowMenu();

        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();
        backgroundMaterial.Update();

        uint8_t faceSize = Menu::GetFaceSize();

        float scale = menuRatio * 0.6f + 0.4f;
        float faceSizeOffset = faceSize * 8.0f;

        //objA.SetPlaneOffsetAngle(360.0f * ratio);
        objA.SetEdgeMargin(2.0f);
        objA.SetCameraMax(Vector2D(110.0f + faceSizeOffset, 115.0f).Multiply(scale));

        objA.AlignObjects(scene.GetObjects(), 4);
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset + 5.0f, yOffset - 150.0f * offsetFace + 5.0f, 0.0f));
        pM.GetObject()->UpdateTransform();

        float stinkOffset = fGenMatStinkY.Update() * 15.0f;
        float blushOffset = fGenMatBlushY.Update() * 10.0f;

        pMBlush.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset - 60.0f + 5.0f - stinkOffset, yOffset - 150.0f * offsetFace + blushOffset, 0.0f));
        pMBlush.GetObject()->GetTransform()->SetScale(Vector3D(1.0f, 1.0f, 1.0f) * showBlush);
        pMBlush.GetObject()->UpdateTransform();
        pMStinky.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset - 35.0f + 5.0f, yOffset - 150.0f * offsetFace - 10.0f - stinkOffset, 0.0f));
        pMStinky.GetObject()->GetTransform()->SetScale(Vector3D(1.0f, 1.0f, 1.0f) * showStink);
        pMStinky.GetObject()->UpdateTransform();
        pMTears.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset + 5.0f, yOffset - 150.0f * offsetFace - 48.0f, 0.0f));
        pMTears.GetObject()->GetTransform()->SetScale(Vector3D(1.0f, 1.0f, 1.0f) * showTears);
        pMTears.GetObject()->UpdateTransform();
    }
};
