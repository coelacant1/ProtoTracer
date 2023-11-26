#pragma once

#include "Effect.h"
#include "..\..\Utils\Signals\FunctionGenerator.h"
#include "..\..\Utils\Math\Mathematics.h"

class PhaseOffsetY : public Effect {
private:
    const uint8_t pixels;
    FunctionGenerator fGenPhase = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 3.5f);

public:
    PhaseOffsetY(uint8_t pixels);

    void ApplyEffect(IPixelGroup* pixelGroup) override;

};

