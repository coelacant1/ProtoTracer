#pragma once

#include "..\Materials\Material.h"
#include "..\Math\Vector2D.h"

class Image : public Material{
public:
    enum Type{
        RGB,
        BW
    };

protected:
    Type type;
    Vector2D size;
    Vector2D offset;
    float angle = 0.0f;
    float hueAngle = 0.0f;
    unsigned int xPixels = 0;
    unsigned int yPixels = 0;
    const uint8_t* data;

    Image(Type type, unsigned int xPixels, unsigned int yPixels) {
        this->type = type;
        this->xPixels = xPixels;
        this->yPixels = yPixels;
    }

    Image(Type type, const uint8_t* data, unsigned int xPixels, unsigned int yPixels) {
        this->type = type;
        this->data = data;
        this->xPixels = xPixels;
        this->yPixels = yPixels;
    }

    ~Image(){}

public:
    void SetData(const uint8_t* data){
        this->data = data;
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

        unsigned int x = (unsigned int)Mathematics::Map(rPos.X, size.X / -2.0f, size.X / 2.0f, xPixels, 0);
        unsigned int y = (unsigned int)Mathematics::Map(rPos.Y, size.Y / -2.0f, size.Y / 2.0f, yPixels, 0);

        if(x <= 0 || x >= xPixels || y <= 0 || y >= yPixels){
            return RGBColor();
        }

        if (type == RGB){//RGB
            unsigned long pos = x * 3 + y * xPixels * 3;

            return RGBColor(data[pos], data[pos + 1], data[pos + 2]).HueShift(hueAngle);
        }
        else{//Black and white
            unsigned long pos = x + y * xPixels;

            return RGBColor(data[pos], data[pos], data[pos]);
        }
    }
};
