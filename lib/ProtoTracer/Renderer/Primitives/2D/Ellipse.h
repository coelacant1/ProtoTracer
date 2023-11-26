#pragma once

#include "Shape.h"

class Ellipse : public Shape {
public:
    Ellipse(Vector2D center, Vector2D size, float rotation);

    bool IsInShape(Vector2D point) override;
};
