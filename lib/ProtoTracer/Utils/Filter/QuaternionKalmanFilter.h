#pragma once

#include "../Math/Quaternion.h"

class QuaternionKalmanFilter {
private:
    float gain;
    int memory;
    Quaternion* values;

    int currentAmount = 0;

    Quaternion* ShiftArray(Quaternion arr[]);

public:
    QuaternionKalmanFilter();
    QuaternionKalmanFilter(float gain, int memory);

    Quaternion Filter(Quaternion value);

    ~QuaternionKalmanFilter();
};
