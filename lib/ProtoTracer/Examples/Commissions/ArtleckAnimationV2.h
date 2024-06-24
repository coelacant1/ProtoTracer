#pragma once

#include "../Animation.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Morph/ArtleckFace.h"
#include "../../Render/Scene.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Sensors/MenuButtonHandler.h"
#include "../../Sensors/BoopSensor.h"

#include "../../Materials/Animated/SpectrumAnalyzer.h"
#include "../../Materials/Animated/RainbowNoise.h"
#include "../../Materials/Animated/RainbowSpiral.h"

#include "../../Materials/CombineMaterial.h"

#include "../AnimationTracks/BlinkTrack.h"

#include "../../Signals/FFTVoiceDetection.h"

class ArtleckAnimationV2 : public Animation<2> {
private:
    ArtleckFace pM;
    Background background;
    EasyEaseAnimator<20> eEA = EasyEaseAnimator<20>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);

    //Materials
    RainbowNoise rainbowNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    SimpleMaterial purpleMaterial = SimpleMaterial(RGBColor(255, 0, 255));
    
    RGBColor gradientSpectrum[2] = {RGBColor(255, 255, 0), RGBColor(255, 128, 0)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);
    
    CombineMaterial<6> faceMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(A0, Vector2D(200, 100), Vector2D(100, 50), true, true); 

    //Animation controllers
    BlinkTrack<1> blink;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 5.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 6.7f);
    FunctionGenerator fGenMatHue = FunctionGenerator(FunctionGenerator::Triangle, 0.0f, 360.0f, 17.3f);

    BoopSensor boop;
    float rainbowFaceMix = 0.0f;
    float angryFaceMix = 0.0f;
    float sadFaceMix = 0.0f;
    float purpleFaceMix = 0.0f;
    uint8_t rainbowFaceIndex = 50;
    uint8_t angryFaceIndex = 51;
    uint8_t sadFaceIndex = 52;
    uint8_t purpleFaceIndex = 53;

    FFTVoiceDetection<128> voiceDetection;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::Anger), ArtleckFace::Anger, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::Sadness), ArtleckFace::Sadness, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::Surprised), ArtleckFace::Surprised, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::Doubt), ArtleckFace::Doubt, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::Frown), ArtleckFace::Frown, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::LookUp), ArtleckFace::LookUp, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::LookDown), ArtleckFace::LookDown, 60, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::vrc_v_ee), ArtleckFace::vrc_v_ee, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::vrc_v_ih), ArtleckFace::vrc_v_ih, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::vrc_v_dd), ArtleckFace::vrc_v_dd, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::vrc_v_rr), ArtleckFace::vrc_v_rr, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::vrc_v_ch), ArtleckFace::vrc_v_ch, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::vrc_v_aa), ArtleckFace::vrc_v_aa, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::vrc_v_oh), ArtleckFace::vrc_v_oh, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ArtleckFace::vrc_v_ss), ArtleckFace::vrc_v_ss, 2, 0.0f, 1.0f);
        
        eEA.AddParameter(&rainbowFaceMix, rainbowFaceIndex, 50, 0.0f, 1.0f);
        eEA.AddParameter(&angryFaceMix, angryFaceIndex, 40, 0.0f, 1.0f);
        eEA.AddParameter(&sadFaceMix, sadFaceIndex, 40, 0.0f, 1.0f);
        eEA.AddParameter(&purpleFaceMix, purpleFaceIndex, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(ArtleckFace::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(ArtleckFace::Sadness, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(rainbowFaceIndex, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(angryFaceIndex, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(sadFaceIndex, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(purpleFaceIndex, EasyEaseInterpolation::Cosine);
        
        eEA.SetInterpolationMethod(ArtleckFace::vrc_v_ee, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(ArtleckFace::vrc_v_ih, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(ArtleckFace::vrc_v_dd, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(ArtleckFace::vrc_v_rr, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(ArtleckFace::vrc_v_ch, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(ArtleckFace::vrc_v_aa, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(ArtleckFace::vrc_v_oh, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(ArtleckFace::vrc_v_ss, EasyEaseInterpolation::Linear);
    }

    void SetMaterials(){
        faceMaterial.AddMaterial(Material::Add, &gradientMat, 1.0f);
        faceMaterial.AddMaterial(Material::Lighten, &rainbowNoise, 0.5f);
        faceMaterial.AddMaterial(Material::Replace, &rainbowSpiral, 0.0f);
        faceMaterial.AddMaterial(Material::Replace, &redMaterial, 0.0f);
        faceMaterial.AddMaterial(Material::Replace, &blueMaterial, 0.0f);
        faceMaterial.AddMaterial(Material::Replace, &purpleMaterial, 0.0f);
    }

public:
    ArtleckAnimationV2() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(background.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterials();

        pM.GetObject()->SetMaterial(&faceMaterial);

        MenuButtonHandler::Initialize(20, 7, 500);//7 is number of faces
        boop.Initialize(5);

        background.GetObject()->SetMaterial(&sA);//sA);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){}

    void Angry(){
        eEA.AddParameterFrame(ArtleckFace::Anger, 1.0f);
        eEA.AddParameterFrame(angryFaceIndex, 0.8f);
    }

    void Sad(){
        eEA.AddParameterFrame(ArtleckFace::Sadness, 1.0f);
        eEA.AddParameterFrame(ArtleckFace::Frown, 1.0f);
        eEA.AddParameterFrame(sadFaceIndex, 0.8f);
    }

    void Surprised(){
        eEA.AddParameterFrame(ArtleckFace::Surprised, 1.0f);
        eEA.AddParameterFrame(purpleFaceIndex, 0.8f);
    }
    
    void Doubt(){
        eEA.AddParameterFrame(ArtleckFace::Doubt, 1.0f);
    }
    
    void Frown(){
        eEA.AddParameterFrame(ArtleckFace::Frown, 1.0f);
    }

    void LookUp(){
        eEA.AddParameterFrame(ArtleckFace::LookUp, 1.0f);
    }

    void LookDown(){
        eEA.AddParameterFrame(ArtleckFace::LookDown, 1.0f);
    }

    void SpectrumAnalyzerFace(){
        pM.GetObject()->Disable();
        background.GetObject()->Enable();
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    void UpdateFFTVisemes(){
        if(MenuButtonHandler::UseMicrophone()){
            eEA.AddParameterFrame(ArtleckFace::vrc_v_ss, MicrophoneFourier::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourier::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourier::GetFourierFiltered(), MicrophoneFourier::GetSampleRate());
        
                eEA.AddParameterFrame(ArtleckFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(ArtleckFace::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(ArtleckFace::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.UH));
                eEA.AddParameterFrame(ArtleckFace::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
                eEA.AddParameterFrame(ArtleckFace::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(ArtleckFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(ArtleckFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
            }
        }
    }

    void Update(float ratio) override {
        pM.Reset();
        pM.GetObject()->Enable();
        background.GetObject()->Disable();

        bool isBooped = MenuButtonHandler::UseBoopSensor() ? boop.isBooped() : 0;
        uint8_t mode = MenuButtonHandler::GetFaceState();//change by button press

        MicrophoneFourier::Update();
        sA.Update(MicrophoneFourier::GetFourierFiltered());
        sA.SetHueAngle(ratio * 360.0f * 4.0f);
        sA.SetMirrorYState(MenuButtonHandler::MirrorSpectrumAnalyzer());
        sA.SetFlipYState(!MenuButtonHandler::MirrorSpectrumAnalyzer());
        
        UpdateFFTVisemes();

        if (isBooped && mode != 6){
            Angry();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Surprised();
            else if (mode == 2) Doubt();
            else if (mode == 3) Frown();
            else if (mode == 4) LookUp();
            else if (mode == 5) Sad();
            else SpectrumAnalyzerFace();
        }

        UpdateKeyFrameTracks();

        eEA.Update();
        pM.Update();
        
        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
    
        faceMaterial.SetOpacity(2, rainbowFaceMix);//set face to spiral
        faceMaterial.SetOpacity(3, angryFaceMix);//set face to angry
        faceMaterial.SetOpacity(4, sadFaceMix);//set face to sad
        faceMaterial.SetOpacity(5, purpleFaceMix);//set face to purple
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, -15.0f));
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(82.5f + fGenMatXMove.Update(), -25.0f + fGenMatYMove.Update(), 600.0f));
        pM.GetObject()->GetTransform()->SetScale(Vector3D(-0.85f, 0.70f, 0.8f));

        pM.GetObject()->UpdateTransform();
    }
};
