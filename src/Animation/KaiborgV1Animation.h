#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "..\Morph\KaiborgV1.h"
#include "..\Render\Scene.h"
#include "..\Materials\GradientMaterial.h"
#include "..\Materials\SimplexNoise.h"
//#include "..\Flash\ImageSequences\Wave2.h"
#include "..\Sensors\SerialInterpreter.h"
#include "..\Filter\QuaternionKalmanFilter.h"

class KaiborgV1Animation : public Animation{
private:
    KaiborgV1 kbFace;
    KeyFrameTrack kbPOGTrack = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Step);
    KeyFrameTrack kbAngryEyesTrack = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Linear);
    KeyFrameTrack kbMouthFrownTrack = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);

    RGBColor spectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    SimpleMaterial sMat = SimpleMaterial(RGBColor(0, 0, 0));
    GradientMaterial gMat = GradientMaterial(6, spectrum, 150.0f, true);
    GradientMaterial gNoiseMat = GradientMaterial(6, spectrum, 2.0f, false);
    SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);

    QuaternionKalmanFilter qKF = QuaternionKalmanFilter(0.05f, 20);

    //Wave2Sequence gif = Wave2Sequence(Vector2D(300, 200), Vector2D(100, 70), 15);

    void LinkParameters(){
        kbPOGTrack.AddParameter(kbFace.GetMorphWeightReference(KaiborgV1::POG));
        kbAngryEyesTrack.AddParameter(kbFace.GetMorphWeightReference(KaiborgV1::AngryEyes));
        kbMouthFrownTrack.AddParameter(kbFace.GetMorphWeightReference(KaiborgV1::MouthFrown));
    }

    void AddPOGKeyFrames(){
        kbPOGTrack.AddKeyFrame(0.0f, 0.0f);
        kbPOGTrack.AddKeyFrame(1.0f, 0.1f);
        kbPOGTrack.AddKeyFrame(2.0f, 0.0f);
    }

    void AddAngryEyeKeyFrames(){
        kbAngryEyesTrack.AddKeyFrame(0.0f, 0.0f);
        kbAngryEyesTrack.AddKeyFrame(0.5f, 0.25f);
        kbAngryEyesTrack.AddKeyFrame(1.0f, 0.0f);
        kbAngryEyesTrack.AddKeyFrame(1.5f, 0.25f);
        kbAngryEyesTrack.AddKeyFrame(2.0f, 0.0f);
    }

    void AddMouthFrownKeyFrames(){
        kbMouthFrownTrack.AddKeyFrame(0.0f, 1.0f);
        kbMouthFrownTrack.AddKeyFrame(0.2f, 0.0f);
        kbMouthFrownTrack.AddKeyFrame(0.4f, 1.0f);
        kbMouthFrownTrack.AddKeyFrame(0.6f, 0.0f);
        kbMouthFrownTrack.AddKeyFrame(0.8f, 1.0f);
        kbMouthFrownTrack.AddKeyFrame(1.0f, 0.0f);
        kbMouthFrownTrack.AddKeyFrame(2.0f, 0.0f);
    }

public:
    KaiborgV1Animation() : Animation(1){
        scene->AddObject(kbFace.GetObject());

        LinkParameters();
        AddPOGKeyFrames();
        AddAngryEyeKeyFrames();
        //AddMouthFrownKeyFrames();
        
        kbFace.GetObject()->SetMaterial(&sNoise);

        SerialInterpreter::Initialize();
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return kbFace.GetObject();
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

        //Example of Face with slight movement, scaling, and rotation
        kbPOGTrack.Update();
        kbAngryEyesTrack.Update();
        kbMouthFrownTrack.Update();
        //gif.Update();

        SerialInterpreter::Update();
        //Quaternion quatFiltered = qKF.Filter(SerialInterpreter::GetOrientation());
        Quaternion quatFiltered = SerialInterpreter::GetOrientation();

        Serial.println(quatFiltered.ToString());

        kbFace.Update();

        //Objects visibility can be enabled and disabled at any point before rasterizing to change its visibility
        kbFace.GetObject()->Enable();//

        //Objects can be moved to a coordinate or translated by a vector
        kbFace.GetObject()->GetTransform()->SetPosition(Vector3D(35.0f, 20.0f, 600.0f));

        //Objects can be rotated with by any rotation object (quaternion is preferred) and about any coordinate or center

        kbFace.GetObject()->GetTransform()->SetRotation(quatFiltered);
        //kbFace.GetObject()->GetTransform()->SetRotation(Vector3D(sinf(ratio * 3.14159f / 180.0f * 1440.0f) * 1.0f, sinf(ratio * 3.14159f / 180.0f * 720.0f) * 1.0f, 1));

        //Objects can be scaled by origin, center, and at a point
        float s = 1.0f + sin(ratio * 3.14159f / 180.0f * 2160.0f) * 0.03f;
        kbFace.GetObject()->GetTransform()->SetScale(Vector3D(s, s, s));

        kbFace.GetObject()->UpdateTransform();
    }
};
