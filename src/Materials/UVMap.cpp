#include "UVMap.h"
#include "../Math/Mathematics.h"

UVMap::UVMap(const uint8_t* data, const uint8_t* rgbColors, uint16_t xPixels, uint16_t yPixels, uint8_t colors)
    : Image(data, rgbColors, xPixels, yPixels, colors) {
    this->size = Vector2D(1.0f, 1.0f);
}

RGBColor UVMap::GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) {
    Vector2D rPos = Vector2D(1.0f - uvw.X, uvw.Y);

    uint16_t x = (uint16_t)Mathematics::Map(rPos.X, 0.0f, size.X, float(xPixels), float(0));
    uint16_t y = (uint16_t)Mathematics::Map(rPos.Y, 0.0f, size.Y, float(yPixels), float(0));

    if (x < 0 || x >= xPixels || y < 0 || y >= yPixels) return RGBColor();

    uint16_t pos = data[x + y * xPixels] * 3;

    if (pos >= (uint16_t(colors - 1))) return RGBColor();

    return RGBColor(rgbColors[pos], rgbColors[pos + 1], rgbColors[pos + 2]).HueShift(hueAngle);
}
