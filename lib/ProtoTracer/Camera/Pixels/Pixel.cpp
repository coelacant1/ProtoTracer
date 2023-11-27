#include "Pixel.h"

Pixel::Pixel() {
    // Default constructor
}

Pixel::Pixel(Vector2D* position) {
    this->position = position;
}

Vector2D Pixel::GetPosition() {
    return *position;
}

void Pixel::SetUpPixel(Pixel* pixel) {
    this->up = pixel;
    this->upExists = true;
}

void Pixel::SetDownPixel(Pixel* pixel) {
    this->down = pixel;
    this->downExists = true;
}

void Pixel::SetLeftPixel(Pixel* pixel) {
    this->left = pixel;
    this->leftExists = true;
}

void Pixel::SetRightPixel(Pixel* pixel) {
    this->right = pixel;
    this->rightExists = true;
}

bool Pixel::HasUpPixel() {
    return upExists;
}

bool Pixel::HasDownPixel() {
    return downExists;
}

bool Pixel::HasLeftPixel() {
    return leftExists;
}

bool Pixel::HasRightPixel() {
    return rightExists;
}

Pixel* Pixel::GetUpPixel() {
    return up;
}

Pixel* Pixel::GetDownPixel() {
    return down;
}

Pixel* Pixel::GetLeftPixel() {
    return left;
}

Pixel* Pixel::GetRightPixel() {
    return right;
}
