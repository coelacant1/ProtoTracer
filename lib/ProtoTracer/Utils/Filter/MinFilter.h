#pragma once

#include "../Math/Mathematics.h"

template<size_t memory>
class MinFilter {
private:
    const int minMemory = static_cast<int>(std::ceil(memory / 10.0));
    float values[memory];
    float minValues[memory / 10];
    uint8_t currentAmount = 0;
    bool ignoreSame;

    void ShiftArray(uint8_t mem, float* arr);

public:
    MinFilter(bool ignoreSame = true);

    float Filter(float value);
};

#include "MinFilter.tpp"
