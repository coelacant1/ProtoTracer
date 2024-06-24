#pragma once

#include "../Math/Mathematics.h"

template<size_t memory>
class MaxFilter {
private:
    const int maxMemory = static_cast<int>(std::ceil(memory / 10.0));
    float values[memory];
    float maxValues[memory / 10];
    uint8_t currentAmount = 0;

    void ShiftArray(uint8_t mem, float* arr);

public:
    MaxFilter();

    float Filter(float value);
};

#include "MaxFilter.tpp"