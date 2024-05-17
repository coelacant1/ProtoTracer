#pragma once

#include "Animation.h"
#include "../Objects/Cube.h"
#include "../Materials/DepthMaterial.h"
#include "../Materials/LightMaterial.h"
#include "../Math/FunctionGenerator.h"

class CubeAnimation : public Animation{
private:
    Cube cube;
    DepthMaterial dMat = DepthMaterial(DepthMaterial::Z, 100.0f, 600.0f);
    LightMaterial lMat = LightMaterial();
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -360.0f, 360.0f, 6.0f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 0.25f, 0.75f, 4.0f);

public:
    CubeAnimation() : Animation(1) {
        scene->AddObject(cube.GetObject());
        
        cube.GetObject()->SetMaterial(&dMat);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        float x = fGenRotation.Update();
        float sx = fGenScale.Update();
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, ratio * 720.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        cube.GetObject()->ResetVertices();

        cube.GetObject()->GetTransform()->SetRotation(rotation);
        cube.GetObject()->GetTransform()->SetScale(Vector3D(sx, sx, sx));
        cube.GetObject()->GetTransform()->SetPosition(Vector3D(125.0f, 75.0f, 600.0f));

        cube.GetObject()->UpdateTransform();
    }
};
