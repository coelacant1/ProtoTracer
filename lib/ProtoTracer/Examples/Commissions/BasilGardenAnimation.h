#pragma once

#include "../Animation.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Objects/LEDStripBackground.h"
#include "../../Morph/Commissions/BasilGarden.h"
#include "../../Render/Scene.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Menu/SingleButtonMenu.h"
#include "../../Sensors/APDS9960.h"

#include "../../Materials/Animated/RainbowNoise.h"
#include "../../Materials/Animated/RainbowSpiral.h"
#include "../../Materials/Animated/SpectrumAnalyzer.h"
#include "../../Materials/Animated/AudioReactiveGradient.h"
#include "../../Materials/Animated/Oscilloscope.h"

#include "../../Materials/MaterialAnimator.h"

#include "../AnimationTracks/BlinkTrack.h"

#include "../../Signals/FFTVoiceDetection.h"

#include "../../Sensors/MicrophoneFourier_MAX9814.h"

#include "../../Render/ObjectAlign.h"

#include "../../Screenspace/GlitchX.h"
#include "../../Screenspace/Fisheye.h"
#include "../../Screenspace/HorizontalBlur.h"
#include "../../Screenspace/PhaseOffsetX.h"
#include "../../Screenspace/PhaseOffsetY.h"
#include "../../Screenspace/PhaseOffsetR.h"
#include "../../Screenspace/Magnet.h"
#include "../../Screenspace/Overflow.h"
#include "../../Screenspace/RadialBlur.h"
#include "../../Screenspace/ShiftR.h"
#include "../../Screenspace/VerticalBlur.h"

class BasilGardenAnimation : public Animation<3> {
private:
    static const uint8_t faceCount = 9;
    BasilGarden pM;
    Background background;
    LEDStripBackground ledStripBackground;
    EasyEaseAnimator<25> eEA = EasyEaseAnimator<25>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    
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
    
    RGBColor gradientSpectrum[2] = {RGBColor(252, 145, 34), RGBColor(252, 80, 15)};
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

