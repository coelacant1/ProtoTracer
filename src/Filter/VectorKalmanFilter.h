#pragma once

#include "KalmanFilter.h"
#include "..\Math\Vector3D.h"

template<typename T>
class VectorKalmanFilter {
private:
	KalmanFilter<T> X;
	KalmanFilter<T> Y;
	KalmanFilter<T> Z;

public:
	VectorKalmanFilter(T processNoise, T sensorNoise T errorCovariance) {
		X = KalmanFilter<T>(processNoise, sensorNoise, errorCovariance);
		Y = KalmanFilter<T>(processNoise, sensorNoise, errorCovariance);
		Z = KalmanFilter<T>(processNoise, sensorNoise, errorCovariance);
	}

	Vector3D Filter(Vector3D input) {
		return Vector3D{
			X.Filter(input.X),
			Y.Filter(input.Y),
			Z.Filter(input.Z)
		};
	}

};
