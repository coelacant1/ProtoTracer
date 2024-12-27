/**
 * @file StaticTriangleGroup.h
 * @brief Defines the StaticTriangleGroup class for managing 3D triangle geometry.
 *
 * The StaticTriangleGroup class represents a fixed collection of 3D triangles, 
 * vertices, and associated UV data. It provides methods to access and manipulate 
 * this data for rendering or simulation purposes.
 *
 * @date 22/12/2024
 * @version 1.0
 * @tparam vertexCount The number of vertices in the group.
 * @tparam triangleCount The number of triangles in the group.
 * @author Coela Can't
 */

#pragma once

#include "Triangle3D.h"
#include "IndexGroup.h"
#include "IStaticTriangleGroup.h"

/**
 * @class StaticTriangleGroup
 * @brief Represents a static collection of 3D triangles and associated vertex/UV data.
 * @tparam vertexCount Number of vertices in the group.
 * @tparam triangleCount Number of triangles in the group.
 */
template<int vertexCount, int triangleCount>
class StaticTriangleGroup : public IStaticTriangleGroup {
private:
    Triangle3D triangles[triangleCount]; ///< Array of 3D triangles in the group.
    Vector3D* vertices; ///< Array of vertex positions.
    const IndexGroup* indexGroup; ///< Index group defining triangle vertex indices.
    const IndexGroup* uvIndexGroup; ///< Index group for UV coordinates (if available).
    const Vector2D* uvVertices; ///< Array of UV coordinates for texture mapping.
    const bool hasUVB; ///< Indicates whether the group contains UV data.

public:
    /**
     * @brief Constructor for a group without UV data.
     * @param vertices Array of vertex positions.
     * @param indexGroup Index group defining triangle vertex indices.
     */
    StaticTriangleGroup(Vector3D* vertices, const IndexGroup* indexGroup);

    /**
     * @brief Constructor for a group with UV data.
     * @param vertices Array of vertex positions.
     * @param indexGroup Index group defining triangle vertex indices.
     * @param uvIndexGroup Index group for UV coordinates.
     * @param uvVertices Array of UV coordinates for texture mapping.
     */
    StaticTriangleGroup(Vector3D* vertices, const IndexGroup* indexGroup, const IndexGroup* uvIndexGroup, const Vector2D* uvVertices);

    /**
     * @brief Checks if the group has UV data.
     * @return True if UV data is present, otherwise false.
     */
    const bool HasUV() override;

    /**
     * @brief Retrieves the triangle index group.
     * @return Pointer to the IndexGroup defining triangle vertex indices.
     */
    const IndexGroup* GetIndexGroup() override;

    /**
     * @brief Gets the total number of triangles in the group.
     * @return The number of triangles.
     */
    const int GetTriangleCount() override;

    /**
     * @brief Retrieves the array of vertex positions.
     * @return Pointer to the array of vertices.
     */
    Vector3D* GetVertices() override;

    /**
     * @brief Gets the total number of vertices in the group.
     * @return The number of vertices.
     */
    const int GetVertexCount() override;

    /**
     * @brief Retrieves the array of triangles in the group.
     * @return Pointer to the array of triangles.
     */
    Triangle3D* GetTriangles() override;

    /**
     * @brief Retrieves the array of UV coordinates.
     * @return Pointer to the array of UV coordinates, or nullptr if not available.
     */
    const Vector2D* GetUVVertices() override;

    /**
     * @brief Retrieves the UV index group.
     * @return Pointer to the UV IndexGroup, or nullptr if not available.
     */
    const IndexGroup* GetUVIndexGroup() override;
};

#include "StaticTriangleGroup.tpp"
