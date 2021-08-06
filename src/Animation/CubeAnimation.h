#pragma once

#include "Animation.h"
#include "..\Objects\Cube.h"
#include "..\Materials\DepthMaterial.h"
#include "..\Materials\LightMaterial.h"

class CubeAnimation : public Animation{
private:
    Cube cube;
    DepthMaterial dMat = DepthMaterial(DepthMaterial::Z, 150.0f, 0.0f);
    LightMaterial lMat = LightMaterial();

public:
    CubeAnimation() : Animation(1) {
        scene->AddObject(cube.GetObject());
        cube.GetObject()->SetMaterial(&lMat);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        float x = sinf(ratio * 3.14159f / 180.0f * 360.0f * 12.0f) * 360.0f;
        //float y = cosf(ratio * 3.14159f / 180.0f * 360.0f * 12.0f) * 360.0f;

        float sx = sinf(ratio * 3.14159f / 180.0f * 360.0f * 8.0f) * 0.75f + 4.0f;
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x / 100.0f, ratio * 1440.0f * 6.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        cube.GetObject()->ResetVertices();

        cube.GetObject()->GetTransform()->SetRotation(rotation);
        cube.GetObject()->GetTransform()->SetScale(Vector3D(sx, sx, sx));
        cube.GetObject()->GetTransform()->SetPosition(Vector3D(0.0f, 0.0f, 600.0f));

        cube.GetObject()->UpdateTransform();
    }
};
