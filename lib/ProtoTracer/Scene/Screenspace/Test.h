#pragma once

#include "Effect.h"
#include "../../Utils/Signals/FunctionGenerator.h"

class Test : public Effect {
private:
    FunctionGenerator fGenD = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 255.0f, 0.5f);

public:
    Test();

    void ApplyEffect(IPixelGroup* pixelGroup) override;
};

