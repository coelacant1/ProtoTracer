#pragma once

#include "../AnimatedMaterial.h"
#include "../Static/GradientMaterial.h"
#include "../Static/SimplexNoise.h"

class HorizontalRainbow : public AnimatedMaterial {
private:
    RGBColor noiseSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    GradientMaterial<6> gNoiseMat = GradientMaterial<6>(&noiseSpectrum[0], 2.0f, false, false);
    float positionOffset = 0.0f;

public:
    HorizontalRainbow() {}

    void Update(float ratio);
    Material* GetMaterial();
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
