#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "../Morph/NukudeFace.h"
#include "../Render/Scene.h"
#include "../Materials/GradientMaterial.h"
#include "../Materials/SimplexNoise.h"
#include "../Math/FunctionGenerator.h"
#include "../Sensors/SerialSync.h"
#include "../Sensors/MicrophoneSimple.h"
#include "../Sensors/ButtonHandler.h"
#include "../Materials/NormalMaterial.h"

#include "Flash/ImageSequences/Rainbow.h"

class NukudeFaceAnimation : public Animation{
private:
    NukudeFace pM;
    EasyEaseAnimator eEA = EasyEaseAnimator(15, EasyEaseAnimator::Cosine);

    RGBColor spectrum[4] = {RGBColor(0, 255, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
    GradientMaterial gNoiseMat = GradientMaterial(4, spectrum, 2.0f, false);
    SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);

    NormalMaterial normalMaterial;
    
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    RainbowSequence gif = RainbowSequence(Vector2D(200, 145), Vector2D(100, 70), 60);

    KeyFrameTrack blink = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack mouth = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);

    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);

    MicrophoneSimple mic = MicrophoneSimple(22);
    bool talk = true;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Anger), NukudeFace::Anger, 40, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Sadness), NukudeFace::Sadness, 90, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Surprised), NukudeFace::Surprised, 30, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Doubt), NukudeFace::Doubt, 60, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Frown), NukudeFace::Frown, 90, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookUp), NukudeFace::LookUp, 60, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookDown), NukudeFace::LookDown, 60, 0.0f);
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
    NukudeFaceAnimation() : Animation(1) {
        scene->AddObject(pM.GetObject());

        LinkEasyEase();
        LinkParameters();

        AddBlinkKeyFrames();
        AddMouthKeyFrames();

        pM.GetObject()->SetMaterial(&gif);

        SerialSync::Initialize();
        ButtonHandler::Initialize(15, 11);
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

        eEA.AddParameterFrame(NukudeFace::Anger, 1.0f);

        talk = true;
    }

    void Sad(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Sadness, 1.0f);

        talk = true;
    }

    void Surprised(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Surprised, 1.0f);

        talk = true;
    }
    
    void Doubt(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Doubt, 1.0f);

        talk = true;
    }
    
    void Frown(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);

        talk = true;
    }

    void LookUp(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::LookUp, 1.0f);

        talk = true;
    }

    void LookDown(){
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::LookDown, 1.0f);

        talk = true;
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    float offset = 0.0f;


    void Update(float ratio) override {
        pM.GetObject()->Enable();//Due to Spyro track

        #ifndef RIGHTFACE
        SerialSync::Read();

        //update offset only 2% of the time
        if(SerialSync::GetRatio() < 0.02f){
            if(ratio > SerialSync::GetRatio()) offset = ratio - 1.0f - SerialSync::GetRatio();
            else offset = ratio - SerialSync::GetRatio();
        }

        //adjust current frame sync to new esp32
        ratio = fmod(ratio - offset, 1.0f);//override input to synchronize from esp

        uint8_t mode = SerialSync::GetMode();
        float mouthMove = SerialSync::GetMouthMove();
        #else
        float mouthMove = mic.Update();
        uint8_t mode = (uint8_t)(ratio * 8.0f);//ButtonHandler::GetValue();
        SerialSync::SetMouthMove(mouthMove);
        SerialSync::SetMode(mode);
        SerialSync::SetRatio(ratio);
        SerialSync::Send();
        #endif

        if (mode == 0) Angry();
        else if (mode == 1) Sad();
        else if (mode == 2) Surprised();
        else if (mode == 3) Doubt();
        else if (mode == 4) Frown();
        else if (mode == 5) LookUp();
        else if (mode == 6) LookDown();
        else Default();

        UpdateKeyFrameTracks();

        if(talk) pM.SetMorphWeight(NukudeFace::vrc_v_aa, mouthMove);
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

        float shift = fGenMatPos.Update();

        gif.SetPosition(Vector2D(20.0f + shift, 135.0f + shift));
        gif.SetSize(Vector2D(-440, 350));
        gif.SetRotation(15.0f);
        gif.Update();
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 0.0f));
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(x + 72.5f, y - 22.5f, 600.0f));
        pM.GetObject()->GetTransform()->Scale(Vector3D(1.0f, 1.0f, 1.0f));

        pM.GetObject()->UpdateTransform();
    }
};
