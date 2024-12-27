/**
 * @file TestRotation.h
 * @brief Provides unit tests for the Rotation class.
 *
 * The `TestRotation` class contains static methods for testing various functionalities
 * of the Rotation class, including constructors, conversions, and utility functions.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <unity.h>
#include "../lib/ProtoTracer/Utils/Math/Rotation.h"

/**
 * @class TestRotation
 * @brief Contains static test methods for the Rotation class.
 *
 * This class provides unit tests for validating the correctness of rotation operations,
 * including conversions between different representations and constructor initialization.
 */
class TestRotation {
private:
    /**
     * @brief Tests the conversion of Euler angles (XYZ) to a quaternion.
     *
     * @param xyz The Euler angles in XYZ order.
     * @param q The expected quaternion after conversion.
     */
    static void TestEulerAngleConversionXYZ(Vector3D xyz, Quaternion q);

public:
    static void TestDefaultConstructor(); ///< Tests the default constructor of the Rotation class.
    static void TestQuaternionConstructor(); ///< Tests the quaternion-based constructor of the Rotation class.
    static void TestAxisAngleConstructor(); ///< Tests the axis-angle-based constructor of the Rotation class.
    static void TestDirectionAngleConstructor(); ///< Tests the direction-angle-based constructor of the Rotation class.
    static void TestRotationMatrixConstructor(); ///< Tests the rotation matrix-based constructor of the Rotation class.
    static void TestVectorConstructor(); ///< Tests the vector-based constructor of the Rotation class.
    static void TestEulerAnglesConstructor(); ///< Tests the Euler angles-based constructor of the Rotation class.
    static void TestYawPitchRollConstructor(); ///< Tests the yaw-pitch-roll-based constructor of the Rotation class.
    static void TestRotationMatrixToEulerAngles(); ///< Tests the conversion of a rotation matrix to Euler angles.
//    static void TestEulerAnglesToRotationMatrix(); ///< Tests the conversion of Euler angles to a rotation matrix (commented out).
//    static void TestQuaternionFromDirectionVectors(); ///< Tests the creation of a quaternion from direction vectors (commented out).

    /**
     * @brief Runs all the test methods in the class.
     */
    static void RunAllTests();
};
