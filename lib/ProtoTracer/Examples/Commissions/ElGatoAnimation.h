#pragma once

#include "../Animation.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Morph/NukudeFace.h"
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

class ElGatoAnimation : public Animation<2> {
private:
    NukudeFace pM;
    Background background;
    EasyEaseAnimator<25> eEA = EasyEaseAnimator<25>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);

    //Materials
    RainbowNoise rainbowNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial greenMaterial = SimpleMaterial(RGBColor(0, 255, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    SimpleMaterial pinkMaterial = SimpleMaterial(RGBColor(255, 0, 255));
    SimpleMaterial yellowMaterial = SimpleMaterial(RGBColor(255, 255, 0));

    //red angry
    //green happy
    //blue normal
    //blush rainbow
    //boop pink
    
    RGBColor gradientSpectrum[4] = {RGBColor(0, 0, 255), RGBColor(0, 255, 0), RGBColor(255, 0, 0), RGBColor(255, 255, 0)};
    GradientMaterial<4> gradientMat = GradientMaterial<4>(gradientSpectrum, 180.0f, false, true);
    
    CombineMaterial<8> faceMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(22, Vector2D(250, 200), Vector2D(120, 100), true, true);

    //Animation controllers
    BlinkTrack<1> blink;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.5f, 2.5f, 5.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.5f, 2.5f, 6.7f);

    BoopSensor boop;
    float rainbowFaceMix = 0.0f;
    float redFaceMix = 0.0f;
    float greenFaceMix = 0.0f;
    float blueFaceMix = 0.0f;
    float pinkFaceMix = 0.0f;
    float customFaceMix = 0.0f;
    uint8_t rainbowFaceIndex = 50;
    uint8_t redFaceIndex = 51;
    uint8_t greenFaceIndex = 52;
    uint8_t blueFaceIndex = 53;
    uint8_t pinkFaceIndex = 54;
    uint8_t customFaceIndex = 55;

    FFTVoiceDetection<128> voiceDetection;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Anger), NukudeFace::Anger, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Sadness), NukudeFace::Sadness, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Surprised), NukudeFace::Surprised, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Doubt), NukudeFace::Doubt, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Frown), NukudeFace::Frown, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookUp), NukudeFace::LookUp, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookDown), NukudeFace::LookDown, 60, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ee), NukudeFace::vrc_v_ee, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ih), NukudeFace::vrc_v_ih, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_dd), NukudeFace::vrc_v_dd, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_rr), NukudeFace::vrc_v_rr, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ch), NukudeFace::vrc_v_ch, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_aa), NukudeFace::vrc_v_aa, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_oh), NukudeFace::vrc_v_oh, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ss), NukudeFace::vrc_v_ss, 2, 0.0f, 1.0f);
        
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::HideBlush), NukudeFace::HideBlush, 30, 1.0f, 0.0f);
        
        eEA.AddParameter(&rainbowFaceMix, rainbowFaceIndex, 50, 0.0f, 1.0f);
        eEA.AddParameter(&redFaceMix, redFaceIndex, 40, 0.0f, 1.0f);
        eEA.AddParameter(&greenFaceMix, greenFaceIndex, 40, 0.0f, 1.0f);
        eEA.AddParameter(&blueFaceMix, blueFaceIndex, 40, 0.0f, 1.0f);
        eEA.AddParameter(&pinkFaceMix, pinkFaceIndex, 40, 0.0f, 1.0f);
        eEA.AddParameter(&customFaceMix, customFaceIndex, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(NukudeFace::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(NukudeFace::HideBlush, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(NukudeFace::Sadness, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(rainbowFaceIndex, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(redFaceIndex, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(greenFaceIndex, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(blueFaceIndex, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(pinkFaceIndex, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(customFaceIndex, EasyEaseInterpolation::Cosine);
        
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ee, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ih, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_dd, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_rr, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ch, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_aa, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_oh, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ss, EasyEaseInterpolation::Linear);
    }

    void SetMaterials(){
        faceMaterial.AddMaterial(Material::Add, &yellowMaterial, 1.0f);
        faceMaterial.AddMaterial(Material::Replace, &rainbowSpiral, 0.0f);
        faceMaterial.AddMaterial(Material::Replace, &redMaterial, 0.0f);
        faceMaterial.AddMaterial(Material::Replace, &greenMaterial, 0.0f);
        faceMaterial.AddMaterial(Material::Replace, &blueMaterial, 0.0f);
        faceMaterial.AddMaterial(Material::Replace, &pinkMaterial, 0.0f);
        faceMaterial.AddMaterial(Material::Replace, &gradientMat, 0.0f);
        faceMaterial.AddMaterial(Material::Add, &rainbowNoise, 0.1f);
    }

public:
    ElGatoAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(background.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterials();

        pM.GetObject()->SetMaterial(&faceMaterial);

        MenuButtonHandler::Initialize(0, 7, 1000);//7 is number of faces
        boop.Initialize(5);

        background.GetObject()->SetMaterial(&sA);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){
        eEA.AddParameterFrame(blueFaceIndex, 1.0f);
    }

    void Default2(){
        eEA.AddParameterFrame(customFaceIndex, 1.0f);
    }

    void Angry(){
        eEA.AddParameterFrame(NukudeFace::Anger, 1.0f);
        eEA.AddParameterFrame(redFaceIndex, 1.0f);
    }

    void Sad(){
        eEA.AddParameterFrame(NukudeFace::Sadness, 1.0f);
        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);
        eEA.AddParameterFrame(blueFaceIndex, 1.0f);
    }

    void Surprised(){
        eEA.AddParameterFrame(NukudeFace::Surprised, 1.0f);
        eEA.AddParameterFrame(NukudeFace::HideBlush, 0.0f);
        eEA.AddParameterFrame(rainbowFaceIndex, 1.0f);
    }
    
    void Doubt(){
        eEA.AddParameterFrame(NukudeFace::Doubt, 1.0f);
        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);
        eEA.AddParameterFrame(greenFaceIndex, 1.0f);
    }

    void LookUp(){
        eEA.AddParameterFrame(NukudeFace::LookUp, 1.0f);
        eEA.AddParameterFrame(NukudeFace::HideBlush, 0.0f);
        eEA.AddParameterFrame(pinkFaceIndex, 1.0f);
    }

    void LookDown(){
        eEA.AddParameterFrame(NukudeFace::LookDown, 1.0f);
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
            eEA.AddParameterFrame(NukudeFace::vrc_v_ss, MicrophoneFourier::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourier::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourier::GetFourierFiltered(), MicrophoneFourier::GetSampleRate());
        
                eEA.AddParameterFrame(NukudeFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(NukudeFace::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(NukudeFace::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.UH));
                eEA.AddParameterFrame(NukudeFace::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
                eEA.AddParameterFrame(NukudeFace::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(NukudeFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(NukudeFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
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
            LookUp();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Angry();
            else if (mode == 2) Doubt();
            else if (mode == 3) Default2();
            else if (mode == 4) Surprised();
            else if (mode == 5) Sad();
            else SpectrumAnalyzerFace();
        }

        UpdateKeyFrameTracks();

        pM.SetMorphWeight(NukudeFace::BiggerNose, 1.0f);
        pM.SetMorphWeight(NukudeFace::MoveEye, 1.0f);

        eEA.Update();
        pM.Update();
        
        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
    
        faceMaterial.SetOpacity(1, rainbowFaceMix);//set face to spiral
        faceMaterial.SetOpacity(2, redFaceMix);//set face to angry
        faceMaterial.SetOpacity(3, greenFaceMix);//set face to angry
        faceMaterial.SetOpacity(4, blueFaceMix);//set face to angry
        faceMaterial.SetOpacity(5, pinkFaceMix);//set face to angry
        faceMaterial.SetOpacity(6, customFaceMix);//set face to angry
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(130.0f + fGenMatXMove.Update(), -15.0f + fGenMatYMove.Update(), 600.0f));
        pM.GetObject()->GetTransform()->SetScale(Vector3D(-1.0f, 0.625f, 0.7f));

        pM.GetObject()->UpdateTransform();
    }
};
