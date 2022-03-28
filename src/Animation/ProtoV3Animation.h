#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "..\Morph\ProtoV3.h"
#include "..\Render\Scene.h"
#include "..\Materials\GradientMaterial.h"
#include "..\Materials\SimplexNoise.h"
#include "..\Sensors\SerialInterpreter.h"
#include "..\Filter\QuaternionKalmanFilter.h"
#include "..\Math\FunctionGenerator.h"

class ProtoV3Animation : public Animation{
private:
    ProtoV3 face;
    
    KeyFrameTrack sadTrack = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack confTrack = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack happyTrack = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);

    FunctionGenerator sineGenX = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 1.7f);
    FunctionGenerator sineGenY = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 1.9f);

    RGBColor spectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    SimpleMaterial sMat = SimpleMaterial(RGBColor(0, 0, 0));
    GradientMaterial gMat = GradientMaterial(6, spectrum, 150.0f, true);
    GradientMaterial gNoiseMat = GradientMaterial(6, spectrum, 2.0f, false);
    SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);

    QuaternionKalmanFilter qKF = QuaternionKalmanFilter(0.05f, 20);

    //Wave2Sequence gif = Wave2Sequence(Vector2D(300, 200), Vector2D(100, 70), 15);
    
    void LinkParameters(){
        sadTrack.AddParameter(face.GetMorphWeightReference(ProtoV3::SadEye));
        sadTrack.AddParameter(face.GetMorphWeightReference(ProtoV3::FlatMouth));
        confTrack.AddParameter(face.GetMorphWeightReference(ProtoV3::ConfuseMouth));
        confTrack.AddParameter(face.GetMorphWeightReference(ProtoV3::AngryEye));
        happyTrack.AddParameter(face.GetMorphWeightReference(ProtoV3::HappyEye));
        happyTrack.AddParameter(face.GetMorphWeightReference(ProtoV3::HappyMouth));
    }

    void AddSadKeyFrames(){
        sadTrack.AddKeyFrame(0.0f, 0.0f);
        sadTrack.AddKeyFrame(1.0f, 1.0f);
        sadTrack.AddKeyFrame(4.0f, 1.0f);
        sadTrack.AddKeyFrame(5.0f, 0.0f);
        sadTrack.AddKeyFrame(15.0f, 0.0f);
    }

    void AddConfKeyFrames(){
        confTrack.AddKeyFrame(0.0f, 0.0f);
        confTrack.AddKeyFrame(5.0f, 0.0f);
        confTrack.AddKeyFrame(6.0f, 1.0f);
        confTrack.AddKeyFrame(9.0f, 1.0f);
        confTrack.AddKeyFrame(10.0f, 0.0f);
        confTrack.AddKeyFrame(15.0f, 0.0f);
    }

    void AddHappyKeyFrames(){
        happyTrack.AddKeyFrame(0.0f, 0.0f);
        happyTrack.AddKeyFrame(10.0f, 0.0f);
        happyTrack.AddKeyFrame(11.0f, 1.0f);
        happyTrack.AddKeyFrame(14.0f, 1.0f);
        happyTrack.AddKeyFrame(15.0f, 0.0f);
    }

public:
    ProtoV3Animation() : Animation(1){
        scene->AddObject(face.GetObject());
        
        face.GetObject()->SetMaterial(&sNoise);

        LinkParameters();
        AddSadKeyFrames();
        AddConfKeyFrames();
        AddHappyKeyFrames();

        SerialInterpreter::Initialize();
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return face.GetObject();
    }

    void Update(float ratio) override {
        float x = sinf(ratio * 3.14159f / 180.0f * 360.0f) * 50.0f;
        float y = cosf(ratio * 3.14159f / 180.0f * 360.0f) * 50.0f;

        float linSweep = ratio > 0.5f ? 1.0f - ratio : ratio;
        float sShift = linSweep * 0.0075f + 0.01f;

        //Change material parameters
        sMat.HueShift(ratio * 360 * 4);
        gMat.SetGradientPeriod(150.0f + x * 150.0f);
        gMat.SetPositionOffset(Vector2D(x * 2.0f, 100.0f + y * 2.0f));
        gNoiseMat.HueShift(ratio * 360 * 2);
        sNoise.SetScale(Vector3D(sShift, sShift, sShift));
        sNoise.SetZPosition(x * 6.0f);

        SerialInterpreter::Update();
        //Quaternion quatFiltered = qKF.Filter(SerialInterpreter::GetOrientation());
        //Quaternion quatFiltered = SerialInterpreter::GetOrientation();
        sadTrack.Update();
        confTrack.Update();
        happyTrack.Update();

        face.Update();

        float offsetX = sineGenX.Update();
        float offsetY = sineGenY.Update();

        face.SetMorphWeight(face.EyeRidgeBigger, 1.0f);
        face.SetMorphWeight(face.EyeMove, 1.0f);

        //Objects visibility can be enabled and disabled at any point before rasterizing to change its visibility
        face.GetObject()->Enable();//

        //Objects can be moved to a coordinate or translated by a vector
        face.GetObject()->GetTransform()->SetPosition(Vector3D(40.0f + offsetX - 50.0f, 20.0f + offsetY + 80.0f, 600.0f));

        //Objects can be rotated with by any rotation object (quaternion is preferred) and about any coordinate or center

        //kbFace.GetObject()->GetTransform()->SetRotation(quatFiltered);
        face.GetObject()->GetTransform()->SetRotation(Vector3D(sinf(ratio * 3.14159f / 180.0f * 1440.0f) * 1.0f, sinf(ratio * 3.14159f / 180.0f * 720.0f) * 1.0f, 1));

        //Objects can be scaled by origin, center, and at a point
        float s = 1.0f + sin(ratio * 3.14159f / 180.0f * 1440.0f) * 0.03f;
        face.GetObject()->GetTransform()->SetScale(Vector3D(s, -s * 0.96f, s));

        face.GetObject()->UpdateTransform();
    }
};
