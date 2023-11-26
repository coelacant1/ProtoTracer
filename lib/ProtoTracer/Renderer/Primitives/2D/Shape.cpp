#include "Shape.h"

Shape::Shape(Vector2D center, Vector2D size, float rotation)
    : center(center), size(size), rotation(rotation) {
}

void Shape::SetCenter(Vector2D center) {
    this->center = center;
}

void Shape::Translate(Vector2D offset) {
    this->center = center + offset;
}

Vector2D Shape::GetCenter() {
    return center;
}

void Shape::SetSize(Vector2D size) {
    this->size = size;
}

void Shape::Scale(Vector2D scale) {
    this->size = size * scale;
}

Vector2D Shape::GetSize() {
    return size;
}

void Shape::SetRotation(float rotation) {
    this->rotation = rotation;
}

void Shape::Rotate(float offset) {
    this->rotation = rotation + offset;
}

float Shape::GetRotation() {
    return rotation;
}
