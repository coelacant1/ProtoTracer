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

    RGBColor(uint8_t R, uint8_t G, uint8_t B);

    RGBColor(const RGBColor& rgbColor);

    RGBColor(Vector3D color);

    void SetColor(uint8_t R, uint8_t G, uint8_t B);

    RGBColor Scale(uint8_t maxBrightness);

    RGBColor Add(uint8_t value);

    RGBColor HueShift(float hueDeg);

    static RGBColor InterpolateColors(RGBColor a, RGBColor b, float ratio);

    String ToString();
};
