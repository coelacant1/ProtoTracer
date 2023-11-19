#pragma once

template<typename T>
KalmanFilter<T>::KalmanFilter(T processNoise, T sensorNoise, T errorCovariance) {
    this->processNoise = processNoise;
    this->sensorNoise = sensorNoise;
    this->estimation = 0;
    this->errorCovariance = errorCovariance;
}

template<typename T>
T KalmanFilter<T>::Filter(T value) {
    // Prediction
    errorCovariance += processNoise;

    // Update
    T kalmanGain = errorCovariance / (errorCovariance + sensorNoise);
    estimation += kalmanGain * (value - estimation);
    errorCovariance *= T(1) - kalmanGain;

    return estimation;
}
