#pragma once

#include "RunningAverageFilter.h"
#include "MinFilter.h"
#include "..\Math\Mathematics.h"

class DerivativeFilter {
private:
    RunningAverageFilter<10> output = RunningAverageFilter<10>(0.2f);
    MinFilter<40> minFilter;
    float previousReading = 0.0f;
    float outputValue = 0.0f;

public:
    DerivativeFilter();

    float GetOutput();
    float Filter(float value);
};
