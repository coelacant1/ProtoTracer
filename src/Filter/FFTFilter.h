#pragma once

#include "..\Math\Mathematics.h"
#include "KalmanFilter.h"
#include "MinFilter.h"
#include <Arduino.h>

class FFTFilter {
private:
    KalmanFilter<10> mv = KalmanFilter<10>(0.1f);
    MinFilter<40> minF = MinFilter<40>();
    KalmanFilter<10> output = KalmanFilter<10>(0.1f);
    float previousReading = 0.0f;
    float outputValue = 0.0f;

public:
    FFTFilter() {}

    float GetOutput() {
        return outputValue;
    }

    float Update(const float value) {
        const float changeRate = value - previousReading;
        const float amplitude = fabs(changeRate); // mv.Filter(fabs(changeRate));
        const float minimum = minF.Filter(value);
        const float normalized = value - amplitude - minimum;
        const float truncate = normalized < 0 ? 0 : output.Filter(normalized); // output.Filter(normalized);

        previousReading = value;
        return outputValue = Mathematics::Constrain(truncate, 0.0f, 1.0f);
    }
};
