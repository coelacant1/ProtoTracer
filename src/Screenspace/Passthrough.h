#pragma once

#include "Effect.h"
#include "Arduino.h"

class Passthrough: public Effect {
public:
    Passthrough(){}

    void ApplyEffect(IPixelGroup* pixelGroup) override {}

};

