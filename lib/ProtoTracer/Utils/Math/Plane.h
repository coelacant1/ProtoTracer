/**
 * @file Plane.h
 * @brief Defines the Plane class for representing a plane in 3D space.
 *
 * The Plane class represents a mathematical plane defined by a centroid and a normal vector.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Vector3D.h"

/**
 * @class Plane
 * @brief Represents a plane in 3D space defined by a centroid and a normal vector.
 *
 * The `Plane` class provides methods for initializing and describing a plane
 * in three-dimensional space using a point on the plane (centroid) and a normal vector.
 */
class Plane {
public:
    Vector3D Centroid; ///< Point on the plane, representing the centroid.
    Vector3D Normal;   ///< Normal vector defining the plane's orientation.

    /**
     * @brief Default constructor.
     *
     * Initializes the plane with a default centroid and normal vector.
     */
    Plane();

    /**
     * @brief Parameterized constructor.
     *
     * Initializes the plane with the specified centroid and normal vector.
     *
     * @param centroid A point on the plane (centroid).
     * @param normal A vector normal to the plane.
     */
    Plane(Vector3D centroid, Vector3D normal);

    /**
     * @brief Converts the Plane object to a string representation.
     *
     * @return A string describing the plane's centroid and normal vector.
     */
    String ToString();
};
