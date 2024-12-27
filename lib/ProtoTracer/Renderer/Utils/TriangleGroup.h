/**
 * @file TriangleGroup.h
 * @brief Defines the TriangleGroup class for dynamic manipulation of triangles in 3D space.
 *
 * The TriangleGroup class represents a group of triangles and provides methods for
 * accessing and managing their vertices, indices, and optional UV mappings.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Triangle3D.h"
#include "ITriangleGroup.h"
#include "IndexGroup.h"
#include "IStaticTriangleGroup.h"

/**
 * @class TriangleGroup
 * @brief Represents a dynamic group of 3D triangles.
 * 
 * This class allows manipulation of a group of triangles based on a static triangle group.
 * It supports optional UV mapping and provides methods to retrieve triangle and vertex data.
 *
 * @tparam vertexCount Number of vertices in the group.
 * @tparam triangleCount Number of triangles in the group.
 */
template<int vertexCount, int triangleCount>
class TriangleGroup : public ITriangleGroup {
private:
    Triangle3D triangles[triangleCount]; ///< Array of triangles in the group.
    Vector3D vertices[vertexCount]; ///< Array of vertices in the group.
    const IndexGroup* indexGroup; ///< Pointer to the index group defining triangle vertices.
    const IndexGroup* uvIndexGroup; ///< Pointer to the UV index group defining texture coordinates.
    const Vector2D* uvVertices; ///< Pointer to the array of UV coordinates.
    bool hasUV = false; ///< Indicates whether UV mapping is enabled.

public:
    /**
     * @brief Constructs a TriangleGroup from a static triangle group.
     * @param triangleGroup Pointer to a static triangle group to initialize this group.
     */
    TriangleGroup(IStaticTriangleGroup* triangleGroup);

    /**
     * @brief Gets the index group defining triangle vertices.
     * @return Pointer to the index group.
     */
    const IndexGroup* GetIndexGroup() override;

    /**
     * @brief Gets the number of triangles in the group.
     * @return Number of triangles.
     */
    int GetTriangleCount() override;

    /**
     * @brief Gets the array of vertices in the group.
     * @return Pointer to the array of vertices.
     */
    Vector3D* GetVertices() override;

    /**
     * @brief Gets the number of vertices in the group.
     * @return Number of vertices.
     */
    int GetVertexCount() override;

    /**
     * @brief Gets the array of triangles in the group.
     * @return Pointer to the array of triangles.
     */
    Triangle3D* GetTriangles() override;

    /**
     * @brief Gets the array of UV vertices in the group.
     * @return Pointer to the array of UV vertices.
     */
    const Vector2D* GetUVVertices() override;

    /**
     * @brief Gets the UV index group defining texture coordinates.
     * @return Pointer to the UV index group.
     */
    const IndexGroup* GetUVIndexGroup() override;
};

#include "TriangleGroup.tpp"
