#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Objects\SolidCube.h"
#include "..\Morph\ProtoArtleckMorph.h"
#include "..\Render\Scene.h"
#include "..\Materials\GradientMaterial.h"
#include "..\Materials\SimplexNoise.h"
#include "..\Math\FunctionGenerator.h"
//#include "..\Sensors\MicrophoneSimple_MAX9814.h"
//#include "..\Sensors\MicrophoneFourier_MAX9814.h"
#include "..\Sensors\ButtonHandler.h"
#include "..\Sensors\BoopSensor.h"
#include "..\Materials\NormalMaterial.h"

#include "..\Materials\CombineMaterial.h"
#include "..\Materials\SpectrumAnalyzer.h"


class ProtogenHUB75Animation : public Animation{
private:
    float colorMix;

    //Face
    ProtoArtleck pM;
    EasyEaseAnimator eEA = EasyEaseAnimator(20, EasyEaseAnimator::Overshoot, 1.0f, 0.5f);

    RGBColor noiseSpectrum[4] = {RGBColor(0, 255, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
    GradientMaterial gNoiseMat = GradientMaterial(4, noiseSpectrum, 2.0f, false);
    SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);
    
    RGBColor gradientSpectrum[2] = {RGBColor(255, 0, 0), RGBColor(0, 0, 255)};
    GradientMaterial gradientMat = GradientMaterial(2, gradientSpectrum, 350.0f, false);

    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    
    //default face material with gradient + simplex noise
    Material* noiseMaterials[2] = {&gradientMat, &sNoise};
    CombineMaterial noiseMaterial = CombineMaterial(CombineMaterial::Lighten, 2, noiseMaterials);

    //for combining angry face with default material
    Material* faceMaterials[2] = {&redMaterial, &noiseMaterial};
    CombineMaterial faceMaterial = CombineMaterial(CombineMaterial::Replace, 2, faceMaterials);

    //Spectrum Analyzer
    SolidCube cube;
    
    RGBColor spectrum3[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    
    GradientMaterial gM = GradientMaterial(6, spectrum3, 1.0f, false);
    SpectrumAnalyzer sA = SpectrumAnalyzer(A0, Vector2D(192, 96), Vector2D(96, 48), &gM);
    
    Material* spectrumMaterials[2] = {&sA, &sNoise};
    CombineMaterial spectrumMaterial = CombineMaterial(CombineMaterial::Lighten, 2, spectrumMaterials);

    //Animations
    KeyFrameTrack blink = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack mouth = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);

    BoopSensor boop;
    bool talk = true;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoArtleck::Anger), ProtoArtleck::Anger, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoArtleck::Sadness), ProtoArtleck::Sadness, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoArtleck::Surprised), ProtoArtleck::Surprised, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoArtleck::Doubt), ProtoArtleck::Doubt, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoArtleck::Frown), ProtoArtleck::Frown, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoArtleck::LookUp), ProtoArtleck::LookUp, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoArtleck::LookDown), ProtoArtleck::LookDown, 30, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(ProtoArtleck::vrc_v_ou), ProtoArtleck::vrc_v_ou, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoArtleck::vrc_v_aa), ProtoArtleck::vrc_v_aa, 30, 0.0f, 1.0f);
        
        eEA.AddParameter(&colorMix, 99, 90, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(ProtoArtleck::Blink));
        mouth.AddParameter(pM.GetMorphWeightReference(ProtoArtleck::vrc_v_aa));
    }

    void AddBlinkKeyFrames(){
        blink.AddKeyFrame(0.0f, 0.0f);
        blink.AddKeyFrame(2.75f, 0.0f);
        blink.AddKeyFrame(3.0f, 1.0f);
        blink.AddKeyFrame(3.25f, 0.0f);
        blink.AddKeyFrame(9.75f, 0.0f);
        blink.AddKeyFrame(10.0f, 1.0f);
        blink.AddKeyFrame(10.25f, 0.0f);
        blink.AddKeyFrame(10.75f, 0.0f);
        blink.AddKeyFrame(11.0f, 1.0f);
        blink.AddKeyFrame(11.25f, 0.0f);
        blink.AddKeyFrame(15.0f, 0.0f);
    }

    void AddMouthKeyFrames(){
        mouth.AddKeyFrame(0.0f, 0.0f);
        mouth.AddKeyFrame(1.5f, 1.0f);
        mouth.AddKeyFrame(4.0f, 0.0f);
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(ProtoArtleck::Sadness, EasyEaseAnimator::Cosine);
        eEA.SetInterpolationMethod(ProtoArtleck::vrc_v_ou, EasyEaseAnimator::Cosine);
        eEA.SetInterpolationMethod(99, EasyEaseAnimator::Cosine);
    }

