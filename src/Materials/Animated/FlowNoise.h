#pragma once

#include "AnimatedMaterial.h"
#include "..\..\Signals\FunctionGenerator.h"
#include "..\..\Materials\GradientMaterial.h"
#include "..\..\Materials\SimplexNoise.h"

class FlowNoise : public AnimatedMaterial{
private:
    FunctionGenerator fGenMatGradient = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 6.65f);
    RGBColor noiseSpectrum[6] = {RGBColor(150, 10, 154), RGBColor(249, 0, 110), RGBColor(253, 20, 91), RGBColor(228, 124, 48), RGBColor(253, 147, 34), RGBColor(0, 0, 80)};
    GradientMaterial<6> gNoiseMat = GradientMaterial<6>(noiseSpectrum, 2.0f, false);
    SimplexNoise<6> sNoise = SimplexNoise<6>(1, &gNoiseMat);
    float simplexNoiseDepth = 0.0f;
    //uint32_t iterate = 0;

public:
    FlowNoise(){}

    void Update(float ratio){
        float sweep = fGenMatGradient.Update();
        float sShift = sweep * 0.005f + 0.007f;

        simplexNoiseDepth += 0.0025f;

        gNoiseMat.SetGradientPeriod(0.5f + sweep * 12.0f);
        //gNoiseMat.HueShift(ratio * 360 * 2);
        sNoise.SetScale(Vector3D(sShift, sShift, sShift));
        sNoise.SetZPosition(simplexNoiseDepth);
    }

    Material* GetMaterial(){
        return &sNoise;
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        return sNoise.GetRGB(position, normal, uvw);
    }
};
