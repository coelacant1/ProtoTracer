#pragma once
#include <math.h> 
#include <WString.h>

class Mathematics {
public:
	static const float EPSILON;
	static const float MPI;
	static const float MPID180;
	static const float M180DPI;

	static float Constrain(unsigned int value, unsigned int minimum, unsigned int maximum);
	static float Constrain(float value, float minimum, float maximum);
	static float DegreesToRadians(float degrees);
	static float RadiansToDegrees(float radians);
	static String DoubleToCleanString(float value);
	static bool IsNaN(float);
	static bool IsInfinite(float);
	static bool IsFinite(float);
	static bool IsClose(float, float, float);
	static int Sign(float);
	static int RoundUpWindow(int value, int multiple);
	static float Map(float value, float inLow, float inMax, float outMin, float outMax);
	static float Pow(float value, float exponent);
	static float Sqrt(float value);

	static float CosineInterpolation(float, float, float);
};
