#pragma once

#include "Animation.h"
#include "..\Objects\SolidCube.h"
#include "..\Materials\DepthMaterial.h"
#include "..\Materials\LightMaterial.h"
#include "..\Math\FunctionGenerator.h"

#include "Flash\Images\CoelaCant.h"

class CoelaCubeAnimation : public Animation{
private:
    SolidCube cube;
    DepthMaterial dMat = DepthMaterial(DepthMaterial::Z, 100.0f, 600.0f);
    LightMaterial lMat = LightMaterial();
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -360.0f, 360.0f, 6.0f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 1.3f);
    FunctionGenerator fGenMatSize = FunctionGenerator(FunctionGenerator::Sine, 100.0f, 250.0f, 2.1f);
    FunctionGenerator fGenMatRot = FunctionGenerator(FunctionGenerator::Sine, -15.0f, 15.0f, 3.2f);
    FunctionGenerator fGenMatHue = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 360.0f, 2.0f);
    CoelaCant coela = CoelaCant(Vector2D(200, 145), Vector2D(100, 70));

public:
    CoelaCubeAnimation() : Animation(1) {
        scene->AddObject(cube.GetObject());
        
        cube.GetObject()->SetMaterial(&coela);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        float x = fGenRotation.Update();
        float sx = fGenScale.Update();
        float shift = fGenMatPos.Update();
        float size = fGenMatSize.Update();
        float rotate = fGenMatRot.Update();
        float hueAngle = fGenMatHue.Update();
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, ratio * 720.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        coela.SetPosition(Vector2D(shift + 130.0f, shift + 80.0f));
        coela.SetSize(Vector2D(size, size));
        coela.SetRotation(rotate);
        coela.SetHueAngle(hueAngle);

        cube.GetObject()->ResetVertices();

        cube.GetObject()->GetTransform()->SetRotation(rotation);
        cube.GetObject()->GetTransform()->SetScale(Vector3D(sx, sx, sx));
        cube.GetObject()->GetTransform()->SetScaleOffset(cube.GetObject()->GetCenterOffset());
        cube.GetObject()->GetTransform()->SetPosition(Vector3D(125.0f, 75.0f, 600.0f));

        cube.GetObject()->UpdateTransform();
    }
};
