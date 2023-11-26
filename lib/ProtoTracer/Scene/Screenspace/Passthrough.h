#pragma once

#include "Effect.h"

class Passthrough : public Effect {
public:
    Passthrough();

    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
