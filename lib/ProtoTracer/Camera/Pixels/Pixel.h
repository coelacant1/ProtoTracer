#pragma once

#include "..\..\Utils\RGBColor.h"
#include "..\..\Utils\Math\Vector2D.h"

class Pixel {
private:
    Vector2D* position;
    bool sorted = false;
    bool upExists = false;
    bool downExists = false;
    bool leftExists = false;
    bool rightExists = false;

    Pixel* up = nullptr;
    Pixel* down = nullptr;
    Pixel* left = nullptr;
    Pixel* right = nullptr;

public:
    RGBColor* Color;

    Pixel();

    Pixel(Vector2D* position);

    Vector2D GetPosition();

    void SetUpPixel(Pixel* pixel);

    void SetDownPixel(Pixel* pixel);

    void SetLeftPixel(Pixel* pixel);

    void SetRightPixel(Pixel* pixel);

    bool HasUpPixel();

    bool HasDownPixel();

    bool HasLeftPixel();

    bool HasRightPixel();

    Pixel* GetUpPixel();

    Pixel* GetDownPixel();

    Pixel* GetLeftPixel();

    Pixel* GetRightPixel();
};
