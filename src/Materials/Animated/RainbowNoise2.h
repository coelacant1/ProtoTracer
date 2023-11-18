#pragma once

#include "AnimatedMaterial.h"
#include "..\..\Signals\FunctionGenerator.h"
#include "..\..\Materials\GradientMaterial.h"
#include "..\..\Materials\SimplexNoise.h"

class RainbowNoise2 : public AnimatedMaterial {
private:
    FunctionGenerator fGenMatGradient = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 6.65f);
    RGBColor noiseSpectrum[4] = {RGBColor(0, 0, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
    GradientMaterial<4> gNoiseMat = GradientMaterial<4>(noiseSpectrum, 2.0f, false);
    SimplexNoise<4> sNoise = SimplexNoise<4>(1, &gNoiseMat);
    float simplexNoiseDepth = 0.0f;

public:
    RainbowNoise2() {}

    void Update(float ratio);
    Material* GetMaterial();
    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override;
};
