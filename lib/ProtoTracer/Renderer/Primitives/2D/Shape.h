/**
 * @file Shape.h
 * @brief Defines the Shape base class for representing geometric shapes in 2D space.
 *
 * The Shape class provides a common interface for 2D shapes with properties such as center,
 * size, and rotation. Derived classes must implement the `IsInShape` method to define
 * specific shape boundaries.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../../Utils/Math/Vector2D.h"

/**
 * @class Shape
 * @brief Abstract base class for 2D geometric shapes.
 */
class Shape {
protected:
    Vector2D center; ///< The center point of the shape.
    Vector2D size;   ///< The size of the shape, large enough to fit within a bounding rectangle.
    float rotation;  ///< The rotation of the shape in degrees.

public:
    /**
     * @brief Constructs a Shape object with specified center, size, and rotation.
     * @param center Center point of the shape.
     * @param size Dimensions of the shape.
     * @param rotation Rotation angle in degrees.
     */
    Shape(Vector2D center, Vector2D size, float rotation);

    /**
     * @brief Sets the center of the shape.
     * @param center New center point.
     */
    void SetCenter(Vector2D center);

    /**
     * @brief Translates the shape by a given offset.
     * @param offset Offset vector to translate the shape.
     */
    void Translate(Vector2D offset);

    /**
     * @brief Gets the center point of the shape.
     * @return The center point of the shape.
     */
    Vector2D GetCenter();

    /**
     * @brief Sets the size of the shape.
     * @param size New dimensions of the shape.
     */
    void SetSize(Vector2D size);

    /**
     * @brief Scales the shape by a given factor.
     * @param scale Scale factor for the shape dimensions.
     */
    void Scale(Vector2D scale);

    /**
     * @brief Gets the size of the shape.
     * @return The size of the shape.
     */
    Vector2D GetSize();

    /**
     * @brief Sets the rotation angle of the shape.
     * @param rotation New rotation angle in degrees.
     */
    void SetRotation(float rotation);

    /**
     * @brief Rotates the shape by a given offset angle.
     * @param offset Offset angle in degrees.
     */
    void Rotate(float offset);

    /**
     * @brief Gets the current rotation angle of the shape.
     * @return The rotation angle in degrees.
     */
    float GetRotation();

    /**
     * @brief Checks if a given point lies within the shape's boundaries.
     * @param point The point to check.
     * @return True if the point is within the shape, otherwise false.
     */
    virtual bool IsInShape(Vector2D point) = 0;
};
