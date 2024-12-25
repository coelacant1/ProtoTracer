/**
 * @file TestMathematics.h
 * @brief Provides unit tests for the Mathematics utility functions.
 *
 * The `TestMathematics` class contains static methods for testing various mathematical
 * operations and utility functions provided by the Mathematics library.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <unity.h>
#include "../lib/ProtoTracer/Utils/Math/Mathematics.h"

/**
 * @class TestMathematics
 * @brief Contains static test methods for the Mathematics utility functions.
 *
 * This class provides unit tests for validating the correctness of various
 * mathematical operations implemented in the Mathematics library.
 */
class TestMathematics {
public:
    static void TestDoubleToCleanString(); ///< Tests the conversion of double values to clean string representations.
    static void TestIsNaN(); ///< Tests if the `Mathematics::IsNaN` function correctly identifies NaN values.
    static void TestIsInfinite(); ///< Tests if the `Mathematics::IsInfinite` function correctly identifies infinite values.
    static void TestIsFinite(); ///< Tests if the `Mathematics::IsFinite` function correctly identifies finite values.
    static void TestIsClose(); ///< Tests if the `Mathematics::IsClose` function correctly identifies close values.
    static void TestSign(); ///< Tests if the `Mathematics::Sign` function correctly identifies the sign of a number.
    static void TestPow(); ///< Tests the `Mathematics::Pow` function for power calculations.
    static void TestSqrt(); ///< Tests the `Mathematics::Sqrt` function for square root calculations.
    static void TestFract(); ///< Tests the `Mathematics::Fract` function for fractional part extraction.
    static void TestCosineInterpolation(); ///< Tests the `Mathematics::CosineInterpolation` function for smooth transitions.
    static void TestCosineTransition(); ///< Tests the `Mathematics::CosineTransition` function for smooth cosine-based transitions.
    static void TestBounceInterpolation(); ///< Tests the `Mathematics::BounceInterpolation` function for bounce effects.
    static void TestFFloor(); ///< Tests the `Mathematics::FFloor` function for floor operations.
    static void TestFAbs(); ///< Tests the `Mathematics::FAbs` function for absolute value calculations.
    static void TestFSqrt(); ///< Tests the `Mathematics::FSqrt` function for square root calculations.
    static void TestHermiteInterpolation(); ///< Tests the `Mathematics::HermiteInterpolation` function for smooth transitions.
    static void TestQuinticInterpolation(); ///< Tests the `Mathematics::QuinticInterpolation` function for smooth transitions.
    static void TestLerp(); ///< Tests the `Mathematics::Lerp` function for linear interpolation.
    static void TestCubicLerp(); ///< Tests the `Mathematics::CubicLerp` function for cubic interpolation.
    static void TestBilinearInterpolation(); ///< Tests the `Mathematics::BilinearInterpolation` function for 2D interpolation.
    static void TestPingPong(); ///< Tests the `Mathematics::PingPong` function for repeating values.
    static void TestRoundUpWindow(); ///< Tests the `Mathematics::RoundUpWindow` function for rounding values to a window.
    static void TestConstrain(); ///< Tests the `Mathematics::Constrain` function for value clamping.
    static void TestDegreesToRadians(); ///< Tests the `Mathematics::DegreesToRadians` function for angle conversion.
    static void TestRadiansToDegrees(); ///< Tests the `Mathematics::RadiansToDegrees` function for angle conversion.
    static void TestMap(); ///< Tests the `Mathematics::Map` function for value mapping.
    static void TestMax(); ///< Tests the `Mathematics::Max` function for finding the maximum value.
    static void TestMin(); ///< Tests the `Mathematics::Min` function for finding the minimum value.
    static void TestConstrainMap(); ///< Tests the `Mathematics::ConstrainMap` function for constrained value mapping.

    /**
     * @brief Runs all the test methods in the class.
     */
    static void RunAllTests();
};
