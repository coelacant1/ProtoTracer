#pragma once

#include <Arduino.h>

class TimeStep {
private:
    unsigned long previousMillis;
    uint16_t updateInterval;

public:
    TimeStep(float frequency);

    void SetFrequency(float frequency);
    bool IsReady();
};
