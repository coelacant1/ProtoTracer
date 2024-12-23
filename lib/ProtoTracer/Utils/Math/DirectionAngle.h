/**
 * @file DirectionAngle.h
 * @brief Represents a rotation defined by a direction vector and an angle.
 *
 * The `DirectionAngle` class encapsulates a rotation where the rotation is specified
 * about a direction vector instead of a strict axis.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Vector3D.h"

/**
 * @class DirectionAngle
 * @brief Defines a rotation in 3D space using a direction vector and a rotation angle.
 *
 * The `DirectionAngle` class provides a representation for rotations, where the rotation
 * is defined by an angle and a direction vector. This is similar to `AxisAngle` but can
 * represent rotations about arbitrary direction vectors.
 */
class DirectionAngle {
public:
    float Rotation; ///< The angle of rotation in degrees (or radians, depending on usage).
    Vector3D Direction; ///< The direction vector defining the axis of rotation.

    /**
     * @brief Constructs a `DirectionAngle` with a rotation angle and individual direction components.
     *
     * @param rotation The angle of rotation.
     * @param x The X component of the direction vector.
     * @param y The Y component of the direction vector.
     * @param z The Z component of the direction vector.
     */
    DirectionAngle(float rotation, float x, float y, float z);

    /**
     * @brief Constructs a `DirectionAngle` with a rotation angle and a direction vector.
     *
     * @param rotation The angle of rotation.
     * @param direction The direction vector, represented as a `Vector3D`.
     */
    DirectionAngle(float rotation, Vector3D direction);

    /**
     * @brief Converts the `DirectionAngle` to a string representation.
     *
     * Useful for debugging and visualization of the rotation data.
     *
     * @return A string representing the `DirectionAngle` in the format "(rotation: X, direction: [X, Y, Z])".
     */
    String ToString();
};
