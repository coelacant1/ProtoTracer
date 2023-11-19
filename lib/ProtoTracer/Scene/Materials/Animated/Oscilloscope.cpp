#include "Oscilloscope.h"

Oscilloscope::Oscilloscope(Vector2D size, Vector2D offset) {
    this->size = size.Divide(2.0f);
    this->offset = offset;
    this->material = &gM;
}

Oscilloscope::~Oscilloscope() {
    for (uint8_t i = 0; i < 128; i++) {
        delete bPhy[i];
    }
}

void Oscilloscope::SetMaterial(Material* material) {
    this->material = material;
}

float* Oscilloscope::GetSampleData() {
    return data;
}

void Oscilloscope::SetSize(Vector2D size) {
    this->size = size.Divide(2.0f);
}

void Oscilloscope::SetPosition(Vector2D offset) {
    this->offset = offset;
}

void Oscilloscope::SetRotation(float angle) {
    this->angle = angle;
}

void Oscilloscope::SetHueAngle(float hueAngle) {
    this->hueAngle = hueAngle;
}

void Oscilloscope::Update(float* data) {
    this->data = data;

    minValue = minF.Filter(data[bins / 2 + 1]);
    maxValue = maxF.Filter(data[bins / 2 + 1]);

    midPoint = (maxValue - minValue) / 2.0f + minValue;
}

RGBColor Oscilloscope::GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) {
    Vector2D rPos = Mathematics::IsClose(angle, 0.0f, 0.1f) ? Vector2D(position.X, position.Y) - offset : Vector2D(position.X, position.Y).Rotate(angle, offset) - offset;

    // Outside of size bounds
    if (rPos.X < -size.X || rPos.X > size.X) return RGBColor();
    if (rPos.Y < -size.Y || rPos.Y > size.Y) return RGBColor();

    uint8_t x = uint8_t(Mathematics::Map(rPos.X, -size.X, size.X, float(bins - 1), float(bins - 1) / 2));

    if (bins > x && 0 > x) return RGBColor();

    float xDistance = size.X / float(bins) * x - size.X;
    float xDistance2 = size.X / float(bins) * (x + 2) - size.X;
    float ratio = Mathematics::Map(rPos.X, xDistance, xDistance2, 0.0f, 1.0f); // ratio between two bins

    float firstPoint = Mathematics::Map(data[x], minValue, maxValue, 0.0f, 0.75f);
    float secondPoint = Mathematics::Map(data[x + 2], minValue, maxValue, 0.0f, 0.75f);

    float height = Mathematics::CosineInterpolation(firstPoint, secondPoint, ratio); // 0->1.0f of max height of color
    float yColor = Mathematics::Map(rPos.Y, 0.0f, size.Y, 1.0f, 0.0f);

    if (rPos.Y < height * size.Y / 2.0f && rPos.Y > height * size.Y / 2.0f - size.Y * 0.1f) {
        return material->GetRGB(Vector3D(1.0f + height - yColor, 0, 0), Vector3D(), Vector3D()).HueShift(hueAngle);
    } else {
        return RGBColor(0, 0, 0);
    }
}
