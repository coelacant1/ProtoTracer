/**
 * @file TestQuaternion.h
 * @brief Provides unit tests for the Quaternion class.
 *
 * The `TestQuaternion` class contains static methods for testing various functionalities
 * of the Quaternion class, including vector rotation, arithmetic operations, and utility functions.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <unity.h>
#include "../lib/ProtoTracer/Utils/Math/Quaternion.h"

/**
 * @class TestQuaternion
 * @brief Contains static test methods for the Quaternion class.
 *
 * This class provides unit tests for validating the correctness of quaternion operations,
 * including vector rotation, arithmetic operations, and various utility functions.
 */
class TestQuaternion {
private:
    /**
     * @brief Tests the vector rotation using a specific quaternion.
     *
     * @param q The quaternion used for rotation.
     * @param v The vector to be rotated.
     * @param e The expected result after rotation.
     */
    static void TestRotateVector(Quaternion q, Vector3D v, Vector3D e);

public:
    static void TestRotateVectorCase1(); ///< Tests vector rotation using a specific quaternion (Case 1).
    static void TestRotateVectorCase2(); ///< Tests vector rotation using a specific quaternion (Case 2).
    static void TestRotateVectorCase3(); ///< Tests vector rotation using a specific quaternion (Case 3).
    static void TestRotateVectorCase4(); ///< Tests vector rotation using a specific quaternion (Case 4).
    static void TestRotateVectorCase5(); ///< Tests vector rotation using a specific quaternion (Case 5).
    static void TestRotateVectorCase6(); ///< Tests vector rotation using a specific quaternion (Case 6).
    static void TestInitialization(); ///< Tests the initialization of quaternions.
    static void TestArithmeticOperations(); ///< Tests arithmetic operations (add, subtract, multiply, divide) on quaternions.
    static void TestRotationOperations(); ///< Tests quaternion-based rotation operations.
    static void TestUtilityFunctions(); ///< Tests utility functions such as normalization and inversion.
    static void TestStaticFunctions(); ///< Tests static functions like quaternion interpolation.

    /**
     * @brief Runs all the test methods in the class.
     */
    static void RunAllTests();
};
