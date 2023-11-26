#include "SHARPGP2Y.h"

SHARPGP2Y::SHARPGP2Y(uint8_t pin) : pin(pin) {
    pinMode(pin, INPUT);
}

float SHARPGP2Y::ReadingToDistance(uint8_t reading) {
    float value = float(reading);
    float value2 = value * value;

    return 2583.711122992086f
        - 20.19789785547f * value + 0.071746539329f * value2
        - 0.000115854182f * value2 * value + 0.000000068590f * value2 * value2;
}

float SHARPGP2Y::GetDistance() {
    return distance;
}

float SHARPGP2Y::Update() {
    noInterrupts();
    float read = analogRead(pin);
    interrupts();
    distance = rAF.Filter(ReadingToDistance(static_cast<uint8_t>(read)));

    return distance;
}
