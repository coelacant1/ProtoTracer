#include "SpiralMaterial.h"

SpiralMaterial::SpiralMaterial(uint8_t colorCount, RGBColor* rgbColors, float width, float bend) {
    this->colorCount = colorCount;
    this->width = width;
    this->bend = bend;

    this->rgbColors = new RGBColor[colorCount];
    this->baseRGBColors = new RGBColor[colorCount];

    for (int i = 0; i < colorCount; i++) {
        this->rgbColors[i] = rgbColors[i];
        this->baseRGBColors[i] = rgbColors[i];
    }
}

SpiralMaterial::~SpiralMaterial() {
    delete[] rgbColors;
    delete[] baseRGBColors;
}

void SpiralMaterial::SetPositionOffset(Vector2D positionOffset) {
    this->positionOffset = positionOffset;
}

void SpiralMaterial::SetRotationOffset(Vector2D rotationOffset) {
    this->rotationOffset = rotationOffset;
}

void SpiralMaterial::SetRotationAngle(float rotationAngle) {
    this->rotationAngle = rotationAngle;
}

void SpiralMaterial::SetWidth(float width) {
    this->width = width;
}

void SpiralMaterial::SetBend(float bend) {
    this->bend = bend;
}

void SpiralMaterial::HueShift(float hueDeg) {
    for (int i = 0; i < colorCount; i++) {
        rgbColors[i] = baseRGBColors[i].HueShift(hueDeg);
    }
}

RGBColor SpiralMaterial::GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) {
    Vector3D positionL = position;

    if (rotationAngle != 0) {
        Quaternion temp = Rotation(EulerAngles(Vector3D(0, 0, rotationAngle), EulerConstants::EulerOrderXYZS)).GetQuaternion();

        positionL = positionL - Vector3D(positionOffset.X, positionOffset.Y, 0.0f);

        positionL = temp.RotateVector(positionL);
    }

    // From x position, fit into bucket ratio
    // Modulo x value into x range from start position to end position

    float radius = Vector2D(positionL).Magnitude();
    float angle = atan2(positionL.Y, positionL.X);
    float ratio = Mathematics::Fract(width * angle / Mathematics::MPI + bend * powf(radius, 0.3f));

    int startBox = floor(ratio * colorCount);

    RGBColor rgb = rgbColors[startBox];

    return rgb;
}
