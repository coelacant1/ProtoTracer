/**
 * @file BoundingBox2D.h
 * @brief Defines the BoundingBox2D class for managing 2D bounding boxes.
 *
 * The BoundingBox2D class provides functionality to represent, update, and query
 * axis-aligned 2D bounding boxes for collision detection and spatial representation.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../Utils/Math/Vector2D.h"

/**
 * @class BoundingBox2D
 * @brief Represents a 2D axis-aligned bounding box.
 */
class BoundingBox2D {
private:
    Vector2D min; ///< Minimum corner of the bounding box.
    Vector2D max; ///< Maximum corner of the bounding box.
    Vector2D mid; ///< Center point of the bounding box.

public:
    /**
     * @brief Default constructor initializing the bounding box to zero dimensions.
     */
    BoundingBox2D();

    /**
     * @brief Constructs a BoundingBox2D with specified minimum and maximum corners.
     * @param min Minimum corner of the bounding box.
     * @param max Maximum corner of the bounding box.
     */
    BoundingBox2D(const Vector2D& min, const Vector2D& max);

    /**
     * @brief Updates the bounds of the bounding box to include the specified point.
     * @param current The point to include in the bounding box.
     */
    void UpdateBounds(const Vector2D& current);

    /**
     * @brief Gets the minimum corner of the bounding box.
     * @return Minimum corner as a Vector2D.
     */
    Vector2D GetMinimum();

    /**
     * @brief Gets the maximum corner of the bounding box.
     * @return Maximum corner as a Vector2D.
     */
    Vector2D GetMaximum();

    /**
     * @brief Gets the center point of the bounding box.
     * @return Center point as a Vector2D.
     */
    Vector2D GetCenter();

    /**
     * @brief Checks if this bounding box overlaps with another BoundingBox2D.
     * @param bb Pointer to the other BoundingBox2D.
     * @return True if the bounding boxes overlap, false otherwise.
     */
    bool Overlaps(BoundingBox2D* bb);

    /**
     * @brief Checks if this bounding box overlaps with another box defined by min and max corners.
     * @param minI Minimum corner of the other box.
     * @param maxI Maximum corner of the other box.
     * @return True if the boxes overlap, false otherwise.
     */
    bool Overlaps(const Vector2D& minI, const Vector2D& maxI);

    /**
     * @brief Checks if this bounding box contains a specified point.
     * @param v The point to check.
     * @return True if the point is within the bounding box, false otherwise.
     */
    bool Contains(const Vector2D& v);
};
