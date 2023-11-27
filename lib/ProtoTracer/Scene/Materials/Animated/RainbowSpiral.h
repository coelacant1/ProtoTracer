#pragma once

#include "..\AnimatedMaterial.h"
#include "..\..\..\Utils\Signals\FunctionGenerator.h"
#include "..\Static\SpiralMaterial.h"

class RainbowSpiral : public AnimatedMaterial {
private:
    FunctionGenerator fGenMatBend = FunctionGenerator(FunctionGenerator::Sine, 0.8f, 0.9f, 6.7f);
    RGBColor rainbowSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    SpiralMaterial spiralMaterial = SpiralMaterial(6, rainbowSpectrum, 3.0f, 7.0f);

public:
    RainbowSpiral() {}

    void Update(float ratio);
    Material* GetMaterial();
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
