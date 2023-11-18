#pragma once

#include "Material.h"
#include "../Math/Mathematics.h"
#include "../Math/Vector2D.h"
#include "../Math/Rotation.h"

class SpiralMaterial : public Material {
private:
    RGBColor* rgbColors;
    RGBColor* baseRGBColors;
    uint8_t colorCount;
    Vector2D positionOffset;
    Vector2D rotationOffset; // Point to rotate about
    float width;
    float bend;
    float rotationAngle; // Rotate input xyPosition

public:
    SpiralMaterial(uint8_t colorCount, RGBColor* rgbColors, float width, float bend);
    ~SpiralMaterial(); // Destructor

    void SetPositionOffset(Vector2D positionOffset);
    void SetRotationOffset(Vector2D rotationOffset);
    void SetRotationAngle(float rotationAngle);
    void SetWidth(float width);
    void SetBend(float bend);

    void HueShift(float hueDeg);

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override;
};
