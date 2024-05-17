#pragma once

#include "../Templates/Project.h"
#include "../../Utils/Signals/FunctionGenerator.h"
#include "../../Assets/Models/OBJ/Spyro.h"
#include "../../Scene/Materials/Static/NormalMaterial.h"
#include "../../Scene/Objects/ObjectDeformer.h"

#include "../../Camera/CameraManager/Implementations/HUB75DeltaCameras.h"
#include "../../Controller/HUB75Controller.h"

class SpyroAnimation : public Project{
private:
    HUB75DeltaCameraManager cameras;
    HUB75Controller controller = HUB75Controller(&cameras, 50, 50);

    Spyro spyro;
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 6.0f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 2.0f, 7.0f, 4.2f);
    FunctionGenerator fGenPersp = FunctionGenerator(FunctionGenerator::Sine, 20.0f, 250.0f, 4.0f);
    NormalMaterial nM;
    ObjectDeformer oD = ObjectDeformer(spyro.GetObject());

public:
    SpyroAnimation() : Project(&cameras, &controller, 1) {
        scene.AddObject(spyro.GetObject());

        //spyro.GetObject()->SetMaterial(&nM);
    }

    void Initialize() override {
        controller.Initialize();
    }

    void Update(float ratio) override {
        float x = fGenRotation.Update();
        float sx = fGenScale.Update();
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, ratio * 720.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        spyro.GetObject()->ResetVertices();

        spyro.GetObject()->GetTransform()->SetRotation(rotation);
        spyro.GetObject()->GetTransform()->SetScale(Vector3D(sx, sx, sx));
        spyro.GetObject()->GetTransform()->SetPosition(Vector3D(96.0f, 0.0f, 0.0f));

        spyro.GetObject()->UpdateTransform();

        //oD.SineWaveSurfaceDeform(Vector3D(), 15.0f, 1.0f, 0.25f, 0.1f, ObjectDeformer::Axis::XAxis);
        //oD.PerspectiveDeform(fGenPersp.Update(), Vector3D(0, 0, 0), ObjectDeformer::Axis::ZAxis);
    }
};
