#pragma once

#include "Animation.h"
#include "../Math/FunctionGenerator.h"
#include "../Objects/Rocks.h"

class RocksAnimation : public Animation{
private:
    Rocks rocks;
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 0.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 5.0f * 25.0f, 7.5f * 25.0f, 4.2f);

public:
    RocksAnimation() : Animation(1) {
        scene->AddObject(rocks.GetObject());
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        float x = fGenRotation.Update();
        float sx = fGenScale.Update();
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, ratio * 1440.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        rocks.GetObject()->ResetVertices();

        rocks.GetObject()->GetTransform()->SetRotation(rotation);
        rocks.GetObject()->GetTransform()->SetScale(Vector3D(sx, sx, sx));
        rocks.GetObject()->GetTransform()->SetPosition(Vector3D(0.0f, 125.0f, 600.0f));

        rocks.GetObject()->UpdateTransform();
    }
};
