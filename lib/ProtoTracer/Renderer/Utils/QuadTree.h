/**
 * @file QuadTree.h
 * @brief Defines the QuadTree class for spatial partitioning in 2D space.
 *
 * The QuadTree class provides a hierarchical structure for efficient spatial 
 * partitioning and management of 2D entities like triangles. It supports 
 * insertion, intersection checks, and dynamic rebuilding of the tree.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author moepforfreedom, Coela Can't
 */

#pragma once

#include "Node.h"

/**
 * @class QuadTree
 * @brief Represents a quadtree for spatial partitioning of 2D entities.
 */
class QuadTree {
private:
    BoundingBox2D bbox; ///< Bounding box representing the spatial extent of the quadtree.
    Node root; ///< Root node of the quadtree.
    uint16_t count = 0; ///< Current count of entities in the quadtree.

    /**
     * @brief Recursively finds the node intersecting with a given point.
     * @param node Pointer to the current node being checked.
     * @param p The point to check for intersection.
     * @return Pointer to the intersecting node, or nullptr if no intersection.
     */
    Node* Intersect(Node* node, const Vector2D& p);

public:
    /**
     * @brief Constructs a QuadTree with specified bounds.
     * @param min Minimum bounds of the quadtree.
     * @param max Maximum bounds of the quadtree.
     */
    QuadTree(const Vector2D& min, const Vector2D& max);

    /**
     * @brief Destructor for the QuadTree class.
     */
    ~QuadTree();

    /**
     * @brief Inserts a triangle entity into the quadtree.
     * @param triangle Pointer to the Triangle2D entity to insert.
     * @return True if the entity was successfully inserted, otherwise false.
     */
    bool Insert(Triangle2D* triangle);

    /**
     * @brief Finds the node intersecting with a given point.
     * @param p The point to check for intersection.
     * @return Pointer to the intersecting node, or nullptr if no intersection.
     */
    Node* Intersect(const Vector2D& p);

    /**
     * @brief Rebuilds the quadtree, recalculating all spatial partitions.
     */
    void Rebuild();
};
