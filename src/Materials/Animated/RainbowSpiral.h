#pragma once

#include "AnimatedMaterial.h"
#include "..\..\Signals\FunctionGenerator.h"
#include "..\..\Materials\SpiralMaterial.h"

class RainbowSpiral : public AnimatedMaterial{
private:
    FunctionGenerator fGenMatBend = FunctionGenerator(FunctionGenerator::Sine, 0.8f, 0.9f, 6.7f);
    RGBColor rainbowSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    SpiralMaterial spiralMaterial = SpiralMaterial(6, rainbowSpectrum, 3.0f, 7.0f);

public:
    RainbowSpiral(){}

    void Update(float ratio){
        spiralMaterial.SetBend(fGenMatBend.Update());
        spiralMaterial.SetRotationAngle((1.0f - ratio) * 360.0f);
        spiralMaterial.SetPositionOffset(Vector2D(0.0f, 75.0f));
    }

    Material* GetMaterial(){
        return &spiralMaterial;
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        return spiralMaterial.GetRGB(position, normal, uvw);
    }
};
