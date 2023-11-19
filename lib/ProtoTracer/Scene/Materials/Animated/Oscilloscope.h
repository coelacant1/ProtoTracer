#pragma once

#include "..\Material.h"
#include "..\Static\GradientMaterial.h"
#include "..\..\..\Physics\Utils\BouncePhysics.h"
#include "..\..\..\Utils\Filter\MaxFilter.h"
#include "..\..\..\Utils\Filter\MinFilter.h"
#include "..\..\..\Utils\Math\Mathematics.h"

class Oscilloscope : public Material {
private:
    BouncePhysics* bPhy[128];
    Vector2D size;
    Vector2D offset;
    float angle = 0.0f;
    float hueAngle = 0.0f;
    float radius = 40.0f;
    uint8_t colors;
    float* data;
    float midPoint = 0.0f;
    uint8_t bins = 128;

    MaxFilter<40> maxF = MaxFilter<40>();
    MinFilter<40> minF = MinFilter<40>();

    RGBColor rainbowSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    GradientMaterial<6> gM = GradientMaterial<6>(rainbowSpectrum, 1.0f, false);

    Material* material;

    float minValue, maxValue;

public:
    Oscilloscope(Vector2D size, Vector2D offset);
    ~Oscilloscope();

    void SetMaterial(Material* material);
    float* GetSampleData();
    void SetSize(Vector2D size);
    void SetPosition(Vector2D offset);
    void SetRotation(float angle);
    void SetHueAngle(float hueAngle);
    void Update(float* data);

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override;
};
