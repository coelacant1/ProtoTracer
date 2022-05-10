#pragma once

#include "KalmanFilter.h"
#include "..\Math\Vector3D.h"

class VectorKalmanFilter {
private:
	KalmanFilter X;
	KalmanFilter Y;
	KalmanFilter Z;

public:
	VectorKalmanFilter()
		: X(KalmanFilter()),
		  Y(KalmanFilter()),
		  Z(KalmanFilter()) {}
	VectorKalmanFilter(const float gain, const int memory)
		: X(KalmanFilter(gain, memory)),
		  Y(KalmanFilter(gain, memory)),
		  Z(KalmanFilter(gain, memory)) {}
	VectorKalmanFilter(const Vector3D gain, const Vector3D memory)
		: X(KalmanFilter(gain.X, (int)memory.X)),
		  Y(KalmanFilter(gain.Y, (int)memory.Y)),
		  Z(KalmanFilter(gain.Z, (int)memory.Z)) {}

	Vector3D Filter(const Vector3D input) {
		return Vector3D{
			X.Filter(input.X),
			Y.Filter(input.Y),
			Z.Filter(input.Z)
		};
	}
};
