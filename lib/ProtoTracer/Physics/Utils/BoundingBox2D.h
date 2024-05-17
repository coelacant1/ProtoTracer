#pragma once

#include "../../Utils/Math/Vector2D.h"

class BoundingBox2D {
private:
    Vector2D min;
    Vector2D max;
    Vector2D mid;

public:
    BoundingBox2D();
    BoundingBox2D(const Vector2D& min, const Vector2D& max);

    void UpdateBounds(const Vector2D& current);
    Vector2D GetMinimum();
    Vector2D GetMaximum();
    Vector2D GetCenter();
    bool Overlaps(BoundingBox2D* bb);
    bool Overlaps(const Vector2D& minI, const Vector2D& maxI);
    bool Contains(const Vector2D& v);
};
