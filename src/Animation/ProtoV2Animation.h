#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Morph\ProtoV2Morph.h"
#include "..\Render\Scene.h"
#include "..\Materials\GradientMaterial.h"
#include "..\Materials\SimplexNoise.h"
#include "..\Sensors\SerialInterpreter.h"
#include "..\Filter\QuaternionKalmanFilter.h"
#include "..\Math\FunctionGenerator.h"
#include "..\Sensors\ButtonHandler.h"
#include "..\Sensors\MicrophoneSimple.h"

class ProtoV2Animation : public Animation{
private:
    ProtoV2 face;
    
    EasyEaseAnimator eEA = EasyEaseAnimator(20, EasyEaseAnimator::Cosine);
    
    FunctionGenerator sineGenX = FunctionGenerator(FunctionGenerator::Sine, -3.0f, 3.0f, 3.7f);
    FunctionGenerator sineGenY = FunctionGenerator(FunctionGenerator::Sine, -3.0f, 3.0f, 2.9f);

    FunctionGenerator sineSidePanel = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 3.0f);

    KeyFrameTrack blink = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);

    RGBColor spectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    SimpleMaterial sMat = SimpleMaterial(RGBColor(0, 0, 0));
    GradientMaterial gMat = GradientMaterial(6, spectrum, 150.0f, true);
    GradientMaterial gNoiseMat = GradientMaterial(6, spectrum, 2.0f, false);
    SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);

    QuaternionKalmanFilter qKF = QuaternionKalmanFilter(0.05f, 20);
    MicrophoneSimple mic = MicrophoneSimple(22);
    
    void LinkEasyEase(){
        eEA.AddParameter(face.GetMorphWeightReference(ProtoV2::Squint), ProtoV2::Squint, 60, 0.0f);
        eEA.AddParameter(face.GetMorphWeightReference(ProtoV2::Surprised), ProtoV2::Surprised, 60, 0.0f);
        eEA.AddParameter(face.GetMorphWeightReference(ProtoV2::Happy), ProtoV2::Happy, 60, 0.0f);
        eEA.AddParameter(face.GetMorphWeightReference(ProtoV2::Sad), ProtoV2::Sad, 60, 0.0f);
        eEA.AddParameter(face.GetMorphWeightReference(ProtoV2::Whoop), ProtoV2::Whoop, 60, 0.0f);
        eEA.AddParameter(face.GetMorphWeightReference(ProtoV2::Hideblush), ProtoV2::Hideblush, 60, 0.0f);
        eEA.AddParameter(face.GetMorphWeightReference(ProtoV2::Angry), ProtoV2::Angry, 60, 0.0f);
        eEA.AddParameter(face.GetMorphWeightReference(ProtoV2::Blush), ProtoV2::Blush, 60, 0.0f);
    }
    
    void LinkParameters(){
        blink.AddParameter(face.GetMorphWeightReference(ProtoV2::Blink));
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

    void Default(){
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }

    void Squint(){
        eEA.AddParameterFrame(ProtoV2::Squint, 1.0f);
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }

    void Surprised(){
        eEA.AddParameterFrame(ProtoV2::Surprised, 1.0f);
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }

    void Happy(){
        eEA.AddParameterFrame(ProtoV2::Happy, 1.0f);
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }

    void Sad(){
        eEA.AddParameterFrame(ProtoV2::Sad, 1.0f);
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }

    void Whoop(){
        eEA.AddParameterFrame(ProtoV2::Whoop, 1.0f);
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }
    
    void Angry(){
        eEA.AddParameterFrame(ProtoV2::Angry, 1.0f);
        eEA.AddParameterFrame(ProtoV2::Hideblush, 1.0f);
    }

    void Blush(){
        eEA.AddParameterFrame(ProtoV2::Blush, 1.0f);
    }
    
public:
    ProtoV2Animation() : Animation(1){
        scene->AddObject(face.GetObject());
        
        face.GetObject()->SetMaterial(&sNoise);

        LinkEasyEase();
        LinkParameters();

        AddBlinkKeyFrames();

        SerialInterpreter::Initialize();
        ButtonHandler::Initialize(15, 7);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return face.GetObject();
    }

    void Update(float ratio) override {
        blink.Update();

        float x = sinf(ratio * 3.14159f / 180.0f * 360.0f) * 50.0f;
        float y = cosf(ratio * 3.14159f / 180.0f * 360.0f) * 50.0f;

        float linSweep = ratio > 0.5f ? 1.0f - ratio : ratio;
        float sShift = linSweep * 0.0075f + 0.01f;
        
        float micRatio = mic.Update();

        face.SetMorphWeight(ProtoV2::Talk, micRatio);
        face.SetMorphWeight(ProtoV2::Side1, sineSidePanel.Update());

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

        uint8_t mode = ButtonHandler::GetValue();

        if(mode == 0) Happy();
        else if(mode == 1) Surprised();
        else if(mode == 2) Squint();
        else if(mode == 3) Sad();
        else if(mode == 4) Whoop();
        else if(mode == 5) Angry();
        else if(mode == 6) Blush();
        else Default();

        eEA.Update();

        Serial.print(micRatio);
        Serial.print('\t');
        Serial.println(mode);

        face.Update();

        float offsetX = sineGenX.Update();
        float offsetY = sineGenY.Update();

        //Objects visibility can be enabled and disabled at any point before rasterizing to change its visibility
        face.GetObject()->Enable();//

        //Objects can be moved to a coordinate or translated by a vector
        face.GetObject()->GetTransform()->SetPosition(Vector3D(40.0f + offsetX, 20.0f + offsetY, 600.0f));

        //Objects can be rotated with by any rotation object (quaternion is preferred) and about any coordinate or center

        //kbFace.GetObject()->GetTransform()->SetRotation(quatFiltered);
        face.GetObject()->GetTransform()->SetRotation(Vector3D(sinf(ratio * 3.14159f / 180.0f * 1440.0f) * 1.0f, sinf(ratio * 3.14159f / 180.0f * 720.0f) * 1.0f, 1));

        face.GetObject()->UpdateTransform();
    }
};
