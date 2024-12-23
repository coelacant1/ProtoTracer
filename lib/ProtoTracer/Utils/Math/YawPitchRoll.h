/**
 * @file YawPitchRoll.h
 * @brief Represents an orientation using yaw, pitch, and roll angles.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Vector3D.h"

/**
 * @class YawPitchRoll
 * @brief A class to represent yaw, pitch, and roll angles for orientation.
 */
class YawPitchRoll {
public:
    float Yaw;   ///< The yaw angle, representing rotation around the vertical axis.
    float Pitch; ///< The pitch angle, representing rotation around the lateral axis.
    float Roll;  ///< The roll angle, representing rotation around the longitudinal axis.

    /**
     * @brief Default constructor, initializes yaw, pitch, and roll to 0.
     */
    YawPitchRoll();

    /**
     * @brief Constructor to initialize yaw, pitch, and roll from a vector.
     * @param vector A Vector3D where X = yaw, Y = pitch, Z = roll.
     */
    YawPitchRoll(Vector3D vector);

    /**
     * @brief Copy constructor.
     * @param ypr The YawPitchRoll object to copy from.
     */
    YawPitchRoll(const YawPitchRoll& ypr);

    /**
     * @brief Constructor to initialize yaw, pitch, and roll with specific values.
     * @param yaw The yaw angle.
     * @param pitch The pitch angle.
     * @param roll The roll angle.
     */
    YawPitchRoll(float yaw, float pitch, float roll);

    /**
     * @brief Converts the yaw, pitch, and roll angles to a string representation.
     * @return A string representation of the YawPitchRoll object.
     */
    String ToString() const;
};
