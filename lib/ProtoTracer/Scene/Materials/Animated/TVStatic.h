#pragma once

#include "..\AnimatedMaterial.h"
#include "..\..\..\Utils\Signals\FunctionGenerator.h"
#include "..\Static\GradientMaterial.h"
#include "..\Static\SimplexNoise.h"
#include "..\CombineMaterial.h"

#include "..\..\..\Assets\Textures\Static\ColorTest.h"

class TVStatic : public AnimatedMaterial {
private:
    FunctionGenerator colorWiggle1 = FunctionGenerator(FunctionGenerator::Sine, -40.0f, 20.0f, 1.95f);
    FunctionGenerator colorWiggle2 = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 0.87f);
    FunctionGenerator fGenMatGradient = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 6.65f);
    RGBColor noiseSpectrum[5] = {RGBColor(255, 255, 255), RGBColor(0, 0, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
    GradientMaterial<5> gNoiseMat = GradientMaterial<5>(noiseSpectrum, 2.0f, false, true);
    SimplexNoise<5> sNoise = SimplexNoise<5>(1, &gNoiseMat);
    float simplexNoiseDepth = 0.0f;

    RGBColor scanlineSpectrum[10] = {RGBColor(0, 0, 0), RGBColor(0, 0, 0), RGBColor(255, 255, 255), RGBColor(0, 0, 0), RGBColor(255, 255, 255), RGBColor(255, 255, 255), RGBColor(255, 255, 255), RGBColor(0, 0, 0), RGBColor(0, 0, 0), RGBColor(255, 255, 255)};
    GradientMaterial<10> scanlineGradient = GradientMaterial<10>(scanlineSpectrum, 100.0f, false, false);

    ColorTest colorTest = ColorTest(Vector2D(192.0f, 96.0f), Vector2D(96.0f, 48.0f));
    CombineMaterial<3> combineScanline = CombineMaterial<3>();

public:
    TVStatic() {
        //Material::Method method, Material* material, uint16_t frames, float minOpacity, float maxOpacity
        combineScanline.AddMaterial(Material::Method::Base, &sNoise, 1.0f);
        combineScanline.AddMaterial(Material::Method::Multiply, &scanlineGradient, 0.75f);
        combineScanline.AddMaterial(Material::Method::Lighten, &colorTest, 1.0f);

        scanlineGradient.SetRotationAngle(90.0f);
    }

    void Update(float ratio);
    Material* GetMaterial();
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
