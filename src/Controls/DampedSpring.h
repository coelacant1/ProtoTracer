#pragma once

#include <Arduino.h>

class DampedSpring{
private:
	float currentVelocity;
	float currentPosition;
	float springConstant;
    float springForce;
    float dampingForce;
    float force;
    float damping;
    long previousMillis;

public:
    DampedSpring(){
        currentVelocity = 0.001f;
        currentPosition = 0.001f;
        springForce = 0.0f;
        dampingForce = 0.0f;
        force = 0.0f;
        previousMillis = 0;
    }

    DampedSpring(float springConstant, float damping){
	    this->springConstant = -1.0f * springConstant;
        this->damping = -1.0f * damping;
        
        currentVelocity = 0.001f;
        currentPosition = 0.001f;
        springForce = 0.0f;
        dampingForce = 0.0f;
        force = 0.0f;
        previousMillis = 0;
    }

    float GetCurrentPosition(){
        return currentPosition;
    }

    void SetConstants(float springConstant, float damping){
        this->springConstant = -1.0f * springConstant;
        this->damping = -1.0f * damping;
    }

    float Calculate(float target) {
        long currentMillis = millis();

        float dT = ((float)(currentMillis - previousMillis)) / 1000.0f;

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

    float Calculate(float target, float dT) {
        if (!Mathematics::IsClose(target, currentPosition, 0.01f)){
            springForce = springConstant * currentPosition;
            dampingForce = damping * currentVelocity;
            force = springForce + dampingForce + target;

            currentVelocity += force * dT;
            currentPosition += currentVelocity * dT;
        }

        return currentPosition;
    }
};