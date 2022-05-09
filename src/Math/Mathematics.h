#pragma once
#include <math.h> 
#include <WString.h>

namespace Mathematics {
	const float EPSILON = 0.001f;
	const float MPI = acos(-1.0f);
	const float MPID180 = MPI / 180.0f;
	const float M180DPI = 180.0f / MPI;

	uint32_t Constrain(const uint32_t value, const uint32_t minimum, const uint32_t maximum) const {
		if (value > maximum) return maximum;
		if (value < minimum) return minimum;

		return value;
	}

	unsigned int Constrain(const unsigned int value, const unsigned int minimum, const unsigned int maximum) const {
		if (value > maximum) return maximum;
		if (value < minimum) return minimum;

		return value;
	}

	float Constrain(const float value, const float minimum, const float maximum) const {
		if (value > maximum) return maximum;
		if (value < minimum) return minimum;

		return value;
	}

	float DegreesToRadians(const float degrees) const {
		return degrees * MPID180;
	}

	float RadiansToDegrees(const float radians) const {
		return radians * M180DPI;
	}

	String DoubleToCleanString(const float value) const {
		return String(value, 4);
	}

	bool IsNaN(const float value) const {
		return value != value;
	}

	bool IsInfinite(const float value) const {
		return value == 3.402823466e+38f;
	}

	bool IsFinite(const float value) const {
		return value != 3.402823466e+38f;
	}

	bool IsClose(const float v1, const float v2, const float epsilon) const {
		return fabs(v1 - v2) < epsilon;
	}

	int Sign(const float value) const {
		return (0 < value) - (value < 0);
	}

	float Pow(const float value, const float exponent) const {
		union {
			float d;
			int x[2];
		}

		u = { value };
		u.x[1] = (int)(exponent * (u.x[1] - 1072632447) + 1072632447);
		u.x[0] = 0;

		return u.d;
	}

	float Sqrt(float value) const {//IEEE-754 specific approximation
		const int result = 0x1fbb4000 + (*(int*)&value >> 1);

		return *(float*)&result;
	}

	float Fract(float value) const {
		return value - floor(value);
	}

	float CosineInterpolation(float beg, float fin, float ratio) const {
		const float mu2 = (1.0f - cosf(ratio * MPI)) / 2.0f;
		
		return(beg * (1.0f - mu2) + fin * mu2);
	}

	float BounceInterpolation(const float beg, const float fin, const float ratio) const {
		//logarithm added with diminshing sine wave
		//log max amplitude = 1 - sine max amplitude / 2
		const float baseLog = log10f(10.0f * ratio + 1.0f);
		const float t = 2.0f * ratio - 2.0f;
		const float baseSine = sinf(16.0f * ratio) * t * t / 16.0f;
		const float bounce = baseLog + baseSine;

		return Map(ratio, 0.0f, bounce, beg, fin);
	}

	float Map(const float value, const float inLow, const float inMax, const float outMin, const float outMax) const {
		return (value - inLow) * (outMax - outMin) / (inMax - inLow) + outMin;
	}

	int RoundUpWindow(const int value, const int multiple) const {
		if (multiple == 0) return value;

		int remainder = abs(value) % multiple;
		if (remainder == 0) return value;

		if (value < 0) return -(abs(value) - remainder);
		return value + multiple - remainder;
	}
};