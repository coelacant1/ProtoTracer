#include "VectorKalmanFilter.h"

template<typename T>
VectorKalmanFilter<T>::VectorKalmanFilter(T processNoise, T sensorNoise, T errorCovariance) {
    X = KalmanFilter<T>(processNoise, sensorNoise, errorCovariance);
    Y = KalmanFilter<T>(processNoise, sensorNoise, errorCovariance);
    Z = KalmanFilter<T>(processNoise, sensorNoise, errorCovariance);
}

template<typename T>
Vector3D VectorKalmanFilter<T>::Filter(Vector3D input) {
    return Vector3D{
        X.Filter(input.X),
        Y.Filter(input.Y),
        Z.Filter(input.Z)
    };
}
