#pragma once

#include "../Math/Mathematics.h"

template <size_t sampleSize>
class PeakDetection {
private:
    uint8_t lag;

    float threshold;
    float influence;
    float filData[sampleSize];
    float avg[sampleSize];
    float std[sampleSize];

    void GetStdDev(uint8_t start, uint8_t length, float* data, float& avgRet, float& stdRet);

public:
    PeakDetection(uint8_t lag = 12, float threshold = 0.75f, float influence = 0.5f);

    void Calculate(float* data, bool* peaks);
};

#include "PeakDetection.tpp"