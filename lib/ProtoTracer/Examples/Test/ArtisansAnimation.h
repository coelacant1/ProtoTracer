#pragma once

#include "Animation.h"
#include "../Objects/Cube.h"
#include "../Math/FunctionGenerator.h"
#include "../Objects/Artisans.h"

class ArtisansAnimation : public Animation{
private:
    Artisans artisans;
    FunctionGenerator fGen = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 30.0f, 6.0f);
    FunctionGenerator fGenPos = FunctionGenerator(FunctionGenerator::Sine, 0.75f, 1.0f, 5.0f);

public:
    ArtisansAnimation() : Animation(1) {
        scene->AddObject(artisans.GetObject());
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        Quaternion rotation = Rotation(EulerAngles(Vector3D(0, fGen.Update() + 180.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        artisans.GetObject()->ResetVertices();

        float scale = fGenPos.Update();

        artisans.GetObject()->GetTransform()->SetRotation(rotation);
        artisans.GetObject()->GetTransform()->SetScale(Vector3D(scale, scale, scale));
        artisans.GetObject()->GetTransform()->SetScaleOffset(Vector3D(0.0f, 150.0f, 0.0f));
        artisans.GetObject()->GetTransform()->SetPosition(Vector3D(0.0f, (1.0f - scale) * 50.0f, 600.0f));

        artisans.GetObject()->UpdateTransform();
    }
};
