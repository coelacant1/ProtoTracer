#pragma once

#include "Animation.h"
#include "../Objects/SolidCube.h"
#include "../Materials/DepthMaterial.h"
#include "../Materials/LightMaterial.h"
#include "../Math/FunctionGenerator.h"

//#include "Flash/Images/CoelaToot.h"
#include "Flash/ImageSequences/Bonk.h"

class CoelaBonkAnimation : public Animation{
private:
    SolidCube cube;
    FunctionGenerator fGenObjRotation = FunctionGenerator(FunctionGenerator::Sine, -360.0f, 360.0f, 6.0f);
    FunctionGenerator fGenObjScale = FunctionGenerator(FunctionGenerator::Sine, 10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 3.0f);
    FunctionGenerator fGenMatSize = FunctionGenerator(FunctionGenerator::Sine, 150.0f, 175.0f, 2.1f);
    FunctionGenerator fGenMatRot = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 3.2f);
    BonkSequence gif = BonkSequence(Vector2D(200, 145), Vector2D(100, 70), 30);

public:
    CoelaBonkAnimation() : Animation(1) {
        scene->AddObject(cube.GetObject());
        
        cube.GetObject()->SetMaterial(&gif);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Reset(){
        gif.Reset();
    }

    void Update(float ratio) override {
        float x = fGenObjRotation.Update();
        float sx = fGenObjScale.Update();
        float shift = fGenMatPos.Update();
        float size = fGenMatSize.Update();
        float rotate = fGenMatRot.Update();
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, ratio * 720.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        gif.SetPosition(Vector2D(140.0f + shift, 90.0f + shift));
        gif.SetSize(Vector2D(-size, size));
        gif.SetRotation(rotate);
        gif.Update();

        cube.GetObject()->ResetVertices();

        cube.GetObject()->GetTransform()->SetRotation(rotation);
        cube.GetObject()->GetTransform()->SetScale(Vector3D(sx, sx, sx));
        cube.GetObject()->GetTransform()->SetScaleOffset(cube.GetObject()->GetCenterOffset());
        cube.GetObject()->GetTransform()->SetPosition(Vector3D(125.0f, 75.0f, 600.0f));

        cube.GetObject()->UpdateTransform();
    }
};
