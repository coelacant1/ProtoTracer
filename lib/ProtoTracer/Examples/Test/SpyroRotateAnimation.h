#pragma once

#include "Animation.h"
#include "../Math/FunctionGenerator.h"
#include "../Objects/Spyro.h"
#include "../Sensors/SerialInterpreter.h"

class SpyroRotateAnimation : public Animation{
private:
    Spyro spyro;
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 2.0f, 10.0f, 4.2f);
    SimpleMaterial sM = SimpleMaterial(RGBColor(255, 255, 255));

public:
    SpyroRotateAnimation() : Animation(1) {
        scene->AddObject(spyro.GetObject());

        SerialInterpreter::Initialize();

        //spyro.GetObject()->SetMaterial(&sM);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        SerialInterpreter::Update();

        float sx = fGenScale.Update();
        
        Quaternion rotation = SerialInterpreter::GetOrientation();
        sM.SetRGB(RGBColor(SerialInterpreter::GetColor().R + 25, SerialInterpreter::GetColor().G + 25, SerialInterpreter::GetColor().B + 25));

        spyro.GetObject()->ResetVertices();

        spyro.GetObject()->GetTransform()->SetRotation(rotation);
        spyro.GetObject()->GetTransform()->SetScale(Vector3D(sx, sx, sx));
        spyro.GetObject()->GetTransform()->SetPosition(Vector3D(120.0f, 40.0f, 600.0f));

        spyro.GetObject()->UpdateTransform();
    }
};
