/**
 * @file Triangle3D.h
 * @brief Defines the Triangle3D class for representing and manipulating 3D triangles.
 *
 * The Triangle3D class provides functionality for defining, calculating normals,
 * testing ray intersections, and managing UV mappings of 3D triangles.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../Utils/Math/Quaternion.h"
#include "../../Utils/Math/Vector3D.h"

/**
 * @class Triangle3D
 * @brief Represents a 3D triangle with support for UV mapping and ray intersection testing.
 */
class Triangle3D {
public:
    Vector3D* p1; ///< Pointer to the first vertex of the triangle.
    Vector3D* p2; ///< Pointer to the second vertex of the triangle.
    Vector3D* p3; ///< Pointer to the third vertex of the triangle.

    const Vector2D* p1UV; ///< Pointer to the UV coordinates of the first vertex.
    const Vector2D* p2UV; ///< Pointer to the UV coordinates of the second vertex.
    const Vector2D* p3UV; ///< Pointer to the UV coordinates of the third vertex.

    Vector3D edge1; ///< Edge vector from the first to the second vertex.
    Vector3D edge2; ///< Edge vector from the first to the third vertex.
    Vector3D normal; ///< Normal vector of the triangle.

    bool hasUV = false; ///< Indicates whether the triangle has UV mapping.

    /**
     * @brief Default constructor.
     */
    Triangle3D();

    /**
     * @brief Constructs a triangle with specified vertices.
     * @param p1 Pointer to the first vertex.
     * @param p2 Pointer to the second vertex.
     * @param p3 Pointer to the third vertex.
     */
    Triangle3D(Vector3D* p1, Vector3D* p2, Vector3D* p3);

    /**
     * @brief Calculates and returns the normal of the triangle.
     * @return Pointer to the calculated normal vector.
     */
    Vector3D* Normal();

    /**
     * @brief Tests whether a ray intersects with the triangle.
     * @param ray The origin of the ray.
     * @param direction The direction of the ray.
     * @param intersect Output parameter for the intersection point.
     * @param color Output parameter for color (optional).
     * @return True if the ray intersects the triangle, otherwise false.
     */
    bool DidIntersect(Vector3D ray, Vector3D direction, Vector3D* intersect, Vector3D* color);

    /**
     * @brief Converts the triangle's data to a string representation.
     * @return String representation of the triangle.
     */
    String ToString();
};
