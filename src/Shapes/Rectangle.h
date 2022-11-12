#pragma once

#include "Shape.h"

class Rectangle : public Shape {
public:
    Rectangle(Vector2D center, Vector2D size, float rotation) : Shape(center, size, rotation){}

    bool IsInShape(Vector2D point) override {
        float x = (point.X - center.X);
        float y = (point.Y - center.Y);

        float sinR = sinf(rotation * Mathematics::MPID180);
        float cosR = cosf(rotation * Mathematics::MPID180);

        float xP = x * cosR - y * sinR;//rotate about center
        float yP = y * cosR + x * sinR;//rotate about center

        float sizeXH = size.X / 2.0f;
        float sizeYH = size.Y / 2.0f;

        float xL = center.X - sizeXH;
        float xR = center.X + sizeXH;
        float yB = center.Y - sizeYH;
        float yT = center.Y + sizeYH;

        return (xP > xL && xP < xR && yP > yB && yP < yT);
    }

};
