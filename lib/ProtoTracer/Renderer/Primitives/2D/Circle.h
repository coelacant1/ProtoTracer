/**
 * @file Circle.h
 * @brief Defines the Circle class for representing circular shapes in 2D space.
 *
 * The Circle class provides functionality to define a circle by its center and radius,
 * and check if a given point lies within the circle's boundaries.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Shape.h"

/**
 * @class Circle
 * @brief Represents a circle in 2D space.
 */
class Circle : public Shape {
private:
    float radius; ///< Radius of the circle.

public:
    /**
     * @brief Constructs a Circle object with a specified center and radius.
     * @param center Center point of the circle.
     * @param radius Radius of the circle.
     */
    Circle(Vector2D center, float radius);

    /**
     * @brief Checks if a given point lies within the circle's boundaries.
     * @param point The point to check.
     * @return True if the point is within the circle, otherwise false.
     */
    bool IsInShape(Vector2D point) override;
};
