#pragma once

#include <Arduino.h>
#include "Effect.h"
#include "..\..\Utils\Math\Mathematics.h"

class GlitchX : public Effect {
private:
    const uint8_t pixels;

public:
    GlitchX(uint8_t pixels);

    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
