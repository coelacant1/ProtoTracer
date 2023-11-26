#pragma once

#include "Effect.h"
#include "..\..\Utils\Math\Mathematics.h"

class HorizontalBlur : public Effect {
private:
    const uint8_t pixels;

public:
    HorizontalBlur(uint8_t pixels);

    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
