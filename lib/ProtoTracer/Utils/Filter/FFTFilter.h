#pragma once

#include "RunningAverageFilter.h"
#include "..\Math\Mathematics.h"

class FFTFilter {
private:
    RunningAverageFilter<20> minKF = RunningAverageFilter<20>(0.05f);
    float outputValue = 0.0f;

public:
    FFTFilter();

    float GetOutput();
    float Filter(float value);
};

#include "FFTFilter.tpp"
