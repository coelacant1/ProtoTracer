/**
 * @file Rotation.h
 * @brief Defines the Rotation class for handling 3D rotations using various representations.
 *
 * The Rotation class provides conversions between different rotation representations,
 * including quaternions, axis-angle, direction-angle, rotation matrices, Euler angles,
 * and yaw-pitch-roll.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "AxisAngle.h"
#include "DirectionAngle.h"
#include "EulerAngles.h"
#include "EulerConstants.h"
#include "Quaternion.h"
#include "RotationMatrix.h"
#include "Vector3D.h"
#include "YawPitchRoll.h"

/**
 * @class Rotation
 * @brief Handles 3D rotations and conversions between various rotation representations.
 *
 * The `Rotation` class simplifies the process of converting between multiple rotation representations,
 * enabling flexible handling of 3D rotations in applications such as graphics and robotics.
 */
class Rotation {
private:
    Quaternion quaternionRotation; ///< Quaternion representation of the rotation.

    /**
     * @brief Converts an AxisAngle to a Quaternion.
     *
     * @param axisAngle The axis-angle representation.
     * @return The corresponding quaternion.
     */
    Quaternion AxisAngleToQuaternion(const AxisAngle& axisAngle);

    /**
     * @brief Converts a DirectionAngle to a Quaternion.
     *
     * @param directionAngle The direction-angle representation.
     * @return The corresponding quaternion.
     */
    Quaternion DirectionAngleToQuaternion(const DirectionAngle& directionAngle);

    /**
     * @brief Converts a RotationMatrix to a Quaternion.
     *
     * @param rM The rotation matrix representation.
     * @return The corresponding quaternion.
     */
    Quaternion RotationMatrixToQuaternion(const RotationMatrix& rM);

    /**
     * @brief Converts three basis vectors to a Quaternion.
     *
     * @param X The X-axis vector.
     * @param Y The Y-axis vector.
     * @param Z The Z-axis vector.
     * @return The corresponding quaternion.
     */
    Quaternion RotationMatrixToQuaternion(const Vector3D& X, const Vector3D& Y, const Vector3D& Z);

    /**
     * @brief Converts Euler angles to a Quaternion.
     *
     * @param eulerAngles The Euler angles representation.
     * @return The corresponding quaternion.
     */
    Quaternion EulerAnglesToQuaternion(const EulerAngles& eulerAngles);

    /**
     * @brief Converts a YawPitchRoll representation to a Quaternion.
     *
     * @param ypr The yaw-pitch-roll representation.
     * @return The corresponding quaternion.
     */
    Quaternion YawPitchRollToQuaternion(const YawPitchRoll& ypr);

    /**
     * @brief Converts a RotationMatrix to Euler angles.
     *
     * @param rM The rotation matrix representation.
     * @param order The Euler order to use for conversion.
     * @return The corresponding Euler angles.
     */
    EulerAngles RotationMatrixToEulerAngles(const RotationMatrix& rM, const EulerOrder& order);

    /**
     * @brief Converts Euler angles to a RotationMatrix.
     *
     * @param eulerAngles The Euler angles representation.
     * @return The corresponding rotation matrix.
     */
    RotationMatrix EulerAnglesToRotationMatrix(const EulerAngles& eulerAngles);

    /**
     * @brief Creates a Quaternion from direction vectors.
     *
     * @param initial The initial direction vector.
     * @param target The target direction vector.
     * @return The corresponding quaternion.
     */
    Quaternion QuaternionFromDirectionVectors(const Vector3D& initial, const Vector3D& target);

public:
    /**
     * @brief Default constructor.
     *
     * Initializes the rotation to the identity quaternion.
     */
    Rotation();

    /**
     * @brief Constructor from a Quaternion.
     *
     * @param quaternion The quaternion representation of the rotation.
     */
    Rotation(const Quaternion& quaternion);

    /**
     * @brief Constructor from an AxisAngle representation.
     *
     * @param axisAngle The axis-angle representation of the rotation.
     */
    Rotation(const AxisAngle& axisAngle);

    /**
     * @brief Constructor from a DirectionAngle representation.
     *
     * @param directionAngle The direction-angle representation of the rotation.
     */
    Rotation(const DirectionAngle& directionAngle);

    /**
     * @brief Constructor from a RotationMatrix.
     *
     * @param rotationMatrix The rotation matrix representation of the rotation.
     */
    Rotation(const RotationMatrix& rotationMatrix);

    /**
     * @brief Constructor from basis vectors.
     *
     * @param X The X-axis vector.
     * @param Y The Y-axis vector.
     * @param Z The Z-axis vector.
     */
    Rotation(const Vector3D& X, const Vector3D& Y, const Vector3D& Z);

    /**
     * @brief Constructor from Euler angles.
     *
     * @param eulerAngles The Euler angles representation of the rotation.
     */
    Rotation(const EulerAngles& eulerAngles);

    /**
     * @brief Constructor from direction vectors.
     *
     * @param initial The initial direction vector.
     * @param target The target direction vector.
     */
    Rotation(const Vector3D& initial, const Vector3D& target);

    /**
     * @brief Constructor from a YawPitchRoll representation.
     *
     * @param ypr The yaw-pitch-roll representation of the rotation.
     */
    Rotation(const YawPitchRoll& ypr);

    /**
     * @brief Gets the quaternion representation of the rotation.
     *
     * @return The quaternion representing the rotation.
     */
    Quaternion GetQuaternion();

    /**
     * @brief Gets the axis-angle representation of the rotation.
     *
     * @return The axis-angle representation.
     */
    AxisAngle GetAxisAngle();

    /**
     * @brief Gets the direction-angle representation of the rotation.
     *
     * @return The direction-angle representation.
     */
    DirectionAngle GetDirectionAngle();

    /**
     * @brief Gets the rotation matrix representation of the rotation.
     *
     * @return The rotation matrix representation.
     */
    RotationMatrix GetRotationMatrix();

    /**
     * @brief Gets the Euler angles representation of the rotation.
     *
     * @param order The Euler order to use for conversion.
     * @return The Euler angles representation.
     */
    EulerAngles GetEulerAngles(const EulerOrder& order);

    /**
     * @brief Gets the yaw-pitch-roll representation of the rotation.
     *
     * @return The yaw-pitch-roll representation.
     */
    YawPitchRoll GetYawPitchRoll();
};
