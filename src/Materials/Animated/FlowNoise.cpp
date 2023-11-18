#include "FlowNoise.h"

void FlowNoise::SetGradient(RGBColor color, uint8_t colorIndex) {
    noiseSpectrum[colorIndex] = color;
    gNoiseMat.UpdateGradient(noiseSpectrum);
}

void FlowNoise::Update(float ratio) {
    float sweepX = fGenMatGradientX.Update();
    float sweepY = fGenMatGradientY.Update();
    float sweepZ = fGenMatGradientZ.Update();
    float sShiftX = sweepX * 0.005f + 0.007f;
    float sShiftY = sweepY * 0.005f + 0.007f;
    float sShiftZ = sweepZ * 0.005f + 0.007f;

    simplexNoiseDepth += 0.0025f;

    gNoiseMat.SetGradientPeriod(fGenMatGradientP.Update());
    sNoise.SetScale(Vector3D(sShiftX, sShiftY, sShiftZ));
    sNoise.SetZPosition(simplexNoiseDepth);
}

Material* FlowNoise::GetMaterial() {
    return &sNoise;
}

RGBColor FlowNoise::GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) {
    return sNoise.GetRGB(position, normal, uvw);
}
