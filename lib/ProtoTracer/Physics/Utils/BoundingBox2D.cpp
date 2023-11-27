#include "BoundingBox2D.h"

BoundingBox2D::BoundingBox2D() {
    // Initialize min and max to default values
    min = Vector2D(0.0f, 0.0f);
    max = Vector2D(0.0f, 0.0f);
    mid = Vector2D(0.0f, 0.0f);
}

BoundingBox2D::BoundingBox2D(const Vector2D& min, const Vector2D& max) {
    this->min = min;
    this->max = max;

    mid.X = (min.X + max.X) * 0.5f;
    mid.Y = (min.Y + max.Y) * 0.5f;
}

void BoundingBox2D::UpdateBounds(const Vector2D& current) {
    min = min.Minimum(current);
    max = max.Maximum(current);
    
    mid.X = (min.X + max.X) * 0.5f;
    mid.Y = (min.Y + max.Y) * 0.5f;
}

Vector2D BoundingBox2D::GetMinimum() {
    return min;
}

Vector2D BoundingBox2D::GetMaximum() {
    return max;
}

Vector2D BoundingBox2D::GetCenter() {
    return mid;
}

bool BoundingBox2D::Overlaps(BoundingBox2D* bb) {
    bool xOverlap = bb->GetMinimum().X < max.X && bb->GetMaximum().X > min.X;
    bool yOverlap = bb->GetMinimum().Y < max.Y && bb->GetMaximum().Y > min.Y;

    return xOverlap && yOverlap;
}

bool BoundingBox2D::Contains(const Vector2D& v) {
    return min.X <= v.X && v.X <= max.X && min.Y <= v.Y && v.Y <= max.Y;
}

