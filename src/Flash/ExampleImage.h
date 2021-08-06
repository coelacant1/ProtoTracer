#pragma once

#include "..\Materials\Image.h"

class ExampleImage : public Image{
private:
    uint8_t rgbMemory[48] = {};

public:
    ExampleImage(Vector2D size, Vector2D offset) : Image(size, offset) {
        this->rgbData = &rgbMemory[0];
        this->xPixels = 16;
        this->yPixels = 16;
    }
};
