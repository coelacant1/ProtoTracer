#pragma once

#include <Arduino.h>
#include "..\..\..\Utils\Math\Mathematics.h"
#include "..\..\..\Utils\Filter\RunningAverageFilter.h"
#include "..\..\..\Utils\Filter\MinFilter.h"

class MicrophoneSimple {
private:
    uint8_t pin;
    RunningAverageFilter<40> mv = RunningAverageFilter<40>(0.075f);
    MinFilter<100> minF = MinFilter<100>();
    RunningAverageFilter<10> output = RunningAverageFilter<10>(0.1f);
    float previousReading = 0.0f;
    long previousMillis = 0;
    long startMillis = 0;

public:
    MicrophoneSimple(uint8_t pin);
    float Update();
};
