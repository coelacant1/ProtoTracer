#pragma once

#include <Arduino.h>

class DampedSpring {
private:
    float currentVelocity = 0.0f;
    float currentPosition = 1.0f;
    float springConstant = 0.0f;
    float damping = 0.0f;
    unsigned long previousMillis = 0;

public:
    DampedSpring(const float springConstant, const float damping)
        : springConstant(springConstant),
          damping(damping) {}

    float Calculate(const float target) {
        const unsigned long currentMillis = millis();

        const float dT = ((float)(currentMillis - previousMillis)) * 0.001f; // / 1000.0f

        if (dT > 0.1f && dT < 2.0f) {
            const float springForce = -springConstant * currentPosition;
            const float dampingForce = damping * currentVelocity;
            const float force = springForce - dampingForce + target;

            currentVelocity += force * dT;
            currentPosition += currentVelocity * dT;

            previousMillis = currentMillis;
        }

        return currentPosition;
    }

    float Calculate(const float target, const float dT) {
        const float springForce = -springConstant * currentPosition;
        const float dampingForce = damping * currentVelocity;
        const float force = springForce - dampingForce + target;

        currentVelocity += force * dT;
        currentPosition += currentVelocity * dT;

        return currentPosition;
    }
};