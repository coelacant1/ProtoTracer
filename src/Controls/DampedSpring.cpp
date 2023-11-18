#include "DampedSpring.h"

DampedSpring::DampedSpring() :
    currentVelocity(0.001f),
    currentPosition(0.001f),
    springConstant(0.0f),
    springForce(0.0f),
    dampingForce(0.0f),
    force(0.0f),
    damping(0.0f),
    previousMillis(0) {
}

DampedSpring::DampedSpring(float springConstant, float damping) :
    currentVelocity(0.001f),
    currentPosition(0.001f),
    springConstant(-1.0f * springConstant),
    springForce(0.0f),
    dampingForce(0.0f),
    force(0.0f),
    damping(-1.0f * damping),
    previousMillis(0) {
}

float DampedSpring::GetCurrentPosition() {
    return currentPosition;
}

void DampedSpring::SetConstants(float springConstant, float damping) {
    this->springConstant = -1.0f * springConstant;
    this->damping = -1.0f * damping;
}

float DampedSpring::Calculate(float target, unsigned long currentMillis) {
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

float DampedSpring::Calculate(float target, float dT) {
    if (!Mathematics::IsClose(target, currentPosition, 0.01f)) {
        springForce = springConstant * currentPosition;
        dampingForce = damping * currentVelocity;
        force = springForce + dampingForce + target;

        currentVelocity += force * dT;
        currentPosition += currentVelocity * dT;
    }

    return currentPosition;
}
