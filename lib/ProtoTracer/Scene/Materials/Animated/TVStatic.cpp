#include "TVStatic.h"

void TVStatic::Update(float ratio) {
    simplexNoiseDepth += 0.1f;

    gNoiseMat.SetGradientPeriod(0.5f);
    gNoiseMat.HueShift(ratio * 360 * 2);
    sNoise.SetScale(Vector3D(0.5f, 0.5f, 0.5f));
    sNoise.SetZPosition(simplexNoiseDepth);

    scanlineGradient.GradientShift(fmodf(ratio * 5.0f, 1.0f));

    colorTest.SetHueAngle(360.0f * ratio);
    colorTest.SetPosition(Vector2D(96.0f + colorWiggle1.Update(), Mathematics::Map(ratio, 0.0f, 1.0f, -100.0f, 100.0f) + colorWiggle2.Update()));
}

Material* TVStatic::GetMaterial() {
    return &combineScanline;
}

RGBColor TVStatic::GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) {
    return combineScanline.GetRGB(position, normal, uvw);
}
