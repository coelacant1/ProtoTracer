/**
 * @file AxisAngle.h
 * @brief Represents a rotation defined by an axis and an angle.
 *
 * The `AxisAngle` class encapsulates a rotation using a specified axis and a rotation angle.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Vector3D.h"

/**
 * @class AxisAngle
 * @brief Defines a rotation in 3D space using an axis and an angle.
 *
 * The `AxisAngle` class provides a representation for rotations, where the rotation is defined
 * by an angle in degrees (or radians) and a unit axis vector.
 */
class AxisAngle {
public:
    float Rotation; ///< The angle of rotation in degrees (or radians, depending on usage).
    Vector3D Axis;  ///< The axis of rotation, represented as a 3D vector.

    /**
     * @brief Constructs an `AxisAngle` with a rotation angle and individual axis components.
     *
     * @param rotation The angle of rotation.
     * @param x The X component of the rotation axis.
     * @param y The Y component of the rotation axis.
     * @param z The Z component of the rotation axis.
     */
    AxisAngle(float rotation, float x, float y, float z);

    /**
     * @brief Constructs an `AxisAngle` with a rotation angle and a vector axis.
     *
     * @param rotation The angle of rotation.
     * @param axis The axis of rotation, represented as a `Vector3D`.
     */
    AxisAngle(float rotation, Vector3D axis);

    /**
     * @brief Converts the `AxisAngle` to a string representation.
     *
     * Useful for debugging and visualization of the rotation data.
     *
     * @return A string representing the `AxisAngle` in the format "(rotation: X, axis: [X, Y, Z])".
     */
    String ToString();
};
