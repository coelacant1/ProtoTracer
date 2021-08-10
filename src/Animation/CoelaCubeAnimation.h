#pragma once

#include "Animation.h"
#include "..\Objects\SolidCube.h"
#include "..\Materials\DepthMaterial.h"
#include "..\Materials\LightMaterial.h"
#include "..\Math\FunctionGenerator.h"

#include "Flash\Images\ColorTest.h"

class CoelaCubeAnimation : public Animation{
private:
    SolidCube cube;
    DepthMaterial dMat = DepthMaterial(DepthMaterial::Z, 100.0f, 600.0f);
    LightMaterial lMat = LightMaterial();
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -360.0f, 360.0f, 6.0f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 2.0f);
    FunctionGenerator fGenMatSize = FunctionGenerator(FunctionGenerator::Sine, 100.0f, 200.0f, 2.0f);
    FunctionGenerator fGenMatRot = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 3.0f);
    ColorTest coela = ColorTest(Vector2D(150, 150), Vector2D(0, 0));

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
        float scale = fGenMatSize.Update();
        float rotate = fGenMatRot.Update();
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, ratio * 720.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        coela.SetPosition(Vector2D(shift + 60.0f, shift));
        coela.SetSize(Vector2D(scale, scale));
        coela.SetRotation(rotate);

        cube.GetObject()->ResetVertices();

        cube.GetObject()->GetTransform()->SetRotation(rotation);
        cube.GetObject()->GetTransform()->SetScale(Vector3D(sx, sx, sx));
        cube.GetObject()->GetTransform()->SetPosition(Vector3D(125.0f, 75.0f, 600.0f));

        cube.GetObject()->UpdateTransform();
    }
};
