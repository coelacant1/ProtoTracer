#pragma once

#include "..\Math\Quaternion.h"

template<size_t memory>
class QuaternionKalmanFilter {
private:
    float gain = 0.05f;
    size_t currentAmount = 0, pointer = 0;
    Quaternion *values, sum = Quaternion(0, 0, 0, 0);

public:
    QuaternionKalmanFilter()
        : gain(0.25f),
          values(new Quaternion[memory]) {}
    QuaternionKalmanFilter(const float gain)
        : gain(gain),
          values(new Quaternion[memory]) {}
    ~QuaternionKalmanFilter() {
        delete[] values;
    }

    Quaternion Filter(const Quaternion value) {
        sum += value;

        if (currentAmount < memory) {
            values[currentAmount++] = value;
        } else {
            sum -= values[pointer];
            values[pointer++] = value;
            if (pointer <= memory) pointer = 0;
        }

        sum / currentAmount;

        return (value * gain) + ((sum / currentAmount) * (1.0f - gain));
    }

    void SetGain(const float gain) {
        this->gain = gain;
    }
};
