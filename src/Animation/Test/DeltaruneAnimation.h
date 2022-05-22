#pragma once

#include "Animation.h"
#include "..\Objects\SolidCube.h"
#include "..\Materials\DepthMaterial.h"
#include "..\Materials\LightMaterial.h"
#include "..\Math\FunctionGenerator.h"

//#include "Flash\Images\CoelaToot.h"
#include "Flash\ImageSequences\Rainbow.h"

class DeltaruneAnimation : public Animation{
private:
    SolidCube cube;
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 1.5f);
    FunctionGenerator fGenMatSize = FunctionGenerator(FunctionGenerator::Sine, 250.0f, 350.0f, 2.1f);
    FunctionGenerator fGenMatRot = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 3.2f);
    RainbowSequence gif = RainbowSequence(Vector2D(1000, 1000), Vector2D(0, 0), 30);

public:
    DeltaruneAnimation() : Animation(1) {
        scene->AddObject(cube.GetObject());
        
        cube.GetObject()->SetMaterial(&gif);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Reset(){
        gif.Reset();
    }

    void Update(float ratio) override {
        float shift = fGenMatPos.Update();
        float size = fGenMatSize.Update();
        float rotate = fGenMatRot.Update();

        gif.SetPosition(Vector2D(150.0f + shift, 75.0f + shift));
        gif.SetSize(Vector2D(-size, size));
        gif.SetRotation(15.0f + rotate);
        gif.Update();

        cube.GetObject()->ResetVertices();
        cube.GetObject()->GetTransform()->SetScale(Vector3D(1000, 1000, 1));
        cube.GetObject()->UpdateTransform();
    }
};
