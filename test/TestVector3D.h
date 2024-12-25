/**
 * @file TestVector3D.h
 * @brief Provides unit tests for the Vector3D class.
 *
 * The `TestVector3D` class contains static methods for testing the functionalities
 * of the Vector3D class, including vector operations, rotations, and utility functions.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <unity.h>
#include "../lib/ProtoTracer/Utils/Math/Vector3D.h"

/**
 * @class TestVector3D
 * @brief Contains static test methods for the Vector3D class.
 *
 * This class provides unit tests to ensure the correctness of operations and transformations
 * performed by the Vector3D class, such as arithmetic operations, cross product, and magnitude calculations.
 */
class TestVector3D {
public:
    static void TestConstructor(); ///< Tests the initialization of Vector3D objects.
    static void TestAbsolute(); ///< Tests the absolute value computation for a vector.
    static void TestNormal(); ///< Tests normalization of vectors.
    static void TestAdd(); ///< Tests vector addition.
    static void TestSubtract(); ///< Tests vector subtraction.
    static void TestMultiplyVector(); ///< Tests element-wise vector multiplication.
    static void TestDivideVector(); ///< Tests element-wise vector division.
    static void TestMultiplyScalar(); ///< Tests vector multiplication by a scalar.
    static void TestDivideScalar(); ///< Tests vector division by a scalar.
    static void TestCrossProduct(); ///< Tests the cross product operation.
    static void TestUnitSphere(); ///< Tests unit sphere generation and validity.
    static void TestConstrain(); ///< Tests vector value constraining.
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
