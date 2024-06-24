#pragma once

#include <cmath>
#include <math.h>
#include <WString.h>

class Mathematics {
public:
    static const float EPSILON;
    static const float MPI;
    static const float MPID180;
    static const float M180DPI;
    static const float FLTMAX;
    static const float FLTMIN;

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
	static float FFloor(float f);
	static float FAbs(float f);
	static float FSqrt(float f);
	static float HermiteInterpolation(float t);
	static float QuinticInterpolation(float t);
	static float Lerp(float a, float b, float t);
	static float CubicLerp(float a, float b, float c, float d, float t);
	
	static float BilinearInterpolation(float scaleX, float scaleY, float x1, float y1, float x2, float y2, float v11, float v12, float v21, float v22);
	static float PingPong(float t);

    static int RoundUpWindow(int value, int multiple);
	
    template<typename T>
	static T Constrain(T value, T minimum, T maximum);

	template<typename T>
	static T DegreesToRadians(T degrees);

	template<typename T>
	static T RadiansToDegrees(T radians);

    template<typename T>
	static T Map(T value, T inLow, T inMax, T outMin, T outMax);

	template <typename T>
	static T Max(T value1, T value2);

	template <typename T>
	static T Min(T value1, T value2);

	template <typename T>
	static T Min(T v1, T v2, T v3);

	template <typename T>
	static T Max(T v1, T v2, T v3);

	template<typename T>
	static T ConstrainMap(T value, T inLow, T inMax, T outMin, T outMax);

};

#include "Mathematics.tpp"