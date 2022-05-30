#pragma once

#include "KalmanFilter.h"
#include "..\Math\Vector3D.h"

template<size_t memoryX, size_t memoryY, size_t memoryZ>
class VectorKalmanFilter {
private:
	KalmanFilter<memoryX> X;
	KalmanFilter<memoryY> Y;
	KalmanFilter<memoryZ> Z;

public:
	VectorKalmanFilter() {
		X = KalmanFilter<memoryX>();
		Y = KalmanFilter<memoryY>();
		Z = KalmanFilter<memoryZ>();
	}

	VectorKalmanFilter(float gain) {
		X = KalmanFilter<memoryX>(gain);
		Y = KalmanFilter<memoryY>(gain);
		Z = KalmanFilter<memoryZ>(gain);
	}

	Vector3D Filter(Vector3D input) {
		return Vector3D{
			X.Filter(input.X),
			Y.Filter(input.Y),
			Z.Filter(input.Z)
		};
	}

};
