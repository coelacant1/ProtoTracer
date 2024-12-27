/**
 * @file Ellipse.h
 * @brief Defines the Ellipse class for representing elliptical shapes in 2D space.
 *
 * The Ellipse class provides functionality to define an ellipse by its center, size, and rotation,
 * and check if a given point lies within the ellipse's boundaries.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Shape.h"

/**
 * @class Ellipse
 * @brief Represents an ellipse in 2D space.
 */
class Ellipse : public Shape {
public:
    /**
     * @brief Constructs an Ellipse object with specified center, size, and rotation.
     * @param center Center point of the ellipse.
     * @param size Dimensions of the ellipse (width and height).
     * @param rotation Rotation angle of the ellipse in degrees.
     */
    Ellipse(Vector2D center, Vector2D size, float rotation);

    /**
     * @brief Checks if a given point lies within the ellipse's boundaries.
     * @param point The point to check.
     * @return True if the point is within the ellipse, otherwise false.
     */
    bool IsInShape(Vector2D point) override;
};
