#pragma once

#include "..\Math\Mathematics.h"

template<size_t memory>
class RunningAverageFilter {
private:
    float gain;
    float values[memory];
    uint8_t currentAmount;

public:
    RunningAverageFilter();
    RunningAverageFilter(float gain);
    void SetGain(float gain);
    float Filter(float value);
};

#include "RunningAverageFilter.tpp"
