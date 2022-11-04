#pragma once
#include <math.h> 
#include <WString.h>

class Mathematics {
public:
	static const float EPSILON;
	static const float MPI;
	static const float MPID180;
	static const float M180DPI;
	
	static uint32_t Constrain(uint32_t value, uint32_t minimum, uint32_t maximum) {
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

	static unsigned int Constrain(unsigned int value, unsigned int minimum, unsigned int maximum) {
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

	static float Constrain(float value, float minimum, float maximum) {
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

	static float DegreesToRadians(float degrees) {
		return degrees * MPID180;
	}

	static float RadiansToDegrees(float radians) {
		return radians * M180DPI;
	}

	static String DoubleToCleanString(float value) {
		return String(value, 4);
	}

	static bool IsNaN(float value) {
		return value != value;
	}

	static bool IsInfinite(float value) {
		return value == 3.402823466e+38f;
	}

	static bool IsFinite(float value) {
		return value != 3.402823466e+38f;
	}

	static bool IsClose(float v1, float v2, float epsilon){
		return fabs(v1 - v2) < epsilon;
	}

	static int Sign(float value) {
		return (0 < value) - (value < 0);
	}

	static float Pow(float value, float exponent){
		union {
			float d;
			int x[2];
		}

		u = { value };
		u.x[1] = (int)(exponent * (u.x[1] - 1072632447) + 1072632447);
		u.x[0] = 0;

		return u.d;
	}

	static float Sqrt(float value){
		return sqrtf(value);
	}

	static float Fract(float value){
		return value - floor(value);
	}

	static float CosineInterpolation(float beg, float fin, float ratio){
		float mu2 = (1.0f - cosf(ratio * MPI)) / 2.0f;
		
		return(beg * (1.0f - mu2) + fin * mu2);
	}

	static float BounceInterpolation(float beg, float fin, float ratio){
		//logarithm added with diminshing sine wave
		//log max amplitude = 1 - sine max amplitude / 2
		float baseLog = log10f(10.0f * ratio + 1.0f);
		float baseSine = sinf(16.0f * ratio) * powf((2.0f * ratio - 2.0f), 2.0f) / 4.0f / 4.0f;
		float bounce = baseLog + baseSine;

		return Map(ratio, 0.0f, bounce, beg, fin);
	}

	static float Map(float value, float inLow, float inMax, float outMin, float outMax){
		return (value - inLow) * (outMax - outMin) / (inMax - inLow) + outMin;
	}

	static float Max(float value1, float value2){
		return value1 > value2 ? value1 : value2;
	}
	
	static float Min(float value1, float value2){
		return value1 < value2 ? value1 : value2;
	}

	static int RoundUpWindow(int value, int multiple){
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
};

const float Mathematics::EPSILON = 0.001f;
const float Mathematics::MPI = atan(1) * 4;
const float Mathematics::MPID180 = MPI / 180.0f;
const float Mathematics::M180DPI = 180.0f / MPI;
