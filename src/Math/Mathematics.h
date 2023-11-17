#pragma once
#include <math.h>
#include <WString.h>

class Mathematics {
public:
    static constexpr float EPSILON = 0.001f;
    static constexpr float MPI = 3.14159265358979323846f;
    static constexpr float MPID180 = 0.01745329251994329576f;
    static constexpr float M180DPI = 57.29577951308232087684f;
    static constexpr float FLTMAX = __FLT_MAX__;
    static constexpr float FLTMIN = __FLT_MIN__;


    static String DoubleToCleanString(float value);

    static bool IsNaN(float value);

    static bool IsInfinite(float value);

    static bool IsFinite(float value);

    static bool IsClose(float v1, float v2, float epsilon);

    static int Sign(float value);

    static float Pow(float value, float exponent);

    static float Sqrt(float value);

    static float Fract(float value);

    static float CosineInterpolation(float beg, float fin, float ratio);

    static float CosineTransition(float beg, float fin, float ratio);

    static float BounceInterpolation(float beg, float fin, float ratio);

    static int RoundUpWindow(int value, int multiple);
	
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

    template<typename T>
	static T Map(T value, T inLow, T inMax, T outMin, T outMax) {
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

	template<typename T>
	static T ConstrainMap(T value, T inLow, T inMax, T outMin, T outMax) {
		T mappedValue = (value - inLow) * (outMax - outMin) / (inMax - inLow) + outMin;
		return Constrain(mappedValue, outMin, outMax);
	}
};
