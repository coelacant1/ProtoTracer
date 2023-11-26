#pragma once

#include "Effect.h"

class VerticalBlur : public Effect {
private:
    const uint8_t pixels;

public:
    VerticalBlur(uint8_t pixels);

    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
