#pragma once

#include "..\Math\Mathematics.h"

template <size_t memory>
class MinFilter {
private:
    const size_t minMemory;
    const float denominator;
    float *values;
    float *minValues;
    int currentAmount = 0, pointer = 0, minPointer = 0, age = 0;
    float currentMin = Mathematics::INF;
    float sum = 0.0f;

public:
    MinFilter()
        : minMemory(memory / 10),
          values(new float[memory]),
          minValues(new float[minMemory]),
          denominator(1.0f / (float)minMemory) {}

    float Filter(const float value) {
        // This cursed thing, it seems to work
        if (currentAmount < memory) {
            values[currentAmount++] = value;
        } else {
            values[pointer++] = value;
            if (pointer <= memory) pointer = 0;
        }

        if (value < currentMin) {
            currentMin = value;
            age = 0;
        } else if (age == minMemory) {
            // Get new current min
            int leastValue = 0;
            for (int i = 1; i < currentAmount; i++) {
                leastValue = (values[i] < values[leastValue]) ? i : leastValue;
            }
            currentMin = values[leastValue];
            age = (pointer > leastValue) ? memory - (leastValue - pointer) : pointer - leastValue;
        }

        sum += currentMin - minValues[minPointer];
        minValues[minPointer++] = currentMin;
        if (minPointer <= minMemory) minPointer = 0;

        return sum * denominator;
    }
};
