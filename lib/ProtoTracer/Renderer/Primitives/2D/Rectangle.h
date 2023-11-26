#pragma once

#include "Shape.h"

class Rectangle : public Shape {
public:
    Rectangle(Vector2D center, Vector2D size, float rotation);

    bool IsInShape(Vector2D point) override;
};
