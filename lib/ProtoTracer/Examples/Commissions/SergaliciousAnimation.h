#pragma once

#include "../Animation.h"
#include "../AnimationTracks/BlinkTrack.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Objects/LEDStripBackground.h"
#include "../../Morph/Commissions/SergaliciousFace.h"
#include "../../Render/Scene.h"
#include "../../Menu/SingleButtonMenu.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Signals/FFTVoiceDetection.h"
#include "../../Sensors/APDS9960.h"
#include "../../Sensors/MicrophoneFourier_DMA.h"
#include "../../Render/ObjectAlign.h"

#include "../../Materials/Animated/RainbowNoise.h"
#include "../../Materials/Animated/RainbowSpiral.h"
#include "../../Materials/Animated/SpectrumAnalyzer.h"
#include "../../Materials/Animated/AudioReactiveGradient.h"
#include "../../Materials/Animated/Oscilloscope.h"
#include "../../Materials/MaterialAnimator.h"



class SergaliciousAnimation : public Animation<4> {
private:
    SergaliciousFace pM;
    Background background;
    LEDStripBackground ledStripBackground;
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
    
    RGBColor gradientSpectrum[2] = {RGBColor(20, 69, 252), RGBColor(34, 243, 254)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 75.0f, false);
    
    MaterialAnimator<10> materialAnimator;
    MaterialAnimator<5> backgroundMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(200, 100), Vector2D(100, 50), true, true); 
    AudioReactiveGradient aRG = AudioReactiveGradient(Vector2D(160, 160), Vector2D(0, 0), true, true); 
    Oscilloscope oSC = Oscilloscope(Vector2D(200, 100), Vector2D(0, 0));

    //Animation controllers
    BlinkTrack<1> blink;
    BlinkTrack<1> blinkIdle;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 5.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 6.7f);
    FunctionGenerator fGenMatHue = FunctionGenerator(FunctionGenerator::Triangle, 0.0f, 360.0f, 17.3f);

    FunctionGenerator fGenMatXMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 1.1f);
    FunctionGenerator fGenMatYMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 2.7f);
    FunctionGenerator fGenMatRMenu = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 1.7f);

    FunctionGenerator fGenMatM1Sleep = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 5.3f);
    FunctionGenerator fGenMatM2Sleep = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 6.7f);
    FunctionGenerator fGenMatS1Sleep = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 4.6f);

    FunctionGenerator fGenLoadingRamp = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 8.3f);

    APDS9960 boop;

    FFTVoiceDetection<128> voiceDetection;

    ObjectAlign objA = ObjectAlign(Vector2D(0.0f, 0.0f), Vector2D(189.0f, 93.0f), Quaternion());

    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    float backgroundBSOD = 0.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;
    uint8_t backgroundBSODInd = 54;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::Happy), SergaliciousFace::Happy, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::Idle), SergaliciousFace::Idle, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::OwO), SergaliciousFace::OwO, 20, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::Squint), SergaliciousFace::Squint, 20, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::Loading), SergaliciousFace::Loading, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::LoadMove), SergaliciousFace::LoadMove, 20, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::Sad), SergaliciousFace::Sad, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::Heart), SergaliciousFace::Heart, 20, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::Question), SergaliciousFace::Question, 20, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::BSOD), SergaliciousFace::BSOD, 15, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::vrc_v_aa), SergaliciousFace::vrc_v_aa, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::vrc_v_ee), SergaliciousFace::vrc_v_ee, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::vrc_v_oo), SergaliciousFace::vrc_v_oo, 2, 0.0f, 1.0f);

        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
        eEA.AddParameter(&backgroundBSOD, backgroundBSODInd, 25, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::Blink));
        blinkIdle.AddParameter(pM.GetMorphWeightReference(SergaliciousFace::BlinkIdle));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(SergaliciousFace::vrc_v_aa, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(SergaliciousFace::vrc_v_ee, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(SergaliciousFace::vrc_v_oo, EasyEaseInterpolation::Linear);
        
        eEA.SetInterpolationMethod(SergaliciousFace::LoadMove, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(SergaliciousFace::Sad, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(SergaliciousFace::BSOD, EasyEaseInterpolation::Cosine);
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
        backgroundMaterial.AddMaterial(Material::Replace, &blueMaterial, 20, 0.0f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
        blinkIdle.Update();
    }

    void Default(){//Default mouth
        blink.Play();
        blinkIdle.Pause();
    }

    void Happy(){
        eEA.AddParameterFrame(SergaliciousFace::Happy, 1.0f);
        blink.Pause();
        blinkIdle.Pause();
    }

    void Idle(){
        eEA.AddParameterFrame(SergaliciousFace::Idle, 1.0f);
        blink.Pause();
        blinkIdle.Play();
    }

    void OwO(){
        eEA.AddParameterFrame(SergaliciousFace::OwO, 1.0f);
        blink.Pause();
        blinkIdle.Pause();
    }

    void Squint(){
        eEA.AddParameterFrame(SergaliciousFace::Squint, 1.0f);
        blink.Pause();
        blinkIdle.Pause();
    }

    void BSOD(){
        eEA.AddParameterFrame(SergaliciousFace::BSOD, 1.0f);
        eEA.AddParameterFrame(backgroundBSODInd, 1.0f);

        blink.Pause();
        blinkIdle.Pause();
        materialAnimator.AddMaterialFrame(whiteMaterial, 1.0f);
        backgroundMaterial.AddMaterialFrame(blueMaterial, backgroundBSOD);
    }

    void Loading(){
        eEA.AddParameterFrame(SergaliciousFace::Loading, 1.0f);
        eEA.AddParameterFrame(backgroundBSODInd, 1.0f);
        eEA.AddParameterFrame(SergaliciousFace::LoadMove, fGenLoadingRamp.Update());

        blink.Pause();
        blinkIdle.Pause();
    }
    
    void Sad(){
        eEA.AddParameterFrame(SergaliciousFace::Sad, 1.0f);
        blink.Play();
        blinkIdle.Pause();
    }
    
    void Heart(){
        eEA.AddParameterFrame(SergaliciousFace::Heart, 1.0f);
        blink.Pause();
        blinkIdle.Pause();
    }

    void Question(){
        eEA.AddParameterFrame(SergaliciousFace::Question, 1.0f);
        blink.Pause();
        blinkIdle.Pause();
    }

    void SpectrumAnalyzerFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndSA, 1.0f);

        backgroundMaterial.AddMaterialFrame(sA, offsetFaceSA);
        blinkIdle.Pause();
    }

    void AudioReactiveGradientFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndARG, 1.0f);

        backgroundMaterial.AddMaterialFrame(aRG, offsetFaceARG);
        blinkIdle.Pause();
    }

    void OscilloscopeFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndOSC, 1.0f);

        backgroundMaterial.AddMaterialFrame(oSC, offsetFaceOSC);
        blinkIdle.Pause();
    }

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            eEA.AddParameterFrame(SergaliciousFace::vrc_v_aa, MicrophoneFourier::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourier::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourier::GetFourierFiltered(), MicrophoneFourier::GetSampleRate());
        
                eEA.AddParameterFrame(SergaliciousFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                //eEA.AddParameterFrame(SergaliciousFace::vrc_v_oo, voiceDetection.GetViseme(voiceDetection.AH));
                //eEA.AddParameterFrame(SergaliciousFace::vrc_v_oo, voiceDetection.GetViseme(voiceDetection.UH));
                //eEA.AddParameterFrame(SergaliciousFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AR));
                //eEA.AddParameterFrame(SergaliciousFace::vrc_v_oo, voiceDetection.GetViseme(voiceDetection.ER));
                //eEA.AddParameterFrame(SergaliciousFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(SergaliciousFace::vrc_v_oo, voiceDetection.GetViseme(voiceDetection.OO));
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
    SergaliciousAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(background.GetObject());
        scene.AddObject(ledStripBackground.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        pM.GetObject()->SetMaterial(&materialAnimator);
        background.GetObject()->SetMaterial(&backgroundMaterial);
        ledStripBackground.GetObject()->SetMaterial(&materialAnimator);

        boop.Initialize(5);

        MicrophoneFourier::Initialize(15, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
        Menu::Initialize(11, 20, 500);//13 is number of faces

        gradientMat.SetRotationAngle(45);

        objA.SetJustification(ObjectAlign::Stretch);
        objA.SetMirrorX(true);
        //objA.SetMirrorY(true);
    }

    uint8_t GetAccentBrightness(){
        return Menu::GetAccentBrightness();
    };

    uint8_t GetBrightness(){
        return Menu::GetBrightness();
    };

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

        MicrophoneFourier::Update();
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
            Squint();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Happy();
            else if (mode == 2) Idle();
            else if (mode == 3) OwO();
            else if (mode == 4) BSOD();
            else if (mode == 5) Loading();
            else if (mode == 6) Heart();
            else if (mode == 7) Question();
            else if (mode == 8) {
                aRG.Update(MicrophoneFourier::GetFourierFiltered());
                AudioReactiveGradientFace();
            }
            else if (mode == 9){
                oSC.Update(MicrophoneFourier::GetSamples());
                OscilloscopeFace();
            }
            else {
                sA.Update(MicrophoneFourier::GetFourierFiltered());
                SpectrumAnalyzerFace();
            }
        }

        UpdateKeyFrameTracks();

        eEA.Update();
        pM.Update();
        
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
        objA.SetCameraMax(Vector2D(110.0f + faceSizeOffset, 93.0f).Multiply(scale));

        objA.AlignObjects(scene.GetObjects(), 1);
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset, yOffset - 110.0f * offsetFace, 0.0f));
        pM.GetObject()->UpdateTransform();
    }
};
