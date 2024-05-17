#pragma once

#include "Effect.h"
#include "../../Utils/Signals/FunctionGenerator.h"
#include "../../Utils/Math/Mathematics.h"

class PhaseOffsetR : public Effect {
private:
    const uint8_t pixels;
    FunctionGenerator fGenPhase1 = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 4.5f);
    FunctionGenerator fGenPhase2 = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 3.2f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 360.0f, 3.7f);

public:
    PhaseOffsetR(uint8_t pixels);

    void ApplyEffect(IPixelGroup* pixelGroup) override;
};

