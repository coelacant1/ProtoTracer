#pragma once

#include "../Animation.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Objects/LEDStripBackground.h"
#include "../../Morph/ProtoV2Morph.h"
#include "../../Render/Scene.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Menu/Menu.h"
#include "../../Sensors/APDS9960.h"
#include "../../Sensors/SSD1306.h"

#include "../../Materials/Animated/RainbowNoise.h"
#include "../../Materials/Animated/RainbowSpiral.h"
#include "../../Materials/Animated/SpectrumAnalyzer.h"
#include "../../Materials/Animated/AudioReactiveGradient.h"
#include "../../Materials/Animated/Oscilloscope.h"

#include "../../Materials/MaterialAnimator.h"

#include "../AnimationTracks/BlinkTrack.h"

#include "../../Signals/FFTVoiceDetection.h"

#include "../../Sensors/MicrophoneFourier_MAX9814.h"


class HertzzAnimation : public Animation<2> {
private:
    ProtoV2 pM;
    Background background;
    EasyEaseAnimator<21> eEA = EasyEaseAnimator<21>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    
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
    
    RGBColor gradientSpectrum[2] = {RGBColor(5, 162, 232), RGBColor(10, 170, 255)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);
    
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
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 5.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 6.7f);
    FunctionGenerator fGenMatHue = FunctionGenerator(FunctionGenerator::Triangle, 0.0f, 360.0f, 17.3f);

    FunctionGenerator fGenMatXMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 1.1f);
    FunctionGenerator fGenMatYMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 2.7f);
    FunctionGenerator fGenMatRMenu = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 1.7f);

    FunctionGenerator sineSidePanel = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 3.0f);
    APDS9960 boop;
    
    SSD1306 oledDisplay;

    FFTVoiceDetection<128> voiceDetection;

    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoV2::Normal), ProtoV2::Normal, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoV2::Blush), ProtoV2::Blush, 25, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoV2::Hideblush), ProtoV2::Hideblush, 25, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoV2::Squint), ProtoV2::Squint, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoV2::Surprised), ProtoV2::Surprised, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoV2::Happy), ProtoV2::Happy, 20, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoV2::Sad), ProtoV2::Sad, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoV2::Talk), ProtoV2::Talk, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoV2::Whoop), ProtoV2::Whoop, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoV2::Side1), ProtoV2::Side1, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoV2::Angry), ProtoV2::Angry, 20, 0.0f, 1.0f);

        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(ProtoV2::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(ProtoV2::Hideblush, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(ProtoV2::Sad, EasyEaseInterpolation::Cosine);
        
        eEA.SetInterpolationMethod(ProtoV2::Talk, EasyEaseInterpolation::Linear);
    }

    void SetMaterialLayers(){
        materialAnimator.SetBaseMaterial(Material::Add, &gradientMat);
        materialAnimator.AddMaterial(Material::Replace, &orangeMaterial, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &whiteMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &greenMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Replace, &yellowMaterial, 40, 0.0f, 1.0f);//layer 4
        materialAnimator.AddMaterial(Material::Replace, &purpleMaterial, 40, 0.0f, 1.0f);//layer 5
        materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 6
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 7
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 8
        materialAnimator.AddMaterial(Material::Lighten, &rainbowNoise, 40, 0.35f, 1.0f);//layer 9

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    
    void Default(){
        oledDisplay.Display(F("Animating..."), F("Face: "), F("Default"));
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }

    void Squint(){
        oledDisplay.Display(F("Animating..."), F("Face: "), F("Squint"));
        eEA.AddParameterFrame(ProtoV2::Squint, 1.0f);
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }

    void Surprised(){
        oledDisplay.Display(F("Animating..."), F("Face: "), F("Surprised"));
        eEA.AddParameterFrame(ProtoV2::Surprised, 1.0f);
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }

    void Happy(){
        oledDisplay.Display(F("Animating..."), F("Face: "), F("Happy"));
        eEA.AddParameterFrame(ProtoV2::Happy, 1.0f);
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }

    void Sad(){
        oledDisplay.Display(F("Animating..."), F("Face: "), F("Sad"));
        eEA.AddParameterFrame(ProtoV2::Sad, 1.0f);
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }

    void Whoop(){
        oledDisplay.Display(F("Animating..."), F("Face: "), F("Whoop"));
        eEA.AddParameterFrame(ProtoV2::Whoop, 1.0f);
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }
    
    void Angry(){
        oledDisplay.Display(F("Animating..."), F("Face: "), F("Angry"));
        eEA.AddParameterFrame(ProtoV2::Angry, 1.0f);
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }

    void Blush(){
        oledDisplay.Display(F("Animating..."), F("Face: "), F("Blush"));
        eEA.AddParameterFrame(ProtoV2::Blush, 1.0f);
    }

    void SpectrumAnalyzerFace(){
        oledDisplay.Display(F("Animating..."), F("Audio: "), F("Fourier"));
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndSA, 1.0f);

        backgroundMaterial.AddMaterialFrame(sA, offsetFaceSA);
    }

    void AudioReactiveGradientFace(){
        oledDisplay.Display(F("Animating..."), F("Audio: "), F("Round"));
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndARG, 1.0f);

        backgroundMaterial.AddMaterialFrame(aRG, offsetFaceARG);
    }

    void OscilloscopeFace(){
        oledDisplay.Display(F("Animating..."), F("Audio: "), F("Oscillo"));
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndOSC, 1.0f);

        backgroundMaterial.AddMaterialFrame(oSC, offsetFaceOSC);
    }

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            //eEA.AddParameterFrame(ProtoV2::Talk, MicrophoneFourierIT::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourierIT::GetCurrentMagnitude() > 0.05f){
                /*
                voiceDetection.Update(MicrophoneFourierIT::GetFourierFiltered(), MicrophoneFourierIT::GetSampleRate());
        
                eEA.AddParameterFrame(ProtoV2::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(ProtoV2::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(ProtoV2::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.UH));
                eEA.AddParameterFrame(ProtoV2::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
                eEA.AddParameterFrame(ProtoV2::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(ProtoV2::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(ProtoV2::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
                */
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
    HertzzAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(background.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        pM.GetObject()->SetMaterial(&materialAnimator);
        background.GetObject()->SetMaterial(&backgroundMaterial);

        boop.Initialize(5);
        oledDisplay.Initialize();

        MicrophoneFourierIT::Initialize(22, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
        Menu::Initialize(10, 15, 500);//7 is number of faces
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
        
        Menu::Update(ratio);

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
            else if (mode == 1) Squint();
            else if (mode == 2) Happy();
            else if (mode == 3) Sad();
            else if (mode == 4) Whoop();
            else if (mode == 5) Angry();
            else if (mode == 6) Surprised();
            else if (mode == 7) {
                aRG.Update(MicrophoneFourierIT::GetFourierFiltered());
                AudioReactiveGradientFace();
            }
            else if (mode == 8){
                oSC.Update(MicrophoneFourierIT::GetSamples());
                OscilloscopeFace();
            }
            else {
                sA.Update(MicrophoneFourierIT::GetFourierFiltered());
                SpectrumAnalyzerFace();
            }
        }

        UpdateKeyFrameTracks();
        
        pM.SetMorphWeight(ProtoV2::Side1, sineSidePanel.Update());

        eEA.Update();
        pM.Update();
        
        float menuRatio = Menu::ShowMenu();

        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();
        backgroundMaterial.Update();

        uint8_t faceSize = Menu::GetFaceSize();

        float scale = menuRatio * 0.5f + 0.5f;
        float xShift = (1.0f - menuRatio) * -10.0f;
        float yShift = (1.0f - menuRatio) * 70.0f + offsetFaceSA * -150.0f;
        float adjustFacePos = float(4 - faceSize) * 5.0f;
        float adjustFaceX = float(faceSize) * 0.05f;
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(20.0f + xOffset, 0.0f + yOffset, 600.0f));
        //pM.GetObject()->GetTransform()->SetPosition(Vector3D(-20.0f + xOffset - xShift + adjustFacePos, 0.0f + yOffset + yShift, 600.0f));
        //pM.GetObject()->GetTransform()->SetScale(Vector3D(-0.975f + adjustFaceX, 0.65f, 0.8f).Multiply(scale));
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(sinf(ratio * 3.14159f / 180.0f * 1440.0f) * 1.0f, sinf(ratio * 3.14159f / 180.0f * 720.0f) * 1.0f, 0.0f));

        pM.GetObject()->UpdateTransform();
    }
};