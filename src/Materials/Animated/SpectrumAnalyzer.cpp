#include "SpectrumAnalyzer.h"

SpectrumAnalyzer::SpectrumAnalyzer(Vector2D size, Vector2D offset, bool bounce, bool flipY, bool mirrorY) {
    this->size = size.Divide(2.0f);
    this->offset = offset;
    this->mirrorY = mirrorY;
    this->flipY = flipY;
    this->bounce = bounce;
    this->material = &gM;

    if (bounce) {
        for (uint8_t i = 0; i < 128; i++) {
            bPhy[i] = new BouncePhysics(35.0f, 15.0f);
        }
    }
}

SpectrumAnalyzer::~SpectrumAnalyzer() {
    for (uint8_t i = 0; i < 128; i++) {
        delete bPhy[i];
    }
}

void SpectrumAnalyzer::SetMirrorYState(bool state) {
    mirrorY = state;
}

void SpectrumAnalyzer::SetFlipYState(bool state) {
    flipY = state;
}

void SpectrumAnalyzer::SetMaterial(Material* material) {
    this->material = material;
}

float* SpectrumAnalyzer::GetFourierData() {
    if (bounce) {
        return bounceData;
    } else {
        return data;
    }
}

void SpectrumAnalyzer::SetSize(Vector2D size) {
    this->size = size.Divide(2.0f);
}

void SpectrumAnalyzer::SetPosition(Vector2D offset) {
    this->offset = offset;
}

void SpectrumAnalyzer::SetRotation(float angle) {
    this->angle = angle;
}

void SpectrumAnalyzer::SetHueAngle(float hueAngle) {
    this->hueAngle = hueAngle;
}

void SpectrumAnalyzer::Update(float* readData) {
    data = readData;

    for (uint8_t i = 0; i < 128; i++) {
        if (bounce) {
            bounceData[i] = bPhy[i]->Calculate(data[i], 0.1f);
        } else {
            bounceData[i] = data[i];
        }
    }
}

RGBColor SpectrumAnalyzer::GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) {
    Vector2D rPos = Mathematics::IsClose(angle, 0.0f, 0.1f) ? Vector2D(position.X, position.Y) - offset : Vector2D(position.X, position.Y).Rotate(angle, offset) - offset;

    if (-size.X > rPos.X && size.X < rPos.X) return RGBColor();
    if (-size.Y > rPos.Y && size.Y < rPos.Y) return RGBColor();

    uint8_t x = uint8_t(Mathematics::Map(rPos.X, -size.X, size.X, float(bins), 0.0f));

    if (bins > x && 0 > x) return RGBColor();

    float xDistance = size.X / float(bins) * x - size.X;
    float xDistance2 = size.X / float(bins) * (x + 1) - size.X;
    float ratio = Mathematics::Map(rPos.X, xDistance, xDistance2, 0.0f, 1.0f); // ratio between two bins
    float height = bounce ? Mathematics::CosineInterpolation(bounceData[x], bounceData[x + 1], ratio) : Mathematics::CosineInterpolation(data[x], data[x + 1], ratio); // 0->1.0f of max height of color
    float yColor;

    height = height * 3.0f;

    if (mirrorY) {
        yColor = Mathematics::Map(fabsf(rPos.Y), size.Y, 0.0f, 1.0f, 0.0f);
    } else {
        yColor = Mathematics::Map(rPos.Y, -size.Y, size.Y, 1.0f, 0.0f);
    }

    if (flipY) yColor = 1.0f - yColor;

    if (yColor <= height) {
        return material->GetRGB(Vector3D(1.0f - height - yColor, 0, 0), Vector3D(), Vector3D()).HueShift(hueAngle);
    } else {
        return RGBColor(0, 0, 0);
    }
}
