#pragma once

#include "..\Material.h"
#include "..\..\..\Utils\Math\Mathematics.h"
#include "..\..\..\Utils\Math\Rotation.h"
#include "..\..\..\Utils\Math\Vector2D.h"

template<size_t colorCount>
class GradientMaterial : public Material {
private:
    RGBColor rgbColors[colorCount];
    RGBColor* baseRGBColors;
    Vector2D positionOffset;
    Vector2D rotationOffset; // point to rotate about
    float gradientPeriod = 1.0f;
    float rotationAngle = 0.0f; // rotate input xyPosition
    bool isRadial = false;
    bool isStepped = false;
    float gradientShift = 0.0f;

public:
    GradientMaterial(RGBColor* rgbColors, float gradientPeriod, bool isRadial, bool isStepped = false);

    void UpdateGradient(RGBColor* rgbColors);

    void SetPositionOffset(Vector2D positionOffset);

    void SetRotationOffset(Vector2D rotationOffset);

    void SetRotationAngle(float rotationAngle);

    void SetGradientPeriod(float gradientPeriod);

    void GradientShift(float ratio);

    void HueShift(float hueDeg);

    void UpdateRGB();

    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};

#include "GradientMaterial.tpp"