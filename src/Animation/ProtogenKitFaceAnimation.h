#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Morph\NukudeFace.h"
#include "..\Render\Scene.h"
#include "..\Materials\GradientMaterial.h"
#include "..\Materials\SimplexNoise.h"
#include "..\Math\FunctionGenerator.h"
#include "..\Sensors\MicrophoneSimple.h"
#include "..\Sensors\ButtonHandler.h"
#include "..\Sensors\BoopSensor.h"
#include "..\Materials\NormalMaterial.h"

#include "Flash\ImageSequences\Rainbow.h"
#include "..\Materials\CombineMaterial.h"


class ProtogenKitFaceAnimation : public Animation{
private:
    float colorMix;

    NukudeFace pM;
    EasyEaseAnimator eEA = EasyEaseAnimator(20, EasyEaseAnimator::Cosine);

    RGBColor spectrum[4] = {RGBColor(0, 255, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
    GradientMaterial gNoiseMat = GradientMaterial(4, spectrum, 2.0f, false);
    SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);

    NormalMaterial normalMaterial;

    SimpleMaterial rgbColor = SimpleMaterial(RGBColor(255, 0, 0));
    
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    RainbowSequence gif = RainbowSequence(Vector2D(200, 145), Vector2D(100, 70), 60);
    
    Material* materials[2] = {&rgbColor, &sNoise};
    CombineMaterial material = CombineMaterial(CombineMaterial::Add, 2, materials);

    KeyFrameTrack blink = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack mouth = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);

    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);

    MicrophoneSimple mic = MicrophoneSimple(22);
    BoopSensor boop;
    bool talk = true;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Anger), NukudeFace::Anger, 20, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Sadness), NukudeFace::Sadness, 20, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Surprised), NukudeFace::Surprised, 20, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Doubt), NukudeFace::Doubt, 20, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Frown), NukudeFace::Frown, 20, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookUp), NukudeFace::LookUp, 20, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookDown), NukudeFace::LookDown, 20, 0.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ee), NukudeFace::vrc_v_ee, 20, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ff), NukudeFace::vrc_v_ff, 20, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_aa), NukudeFace::vrc_v_aa, 20, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_nn), NukudeFace::vrc_v_nn, 20, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_dd), NukudeFace::vrc_v_dd, 20, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ih), NukudeFace::vrc_v_ih, 20, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_pp), NukudeFace::vrc_v_pp, 20, 0.0f);
        
        eEA.AddParameter(&colorMix, 99, 20, 0.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(NukudeFace::Blink));
        mouth.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_aa));
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

public:
    ProtogenKitFaceAnimation() : Animation(1) {
        scene->AddObject(pM.GetObject());

        LinkEasyEase();
        LinkParameters();

        AddBlinkKeyFrames();
        AddMouthKeyFrames();

        pM.GetObject()->SetMaterial(&material);

        ButtonHandler::Initialize(0, 8);//8 is number of faces
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

        eEA.AddParameterFrame(99, 0.0f);

        talk = true;
    }

    void Angry(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Anger, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_ee, 1.0f);
        eEA.AddParameterFrame(99, 1.0f);

        talk = true;
    }

    void Sad(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Sadness, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_ff, 1.0f);

        talk = true;
    }

    void Surprised(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Surprised, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_aa, 1.0f);

        talk = true;
    }
    
    void Doubt(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Doubt, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_nn, 1.0f);

        talk = true;
    }
    
    void Frown(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_dd, 1.0f);

        talk = true;
    }

    void LookUp(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::LookUp, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_ih, 1.0f);

        talk = true;
    }

    void LookDown(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::LookDown, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_pp, 1.0f);

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
            else if (mode == 5) LookDown();
            else Sad();
        }

        UpdateKeyFrameTracks();

        if(talk) pM.SetMorphWeight(NukudeFace::vrc_v_th, mouthMove);
        eEA.Update();
        pM.Update();
        
        float x = sinf(ratio * 3.14159f / 180.0f * 360.0f * 2.0f) * 3.0f;
        float y = cosf(ratio * 3.14159f / 180.0f * 360.0f * 3.0f) * 3.0f;
        
        float linSweep = ratio > 0.5f ? 1.0f - ratio : ratio;
        float sShift = linSweep * 0.002f + 0.005f;

        gNoiseMat.SetGradientPeriod(0.5f + linSweep * 6.0f);
        gNoiseMat.HueShift(ratio * 360 * 2);
        sNoise.SetScale(Vector3D(sShift, sShift, sShift));
        sNoise.SetZPosition(x * 4.0f);
        
        material.SetFirstLayerOpacity(colorMix);

        Serial.print(isBooped);
        Serial.print('\t');
        Serial.print(ratio);
        Serial.print('\t');
        Serial.println(colorMix);

        float shift = fGenMatPos.Update();

        gif.SetPosition(Vector2D(20.0f + shift, 135.0f + shift));
        gif.SetSize(Vector2D(-440, 350));
        gif.SetRotation(15.0f);
        gif.Update();
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 0.0f));
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(170.0f + x, 10.0f + y, 600.0f));
        pM.GetObject()->GetTransform()->SetScale(Vector3D(-1.0f, 0.6f, 0.7f));

        pM.GetObject()->UpdateTransform();
    }
};