public:
    ProtogenHUB75Animation() : Animation(2) {
        scene->AddObject(pM.GetObject());
        scene->AddObject(cube.GetObject());

        LinkEasyEase();
        LinkParameters();

        AddBlinkKeyFrames();
        AddMouthKeyFrames();
        ChangeInterpolationMethods();

        pM.GetObject()->SetMaterial(&faceMaterial);
        cube.GetObject()->SetMaterial(&spectrumMaterial);
        noiseMaterial.SetFirstLayerOpacity(0.4f);
        spectrumMaterial.SetFirstLayerOpacity(1.0f);

        ButtonHandler::Initialize(20, 6);//6 is number of faces

        boop.Initialize(5);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
        mouth.Update();
    }

    void Default(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        talk = true;
    }

    void Angry(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(ProtoArtleck::Anger, 1.0f);
        eEA.AddParameterFrame(99, 1.0f);

        talk = true;
    }

    void Sad(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(ProtoArtleck::Sadness, 1.0f);

        talk = true;
    }

    void Surprised(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(ProtoArtleck::Surprised, 1.0f);

        talk = true;
    }
    
    void Doubt(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(ProtoArtleck::Doubt, 1.0f);
        eEA.AddParameterFrame(ProtoArtleck::vrc_v_ou, 1.0f);

        talk = true;
    }
    
    void Frown(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(ProtoArtleck::Frown, 1.0f);
        eEA.AddParameterFrame(ProtoArtleck::vrc_v_ou, 1.0f);

        talk = true;
    }

    void LookUp(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(ProtoArtleck::LookUp, 1.0f);

        talk = true;
    }

    void LookDown(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(ProtoArtleck::LookDown, 1.0f);

        talk = true;
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    float offset = 0.0f;

    void Update(float ratio) override {
        bool isBooped = boop.isBooped();
        float mouthMove = 0.0f;//mic.Update();
        //uint8_t mode = (uint8_t)(ratio * 8.0f);//change sequentially
        uint8_t mode = ButtonHandler::GetValue();//change by button press

        sA.Update();

        if (isBooped){
            Angry();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Surprised();
            else if (mode == 2) Doubt();
            else if (mode == 3) Frown();
            else if (mode == 4) LookUp();
            else if (mode == 5) Angry();
            else Sad();
        }

        UpdateKeyFrameTracks();

        if(talk) eEA.AddParameterFrame(ProtoArtleck::vrc_v_aa, mouthMove);

        eEA.Update();
        pM.Update();
        
        float x = sinf(ratio * 3.14159f / 180.0f * 360.0f * 2.0f) * 2.25f;
        float y = cosf(ratio * 3.14159f / 180.0f * 360.0f * 3.0f) * 2.25f;
        
        float linSweep = ratio > 0.5f ? 1.0f - ratio : ratio;
        float sShift = linSweep * 0.002f + 0.005f;

        gNoiseMat.SetGradientPeriod(0.5f + linSweep * 6.0f);
        gNoiseMat.HueShift(ratio * 360 * 2);
        sNoise.SetScale(Vector3D(sShift, sShift, sShift));
        sNoise.SetZPosition(x * 4.0f);
        
        faceMaterial.SetFirstLayerOpacity(colorMix);
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 0.0f + 15.0f));
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(x + 90.0f, y + 115.0f, 600.0f));
        //pM.GetObject()->GetTransform()->SetScale(Vector3D(-0.65f, -0.65f, 0.5f));
        pM.GetObject()->GetTransform()->SetScale(Vector3D(-0.85f, -0.65f, 0.5f));

        pM.GetObject()->UpdateTransform();
        
        cube.GetObject()->ResetVertices();
        cube.GetObject()->GetTransform()->SetPosition(Vector3D(1000, 1000, 10000.0f));
        cube.GetObject()->GetTransform()->SetScale(Vector3D(1000, 1000, 1));
        cube.GetObject()->UpdateTransform();
    }
};
