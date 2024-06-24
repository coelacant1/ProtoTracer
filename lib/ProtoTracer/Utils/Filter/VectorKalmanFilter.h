#pragma once

#include "KalmanFilter.h"
#include "../Math/Vector3D.h"

template<typename T>
class VectorKalmanFilter {
private:
    KalmanFilter<T> X;
    KalmanFilter<T> Y;
    KalmanFilter<T> Z;

public:
    VectorKalmanFilter(T processNoise, T sensorNoise, T errorCovariance);
    Vector3D Filter(Vector3D input);
};
