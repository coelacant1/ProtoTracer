#include "Mathematics.h"

float Mathematics::MPI = atan(1) * 4;

float Mathematics::Constrain(float value, float minimum, float maximum) {
	if (value > maximum)
	{
		value = maximum;
	}
	else if (value < minimum)
	{
		value = minimum;
	}

	return value;
}

float Mathematics::DegreesToRadians(float degrees) {
	return degrees / (180.0f / MPI);
}

float Mathematics::RadiansToDegrees(float radians) {
	return radians * (180.0f / MPI);
}

String Mathematics::DoubleToCleanString(float value) {
	return String(value, 4);
}

bool Mathematics::IsNaN(float value) {
	return value != value;
}

bool Mathematics::IsInfinite(float value) {
	return value == 3.402823466e+38f;
}

bool Mathematics::IsFinite(float value) {
	return value != 3.402823466e+38f;
}

int Mathematics::Sign(float value) {
		return (0 < value) - (value < 0);
}
