#pragma once

#include "..\..\Utils\Math\Vector2D.h"

class BoundingBox2D {
private:
    Vector2D min;
    Vector2D max;

public:
    BoundingBox2D();
    BoundingBox2D(Vector2D min, Vector2D max);

    void UpdateBounds(Vector2D current);
    Vector2D GetMinimum();
    Vector2D GetMaximum();
    bool Overlaps(BoundingBox2D* bb);
    bool Contains(const Vector2D& v);
};
