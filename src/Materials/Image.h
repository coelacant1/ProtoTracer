#pragma once

#include "..\Materials\Material.h"
#include "..\Math\Vector2D.h"

class Image : public Material{
private:
    Vector2D size;
    Vector2D offset;
    float angle = 0.0f;
    unsigned int xPixels = 0;
    unsigned int yPixels = 0;
    const uint8_t* rgbData;
    
protected:
    Image(const uint8_t* rgbData, unsigned int xPixels, unsigned int yPixels) : rgbData(rgbData) {
        this->xPixels = xPixels;
        this->yPixels = yPixels;
    }

public:
    void SetSize(Vector2D size){
        this->size = size;
    }

    void SetPosition(Vector2D offset){
        this->offset = offset;
    }

    void SetRotation(float angle){
        this->angle = angle;
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override {
        Vector2D rPos = angle != 0.0f ? Vector2D(position.X, position.Y).Subtract(size.Divide(2.0f)).Rotate(angle, offset).Add(size.Divide(2.0f)) : Vector2D(position.X, position.Y);

        unsigned int x = (unsigned int)Mathematics::Map(rPos.X, offset.X, size.X + offset.X, xPixels, 0);
        unsigned int y = (unsigned int)Mathematics::Map(rPos.Y, offset.Y, size.Y + offset.Y, yPixels, 0);

        if(x <= 0 || x >= xPixels || y <= 0 || y >= yPixels){
            return RGBColor();
        }

        unsigned long pos = x * 3 + y * xPixels * 3;

        return RGBColor(rgbData[pos], rgbData[pos + 1], rgbData[pos + 2]);
    }
};
