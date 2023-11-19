#pragma once

#include "..\..\Utils\Math\Vector2D.h"

class BoundingBox2D{
private:
    Vector2D min;
    Vector2D max;

public:
    BoundingBox2D(){}
    BoundingBox2D(Vector2D min, Vector2D max): min(min), max(max) {}

    void UpdateBounds(Vector2D current){
        min = min.Minimum(current);
        max = max.Maximum(current);
    }
    
    Vector2D GetMinimum(){
        return min;
    }

    Vector2D GetMaximum(){
        return max;
    }

    bool Overlaps(BoundingBox2D* bb){
        bool xOverlap = bb->GetMinimum().X < max.X && bb->GetMaximum().X > min.X;
        bool yOverlap = bb->GetMinimum().Y < max.Y && bb->GetMaximum().Y > min.Y;

        return xOverlap && yOverlap;
    }

    bool Contains(const Vector2D& v) {
        return min.X <= v.X && v.X <= max.X && min.Y <= v.Y && v.Y <= max.Y;
    }
};
