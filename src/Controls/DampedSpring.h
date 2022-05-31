#pragma once

#include <Arduino.h>

class DampedSpring {
private:
    float springConstant;
    float damping;
    float currentVelocity = 0.001f;
    float currentPosition = 0.001f;
    float springForce = 0.0f;
    float dampingForce = 0.0f;
    float force = 0.0f;
    long previousMillis = 0;

public:
    DampedSpring() {}

    DampedSpring(const float springConstant, const float damping)
        : springConstant(-1.0f * springConstant),
          damping(-1.0f * damping) {}

    void SetConstants(const float springConstant, const float damping) {
        this->springConstant = -1.0f * springConstant;
        this->damping = -1.0f * damping;
    }

    float Calculate(const float target) {
        const long currentMillis = millis();

        const float dT = ((float)(currentMillis - previousMillis)) / 1000.0f;

        if (dT > 0.01f && dT < 2.0f) {
            springForce = springConstant * currentPosition;
            dampingForce = damping * currentVelocity;
            force = springForce - dampingForce + target;

            currentVelocity += force * dT;
            currentPosition += currentVelocity * dT;
        }

        previousMillis = currentMillis;

        return currentPosition;
    }

    float Calculate(const float target, const float dT) {
        if (!Mathematics::IsClose(target, currentPosition, 0.01f)) {
            springForce = springConstant * currentPosition;
            dampingForce = damping * currentVelocity;
            force = springForce + dampingForce + target;

            currentVelocity += force * dT;
            currentPosition += currentVelocity * dT;
        }

        return currentPosition;
    }
};