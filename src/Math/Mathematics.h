#pragma once
#include <math.h> 
#include <WString.h>

class Mathematics {
public:
	static constexpr float EPSILON =  0.001f;
	static constexpr float MPI     =  3.14159265358979323846f;
	static constexpr float MPID180 =  0.01745329251994329576f;
	static constexpr float M180DPI = 57.29577951308232087684f;

	template<typename T>
	static T Constrain(T value, T minimum, T maximum) {
		if (value > maximum) {
			value = maximum;
		} else if (value < minimum) {
			value = minimum;
		}

		return value;
	}

	template<typename T>
	static T DegreesToRadians(T degrees) {
		return degrees * MPID180;
	}

	template<typename T>
	static T RadiansToDegrees(T radians) {
		return radians * M180DPI;
	}

	static String DoubleToCleanString(float value) {
		return String(value, 4);
	}

	static bool IsNaN(float value) {
		return value != value;
	}

	static bool IsInfinite(float value) {
		return isinf(value);
	}

	static bool IsFinite(float value) {
		return isfinite(value);
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

	template<typename T>
	static T Map(T value, T inLow, T inMax, T outMin, T outMax){
		return (value - inLow) * (outMax - outMin) / (inMax - inLow) + outMin;
	}

	template <typename T>
	static T Max(T value1, T value2) {
		return value1 > value2 ? value1 : value2;
	}

	template <typename T>
	static T Min(T value1, T value2) {
		return value1 < value2 ? value1 : value2;
	}

	template <typename T>
	static T Min(T v1, T v2, T v3) {
		return v1 < v2 ? (v1 < v3 ? v1 : v3) : (v2 < v3 ? v2 : v3);
	}

	template <typename T>
	static T Max(T v1, T v2, T v3) {
		return v1 > v2 ? (v1 > v3 ? v1 : v3) : (v2 > v3 ? v2 : v3);
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
