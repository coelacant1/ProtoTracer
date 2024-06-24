#pragma once

#include "Animation.h"
#include "../Objects/Cube.h"
#include "../Math/FunctionGenerator.h"
#include "../Objects/Pikachu.h"

class PikachuAnimation : public Animation{
private:
    Pikachu pikachu;
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 0.004f, 0.006f, 4.2f);

public:
    PikachuAnimation() : Animation(1) {
        scene->AddObject(pikachu.GetObject());
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        float x = fGenRotation.Update();
        float sx = fGenScale.Update();
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, ratio * 11520.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        pikachu.GetObject()->ResetVertices();

        pikachu.GetObject()->GetTransform()->SetRotation(rotation);
        pikachu.GetObject()->GetTransform()->SetScale(Vector3D(sx, sx, sx));
        //pikachu.GetObject()->GetTransform()->SetScaleOffset(Vector3D(100.0f, 75.0f, 0.0f));
        pikachu.GetObject()->GetTransform()->SetPosition(Vector3D(000.0f, 0.0f, 600.0f));

        pikachu.GetObject()->UpdateTransform();
    }
};
