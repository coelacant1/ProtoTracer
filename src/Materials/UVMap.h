#pragma once

#include "Image.h"

class UVMap : public Image{
public:
    UVMap(const uint8_t* data, const uint8_t* rgbColors, unsigned int xPixels, unsigned int yPixels, uint8_t colors) : Image(data, rgbColors, xPixels, yPixels, colors) {
        this->size = Vector2D(1.0f, 1.0f);
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override {
        Vector2D rPos = Vector2D(1.0f - uvw.X, uvw.Y);

        unsigned int x = (unsigned int)Mathematics::Map(rPos.X, 0.0f, size.X, xPixels, 0);
        unsigned int y = (unsigned int)Mathematics::Map(rPos.Y, 0.0f, size.Y, yPixels, 0);

        if(x < 0 || x > xPixels || y < 0 || y > yPixels) return RGBColor();

        unsigned int pos = data[x + y * xPixels] * 3;

        if (pos > colors - (unsigned int)1) return RGBColor();

        return RGBColor(rgbColors[pos], rgbColors[pos + 1], rgbColors[pos + 2]).HueShift(hueAngle);
    }
};
