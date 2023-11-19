#pragma once

#include "..\..\Utils\Math\Mathematics.h"

class DampedSpring {
private:
    float currentVelocity;
    float currentPosition;
    float springConstant;
    float springForce;
    float dampingForce;
    float force;
    float damping;
    unsigned long previousMillis;

public:
    DampedSpring();
    DampedSpring(float springConstant, float damping);
    float GetCurrentPosition();
    void SetConstants(float springConstant, float damping);
    float Calculate(float target, unsigned long currentMillis);
    float Calculate(float target, float dT);
};
