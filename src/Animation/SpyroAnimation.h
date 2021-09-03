#pragma once

#include "Animation.h"
#include "..\Math\FunctionGenerator.h"
#include "..\Objects\Spyro.h"
#include "..\Materials\NormalMaterial.h"

class SpyroAnimation : public Animation{
private:
    Spyro spyro;
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    NormalMaterial nM;

public:
    SpyroAnimation() : Animation(1) {
        scene->AddObject(spyro.GetObject());

        //spyro.GetObject()->SetMaterial(&nM);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        float x = fGenRotation.Update();
        float sx = fGenScale.Update();
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, ratio * 2880.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        spyro.GetObject()->ResetVertices();

        spyro.GetObject()->GetTransform()->SetRotation(rotation);
        spyro.GetObject()->GetTransform()->SetScale(Vector3D(sx, sx, sx));
        //spyro.GetObject()->GetTransform()->SetScaleOffset(Vector3D(100.0f, 75.0f, 0.0f));
        spyro.GetObject()->GetTransform()->SetPosition(Vector3D(120.0f, 30.0f, 600.0f));

        spyro.GetObject()->UpdateTransform();
    }
};
