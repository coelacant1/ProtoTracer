#pragma once

#include "Animation.h"
#include "../Objects/SolidCube.h"
#include "../Math/FunctionGenerator.h"
#include "../Morph/ProtoDRMorph.h"

#include "../Materials/VectorField2D.h"

class VectorFieldAnimation : public Animation{
private:
    ProtoDR pM;

    SolidCube cube;
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 1.5f);
    FunctionGenerator fGenMatSize = FunctionGenerator(FunctionGenerator::Sine, 400.0f, 550.0f, 2.1f);
    FunctionGenerator fGenMatRot = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 360.0f, 15.0f);
    FunctionGenerator fGenMatPeriod = FunctionGenerator(FunctionGenerator::Sine, 0.1f, 1.0f, 8.0f);
    FunctionGenerator fGenMatAmpl = FunctionGenerator(FunctionGenerator::Sine, 0.1f, 1.0f, 4.3f);

    RGBColor spectrum1[6] = {RGBColor(255, 255, 0), RGBColor(0, 0, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 0), RGBColor(255, 0, 255), RGBColor(0, 0, 0)};
    RGBColor spectrum2[6] = {RGBColor(255, 0, 0), RGBColor(0, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 0), RGBColor(0, 0, 255), RGBColor(0, 0, 0)};
    RGBColor spectrum3[7] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255), RGBColor(255, 0, 0)};
    GradientMaterial colorDirection = GradientMaterial(7, spectrum3, 1.0f, false);
    VectorField2D vectorField = VectorField2D(100, 70, &colorDirection);

public:
    VectorFieldAnimation() : Animation(1) {
        scene->AddObject(cube.GetObject());
        
        cube.GetObject()->SetMaterial(&vectorField);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        float shift = fGenMatPos.Update();
        //float size = fGenMatSize.Update();
        //float rotate = fGenMatRot.Update();
        float period = fGenMatPeriod.Update();
        float amplitude = fGenMatAmpl.Update();

        float x = sinf(ratio * 3.14159f / 180.0f * 360.0f * 4.0f) * 50.0f + sinf(ratio * 3.14159f / 180.0f * 360.0f * 3.0f) * 50.0f;
        float y = cosf(ratio * 3.14159f / 180.0f * 360.0f * 6.0f) * 10.0f;

        pM.SetMorphWeight(ProtoDR::HideBlush, 1.0f);
        pM.SetMorphWeight(ProtoDR::HideSecondEye, 1.0f);
        pM.Update();
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0, 180.0f, 0.0f));
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(x, y - 250.0f, 600.0f));
        pM.GetObject()->GetTransform()->SetScale(Vector3D(2.0f, 2.0f, 2.0f));

        pM.GetObject()->UpdateTransform();

        vectorField.RenderDensity();
        vectorField.SetSize(550, 450);
        vectorField.SetPosition(0, 125);
        //vectorField.SetRotation(ratio * 360.0f);

        //if (ratio < 0.02f) vectorField.SineField(ratio, period, amplitude);
        //if (ratio < 0.2f) vectorField.StepField(ratio, 40.0f, 5);
        vectorField.ObjectField(pM.GetObject(), 20.0f);
        //vectorField.MovingSquareField(ratio, 160.0f, 15);
        vectorField.Diffuse(0.05f, 0.0001f);
        vectorField.Advect(0.00001f);
        //vectorField.ObjectField(pM.GetObject());
        
        cube.GetObject()->ResetVertices();
        cube.GetObject()->GetTransform()->SetScale(Vector3D(1000, 1000, 1));
        cube.GetObject()->UpdateTransform();
    }
};
