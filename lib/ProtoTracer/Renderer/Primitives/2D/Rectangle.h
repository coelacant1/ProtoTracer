/**
 * @file Rectangle.h
 * @brief Defines the Rectangle class for representing rectangular shapes in 2D space.
 *
 * The Rectangle class provides functionality to define a rectangle by its center, size, and rotation,
 * and check if a given point lies within the rectangle's boundaries.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Shape.h"

/**
 * @class Rectangle
 * @brief Represents a rectangle in 2D space.
 */
class Rectangle : public Shape {
public:
    /**
     * @brief Constructs a Rectangle object with specified center, size, and rotation.
     * @param center Center point of the rectangle.
     * @param size Dimensions of the rectangle (width and height).
     * @param rotation Rotation angle of the rectangle in degrees.
     */
    Rectangle(Vector2D center, Vector2D size, float rotation);

    /**
     * @brief Checks if a given point lies within the rectangle's boundaries.
     * @param point The point to check.
     * @return True if the point is within the rectangle, otherwise false.
     */
    bool IsInShape(Vector2D point) override;
};
