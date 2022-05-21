#pragma once

#include <Arduino.h>

class DampedSpring{
private:
	float currentVelocity = 0.0f;
	float currentPosition = 1.0f;
	float springConstant = 0.0f;
    float damping = 0.0f;
    long previousMillis = 0;

public:
    DampedSpring(float springConstant, float dampin){
	    this->springConstant = springConstant;
        this->damping = damping;
    }

    float Calculate(float target) {
        long currentMillis = millis();

        float dT = ((float)(currentMillis - previousMillis)) / 1000.0f;

        if (dT > 0.1f && dT < 2.0f) {
            float springForce = -springConstant * currentPosition;
            float dampingForce = damping * currentVelocity;
            float force = springForce - dampingForce + target;

            currentVelocity += force * dT;
            currentPosition += currentVelocity * dT;

            previousMillis = currentMillis;
        }

        return currentPosition;
    }

    float Calculate(float target, float dT) {
        float springForce = -springConstant * currentPosition;
        float dampingForce = damping * currentVelocity;
        float force = springForce - dampingForce + target;

        currentVelocity += force * dT;
        currentPosition += currentVelocity * dT;
        
        return currentPosition;
    }
};