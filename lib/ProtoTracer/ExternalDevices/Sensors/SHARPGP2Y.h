#pragma once

#include <Arduino.h>
#include "../../Utils/Filter/RunningAverageFilter.h"

class SHARPGP2Y {
private:
    RunningAverageFilter<25> rAF = RunningAverageFilter<25>(0.1f);
    float distance = 0.0f;
    uint8_t pin;

    float ReadingToDistance(uint8_t reading);

public:
    SHARPGP2Y(uint8_t pin);
    float GetDistance();
    float Update();
};
