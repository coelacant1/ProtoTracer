#include "HorizontalRainbow.h"

void HorizontalRainbow::Update(float ratio) {
    positionOffset -= 1.0f;

    gNoiseMat.SetRotationAngle(90.0f);
    gNoiseMat.SetPositionOffset(Vector2D(positionOffset, 0.0f));
    gNoiseMat.SetGradientPeriod(96.0f);
}

Material* HorizontalRainbow::GetMaterial() {
    return &gNoiseMat;
}

RGBColor HorizontalRainbow::GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) {
    return gNoiseMat.GetRGB(position, normal, uvw);
}
