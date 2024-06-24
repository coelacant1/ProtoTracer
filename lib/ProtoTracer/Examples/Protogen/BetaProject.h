#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "../Objects/Background.h"
#include "../Objects/LEDStripBackground.h"
#include "../Morph/BetaFront.h"
#include "../Morph/BetaRear.h"
#include "../Render/Scene.h"
#include "../Signals/FunctionGenerator.h"
#include "../Menu/Menu.h"
//#include "..\Menu\NeoTrellisMenu.h"
#include "../Sensors/APDS9960.h"

#include "../Materials/Animated/RainbowNoise.h"
#include "../Materials/Animated/RainbowSpiral.h"
#include "../Materials/Animated/SpectrumAnalyzer.h"
#include "../Materials/Animated/AudioReactiveGradient.h"
#include "../Materials/Animated/Oscilloscope.h"

#include "../Materials/MaterialAnimator.h"

#include "AnimationTracks/BlinkTrack.h"

#include "../Signals/FFTVoiceDetection.h"

#include "../Sensors/MicrophoneFourier_MAX9814.h"

#include "../Render/ObjectAlign.h"


class BetaAnimation : public Animation<4> {
private:
    static const uint8_t faceCount = 9;
    BetaFront pM;
    BetaRear rear;
    Background background;
    LEDStripBackground ledStripBackground;
    EasyEaseAnimator<35> eEA = EasyEaseAnimator<35>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    
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
    
    RGBColor gradientSpectrum[2] = {RGBColor(255, 255, 0), RGBColor(0, 255, 255)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 450.0f, false);
    
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

