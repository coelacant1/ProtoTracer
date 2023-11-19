#include "RGBColor.h"

RGBColor::RGBColor() {}

RGBColor::RGBColor(uint8_t R, uint8_t G, uint8_t B) {
    this->R = R;
    this->G = G;
    this->B = B;
}

RGBColor::RGBColor(const RGBColor& rgbColor) {
    this->R = rgbColor.R;
    this->G = rgbColor.G;
    this->B = rgbColor.B;
}

RGBColor::RGBColor(Vector3D color) {
    this->R = color.X;
    this->G = color.Y;
    this->B = color.Z;
}

void RGBColor::SetColor(uint8_t R, uint8_t G, uint8_t B) {
    this->R = R;
    this->G = G;
    this->B = B;
}

RGBColor RGBColor::Scale(uint8_t maxBrightness) {
    uint8_t sR, sG, sB;

    sR = (uint8_t)R * (uint8_t)maxBrightness / 255;
    sG = (uint8_t)G * (uint8_t)maxBrightness / 255;
    sB = (uint8_t)B * (uint8_t)maxBrightness / 255;

    sR = sR > 255 ? 255 : sR;
    sG = sG > 255 ? 255 : sG;
    sB = sB > 255 ? 255 : sB;

    sR = sR < 0 ? 0 : sR;
    sG = sG < 0 ? 0 : sG;
    sB = sB < 0 ? 0 : sB;

    return RGBColor(sR, sG, sB);
}

RGBColor RGBColor::Add(uint8_t value) {
    int sR, sG, sB;

    sR = (uint8_t)R + (uint8_t)value;
    sG = (uint8_t)G + (uint8_t)value;
    sB = (uint8_t)B + (uint8_t)value;

    sR = sR > 255 ? 255 : sR;
    sG = sG > 255 ? 255 : sG;
    sB = sB > 255 ? 255 : sB;

    sR = sR < 0 ? 0 : sR;
    sG = sG < 0 ? 0 : sG;
    sB = sB < 0 ? 0 : sB;

    return RGBColor(sR, sG, sB);
}

RGBColor RGBColor::HueShift(float hueDeg) {
    // Ensure the hue is in the range [0, 360)
    hueDeg = fmodf(hueDeg, 360.0f);
    if (hueDeg < 0.0f) {
        hueDeg += 360.0f;
    }

    // Convert hue to radians
    float hueRad = hueDeg * Mathematics::MPI / 180.0f;

    // Calculate sine and cosine of half hue angle
    float halfHueSin = sinf(hueRad / 2.0f);
    float halfHueCos = cosf(hueRad / 2.0f);

    // Calculate new RGB values
    float r = R * halfHueCos - G * halfHueSin;
    float g = R * halfHueSin + G * halfHueCos;
    float b = B * halfHueCos - G * halfHueSin;

    // Ensure RGB values are within the valid range
    r = fmaxf(0.0f, fminf(r, 255.0f));
    g = fmaxf(0.0f, fminf(g, 255.0f));
    b = fmaxf(0.0f, fminf(b, 255.0f));

    return RGBColor(r, g, b);
}


RGBColor RGBColor::InterpolateColors(RGBColor a, RGBColor b, float ratio) {
    RGBColor c;

    c.R = a.R * (1.0f - ratio) + b.R * ratio;
    c.G = a.G * (1.0f - ratio) + b.G * ratio;
    c.B = a.B * (1.0f - ratio) + b.B * ratio;

    return c;
}

String RGBColor::ToString() {
    String r = String(this->R);
    String g = String(this->G);
    String b = String(this->B);

    return "[" + r + ", " + g + ", " + b + "]";
}
