/**
 * @file Mathematics.h
 * @brief Provides a collection of mathematical utility functions and constants.
 *
 * This header defines the Mathematics class, containing static methods and constants
 * useful for a variety of common mathematical operations, including interpolation,
 * range mapping, and basic trigonometric utilities.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <cmath>
#include <math.h>
#include <WString.h>

/**
 * @class Mathematics
 * @brief A static utility class for mathematical operations commonly used
 *        throughout embedded or real-time applications.
 *
 * This class provides:
 * - Constants (e.g., \c EPSILON, \c MPI, \c FLTMAX).
 * - Methods for numeric checks (NaN, Infinity, etc.).
 * - Interpolation methods (Lerp, Cosine, Bounce, Cubic).
 * - Mapping and constraint utilities for data normalization.
 * - Basic arithmetic wrappers (Pow, Sqrt, etc.).
 */
class Mathematics {
public:
    /** 
     * @brief A small constant used for floating-point comparisons.
     */
    static const float EPSILON;

    /**
     * @brief Mathematical constant \f$\pi\f$ (3.14159265358979323846...).
     */
    static const float MPI;

    /**
     * @brief The value of \f$\pi \div 180.0\f$, useful for converting degrees to radians.
     */
    static const float MPID180;

    /**
     * @brief The value of \f$180.0 \div \pi\f$, useful for converting radians to degrees.
     */
    static const float M180DPI;

    /**
     * @brief Maximum float value (shortcut to a large number).
     */
    static const float FLTMAX;

    /**
     * @brief Minimum float value (shortcut to a very small or near-zero number).
     */
    static const float FLTMIN;

    /**
     * @brief Converts a floating-point value to a String, removing trailing decimals if not needed.
     * @param value The float to convert.
     * @return A \c String without unnecessary trailing zeros.
     */
    static String DoubleToCleanString(float value);

    /**
     * @brief Checks if a floating-point value is NaN (Not a Number).
     * @param value The float value to check.
     * @return \c true if \p value is NaN, otherwise \c false.
     */
    static bool IsNaN(float value);

    /**
     * @brief Checks if a floating-point value is infinite.
     * @param value The float value to check.
     * @return \c true if \p value is infinite, otherwise \c false.
     */
    static bool IsInfinite(float value);

    /**
     * @brief Checks if a floating-point value is finite.
     * @param value The float value to check.
     * @return \c true if finite, otherwise \c false.
     */
    static bool IsFinite(float value);

    /**
     * @brief Checks if two values are close within a specified epsilon.
     * @param v1 The first value.
     * @param v2 The second value.
     * @param epsilon The tolerance for comparison.
     * @return \c true if \p v1 and \p v2 differ by less than \p epsilon.
     */
    static bool IsClose(float v1, float v2, float epsilon);

    /**
     * @brief Determines the sign of a floating-point value.
     * @param value The float to check.
     * @return \c +1 if \p value > 0, \c -1 if \p value < 0, and \c 0 if \p value == 0.
     */
    static int Sign(float value);

    /**
     * @brief Raises a value to a given exponent.
     * @param value The base value.
     * @param exponent The exponent to raise by.
     * @return \p value raised to \p exponent.
     */
    static float Pow(float value, float exponent);

    /**
     * @brief Computes the square root of a value.
     * @param value The float to take the square root of.
     * @return The square root of \p value.
     */
    static float Sqrt(float value);

    /**
     * @brief Returns the fractional part of a floating-point value.
     *
     * For example, Fract(3.75) = 0.75.
     *
     * @param value The float to evaluate.
     * @return The fractional component of \p value.
     */
    static float Fract(float value);

    /**
     * @brief Applies a cosine-based interpolation between two values.
     * @param beg The start value.
     * @param fin The end value.
     * @param ratio A normalized ratio (0 to 1).
     * @return The interpolated value.
     *
     * @see CosineTransition
     */
    static float CosineInterpolation(float beg, float fin, float ratio);

    /**
     * @brief A convenience alias for \c CosineInterpolation.
     * @param beg The start value.
     * @param fin The end value.
     * @param ratio A normalized ratio (0 to 1).
     * @return The interpolated value.
     *
     * @see CosineInterpolation
     */
    static float CosineTransition(float beg, float fin, float ratio);

    /**
     * @brief A 'bounce'-like interpolation between two values.
     * @param beg The start value.
     * @param fin The end value.
     * @param ratio A normalized ratio (0 to 1).
     * @return The interpolated value, with a "bounce" effect near the end.
     */
    static float BounceInterpolation(float beg, float fin, float ratio);

    /**
     * @brief Floors a floating-point value (rounds down).
     * @param f The float to floor.
     * @return The greatest integer less than or equal to \p f.
     */
	static float FFloor(float f);

    /**
     * @brief Returns the absolute value of a floating-point number.
     * @param f The float to evaluate.
     * @return \c f if \c f >= 0, otherwise -\c f.
     */
	static float FAbs(float f);

    /**
     * @brief Computes the square root of a value (internal wrapper for \c std::sqrt).
     * @param f The float to take the square root of.
     * @return The square root of \p f.
     */
	static float FSqrt(float f);

    /**
     * @brief Hermite interpolation function for smooth transitions.
     * @param t A normalized value (0 to 1).
     * @return The Hermite-interpolated value.
     */
	static float HermiteInterpolation(float t);

