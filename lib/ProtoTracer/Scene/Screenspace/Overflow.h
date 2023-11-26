#pragma once

#include "Effect.h"

class Overflow : public Effect {
private:
    const uint8_t pixels;

public:
    Overflow(uint8_t pixels);

    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
