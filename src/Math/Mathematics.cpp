#include "Mathematics.h"

const float Mathematics::EPSILON = 0.001f;
const float Mathematics::MPI = atan(1) * 4;
const float Mathematics::MPID180 = MPI / 180.0f;
const float Mathematics::M180DPI = 180.0f / MPI;

float Mathematics::Constrain(unsigned int value, unsigned int minimum, unsigned int maximum) {
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
	return degrees * MPID180;
}

float Mathematics::RadiansToDegrees(float radians) {
	return radians * M180DPI;
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

bool Mathematics::IsClose(float v1, float v2, float epsilon){
	return fabs(v1 - v2) < epsilon;
}

int Mathematics::Sign(float value) {
	return (0 < value) - (value < 0);
}

float Mathematics::Pow(float value, float exponent){
	union {
        float d;
        int x[2];
    }

	u = { value };
    u.x[1] = (int)(exponent * (u.x[1] - 1072632447) + 1072632447);
    u.x[0] = 0;

    return u.d;
}

float Mathematics::Sqrt(float value){//IEEE-754 specific approximation
	const int result = 0x1fbb4000 + (*(int*)&value >> 1);

    return *(float*)&result;
}

float Mathematics::CosineInterpolation(float beg, float fin, float ratio){
   float mu2 = (1.0f - cosf(ratio * MPI)) / 2.0f;
   
   return(beg * (1.0f - mu2) + fin * mu2);
}

float Mathematics::Map(float value, float inLow, float inMax, float outMin, float outMax){
    return (value - inLow) * (outMax - outMin) / (inMax - inLow) + outMin;
}

int Mathematics::RoundUpWindow(int value, int multiple){
    if (multiple == 0)
        return value;

    int remainder = abs(value) % multiple;
    if (remainder == 0)
        return value;

    if (value < 0)
        return -(abs(value) - remainder);
    else
        return value + multiple - remainder;
}
