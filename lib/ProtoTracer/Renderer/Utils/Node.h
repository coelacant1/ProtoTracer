/**
 * @file Node.h
 * @brief Defines the Node class for quadtree spatial partitioning in 2D space.
 *
 * The Node class represents a node in a quadtree structure, designed to manage
 * spatial partitioning of 2D entities like triangles. It supports subdivision,
 * entity insertion, and bounding box management.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author moepforfreedom, Coela Can't
 */

#pragma once

#include "../../Physics/Utils/BoundingBox2D.h"
#include "Triangle2D.h"

/**
 * @class Node
 * @brief Represents a node in a quadtree structure for spatial partitioning.
 */
class Node {
private:
    static const uint16_t maxEntities = 8; ///< Maximum number of entities a node can hold before subdividing.
    static const uint8_t maxDepth = 8; ///< Maximum depth of the quadtree.
    uint16_t count = 0; ///< Current number of entities in the node.
    uint16_t capacity = 0; ///< Capacity of entities allocated in the node.
    Node* childNodes = nullptr; ///< Pointer to the child nodes of this node.
    Triangle2D** entities = nullptr; ///< Array of entities (triangles) contained in the node.
    BoundingBox2D bbox; ///< Bounding box defining the spatial area of this node.

    /**
     * @brief Creates child nodes for this node.
     */
    void CreateChildNodes();

    /**
     * @brief Distributes entities to child nodes after subdivision.
     * @return The number of entities successfully distributed to child nodes.
     */
    uint16_t DistributeEntities();

    /**
     * @brief Determines whether the node should be subdivided.
     * @param childEntitySum Total number of entities in child nodes.
     * @return True if the node should subdivide, otherwise false.
     */
    bool ShouldSubdivide(uint16_t childEntitySum);

public:
    /**
     * @brief Constructs a Node with specified bounds.
     * @param min Minimum bounds of the node.
     * @param max Maximum bounds of the node.
     */
    Node(const Vector2D& min, const Vector2D& max);

    /**
     * @brief Destructor for the Node class.
     */
    ~Node();

    /**
     * @brief Retrieves the bounding box of the node.
     * @return Pointer to the BoundingBox2D object.
     */
    BoundingBox2D* GetBBox();

    /**
     * @brief Retrieves the child nodes of this node.
     * @return Pointer to the array of child nodes.
     */
    Node* GetChildNodes();

    /**
     * @brief Retrieves the entities contained in this node.
     * @return Pointer to the array of Triangle2D entities.
     */
    Triangle2D** GetEntities();

    /**
     * @brief Retrieves the current count of entities in the node.
     * @return Number of entities in the node.
     */
    uint16_t GetCount();

    /**
     * @brief Expands the node's capacity to accommodate more entities.
     * @param newCount New capacity for the node.
     */
    void Expand(uint16_t newCount);

    /**
     * @brief Inserts a triangle entity into the node.
     * @param triangle Pointer to the Triangle2D entity to be inserted.
     * @return True if the entity was successfully inserted, otherwise false.
     */
    bool Insert(Triangle2D* triangle);

    /**
     * @brief Subdivides the node into child nodes if needed.
     * @param depth Current depth of the node in the quadtree.
     */
    void Subdivide(uint8_t depth = 0);

    /**
     * @brief Checks if the node is a leaf node (i.e., has no child nodes).
     * @return True if the node is a leaf, otherwise false.
     */
    bool IsLeaf();
};
