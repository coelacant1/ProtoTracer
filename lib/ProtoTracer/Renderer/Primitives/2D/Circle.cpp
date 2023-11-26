#include "Circle.h"

Circle::Circle(Vector2D center, float radius) : Shape(center, Vector2D(radius, radius), 0.0f), radius(radius) {}

bool Circle::IsInShape(Vector2D point) {
    float x = (point.X - center.X);
    float y = (point.Y - center.Y);
    float powRad = radius * radius;

    return x * x + y * y < powRad;
}
