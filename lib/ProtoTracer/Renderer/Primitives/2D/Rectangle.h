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
        float yP = x * sinR + y * cosR;//rotate about center

        return fabs(xP) <= size.X / 2.0f && fabs(yP) <= size.Y / 2.0f;
    }

};
