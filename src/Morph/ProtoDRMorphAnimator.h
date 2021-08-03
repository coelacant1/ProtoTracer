#pragma once

#include "..\Animation\Animation.h"
#include "..\Animation\KeyFrameTrack.h"
#include "ProtoDRMorph.h"
#include "..\Render\Scene.h"
#include "..\Materials\GradientMaterial.h"
#include "..\Materials\SimplexNoise.h"

class ProtoDRMorphAnimator : public Animation{
private:
    Object3D* objects[1];
    ProtoDR pM;

    RGBColor spectrum[4] = {RGBColor(0, 255, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
    GradientMaterial gNoiseMat = GradientMaterial(4, spectrum, 2.0f, false);
    SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);

    KeyFrameTrack blink = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack topFinOuter = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    KeyFrameTrack topFinInner = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    KeyFrameTrack topFinGap = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    KeyFrameTrack midFin = KeyFrameTrack(3, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR1 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR2 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR3 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR4 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR5 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack mouth = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(ProtoDR::ClosedEye));

        topFinOuter.AddParameter(pM.GetMorphWeightReference(ProtoDR::TopFinOuterThin));
        topFinInner.AddParameter(pM.GetMorphWeightReference(ProtoDR::TopFinInnerThin));
        topFinGap.AddParameter(pM.GetMorphWeightReference(ProtoDR::TopFinInnerCloseGap));

        midFin.AddParameter(pM.GetMorphWeightReference(ProtoDR::MidFinBotThin));
        midFin.AddParameter(pM.GetMorphWeightReference(ProtoDR::MidFinMidBigger));
        midFin.AddParameter(pM.GetMorphWeightReference(ProtoDR::MidFinTopThin));

        botFinLR1.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR1Thin));
        botFinLR2.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR2Thin));
        botFinLR3.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR3Thin));
        botFinLR4.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR4Thin));
        botFinLR5.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR5Thin));

        mouth.AddParameter(pM.GetMorphWeightReference(ProtoDR::ShockedMouth));
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

    void AddTopFinKeyFrames(){
        topFinOuter.AddKeyFrame(0.0f, 0.0f);
        topFinOuter.AddKeyFrame(1.5f, 1.0f);
        topFinOuter.AddKeyFrame(3.0f, 0.0f);

        topFinInner.AddKeyFrame(0.0f, 0.0f);
        topFinInner.AddKeyFrame(0.5f, 0.0f);
        topFinInner.AddKeyFrame(1.5f, 1.0f);
        topFinInner.AddKeyFrame(2.5f, 0.0f);
        topFinInner.AddKeyFrame(3.0f, 0.0f);

        topFinGap.AddKeyFrame(0.0f, 0.0f);
        topFinGap.AddKeyFrame(1.0f, 0.0f);
        topFinGap.AddKeyFrame(1.5f, 1.0f);
        topFinGap.AddKeyFrame(2.0f, 0.0f);
        topFinGap.AddKeyFrame(3.0f, 0.0f);
    }

    void AddMidFinKeyFrames(){
        midFin.AddKeyFrame(0.0f, 0.0f);
        midFin.AddKeyFrame(2.5f, 1.0f);
        midFin.AddKeyFrame(5.0f, 0.0f);
    }

    void AddBotFinKeyFrames(){
        botFinLR1.AddKeyFrame(0.0f, 0.0f);
        botFinLR2.AddKeyFrame(0.0f, 0.0f);
        botFinLR3.AddKeyFrame(0.0f, 0.0f);
        botFinLR4.AddKeyFrame(0.0f, 0.0f);
        botFinLR5.AddKeyFrame(0.0f, 1.0f);

        botFinLR1.AddKeyFrame(0.25f, 1.0f);
        botFinLR2.AddKeyFrame(0.25f, 0.0f);
        botFinLR3.AddKeyFrame(0.25f, 0.0f);
        botFinLR4.AddKeyFrame(0.25f, 0.0f);
        botFinLR5.AddKeyFrame(0.25f, 0.0f);

        botFinLR1.AddKeyFrame(0.5f, 0.0f);
        botFinLR2.AddKeyFrame(0.5f, 1.0f);
        botFinLR3.AddKeyFrame(0.5f, 0.0f);
        botFinLR4.AddKeyFrame(0.5f, 0.0f);
        botFinLR5.AddKeyFrame(0.5f, 0.0f);

        botFinLR1.AddKeyFrame(0.75f, 0.0f);
        botFinLR2.AddKeyFrame(0.75f, 0.0f);
        botFinLR3.AddKeyFrame(0.75f, 1.0f);
        botFinLR4.AddKeyFrame(0.75f, 0.0f);
        botFinLR5.AddKeyFrame(0.75f, 0.0f);

        botFinLR1.AddKeyFrame(1.0f, 0.0f);
        botFinLR2.AddKeyFrame(1.0f, 0.0f);
        botFinLR3.AddKeyFrame(1.0f, 0.0f);
        botFinLR4.AddKeyFrame(1.0f, 1.0f);
        botFinLR5.AddKeyFrame(1.0f, 0.0f);
        
        botFinLR1.AddKeyFrame(1.25f, 0.0f);
        botFinLR2.AddKeyFrame(1.25f, 0.0f);
        botFinLR3.AddKeyFrame(1.25f, 0.0f);
        botFinLR4.AddKeyFrame(1.25f, 0.0f);
        botFinLR5.AddKeyFrame(1.25f, 1.0f);
    }

    void AddMouthKeyFrames(){
        mouth.AddKeyFrame(0.0f, 0.0f);
        mouth.AddKeyFrame(1.5f, 1.0f);
        mouth.AddKeyFrame(4.0f, 0.0f);
    }

