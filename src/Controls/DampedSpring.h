#pragma once

#include <Arduino.h>

class DampedSpring{
private:
	float currentVelocity = 0.0;
	float currentPosition = 0.0;
	float springConstant;
    float damping;
    float mass = 10.0f;
    unsigned long previousMillis;

public:
    DampedSpring(float springConstant, float damping){
	    this->springConstant = springConstant;
        this->damping = damping;

        previousMillis = millis();
    }

    float Calculate(float target) {
        unsigned long currentMillis = millis();
        float dT = 0.25f;//((float)(currentMillis - previousMillis)) / 100.0f;

        //target = gravity

        float springForce = -springConstant * currentPosition;
        float dampingForce = damping * currentVelocity;
        float force = springForce - dampingForce + target;// + target * mass - dampingForce;
        float acceleration = force / 1.0f;

        currentVelocity += acceleration * dT;
        currentPosition += currentVelocity * dT;
        
        previousMillis = currentMillis;

        return currentPosition;
    }
};