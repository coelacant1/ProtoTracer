#pragma once

#include "..\Materials\Image.h"

class ExampleImage : public Image{
private:
    RGBColor rgbMemory[48][48] = {};

public:
    ExampleImage(Vector2D size, Vector2D offset) : Image(size, offset, rgbMemory) {
        this->rgbData = rgbMemory;
        this->xPixels = 16;
        this->yPixels = 16;
    }
};
