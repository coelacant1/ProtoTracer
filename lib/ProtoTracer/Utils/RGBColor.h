#pragma once

#include "Math\Mathematics.h"
#include "Math\Quaternion.h"
#include "Math\Vector3D.h"

class RGBColor {
public:
    uint8_t R = 0;
    uint8_t G = 0;
    uint8_t B = 0;

    RGBColor();

    RGBColor(const uint8_t& R, const uint8_t& G, const uint8_t& B);

    RGBColor(const RGBColor& rgbColor);

    RGBColor(const Vector3D& color);

    void SetColor(const uint8_t& R, const uint8_t& G, const uint8_t& B);

    RGBColor Scale(const uint8_t& maxBrightness);

    RGBColor Add(const uint8_t& value);

    RGBColor HueShift(const float& hueDeg);

    static RGBColor InterpolateColors(const RGBColor& a, const RGBColor& b, const float& ratio);

    String ToString();
};
