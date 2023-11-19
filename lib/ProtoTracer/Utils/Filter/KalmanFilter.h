#pragma once

template<typename T>
class KalmanFilter {
private:
    T processNoise;
    T sensorNoise;
    T estimation;
    T errorCovariance;

public:
    KalmanFilter(T processNoise, T sensorNoise, T errorCovariance);

    T Filter(T value);
};

#include "KalmanFilter.tpp"
