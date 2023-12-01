#pragma once

#include "..\Templates\Project.h"
#include "..\..\Utils\Signals\FunctionGenerator.h"
#include "..\..\Assets\Models\OBJ\Creeper.h"
#include "..\..\Scene\Materials\Static\NormalMaterial.h"
#include "..\..\Scene\Objects\ObjectDeformer.h"

#include "..\..\Camera\CameraManager\Implementations\HUB75DeltaCameras.h"
#include "..\..\Controller\HUB75Controller.h"

class CreeperAnimation : public Project{
private:
    Creeper creeper;
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 0.5f, 1.75f, 2.2f);
    FunctionGenerator fGenPos = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 300.0f, 3.1f);

public:
    CreeperAnimation() : Animation(1) {
        scene->AddObject(creeper.GetObject());
    }

    void Update(float ratio) override {
        float x = fGenRotation.Update();
        float sx = fGenScale.Update();
        float px = fGenPos.Update() / 4.0f;
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, ratio * 1440.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        creeper.GetObject()->ResetVertices();

        creeper.GetObject()->GetTransform()->SetRotation(rotation);
        creeper.GetObject()->GetTransform()->SetScale(Vector3D(sx * 0.25f, sx * -0.25f, sx * 0.25f));
        //spyro.GetObject()->GetTransform()->SetScaleOffset(Vector3D(100.0f, 75.0f, 0.0f));
        creeper.GetObject()->GetTransform()->SetPosition(Vector3D(0.0f + 96.0f, px - 0.0f, 600.0f));

        creeper.GetObject()->UpdateTransform();
    }
};
