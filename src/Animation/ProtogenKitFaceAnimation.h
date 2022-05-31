#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Objects\Background.h"
#include "..\Morph\NukudeFace.h"
#include "..\Render\Scene.h"
#include "..\Signals\FunctionGenerator.h"
#include "..\Sensors\ButtonHandler.h"
#include "..\Sensors\BoopSensor.h"

#include "..\Materials\Animated\SpectrumAnalyzer.h"
#include "..\Materials\Animated\RainbowNoise.h"
#include "..\Materials\Animated\RainbowSpiral.h"

#include "..\Materials\CombineMaterial.h"

#include "AnimationTracks\BlinkTrack.h"
#include "AnimationTracks\MouthTrack.h"

class ProtogenKitFaceAnimation : public Animation<2> {
private:
    NukudeFace pM;
    Background background;
    EasyEaseAnimator<20> eEA = EasyEaseAnimator<20>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);

    //Materials
    RainbowNoise rainbowNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    
    RGBColor gradientSpectrum[2] = {RGBColor(221, 15, 125), RGBColor(214, 35, 168)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);
    
    CombineMaterial<4> faceMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(22, Vector2D(250, 200), Vector2D(160, 125), true, true);

    //Animation controllers
    BlinkTrack<1> blink;
    MouthTrack<1> mouth;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -3.5f, 3.5f, 5.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -3.5f, 3.5f, 6.7f);

    BoopSensor boop;
    float rainbowFaceMix = 0.0f;
    float angryFaceMix = 0.0f;
    uint8_t rainbowFaceIndex = 50;
    uint8_t angryFaceIndex = 51;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Anger), NukudeFace::Anger, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Sadness), NukudeFace::Sadness, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Surprised), NukudeFace::Surprised, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Doubt), NukudeFace::Doubt, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Frown), NukudeFace::Frown, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookUp), NukudeFace::LookUp, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookDown), NukudeFace::LookDown, 60, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ou), NukudeFace::vrc_v_ou, 5, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ee), NukudeFace::vrc_v_ee, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ff), NukudeFace::vrc_v_ff, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_aa), NukudeFace::vrc_v_aa, 5, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_nn), NukudeFace::vrc_v_nn, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_dd), NukudeFace::vrc_v_dd, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ih), NukudeFace::vrc_v_ih, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_pp), NukudeFace::vrc_v_pp, 30, 0.0f, 1.0f);
        
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::HideBlush), NukudeFace::HideBlush, 40, 1.0f, 0.0f);
        
        eEA.AddParameter(&rainbowFaceMix, rainbowFaceIndex, 80, 0.0f, 1.0f);
        eEA.AddParameter(&angryFaceMix, angryFaceIndex, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(NukudeFace::Blink));
        mouth.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_kk));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(NukudeFace::HideBlush, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(NukudeFace::Sadness, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ou, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(rainbowFaceIndex, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(angryFaceIndex, EasyEaseInterpolation::Cosine);

        eEA.SetConstants(NukudeFace::vrc_v_aa, 1.0f, 0.5f);
        eEA.SetConstants(NukudeFace::vrc_v_ou, 0.9f, 0.45f);
    }

    void SetMaterials(){
        faceMaterial.AddMaterial(Material::Add, &gradientMat, 1.0f);
        faceMaterial.AddMaterial(Material::Lighten, &rainbowNoise, 0.6f);
        faceMaterial.AddMaterial(Material::Replace, &rainbowSpiral, 0.0f);
        faceMaterial.AddMaterial(Material::Replace, &redMaterial, 0.0f);
    }

public:
    ProtogenKitFaceAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(background.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterials();

        pM.GetObject()->SetMaterial(&faceMaterial);

        ButtonHandler::Initialize(0, 6);//8 is number of faces
        boop.Initialize(5);

        background.GetObject()->SetMaterial(&sA);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
        mouth.Update();
    }

    void Default(){}

    void Angry(){
        eEA.AddParameterFrame(NukudeFace::Anger, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_ee, 1.0f);
        eEA.AddParameterFrame(angryFaceIndex, 0.8f);
    }

    void Sad(){
        eEA.AddParameterFrame(NukudeFace::Sadness, 1.0f);
        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);
    }

    void Surprised(){
        eEA.AddParameterFrame(NukudeFace::Surprised, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_aa, 1.0f);
        eEA.AddParameterFrame(NukudeFace::HideBlush, 0.0f);
        eEA.AddParameterFrame(rainbowFaceIndex, 0.6f);
    }
    
    void Doubt(){
        eEA.AddParameterFrame(NukudeFace::Doubt, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_nn, 1.0f);
    }
    
    void Frown(){
        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_dd, 1.0f);
    }

    void LookUp(){
        eEA.AddParameterFrame(NukudeFace::LookUp, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_ih, 1.0f);
    }

    void LookDown(){
        eEA.AddParameterFrame(NukudeFace::LookDown, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_pp, 1.0f);
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

    void Update(float ratio) override {
        pM.Reset();
        pM.GetObject()->Enable();
        background.GetObject()->Disable();

        bool isBooped = boop.isBooped();
        uint8_t mode = ButtonHandler::GetValue();//change by button press

        sA.Update();
        sA.SetHueAngle(ratio * 360.0f * 4.0f);

        float mouthMove = sA.GetCurrentValue();

        if (isBooped){
            Surprised();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Angry();
            else if (mode == 2) Doubt();
            else if (mode == 3) Frown();
            else if (mode == 4) LookUp();
            else if (mode == 5) Sad();
            else SpectrumAnalyzerFace();
        }

        UpdateKeyFrameTracks();

        pM.SetMorphWeight(NukudeFace::BiggerNose, 1.0f);
        pM.SetMorphWeight(NukudeFace::MoveEye, 1.0f);

        eEA.AddParameterFrame(NukudeFace::vrc_v_aa, mouthMove);
        eEA.AddParameterFrame(NukudeFace::vrc_v_ou, mouthMove);

        eEA.Update();
        pM.Update();
        
        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
    
        faceMaterial.SetOpacity(2, rainbowFaceMix);//set face to spiral
        faceMaterial.SetOpacity(3, angryFaceMix);//set face to angry
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(170.0f + fGenMatXMove.Update(), 10.0f + fGenMatYMove.Update(), 600.0f));
        pM.GetObject()->GetTransform()->SetScale(Vector3D(-1.0f, 0.625f, 0.7f));

        pM.GetObject()->UpdateTransform();
    }
};
