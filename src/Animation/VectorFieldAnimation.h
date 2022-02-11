#pragma once

#include "Animation.h"
#include "..\Objects\SolidCube.h"
#include "..\Math\FunctionGenerator.h"

#include "..\Materials\VectorField2D.h"

class VectorFieldAnimation : public Animation{
private:
    SolidCube cube;
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 1.5f);
    FunctionGenerator fGenMatSize = FunctionGenerator(FunctionGenerator::Sine, 400.0f, 550.0f, 2.1f);
    FunctionGenerator fGenMatRot = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 360.0f, 15.0f);
    FunctionGenerator fGenMatPeriod = FunctionGenerator(FunctionGenerator::Sine, 50.0f, 1500.0f, 8.0f);
    FunctionGenerator fGenMatAmpl = FunctionGenerator(FunctionGenerator::Sine, 0.1f, 1.0f, 4.3f);

    RGBColor spectrum1[6] = {RGBColor(255, 255, 0), RGBColor(0, 0, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 0), RGBColor(255, 0, 255), RGBColor(0, 0, 0)};
    RGBColor spectrum2[6] = {RGBColor(255, 0, 0), RGBColor(0, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 0), RGBColor(0, 0, 255), RGBColor(0, 0, 0)};
    RGBColor spectrum3[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    GradientMaterial colorDirection = GradientMaterial(6, spectrum3, 1.0f, false);
    VectorField2D vectorField = VectorField2D(40, 40, &colorDirection);

public:
    VectorFieldAnimation() : Animation(1) {
        scene->AddObject(cube.GetObject());
        
        cube.GetObject()->SetMaterial(&vectorField);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Update(float ratio) override {
        //float shift = fGenMatPos.Update();
        //float size = fGenMatSize.Update();
        //float rotate = fGenMatRot.Update();
        float period = fGenMatPeriod.Update();
        float amplitude = fGenMatAmpl.Update();

        vectorField.SetSize(450, 450);
        vectorField.SineField(ratio, period, amplitude);
        vectorField.SetPosition(0, 125);
        vectorField.SetRotation(15);

        cube.GetObject()->ResetVertices();
        cube.GetObject()->GetTransform()->SetScale(Vector3D(1000, 1000, 1));
        cube.GetObject()->UpdateTransform();
    }
};
