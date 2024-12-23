/**
 * @file EulerAngles.h
 * @brief Represents rotations in 3D space using Euler angles.
 *
 * The `EulerAngles` class defines rotations using a sequence of three angles (pitch, yaw, roll)
 * applied in a specific order.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "EulerOrder.h"
#include "Vector3D.h"

/**
 * @class EulerAngles
 * @brief Encapsulates a 3D rotation using Euler angles and a specific order of application.
 *
 * Euler angles are commonly used to represent rotations in 3D space by specifying
 * three angles applied in a specific sequence. The sequence is defined by the `EulerOrder`.
 */
class EulerAngles {
public:
    Vector3D Angles; ///< The three rotation angles (pitch, yaw, roll) in degrees (or radians based on usage).
    EulerOrder Order; ///< The order in which the angles are applied (e.g., XYZ, ZYX, etc.).

    /**
     * @brief Default constructor that initializes angles to zero and order to a default value.
     */
    EulerAngles();

    /**
     * @brief Constructs an `EulerAngles` object with specified angles and order.
     *
     * @param angles The rotation angles as a `Vector3D` (e.g., pitch, yaw, roll).
     * @param order The order in which the angles are applied, represented by `EulerOrder`.
     */
    EulerAngles(Vector3D angles, EulerOrder order);

    /**
     * @brief Converts the `EulerAngles` object to a string representation.
     *
     * Useful for debugging and visualizing the rotation angles and order.
     *
     * @return A string representing the `EulerAngles` in the format "(angles: [X, Y, Z], order: XYZ)".
     */
    String ToString();
};
