#pragma once

#include "../Animation.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Morph/ProtoArtleckMorph.h"
#include "../../Render/Scene.h"
#include "../../Materials/GradientMaterial.h"
#include "../../Materials/SimplexNoise.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Sensors/MicrophoneSimple_MAX9814.h"
#include "../../Sensors/ButtonHandler.h"
#include "../../Sensors/BoopSensor.h"
#include "../../Materials/NormalMaterial.h"

#include "../../Materials/CombineMaterial.h"


class ProtogenArtleckAnimation : public Animation{
private:
    float colorMix;

    ProtoArtleck pM;
    EasyEaseAnimator<20> eEA = EasyEaseAnimator<20>(EasyEaseInterpolation::Overshoot, 1.0f, 0.5f);

    RGBColor noiseSpectrum[4] = {RGBColor(0, 255, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
    GradientMaterial gNoiseMat = GradientMaterial(4, noiseSpectrum, 2.0f, false);
    SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);
    
    RGBColor gradientSpectrum[2] = {RGBColor(255, 255, 0), RGBColor(255, 128, 0)};
    GradientMaterial gradientMat = GradientMaterial(2, gradientSpectrum, 350.0f, false);

    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    
    //default face material with gradient + simplex noise
    Material* noiseMaterials[2] = {&gradientMat, &sNoise};
    CombineMaterial noiseMaterial = CombineMaterial(CombineMaterial::Lighten, 2, noiseMaterials);

    //for combining angry face with default material
    Material* faceMaterials[2] = {&redMaterial, &noiseMaterial};
    CombineMaterial faceMaterial = CombineMaterial(CombineMaterial::Replace, 2, faceMaterials);


    KeyFrameTrack blink = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack mouth = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);

    MicrophoneSimple mic = MicrophoneSimple(14);
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
        eEA.SetInterpolationMethod(ProtoArtleck::Sadness, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(ProtoArtleck::vrc_v_ou, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(99, EasyEaseInterpolation::Cosine);
    }

public:
    ProtogenArtleckAnimation() : Animation(1) {
        scene->AddObject(pM.GetObject());

        LinkEasyEase();
        LinkParameters();

        AddBlinkKeyFrames();
        AddMouthKeyFrames();
        ChangeInterpolationMethods();

        pM.GetObject()->SetMaterial(&faceMaterial);
        noiseMaterial.SetFirstLayerOpacity(0.4f);

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
        float mouthMove = mic.Update();
        //uint8_t mode = (uint8_t)(ratio * 8.0f);//change sequentially
        uint8_t mode = ButtonHandler::GetValue();//change by button press

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

        Serial.println(colorMix);
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 0.0f + 15.0f));
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(x + 90.0f, y + 115.0f, 600.0f));
        //pM.GetObject()->GetTransform()->SetScale(Vector3D(-0.65f, -0.65f, 0.5f));
        pM.GetObject()->GetTransform()->SetScale(Vector3D(-0.85f, -0.65f, 0.5f));

        pM.GetObject()->UpdateTransform();
    }
};
