#pragma once

#include "Effect.h"
#include "..\..\Utils\Signals\FunctionGenerator.h"
#include "..\..\Utils\Math\Mathematics.h"

class RadialBlur: public Effect {
private:
    const uint8_t pixels;
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 360.0f, 3.7f);

public:
    RadialBlur(uint8_t pixels);

    void ApplyEffect(IPixelGroup* pixelGroup) override;
};

