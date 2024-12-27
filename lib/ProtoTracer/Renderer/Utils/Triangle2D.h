/**
 * @file Triangle2D.h
 * @brief Defines the Triangle2D class for representing and manipulating 2D triangles.
 *
 * The Triangle2D class provides functionality to define, transform, and test intersections
 * with 2D triangles. It includes support for UV mapping, depth calculations, and material assignment.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../Scene/Materials/Material.h"
#include "../../Utils/Math/Transform.h"
#include "../../Utils/Math/Vector2D.h"
#include "../../Physics/Utils/BoundingBox2D.h"
#include "Triangle3D.h"

/**
 * @class Triangle2D
 * @brief Represents a 2D triangle with support for UV mapping, depth, and intersection testing.
 */
class Triangle2D {
public:
    float denominator = 0.0f; ///< Precomputed denominator for barycentric coordinate calculations.
    float p1X, p1Y, p2X, p2Y, p3X, p3Y; ///< Coordinates of the triangle's vertices.
    float v0X, v0Y, v1X, v1Y, v2X, v2Y; ///< Edge vectors for barycentric coordinate calculations.
    Vector2D min, max; ///< Minimum and maximum bounds of the triangle.

    Vector3D* normal; ///< Normal vector of the triangle (if available).
    Material* material; ///< Material assigned to the triangle.

    Vector3D* t3p1; ///< Pointer to the first vertex in 3D space.
    Vector3D* t3p2; ///< Pointer to the second vertex in 3D space.
    Vector3D* t3p3; ///< Pointer to the third vertex in 3D space.

    const Vector2D* p1UV; ///< UV coordinates of the first vertex.
    const Vector2D* p2UV; ///< UV coordinates of the second vertex.
    const Vector2D* p3UV; ///< UV coordinates of the third vertex.

    bool hasUV = false; ///< Indicates whether the triangle has UV mapping.
    float averageDepth = 0.0f; ///< Average depth of the triangle for rendering.

    /**
     * @brief Default constructor.
     */
    Triangle2D();

    /**
     * @brief Constructs a triangle from 2D vertices.
     * @param p1 First vertex.
     * @param p2 Second vertex.
     * @param p3 Third vertex.
     */
    Triangle2D(const Vector2D& p1, const Vector2D& p2, const Vector2D& p3);

    /**
     * @brief Constructs a triangle from 3D data with a camera transformation and material.
     * @param lookDirection Camera look direction as a quaternion.
     * @param camT Camera transform.
     * @param t Source 3D triangle.
     * @param material Material to assign to the triangle.
     */
    Triangle2D(const Quaternion& lookDirection, Transform* camT, Triangle3D* t, Material* material);

    /**
     * @brief Constructs a triangle from a 3D triangle.
     * @param t Source 3D triangle.
     */
    Triangle2D(Triangle3D* t);

    /**
     * @brief Gets the first vertex as a 2D point.
     * @return First vertex.
     */
    Vector2D GetP1();

    /**
     * @brief Gets the second vertex as a 2D point.
     * @return Second vertex.
     */
    Vector2D GetP2();

    /**
     * @brief Gets the third vertex as a 2D point.
     * @return Third vertex.
     */
    Vector2D GetP3();

    /**
     * @brief Gets the material assigned to the triangle.
     * @return Pointer to the material.
     */
    Material* GetMaterial();

    /**
     * @brief Checks if a point intersects the triangle using barycentric coordinates.
     * @param x X-coordinate of the point.
     * @param y Y-coordinate of the point.
     * @param u Output barycentric coordinate u.
     * @param v Output barycentric coordinate v.
     * @param w Output barycentric coordinate w.
     * @return True if the point intersects the triangle, otherwise false.
     */
    bool DidIntersect(const float& x, const float& y, float& u, float& v, float& w);

    /**
     * @brief Checks if the triangle intersects a bounding box.
     * @param bbox Bounding box to test against.
     * @return True if the triangle intersects the bounding box, otherwise false.
     */
    bool DidIntersect(BoundingBox2D* bbox);

    /**
     * @brief Checks if the triangle intersects a bounding box using the Separating Axis Theorem (SAT).
     * @param bbox Bounding box to test against.
     * @return True if the triangle intersects the bounding box, otherwise false.
     */
    bool DidIntersectSAT(BoundingBox2D* bbox);

    /**
     * @brief Converts the triangle's data to a string representation.
     * @return String representation of the triangle.
     */
    String ToString();
};
