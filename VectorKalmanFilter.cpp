#include "VectorKalmanFilter.h"

VectorKalmanFilter::VectorKalmanFilter() {
	X = KalmanFilter();
	Y = KalmanFilter();
	Z = KalmanFilter();
}

VectorKalmanFilter::VectorKalmanFilter(float gain, int memory) {
	X = KalmanFilter(gain, memory);
	Y = KalmanFilter(gain, memory);
	Z = KalmanFilter(gain, memory);
}

VectorKalmanFilter::VectorKalmanFilter(Vector3D gain, Vector3D memory) {
	X = KalmanFilter(gain.X, (int)memory.X);
	Y = KalmanFilter(gain.Y, (int)memory.Y);
	Z = KalmanFilter(gain.Z, (int)memory.Z);
}

Vector3D VectorKalmanFilter::Filter(Vector3D input) {
	return Vector3D{
		X.Filter(input.X),
		Y.Filter(input.Y),
		Z.Filter(input.Z)
	};
}
