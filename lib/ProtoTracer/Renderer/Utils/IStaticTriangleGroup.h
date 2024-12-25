/**
 * @file IStaticTriangleGroup.h
 * @brief Defines the IStaticTriangleGroup interface for managing a collection of static 3D triangles.
 *
 * This interface provides methods to access and manipulate static triangle data, including vertices,
 * UV coordinates, and indices. It is useful for rendering, geometric calculations, and other 3D applications.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Triangle3D.h"
#include "IndexGroup.h"

/**
 * @class IStaticTriangleGroup
 * @brief Interface for managing a static group of 3D triangles and associated data.
 */
class IStaticTriangleGroup {
public:
    /**
     * @brief Checks if the triangle group has UV coordinates.
     * @return True if UV coordinates are present, false otherwise.
     */
    virtual const bool HasUV() = 0;

    /**
     * @brief Retrieves the index group for the triangle group.
     * @return A pointer to the IndexGroup array.
     */
    virtual const IndexGroup* GetIndexGroup() = 0;

    /**
     * @brief Retrieves the total number of triangles in the group.
     * @return The number of triangles.
     */
    virtual const int GetTriangleCount() = 0;

    /**
     * @brief Retrieves the array of vertices in the triangle group.
     * @return A pointer to the array of Vector3D vertices.
     */
    virtual const Vector3D* GetVertices() = 0;

    /**
     * @brief Retrieves the total number of vertices in the group.
     * @return The number of vertices.
     */
    virtual const int GetVertexCount() = 0;

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
