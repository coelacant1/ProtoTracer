#pragma once

#include "..\Materials\Material.h"
#include "..\Math\Vector2D.h"

class Image : public Material{
private:
    Vector2D size;
    Vector2D offset;

protected:
    unsigned int xPixels = 0;
    unsigned int yPixels = 0;
    uint8_t* rgbData;
    
    Image(Vector2D size, Vector2D offset){
        this->size = size;
        this->offset = offset;
    }

public:
    void SetPosition(Vector2D offset){
        this->offset = offset;
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        unsigned int x = (unsigned int)Mathematics::Map(position.X, offset.X, size.X + offset.X, 0, xPixels);
        unsigned int y = (unsigned int)Mathematics::Map(position.Y, offset.Y, size.Y + offset.Y, 0, yPixels);

        unsigned long pixel = x * 3 + (x * y * 3);

        return RGBColor(rgbData[pixel + 2], rgbData[pixel + 1], rgbData[pixel]);
    }
};
