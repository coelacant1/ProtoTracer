/**
 * @file TestVector2D.h
 * @brief Provides unit tests for the Vector2D class.
 *
 * The `TestVector2D` class contains static methods for testing the functionalities
 * of the Vector2D class, including vector operations, rotation, and utility functions.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <unity.h>
#include "../lib/ProtoTracer/Utils/Math/Vector2D.h"

/**
 * @class TestVector2D
 * @brief Contains static test methods for the Vector2D class.
 *
 * This class provides unit tests to ensure the correctness of operations and transformations
 * performed by the Vector2D class, such as arithmetic operations, rotations, and bounds checking.
 */
class TestVector2D {
public:
    static void TestConstructor(); ///< Tests the initialization of Vector2D objects.
    static void TestAbsolute(); ///< Tests the absolute value computation for a vector.
    static void TestNormal(); ///< Tests normalization of vectors.
    static void TestAdd(); ///< Tests vector addition.
    static void TestSubtract(); ///< Tests vector subtraction.
    static void TestMultiplyVector(); ///< Tests element-wise vector multiplication.
    static void TestDivideVector(); ///< Tests element-wise vector division.
    static void TestMultiplyScalar(); ///< Tests vector multiplication by a scalar.
    static void TestDivideScalar(); ///< Tests vector division by a scalar.
    static void TestCrossProduct(); ///< Tests the cross product operation.
    static void TestUnitCircle(); ///< Tests unit circle generation and validity.
    static void TestConstrain(); ///< Tests vector value constraining.
    static void TestMinimum(); ///< Tests computation of the minimum value between vectors.
    static void TestMaximum(); ///< Tests computation of the maximum value between vectors.
    static void TestRotate(); ///< Tests vector rotation.
    static void TestCheckBounds(); ///< Tests bounds checking for vectors.
    static void TestMagnitude(); ///< Tests magnitude calculation for vectors.
    static void TestDotProduct(); ///< Tests the dot product operation.
    static void TestCalculateEuclideanDistance(); ///< Tests calculation of Euclidean distance between vectors.
    static void TestIsEqual(); ///< Tests equality checks between vectors.
    static void TestToString(); ///< Tests the string representation of vectors.

    /**
     * @brief Runs all the test methods in the class.
     */
    static void RunAllTests();
};