    /**
     * @brief Quintic interpolation function for smooth transitions.
     * @param t A normalized value (0 to 1).
     * @return The quintic-interpolated value.
     */
	static float QuinticInterpolation(float t);

    /**
     * @brief Linear interpolation between two values.
     * @param a The start value.
     * @param b The end value.
     * @param t A normalized ratio (0 to 1).
     * @return (1 - t)*a + t*b
     */
	static float Lerp(float a, float b, float t);

    /**
     * @brief Cubic interpolation across four points (a, b, c, d).
     * @param a First point.
     * @param b Second point (start).
     * @param c Third point (end).
     * @param d Fourth point.
     * @param t A normalized ratio (0 to 1).
     * @return The cubic interpolation result.
     */
	static float CubicLerp(float a, float b, float c, float d, float t);

    /**
     * @brief Performs a bilinear interpolation on a 2D grid.
     *
     * This is often used for texture sampling or heightmap sampling.
     *
     * @param scaleX Normalized X interpolation factor (0 to 1).
     * @param scaleY Normalized Y interpolation factor (0 to 1).
     * @param x1 Left X coordinate.
     * @param y1 Bottom Y coordinate.
     * @param x2 Right X coordinate.
     * @param y2 Top Y coordinate.
     * @param v11 Value at (x1, y1).
     * @param v12 Value at (x1, y2).
     * @param v21 Value at (x2, y1).
     * @param v22 Value at (x2, y2).
     * @return The interpolated value.
     */
	static float BilinearInterpolation(float scaleX, float scaleY, float x1, float y1, float x2, float y2, float v11, float v12, float v21, float v22);

    /**
     * @brief Repeats a value between 0 and 1, then mirrors back and forth (like a ping-pong).
     *
     * For example, PingPong(t) toggles between [0..1..0..1...] as \p t increases.
     *
     * @param t The time or input value.
     * @return A float between 0 and 1, repeating in a ping-pong pattern.
     */
	static float PingPong(float t);

    /**
     * @brief Rounds \p value up to the nearest multiple of \p multiple.
     * @param value The integer to round up.
     * @param multiple The multiple to round to.
     * @return \p value rounded up to the nearest multiple of \p multiple.
     */
    static int RoundUpWindow(int value, int multiple);

    /**
     * @brief Constrains a value between minimum and maximum.
     * @tparam T A numeric type (e.g., int, float).
     * @param value The value to constrain.
     * @param minimum The lower bound.
     * @param maximum The upper bound.
     * @return The constrained value within [minimum, maximum].
     */
    template<typename T>
	static T Constrain(T value, T minimum, T maximum);

    /**
     * @brief Converts degrees to radians.
     * @tparam T A numeric type.
     * @param degrees The angle in degrees.
     * @return The angle in radians.
     */
	template<typename T>
	static T DegreesToRadians(T degrees);

    /**
     * @brief Converts radians to degrees.
     * @tparam T A numeric type.
     * @param radians The angle in radians.
     * @return The angle in degrees.
     */
	template<typename T>
	static T RadiansToDegrees(T radians);

    /**
     * @brief Maps a value from one range to another.
     * @tparam T A numeric type.
     * @param value The value to map.
     * @param inLow The lower bound of the input range.
     * @param inMax The upper bound of the input range.
     * @param outMin The lower bound of the output range.
     * @param outMax The upper bound of the output range.
     * @return The mapped value within [outMin, outMax].
     */
    template<typename T>
	static T Map(T value, T inLow, T inMax, T outMin, T outMax);

    /**
     * @brief Returns the maximum of two values.
     * @tparam T A numeric type.
     * @param value1 The first value.
     * @param value2 The second value.
     * @return \c value1 if \c value1 >= \c value2, otherwise \c value2.
     */
	template <typename T>
	static T Max(T value1, T value2);

    /**
     * @brief Returns the minimum of two values.
     * @tparam T A numeric type.
     * @param value1 The first value.
     * @param value2 The second value.
     * @return \c value1 if \c value1 <= \c value2, otherwise \c value2.
     */
	template <typename T>
	static T Min(T value1, T value2);

    /**
     * @brief Returns the minimum of three values.
     * @tparam T A numeric type.
     * @param v1 The first value.
     * @param v2 The second value.
     * @param v3 The third value.
     * @return The smallest of \p v1, \p v2, and \p v3.
     */
	template <typename T>
	static T Min(T v1, T v2, T v3);

    /**
     * @brief Returns the maximum of three values.
     * @tparam T A numeric type.
     * @param v1 The first value.
     * @param v2 The second value.
     * @param v3 The third value.
     * @return The largest of \p v1, \p v2, and \p v3.
     */
	template <typename T>
	static T Max(T v1, T v2, T v3);

    /**
     * @brief Combines Constrain and Map in one step:
     *        first maps \p value from [inLow, inMax] to [outMin, outMax],
     *        then constrains it to stay within [outMin, outMax].
     * @tparam T A numeric type.
     * @param value The value to map/constrain.
     * @param inLow The lower bound of the input range.
     * @param inMax The upper bound of the input range.
     * @param outMin The lower bound of the output range.
     * @param outMax The upper bound of the output range.
     * @return The mapped value, constrained between \p outMin and \p outMax.
     */
	template<typename T>
	static T ConstrainMap(T value, T inLow, T inMax, T outMin, T outMax);

};

// Pull in template implementations.
#include "Mathematics.tpp"
