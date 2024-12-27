/**
 * @file TestRotationMatrix.h
 * @brief Provides unit tests for the RotationMatrix class.
 *
 * The `TestRotationMatrix` class contains static methods for testing the functionalities
 * of the RotationMatrix class, including identity, axis-specific rotations, and general rotations.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <unity.h>
#include "../lib/ProtoTracer/Utils/Math/RotationMatrix.h"

/**
 * @class TestRotationMatrix
 * @brief Contains static test methods for the RotationMatrix class.
 *
 * This class provides unit tests to ensure the correctness of operations and transformations
 * performed by the RotationMatrix class, such as rotations about specific axes and matrix inversions.
 */
class TestRotationMatrix {
public:
    static void TestIdentityMatrix(); ///< Tests the creation of an identity rotation matrix.
    static void TestRotationXAxis(); ///< Tests rotation about the X-axis.
    static void TestRotationYAxis(); ///< Tests rotation about the Y-axis.
    static void TestRotationZAxis(); ///< Tests rotation about the Z-axis.
    static void TestGeneralRotation(); ///< Tests a general rotation using an arbitrary axis and angle.
    static void TestInverseRotation(); ///< Tests the inversion of a rotation matrix.

    /**
     * @brief Runs all the test methods in the class.
     */
    static void RunAllTests();
};
