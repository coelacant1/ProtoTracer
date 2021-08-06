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
    RGBColor** rgbData;
    
    Image(Vector2D size, Vector2D offset, RGBColor** rgbData){
        this->size = size;
        this->offset = offset;
        this->rgbData = rgbData;
    }

public:
    void SetPosition(Vector2D offset){
        this->offset = offset;
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override {
        unsigned int x = (unsigned int)Mathematics::Map(position.X, offset.X, size.X + offset.X, 0, xPixels);
        unsigned int y = (unsigned int)Mathematics::Map(position.Y, offset.Y, size.Y + offset.Y, 0, yPixels);

        if(x < 0 || x > xPixels || y < 0 || y > yPixels){
            return RGBColor();
        }

        return rgbData[x][y];
    }
};
