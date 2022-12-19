#pragma once

template<typename T>
class KalmanFilter {
private:
	T processNoise;
	T sensorNoise;
	T estimation;
	T errorCovariance;

public:
	KalmanFilter(T processNoise, T sensorNoise, T errorCovariance) {
		this->processNoise = processNoise;
        this->sensorNoise = sensorNoise;
        this->estimation = 0;
        this->errorCovariance = errorCovariance;
	}

	float Filter(float value) {
		// Prediction
        errorCovariance += processNoise;

        // Update
        T kalmanGain = errorCovariance / (errorCovariance + sensorNoise);
        estimation += kalmanGain * (value - estimation);
        errorCovariance *= T(1) - kalmanGain;

		return estimation;
	}
};
