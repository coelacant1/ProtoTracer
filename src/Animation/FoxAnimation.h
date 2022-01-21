#pragma once

#include "Animation.h"
#include "..\Math\FunctionGenerator.h"
#include "..\Objects\Fox.h"
#include "..\Materials\NormalMaterial.h"
#include "KeyFrameTrack.h"

class FoxAnimation : public Animation{
private:
    Fox fox;
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenHop = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 10.0f, 0.25f);
    FunctionGenerator fGenHopCh = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 3.0f);
    NormalMaterial nM;
    
    KeyFrameTrack xAxis = KeyFrameTrack(1, -500.0f, 500.0f, 20, KeyFrameTrack::Cosine);
    KeyFrameTrack yAxis = KeyFrameTrack(1, -500.0f, 500.0f, 20, KeyFrameTrack::Cosine);
    KeyFrameTrack scale = KeyFrameTrack(1, 0.0f, 2.0f, 20, KeyFrameTrack::Cosine);
    
    KeyFrameTrack xRot = KeyFrameTrack(1, 0.0f, 360.0f, 20, KeyFrameTrack::Cosine);
    KeyFrameTrack yRot = KeyFrameTrack(1, 0.0f, 360.0f, 20, KeyFrameTrack::Cosine);
    KeyFrameTrack zRot = KeyFrameTrack(1, 0.0f, 360.0f, 20, KeyFrameTrack::Cosine);

    void AddXAxisKeyFrames(){
        xAxis.AddKeyFrame(0.0f, -400.0f);
        xAxis.AddKeyFrame(0.9f, 500.0f);
        xAxis.AddKeyFrame(1.0f, 400.0f);
        xAxis.AddKeyFrame(2.0f, 150.0f);
        xAxis.AddKeyFrame(9.0f, 50.0f);
        xAxis.AddKeyFrame(9.5f, -400.0f);
        xAxis.AddKeyFrame(10.0f, -400.0f);
    }

    void AddYAxisKeyFrames(){
        yAxis.AddKeyFrame(0.0f, 0.0f);
        yAxis.AddKeyFrame(1.0f, 0.0f);
        yAxis.AddKeyFrame(2.0f, -150.0f);
        yAxis.AddKeyFrame(2.4f, 0.0f);
        yAxis.AddKeyFrame(2.8f, -150.0f);
        yAxis.AddKeyFrame(4.0f, -160.0f);
        yAxis.AddKeyFrame(4.4f, 0.0f);
        yAxis.AddKeyFrame(4.8f, -160.0f);
        yAxis.AddKeyFrame(6.0f, -170.0f);
        yAxis.AddKeyFrame(6.4f, 0.0f);
        yAxis.AddKeyFrame(6.8f, -170.0f);
        yAxis.AddKeyFrame(9.0f, -100.0f);
        yAxis.AddKeyFrame(10.0f, -500.0f);
    }

    void AddScaleKeyFrames(){
        scale.AddKeyFrame(0.0f, 0.1f);
        scale.AddKeyFrame(0.75f, 0.25f);
        scale.AddKeyFrame(0.8f, 0.1f);
        scale.AddKeyFrame(2.0f, 0.3f);
        scale.AddKeyFrame(9.0f, 0.75f);
        scale.AddKeyFrame(10.0f, 0.65f);
    }

    void AddXRotKeyFrames(){
        xRot.AddKeyFrame(0.0f, 0.0f);
        xRot.AddKeyFrame(1.0f, 10.0f);
        xRot.AddKeyFrame(2.0f, -10.0f);
        xRot.AddKeyFrame(3.0f, 0.0f);
        xRot.AddKeyFrame(10.0f, 0.0f);
    }

    void AddYRotKeyFrames(){
        yRot.AddKeyFrame(0.0f, 270.0f);
        yRot.AddKeyFrame(0.75f, 270.0f);
        yRot.AddKeyFrame(1.0f, 45.0f);
        yRot.AddKeyFrame(2.0f, 25.0f);
        yRot.AddKeyFrame(9.0f, 10.0f);
        yRot.AddKeyFrame(10.0f, 170.0f);
    }

    void AddZRotKeyFrames(){
        zRot.AddKeyFrame(0.0f, 0.0f);
        zRot.AddKeyFrame(1.0f, 0.0f);
    }

public:
    FoxAnimation() : Animation(1) {
        scene->AddObject(fox.GetObject());

        AddXAxisKeyFrames();
        AddYAxisKeyFrames();
        AddScaleKeyFrames();
        AddXRotKeyFrames();
        AddYRotKeyFrames();
        AddZRotKeyFrames();
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        float rOffset = fGenRotation.Update();
        float hop = fGenHop.Update();
        float hopCh = fGenHopCh.Update();
        
        xAxis.Update();
        yAxis.Update();
        scale.Update();
        xRot.Update();
        yRot.Update();
        zRot.Update();

        Serial.println(rOffset);
        
        float xA = xAxis.GetParameterValue();
        float yA = yAxis.GetParameterValue();
        float sA = scale.GetParameterValue() * 500.0f;

        float xR = xRot.GetParameterValue();
        float yR = yRot.GetParameterValue();
        float zR = zRot.GetParameterValue();
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(xR, yR, zR + rOffset * 0.1f), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        fox.GetObject()->ResetVertices();

        fox.GetObject()->GetTransform()->SetRotation(rotation);
        fox.GetObject()->GetTransform()->SetScale(Vector3D(sA, sA, sA));
        fox.GetObject()->GetTransform()->SetPosition(Vector3D(xA, yA + hop * hopCh, 0.0f));

        fox.GetObject()->UpdateTransform();
    }
};
