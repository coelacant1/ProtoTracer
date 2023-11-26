#pragma once

#include "Shape.h"

class Circle : public Shape {
private:
    float radius;

public:
    Circle(Vector2D center, float radius);

    bool IsInShape(Vector2D point) override;
};
