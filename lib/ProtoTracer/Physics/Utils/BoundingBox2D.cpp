#include "BoundingBox2D.h"

BoundingBox2D::BoundingBox2D() {
    // Initialize min and max to default values
    min = Vector2D(0.0f, 0.0f);
    max = Vector2D(0.0f, 0.0f);
}

BoundingBox2D::BoundingBox2D(Vector2D min, Vector2D max) {
    this->min = min;
    this->max = max;
}

void BoundingBox2D::UpdateBounds(Vector2D current) {
    min = min.Minimum(current);
    max = max.Maximum(current);
}

Vector2D BoundingBox2D::GetMinimum() {
    return min;
}

Vector2D BoundingBox2D::GetMaximum() {
    return max;
}

bool BoundingBox2D::Overlaps(BoundingBox2D* bb) {
    bool xOverlap = bb->GetMinimum().X < max.X && bb->GetMaximum().X > min.X;
    bool yOverlap = bb->GetMinimum().Y < max.Y && bb->GetMaximum().Y > min.Y;

    return xOverlap && yOverlap;
}

bool BoundingBox2D::Contains(const Vector2D& v) {
    return min.X <= v.X && v.X <= max.X && min.Y <= v.Y && v.Y <= max.Y;
}
