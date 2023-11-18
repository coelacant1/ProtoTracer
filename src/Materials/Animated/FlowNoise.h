#pragma once

#include "AnimatedMaterial.h"
#include "..\..\Signals\FunctionGenerator.h"
#include "..\..\Materials\GradientMaterial.h"
#include "..\..\Materials\SimplexNoise.h"

class FlowNoise : public AnimatedMaterial {
private:
    FunctionGenerator fGenMatGradientP = FunctionGenerator(FunctionGenerator::Sine, 0.25f, 1.5f, 4.35f);
    FunctionGenerator fGenMatGradientX = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 3.12f);
    FunctionGenerator fGenMatGradientY = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 1.93f);
    FunctionGenerator fGenMatGradientZ = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 4.56f);
    RGBColor noiseSpectrum[2] = {RGBColor(14, 33, 160), RGBColor(236, 83, 176)};
    GradientMaterial<2> gNoiseMat = GradientMaterial<2>(noiseSpectrum, 2.0f, false);
    SimplexNoise<2> sNoise = SimplexNoise<2>(1, &gNoiseMat);
    float simplexNoiseDepth = 0.0f;

public:
    FlowNoise(){}

    void SetGradient(RGBColor color, uint8_t colorIndex);
    void Update(float ratio);
    Material* GetMaterial();
    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override;
};
