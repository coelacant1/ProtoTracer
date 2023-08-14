#pragma once

#include "..\Materials\Material.h"
#include "..\Math\Vector2D.h"

class Image : public Material{
public:
    Vector2D size;
    Vector2D offset;
    float angle = 0.0f;
    float hueAngle = 0.0f;
    unsigned int xPixels = 0;
    unsigned int yPixels = 0;
    const uint8_t* data;
    const uint8_t* rgbColors;
    uint8_t colors;

    Image(const uint8_t* data, const uint8_t* rgbColors, unsigned int xPixels, unsigned int yPixels, uint8_t colors) {
        this->data = data;
        this->rgbColors = rgbColors;
        this->xPixels = xPixels;
        this->yPixels = yPixels;
        this->colors = colors;
    }

    ~Image(){}

    void SetData(const uint8_t* data){
        this->data = data;
    }

    void SetColorPalette(const uint8_t* rgbColors){
        this->rgbColors = rgbColors;
    }

    void SetSize(Vector2D size){
        this->size = size;
    }

    void SetPosition(Vector2D offset){
        this->offset = offset;
    }

    void SetRotation(float angle){
        this->angle = angle;
    }

    void SetHueAngle(float hueAngle){
        this->hueAngle = hueAngle;
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override {
        Vector2D rPos = angle != 0.0f ? Vector2D(position.X, position.Y).Rotate(angle, offset) - offset : Vector2D(position.X, position.Y) - offset;

        unsigned int x = (unsigned int)Mathematics::Map(rPos.X, size.X / -2.0f, size.X / 2.0f, float(xPixels), 0.0f);
        unsigned int y = (unsigned int)Mathematics::Map(rPos.Y, size.Y / -2.0f, size.Y / 2.0f, float(yPixels), 0.0f);

        if(x <= 1 || x >= xPixels || y <= 1 || y >= yPixels) return RGBColor();

        unsigned int pos = data[x + y * xPixels] * 3;

        if (pos > colors - (unsigned int)1) return RGBColor();

        return RGBColor(rgbColors[pos], rgbColors[pos + 1], rgbColors[pos + 2]).HueShift(hueAngle);
    }
};
