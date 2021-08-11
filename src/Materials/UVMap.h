#pragma once

#include "Image.h"
#include "Arduino.h"

class UVMap : public Image{
private:

public:
    UVMap(Type type, const uint8_t* data, unsigned int xPixels, unsigned int yPixels) : Image(type, data, xPixels, yPixels) {
        this->size = Vector2D(1.0f, 1.0f);
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override {
        Vector2D rPos = Vector2D(1.0f - uvw.X, uvw.Y);

        unsigned int x = (unsigned int)Mathematics::Map(rPos.X, 0.0f, size.X, xPixels, 0);
        unsigned int y = (unsigned int)Mathematics::Map(rPos.Y, 0.0f, size.Y, yPixels, 0);

        if(x < 0 || x >= xPixels || y < 0 || y >= yPixels){
            return RGBColor();
        }

        unsigned long pos = x * 3 + y * xPixels * 3;

        return RGBColor(data[pos], data[pos + 1], data[pos + 2]).HueShift(hueAngle);
    }
};
