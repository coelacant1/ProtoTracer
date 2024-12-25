/**
 * @file ITriangleGroup.h
 * @brief Defines the ITriangleGroup interface for managing a collection of mutable 3D triangles.
 *
 * This interface provides methods to access and manipulate triangle data, including vertices,
 * UV coordinates, and indices. It allows for dynamic modifications and updates to the triangle group.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Triangle3D.h"
#include "IndexGroup.h"
#include "IStaticTriangleGroup.h"

/**
 * @class ITriangleGroup
 * @brief Interface for managing a dynamic group of 3D triangles and associated data.
 */
class ITriangleGroup {
public:
    /**
     * @brief Retrieves the index group for the triangle group.
     * @return A pointer to the IndexGroup array.
     */
    virtual const IndexGroup* GetIndexGroup() = 0;

    /**
     * @brief Retrieves the total number of triangles in the group.
     * @return The number of triangles.
     */
    virtual int GetTriangleCount() = 0;

    /**
     * @brief Retrieves the array of mutable vertices in the triangle group.
     * @return A pointer to the array of Vector3D vertices.
     */
    virtual Vector3D* GetVertices() = 0;

    /**
     * @brief Retrieves the total number of vertices in the group.
     * @return The number of vertices.
     */
    virtual int GetVertexCount() = 0;

    /**
     * @brief Retrieves the array of Triangle3D objects representing the triangles.
     * @return A pointer to the array of Triangle3D objects.
     */
    virtual Triangle3D* GetTriangles() = 0;

    /**
     * @brief Retrieves the array of UV vertices in the triangle group.
     * @return A pointer to the array of Vector2D UV vertices.
     */
    virtual const Vector2D* GetUVVertices() = 0;

    /**
     * @brief Retrieves the index group for the UV vertices.
     * @return A pointer to the IndexGroup array for UV vertices.
     */
    virtual const IndexGroup* GetUVIndexGroup() = 0;
};
