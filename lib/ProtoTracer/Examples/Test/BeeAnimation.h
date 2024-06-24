#pragma once

#include "Animation.h"
#include "../Objects/Cube.h"
#include "../Math/FunctionGenerator.h"
#include "../Objects/Bee.h"

class BeeAnimation : public Animation{
private:
    Bee bee;
    FunctionGenerator fGenRotationX = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenRotationY = FunctionGenerator(FunctionGenerator::Sine, -90.0f, 90.0f, 1.3f);

public:
    BeeAnimation() : Animation(1) {
        scene->AddObject(bee.GetObject());
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        float x = fGenRotationX.Update();
        float y = fGenRotationY.Update();
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, y, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        bee.GetObject()->ResetVertices();

        bee.GetObject()->GetTransform()->SetRotation(rotation);
        bee.GetObject()->GetTransform()->SetScale(Vector3D(1.2f, 1.2f, 1.2f));
        //bee.GetObject()->GetTransform()->SetScaleOffset(Vector3D(100.0f, 75.0f, 0.0f));
        bee.GetObject()->GetTransform()->SetPosition(Vector3D(000.0f, -40.0f, 600.0f));

        bee.GetObject()->UpdateTransform();
    }
};