    FunctionGenerator fGenBlur = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 1.5f);

    APDS9960 boop;

    FFTVoiceDetection<128> voiceDetection;

    ObjectAlign objA = ObjectAlign(Vector2D(0.0f, 0.0f), Vector2D(189.0f, 93.0f), Quaternion());
    
    Fisheye fisheye = Fisheye();
    GlitchX glitchX = GlitchX(30);
    HorizontalBlur blurH = HorizontalBlur(8);
    VerticalBlur blurV = VerticalBlur(8);
    Magnet magnet = Magnet();
    RadialBlur blurR = RadialBlur(8);
    PhaseOffsetX phaseX = PhaseOffsetX(8);
    PhaseOffsetY phaseY = PhaseOffsetY(8);
    PhaseOffsetR phaseR = PhaseOffsetR(8);
    ShiftR shiftR = ShiftR(8);
    Overflow overflow = Overflow(8);

    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::Angry), BasilGarden::Angry, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::Sad), BasilGarden::Sad, 50, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::Rage), BasilGarden::Rage, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::Smirk), BasilGarden::Smirk, 25, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::Disappointed), BasilGarden::Disappointed, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::Grimace), BasilGarden::Grimace, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::Whoops), BasilGarden::Whoops, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::Crabby), BasilGarden::Crabby, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::Default), BasilGarden::Default, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::ForReal), BasilGarden::ForReal, 30, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::vrc_v_ee), BasilGarden::vrc_v_ee, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::vrc_v_ih), BasilGarden::vrc_v_ih, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::vrc_v_dd), BasilGarden::vrc_v_dd, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::vrc_v_rr), BasilGarden::vrc_v_rr, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::vrc_v_ch), BasilGarden::vrc_v_ch, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::vrc_v_aa), BasilGarden::vrc_v_aa, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::vrc_v_oh), BasilGarden::vrc_v_oh, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BasilGarden::vrc_v_ss), BasilGarden::vrc_v_ss, 2, 0.0f, 1.0f);

        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(BasilGarden::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(BasilGarden::Sad, EasyEaseInterpolation::Cosine);
        
        eEA.SetInterpolationMethod(BasilGarden::vrc_v_ee, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BasilGarden::vrc_v_ih, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BasilGarden::vrc_v_dd, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BasilGarden::vrc_v_rr, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BasilGarden::vrc_v_ch, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BasilGarden::vrc_v_aa, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BasilGarden::vrc_v_oh, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BasilGarden::vrc_v_ss, EasyEaseInterpolation::Linear);
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
        materialAnimator.AddMaterial(Material::Replace, &rainbowNoise, 40, 0.15f, 1.0f);//layer 9

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){
        scene.DisableEffect();
        eEA.AddParameterFrame(BasilGarden::Default, 1.0f);
    }

    void Angry(){
        eEA.AddParameterFrame(BasilGarden::Angry, 1.0f);
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
    } 

    void Sad(){
        eEA.AddParameterFrame(BasilGarden::Sad, 1.0f);
        materialAnimator.AddMaterialFrame(blueMaterial, 0.8f);
    }

    void Rage(){
        scene.SetEffect(&glitchX);
        scene.DisableEffect();

        eEA.AddParameterFrame(BasilGarden::Rage, 1.0f);
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
    }
    
    void Smirk(){
        eEA.AddParameterFrame(BasilGarden::Smirk, 1.0f);
    }
    
    void Disappointed(){
        eEA.AddParameterFrame(BasilGarden::Disappointed, 1.0f);
    }

    void Grimace(){
        eEA.AddParameterFrame(BasilGarden::Grimace, 1.0f);
    }

    void Whoops(){
        eEA.AddParameterFrame(BasilGarden::Whoops, 1.0f);
    }

    void Crabby(){
        eEA.AddParameterFrame(BasilGarden::Crabby, 1.0f);
    }

    void ForReal(){
        eEA.AddParameterFrame(BasilGarden::ForReal, 1.0f);
        materialAnimator.AddMaterialFrame(rainbowNoise, 0.3f);
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
            eEA.AddParameterFrame(BasilGarden::vrc_v_ss, MicrophoneFourierIT::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourierIT::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourierIT::GetFourierFiltered(), MicrophoneFourierIT::GetSampleRate());
        
                eEA.AddParameterFrame(BasilGarden::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(BasilGarden::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(BasilGarden::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.UH));
                eEA.AddParameterFrame(BasilGarden::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
                eEA.AddParameterFrame(BasilGarden::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(BasilGarden::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(BasilGarden::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
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
    BasilGardenAnimation() {
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

        MicrophoneFourierIT::Initialize(A2, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
        //Menu::Initialize(9);//NeoTrellis
        Menu::Initialize(11, 20, 500);//12 is number of faces

        objA.SetJustification(ObjectAlign::Stretch);
        objA.SetMirrorX(true);
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

        //Menu::SetSize(Vector2D(280, 60));
        //Menu::SetPositionOffset(Vector2D(0.0f, -30.0f * yOffset));
        
        //glitchX.SetRatio(fGenBlur.Update());
        magnet.SetRatio(ratio);
        fisheye.SetRatio(fGenBlur.Update());
        blurH.SetRatio(fGenBlur.Update());
        blurV.SetRatio(fGenBlur.Update());
        blurR.SetRatio(fGenBlur.Update());
        phaseX.SetRatio(fGenBlur.Update());
        phaseY.SetRatio(fGenBlur.Update());
        phaseR.SetRatio(fGenBlur.Update());
        shiftR.SetRatio(fGenBlur.Update());

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

        if (isBooped && mode != 6){
            ForReal();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Sad();
            else if (mode == 2) Grimace();
            else if (mode == 3) Disappointed();
            else if (mode == 4) Angry();
            else if (mode == 5) Whoops();
            else if (mode == 6) Crabby();
            else if (mode == 7) Rage();
            else if (mode == 8) {
                aRG.Update(MicrophoneFourierIT::GetFourierFiltered());
                AudioReactiveGradientFace();
            }
            else if (mode == 9){
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
        
        //phaseR.SetRatio(eEA.GetValue(BasilGarden::Rage));
        glitchX.SetRatio(eEA.GetValue(BasilGarden::Rage));

        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();
        backgroundMaterial.Update();
        
        uint8_t faceSize = Menu::GetFaceSize();
        float scale = Menu::ShowMenu() * 0.6f + 0.4f;
        float faceSizeOffset = faceSize * 8.0f;

        objA.SetPlaneOffsetAngle(-7.5f);
        objA.SetEdgeMargin(2.0f);
        objA.SetCameraMax(Vector2D(110.0f + faceSizeOffset, 93.0f - 93.0f * offsetFace).Multiply(scale));

        objA.AlignObjects(scene.GetObjects(), 1);
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset, yOffset, 0.0f));
        pM.GetObject()->UpdateTransform();
    }
};
