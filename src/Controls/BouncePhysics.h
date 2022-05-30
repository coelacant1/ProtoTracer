#pragma once

#include <Arduino.h>
#include "..\Filter\KalmanFilter.h"
#include "..\Math\Mathematics.h"

class BouncePhysics{
private:
    KalmanFilter<10> velocityFilter = KalmanFilter<10>(0.4f);
	float currentVelocity = 0.0f;
	float currentPosition = 0.0f;
    float velocityRatio = 1.0f;
	float gravity = 0.0f;
    long previousMillis = 0;
    float previousVelocity = 0.0f;

public:
    BouncePhysics(float gravity, float velocityRatio = 1.0f){
	    this->gravity = gravity;
	    this->velocityRatio = velocityRatio;
    }

    float Calculate(float velocity) {
        long currentMillis = millis();

        float dT = ((float)(currentMillis - previousMillis)) / 1000.0f;

        if (dT > 0.1f && dT < 2.0f) {
            currentVelocity += velocity + gravity * dT;
            currentPosition += velocityRatio * currentVelocity * dT;
            
            previousMillis = currentMillis;
        }
        
        return currentPosition;
    }

    float Calculate(float velocity, float dT){
        velocity = velocityFilter.Filter(velocity);
        float changeRate = (velocity - previousVelocity) / dT;

        changeRate = changeRate < 0.0f ? 0.0f : changeRate;

        currentVelocity = changeRate - gravity * dT;
        currentPosition += velocityRatio * currentVelocity * dT;

        if(currentPosition < 0.0f){
            currentVelocity = 0.0f;
            currentPosition = 0.0f;
        }
        else if(currentPosition > 1.0f){
            currentVelocity = 0.0f;
            currentPosition = 1.0f;
        }

        previousVelocity = velocity;

        return currentPosition + velocity;
    }
};