    FunctionGenerator fGenBlur = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 1.5f);

    KeyFrameTrack<1, 10> botFinLR1 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR2 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR3 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR4 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR5 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);

    APDS9960 boop;

    FFTVoiceDetection<128> voiceDetection;

    ObjectAlign objA = ObjectAlign(Vector2D(0.0f, 0.0f), Vector2D(189.0f, 93.0f), Quaternion());

    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::BlushEye), BetaFront::BlushEye, 40, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::HideBlush), BetaFront::HideBlush, 10, 1.0f, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::HideEyeBrow), BetaFront::HideEyeBrow, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::HideSecondEye), BetaFront::HideSecondEye, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::OwOMouth), BetaFront::OwOMouth, 60, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::SadEye), BetaFront::SadEye, 70, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::SadEyeBrow), BetaFront::SadEyeBrow, 80, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::SadMouth), BetaFront::SadMouth, 90, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::FlatMouth), BetaFront::FlatMouth, 50, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::DeadEye), BetaFront::DeadEye, 1, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::HeartEye), BetaFront::HeartEye, 30, 0.0f, 1.0f);
        
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::AlphaGenCircle), BetaFront::AlphaGenCircle, 90, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::HideAll), BetaFront::HideAll, 90, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::AngryEyeMouth), BetaFront::AngryEyeMouth, 90, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::vrc_v_ee), BetaFront::vrc_v_ee, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::vrc_v_ih), BetaFront::vrc_v_ih, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::vrc_v_dd), BetaFront::vrc_v_dd, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::vrc_v_rr), BetaFront::vrc_v_rr, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::vrc_v_ch), BetaFront::vrc_v_ch, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::vrc_v_aa), BetaFront::vrc_v_aa, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::vrc_v_oh), BetaFront::vrc_v_oh, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BetaFront::vrc_v_ss), BetaFront::vrc_v_ss, 2, 0.0f, 1.0f);

        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(BetaFront::ClosedEye));
        
        botFinLR1.AddParameter(rear.GetMorphWeightReference(BetaRear::Move1));
        botFinLR2.AddParameter(rear.GetMorphWeightReference(BetaRear::Move2));
        botFinLR3.AddParameter(rear.GetMorphWeightReference(BetaRear::Move3));
        botFinLR4.AddParameter(rear.GetMorphWeightReference(BetaRear::Move4));
        botFinLR5.AddParameter(rear.GetMorphWeightReference(BetaRear::Move5));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(BetaFront::HideBlush, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BetaFront::SadEye, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BetaFront::SadEyeBrow, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BetaFront::SadMouth, EasyEaseInterpolation::Cosine);

        eEA.SetInterpolationMethod(BetaFront::HideEyeBrow, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BetaFront::HideSecondEye, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BetaFront::AlphaGenCircle, EasyEaseInterpolation::Cosine);
        
        eEA.SetInterpolationMethod(BetaFront::vrc_v_ee, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BetaFront::vrc_v_ih, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BetaFront::vrc_v_dd, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BetaFront::vrc_v_rr, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BetaFront::vrc_v_ch, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BetaFront::vrc_v_aa, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BetaFront::vrc_v_oh, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BetaFront::vrc_v_ss, EasyEaseInterpolation::Linear);
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
        materialAnimator.AddMaterial(Material::Replace, &rainbowNoise, 40, 0.25f, 1.0f);//layer 9

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
    }

    void AddBotFinKeyFrames(){
        botFinLR1.AddKeyFrame(0.0f, 0.0f);
        botFinLR2.AddKeyFrame(0.0f, 0.0f);
        botFinLR3.AddKeyFrame(0.0f, 0.0f);
        botFinLR4.AddKeyFrame(0.0f, 0.0f);
        botFinLR5.AddKeyFrame(0.0f, 1.0f);

        botFinLR1.AddKeyFrame(0.5f, 1.0f);
        botFinLR2.AddKeyFrame(0.5f, 0.0f);
        botFinLR3.AddKeyFrame(0.5f, 0.0f);
        botFinLR4.AddKeyFrame(0.5f, 0.0f);
        botFinLR5.AddKeyFrame(0.5f, 0.0f);

        botFinLR1.AddKeyFrame(1.0f, 0.0f);
        botFinLR2.AddKeyFrame(1.0f, 1.0f);
        botFinLR3.AddKeyFrame(1.0f, 0.0f);
        botFinLR4.AddKeyFrame(1.0f, 0.0f);
        botFinLR5.AddKeyFrame(1.0f, 0.0f);

        botFinLR1.AddKeyFrame(1.5f, 0.0f);
        botFinLR2.AddKeyFrame(1.5f, 0.0f);
        botFinLR3.AddKeyFrame(1.5f, 1.0f);
        botFinLR4.AddKeyFrame(1.5f, 0.0f);
        botFinLR5.AddKeyFrame(1.5f, 0.0f);

        botFinLR1.AddKeyFrame(2.0f, 0.0f);
        botFinLR2.AddKeyFrame(2.0f, 0.0f);
        botFinLR3.AddKeyFrame(2.0f, 0.0f);
        botFinLR4.AddKeyFrame(2.0f, 1.0f);
        botFinLR5.AddKeyFrame(2.0f, 0.0f);
        
        botFinLR1.AddKeyFrame(2.5f, 0.0f);
        botFinLR2.AddKeyFrame(2.5f, 0.0f);
        botFinLR3.AddKeyFrame(2.5f, 0.0f);
        botFinLR4.AddKeyFrame(2.5f, 0.0f);
        botFinLR5.AddKeyFrame(2.5f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        botFinLR1.Update();
        botFinLR2.Update();
        botFinLR3.Update();
        botFinLR4.Update();
        botFinLR5.Update();

        blink.Update();
    }

    void Default(){
        pM.Reset();
        blink.Play();

        eEA.AddParameterFrame(BetaFront::HideSecondEye, 1.0f);
    }

    void OwO(){
        blink.Pause();
        eEA.AddParameterFrame(BetaFront::BlushEye, 1.0f);
        eEA.AddParameterFrame(BetaFront::HideBlush, 0.0f);
        eEA.AddParameterFrame(BetaFront::HideEyeBrow, 1.0f);
        eEA.AddParameterFrame(BetaFront::HideSecondEye, 1.0f);
        eEA.AddParameterFrame(BetaFront::OwOMouth, 1.0f);

        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }

    void Sad(){
        blink.Play();
        eEA.AddParameterFrame(BetaFront::SadEye, 1.0f);
        eEA.AddParameterFrame(BetaFront::SadEyeBrow, 1.0f);
        eEA.AddParameterFrame(BetaFront::SadMouth, 1.0f);
        eEA.AddParameterFrame(BetaFront::HideSecondEye, 1.0f);
        
        materialAnimator.AddMaterialFrame(blueMaterial, 0.8f);
    }

    void Dead(){
        blink.Pause();
        eEA.AddParameterFrame(BetaFront::FlatMouth, 1.0f);
        eEA.AddParameterFrame(BetaFront::DeadEye, 1.0f);
        eEA.AddParameterFrame(BetaFront::HideSecondEye, 1.0f);

        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
    }
    
    void Heart(){
        blink.Pause();
        eEA.AddParameterFrame(BetaFront::HeartEye, 1.0f);
        eEA.AddParameterFrame(BetaFront::HideEyeBrow, 1.0f);
        eEA.AddParameterFrame(BetaFront::OwOMouth, 1.0f);
        eEA.AddParameterFrame(BetaFront::HideSecondEye, 1.0f);

        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }
    
    void OwO2(){
        blink.Pause();
        eEA.AddParameterFrame(BetaFront::HideBlush, 0.0f);
        eEA.AddParameterFrame(BetaFront::HideEyeBrow, 0.0f);
        
        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }

    void AlphaGenCircle(){
        blink.Play();
        eEA.AddParameterFrame(BetaFront::HideBlush, 0.0f);
        eEA.AddParameterFrame(BetaFront::HideEyeBrow, 0.0f);
        eEA.AddParameterFrame(BetaFront::AlphaGenCircle, 1.0f);

        pM.SetMorphWeight(BetaFront::HideSecondEye, 0.0f);
    }

    void AngryFace(){
        blink.Play();
        pM.SetMorphWeight(BetaFront::HideSecondEye, 1.0f);
        
        eEA.AddParameterFrame(BetaFront::HideBlush, 1.0f);
        eEA.AddParameterFrame(BetaFront::HideEyeBrow, 1.0f);
        eEA.AddParameterFrame(BetaFront::AngryEyeMouth, 1.0f);
        pM.SetMorphWeight(BetaFront::HideSecondEye, 0.0f);
        
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
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
            eEA.AddParameterFrame(BetaFront::vrc_v_ss, MicrophoneFourierIT::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourierIT::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourierIT::GetFourierFiltered(), MicrophoneFourierIT::GetSampleRate());
        
                eEA.AddParameterFrame(BetaFront::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(BetaFront::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(BetaFront::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.UH));
                eEA.AddParameterFrame(BetaFront::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
                eEA.AddParameterFrame(BetaFront::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(BetaFront::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(BetaFront::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
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

    void UpdateKeyframeTracks(){
        botFinLR1.Update();
        botFinLR2.Update();
        botFinLR3.Update();
        botFinLR4.Update();
        botFinLR5.Update();
    }

public:
    BetaAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(rear.GetObject());
        scene.AddObject(background.GetObject());
        scene.AddObject(ledStripBackground.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        AddBotFinKeyFrames();

        pM.GetObject()->SetMaterial(&materialAnimator);
        rear.GetObject()->SetMaterial(&materialAnimator);
        background.GetObject()->SetMaterial(&backgroundMaterial);
        ledStripBackground.GetObject()->SetMaterial(&materialAnimator);

        objA.SetJustification(ObjectAlign::Stretch);
        objA.SetMirrorX(false);
    }

    void Initialize() override {
        boop.Initialize(5);

        MicrophoneFourierIT::Initialize(22, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
        //Menu::Initialize(9);//NeoTrellis
        Menu::Initialize(9, 0, 500);//7 is number of faces
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
        rear.Reset();

        float xOffset = fGenMatXMove.Update();
        float yOffset = fGenMatYMove.Update();
        
        Menu::Update(ratio);

        //Menu::SetSize(Vector2D(280, 60));
        //Menu::SetPositionOffset(Vector2D(0.0f, -30.0f * yOffset));

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

        gradientMat.HueShift(ratio * 720.0f);
        
        voiceDetection.SetThreshold(map(Menu::GetMicLevel(), 0, 10, 1000, 50));

        UpdateFFTVisemes();

        gradientSpectrum[0] = RGBColor(255, 0, 0).HueShift(Menu::GetHueF() * 36);
        gradientSpectrum[1] = RGBColor(255, 0, 0).HueShift(Menu::GetHueB() * 36);

        gradientMat.UpdateGradient(gradientSpectrum);

        if(isBooped){
            OwO();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Sad();
            else if (mode == 2) Heart();
            else if (mode == 3) Dead();
            else if (mode == 4) AlphaGenCircle();
            else if (mode == 5) AngryFace();
            else if (mode == 6) {
                aRG.Update(MicrophoneFourierIT::GetFourierFiltered());
                AudioReactiveGradientFace();
            }
            else if (mode == 7){
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
        rear.Update();
        
        //phaseR.SetRatio(eEA.GetValue(BetaFront::Surprised));
        //glitchX.SetRatio(eEA.GetValue(BetaFront::Surprised));

        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();
        backgroundMaterial.Update();

        uint8_t faceSize = Menu::GetFaceSize();
        float scale = Menu::ShowMenu() * 0.6f + 0.4f;
        float faceSizeOffset = faceSize * 8.0f;

        objA.SetPlaneOffsetAngle(0.0f);
        objA.SetEdgeMargin(4.0f);
        objA.SetCameraMax(Vector2D(110.0f + faceSizeOffset, 107.5f - 107.5f * offsetFace).Multiply(scale));

        objA.AlignObjects(scene.GetObjects(), 1);
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset, yOffset, 0.0f));
        pM.GetObject()->UpdateTransform();

        rear.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset * 0.05f + 260.0f, yOffset * 0.05f + 30.0f, 0.0f));
        rear.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 20.0f));
        rear.GetObject()->UpdateTransform();
    }
};