public:
    ProtoDRMorphAnimator(){
        scene = new Scene(objects, 1);

        //LinkParameters();

        //AddBlinkKeyFrames();
        //AddTopFinKeyFrames();
        //AddMidFinKeyFrames();
        //AddBotFinKeyFrames();
        //AddMouthKeyFrames();

        objects[0] = pM.GetObject();
        objects[0]->SetMaterial(&sNoise);
    }

    ~ProtoDRMorphAnimator(){
        delete scene;
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
        topFinOuter.Update();
        topFinInner.Update();
        topFinGap.Update();
        midFin.Update();
        botFinLR1.Update();
        botFinLR2.Update();
        botFinLR3.Update();
        botFinLR4.Update();
        botFinLR5.Update();
        mouth.Update();
    }

    void Default(){
        pM.Reset();
        blink.Play();
        mouth.Play();

    }

    void OwO(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();

        pM.SetMorphWeight(ProtoDR::BlushEye, 1.0f);
        pM.SetMorphWeight(ProtoDR::HideBlush, 0.0f);
        pM.SetMorphWeight(ProtoDR::HideEyeBrow, 1.0f);
        pM.SetMorphWeight(ProtoDR::OwOMouth, 1.0f);
    }

    void Sad(){
        pM.Reset();
        blink.Play();
        mouth.Pause();
        mouth.Reset();

        pM.SetMorphWeight(ProtoDR::SadEye, 1.0f);
        pM.SetMorphWeight(ProtoDR::SadEyeBrow, 1.0f);
        pM.SetMorphWeight(ProtoDR::SadMouth, 1.0f);
    }

    void Dead(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();

        pM.SetMorphWeight(ProtoDR::FlatMouth, 1.0f);
        pM.SetMorphWeight(ProtoDR::DeadEye, 1.0f);
        pM.SetMorphWeight(ProtoDR::HideEyeBrow, 1.0f);
    }

    void Heart(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();

        pM.SetMorphWeight(ProtoDR::HeartEye, 1.0f);
        pM.SetMorphWeight(ProtoDR::HideEyeBrow, 1.0f);
        pM.SetMorphWeight(ProtoDR::OwOMouth, 1.0f);
    }

    void FadeIn(float stepRatio){
        
    }

    void FadeOut(float stepRatio){
        
    }

    Object3D* GetObject(){
        return pM.GetObject();
    }

    void Update(float ratio){
        UpdateKeyFrameTracks();

        if (ratio > 0.8f) OwO();
        else if (ratio > 0.6f) Sad();
        else if (ratio > 0.4f) Dead();
        else if (ratio > 0.2f) Heart();
        else Default();
        pM.Update();
        
        float x = sinf(ratio * 3.14159f / 180.0f * 360.0f * 4.0f) * 3.0f;
        float y = cosf(ratio * 3.14159f / 180.0f * 360.0f * 6.0f) * 3.0f;
        
        float linSweep = ratio > 0.5f ? 1.0f - ratio : ratio;
        float sShift = linSweep * 0.002f + 0.005f;

        gNoiseMat.SetGradientPeriod(0.5f + linSweep * 6.0f);
        gNoiseMat.HueShift(ratio * 360 * 2);
        sNoise.SetScale(Vector3D(sShift, sShift, sShift));
        sNoise.SetZPosition(x * 4.0f);
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0, 180.0f, 0.0f));
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(x, y, 600.0f));
        pM.GetObject()->GetTransform()->Scale(Vector3D(1.0f, 1.0f, 1.0f));

        pM.GetObject()->UpdateTransform();
    }

};
