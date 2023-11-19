#include "RainbowNoise2.h"

void RainbowNoise2::Update(float ratio) {
    float sweep = fGenMatGradient.Update();
    float sShift = sweep * 0.004f + 0.005f;

    simplexNoiseDepth += 0.01f;

    gNoiseMat.SetGradientPeriod(0.5f + sweep * 12.0f);
    gNoiseMat.HueShift(ratio * 360 * 2);
    sNoise.SetScale(Vector3D(sShift, sShift, sShift));
    sNoise.SetZPosition(simplexNoiseDepth);
}

Material* RainbowNoise2::GetMaterial() {
    return &sNoise;
}

RGBColor RainbowNoise2::GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) {
    return sNoise.GetRGB(position, normal, uvw);
}
