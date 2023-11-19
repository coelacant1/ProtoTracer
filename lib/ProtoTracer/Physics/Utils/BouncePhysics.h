#pragma once

#include "..\..\Utils\Math\Mathematics.h"
#include "..\..\Utils\Filter\RunningAverageFilter.h"

class BouncePhysics {
private:
    RunningAverageFilter<10> velocityFilter;
    float currentVelocity;
    float currentPosition;
    float velocityRatio;
    float gravity;
    unsigned long previousMillis;
    float previousVelocity;

public:
    BouncePhysics(float gravity, float velocityRatio = 1.0f);
    float Calculate(float velocity, unsigned long currentMillis);
    float Calculate(float velocity, float dT);
};
