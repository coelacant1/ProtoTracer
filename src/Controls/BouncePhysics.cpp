#include "BouncePhysics.h"

BouncePhysics::BouncePhysics(float gravity, float velocityRatio) :
    velocityFilter(0.4f),
    currentVelocity(0.0f),
    currentPosition(0.0f),
    velocityRatio(velocityRatio),
    gravity(gravity),
    previousMillis(0),
    previousVelocity(0.0f) {
}

float BouncePhysics::Calculate(float velocity, unsigned long currentMillis) {
    float dT = ((float)(currentMillis - previousMillis)) / 1000.0f;

    if (dT > 0.1f && dT < 2.0f) {
        currentVelocity += velocity + gravity * dT;
        currentPosition += velocityRatio * currentVelocity * dT;

        previousMillis = currentMillis;
    }

    return currentPosition;
}

float BouncePhysics::Calculate(float velocity, float dT) {
    velocity = velocityFilter.Filter(velocity);
    float changeRate = (velocity - previousVelocity) / dT;

    changeRate = changeRate < 0.0f ? 0.0f : changeRate;

    currentVelocity = changeRate - gravity * dT;
    currentPosition += velocityRatio * currentVelocity * dT;

    if (currentPosition < 0.0f) {
        currentVelocity = 0.0f;
        currentPosition = 0.0f;
    }
    else if (currentPosition > 1.0f) {
        currentVelocity = 0.0f;
        currentPosition = 1.0f;
    }

    previousVelocity = velocity;

    return currentPosition + velocity;
}
