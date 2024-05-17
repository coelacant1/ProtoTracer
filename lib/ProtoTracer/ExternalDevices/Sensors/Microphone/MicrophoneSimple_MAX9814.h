#pragma once
// Configured for 60dB gain

#include <Arduino.h>
#include "../../../Utils/Math/Mathematics.h"
#include "../../../Utils/Filter/RunningAverageFilter.h"
#include "../../../Utils/Filter/MinFilter.h"

class MicrophoneSimple {
private:
    uint8_t pin;
    RunningAverageFilter<5> mv = RunningAverageFilter<5>(0.2f);
    MinFilter<100> minF = MinFilter<100>();
    RunningAverageFilter<5> output = RunningAverageFilter<5>(0.2f);
    float previousReading = 0.0f;
    float gain = 1.0f;
    float clipping = 1.0f;
    long previousMillis = 0;
    long startMillis = 0;
    float currentValue = 0.0f;

public:
    MicrophoneSimple();
    MicrophoneSimple(uint8_t pin, float gain = 1.0f, float clipping = 1.0f);
    float GetCurrentValue();
    float Update();
    float Update(float read);
};
