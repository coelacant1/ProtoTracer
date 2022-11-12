#pragma once

#include "Shape.h"

class Circle : public Shape {
private:
    float radius = 0.0f;

public:
    Circle(Vector2D center, float radius) : Shape(center, Vector2D(radius, radius), 0.0f){
        this->radius = radius;
    }

    bool IsInShape(Vector2D point) override {
        float x = (point.X - center.X);
        float y = (point.Y - center.Y);
        float powRad = radius * radius;

        return x * x + y * y < powRad;
    }

};
