/**
 * @file Vector2D.h
 * @brief Defines a 2D vector and various related operations.
 *
 * The `Vector2D` class provides a simple 2D vector representation along with
 * utilities for common vector arithmetic, constraints, and geometric operations.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

/**
 * @class Vector2D
 * @brief Represents a 2D vector (X, Y) and provides methods for vector arithmetic.
 *
 * The `Vector2D` class defines basic 2D vector operations such as addition, subtraction,
 * multiplication, division, dot product, cross product, and geometric queries. It also
 * includes static functions to perform operations on multiple `Vector2D` objects without
 * requiring an instance.
 */
class Vector2D {
public:
    float X; ///< The X-component of the 2D vector.
    float Y; ///< The Y-component of the 2D vector.

    /**
     * @brief Constructs a default `Vector2D` with X = 0 and Y = 0.
     */
    Vector2D();

    /**
     * @brief Copy constructor. Initializes this vector with the same values as another `Vector2D`.
     * @param vector The `Vector2D` to copy from.
     */
    Vector2D(const Vector2D& vector);

    /**
     * @brief Constructs a `Vector2D` using specified float components.
     * @param X The X-component of the vector.
     * @param Y The Y-component of the vector.
     */
    Vector2D(const float& X, const float& Y);

    /**
     * @brief Constructs a `Vector2D` from a `Vector3D`, discarding the Z-component.
     * @param vector The `Vector3D` to convert (Z is ignored).
     */
    Vector2D(const Vector3D& vector);

    /**
     * @brief Returns a vector with the absolute value of each component.
     * @return A `Vector2D` where each component is `abs(X)` and `abs(Y)`.
     */
    Vector2D Absolute() const;

    /**
     * @brief Computes the squared magnitude of the vector (X^2 + Y^2).
     * @return A `Vector2D` whose components are squared. (Typically used as an internal helper.)
     */
    Vector2D Normal() const;

    /**
     * @brief Adds this vector to another `Vector2D` component-wise.
     * @param vector The vector to add.
     * @return A new `Vector2D` representing the sum.
     */
    Vector2D Add(const Vector2D& vector) const;

    /**
     * @brief Subtracts another `Vector2D` from this vector component-wise.
     * @param vector The vector to subtract.
     * @return A new `Vector2D` representing the difference.
     */
    Vector2D Subtract(const Vector2D& vector) const;

    /**
     * @brief Multiplies this vector by another `Vector2D` component-wise.
     * @param vector The vector to multiply by.
     * @return A new `Vector2D` representing the product.
     */
    Vector2D Multiply(const Vector2D& vector) const;

    /**
     * @brief Divides this vector by another `Vector2D` component-wise.
     * @param vector The vector to divide by.
     * @return A new `Vector2D` representing the quotient.
     */
    Vector2D Divide(const Vector2D& vector) const;

    /**
     * @brief Scales this vector by a float.
     * @param scalar The scalar value.
     * @return A new `Vector2D` scaled by `scalar`.
     */
    Vector2D Multiply(const float& scalar) const;

    /**
     * @brief Divides this vector by a scalar.
     * @param scalar The scalar divisor.
     * @return A new `Vector2D` after division by `scalar`.
     */
    Vector2D Divide(const float& scalar) const;

    /**
     * @brief Calculates the 2D cross product of this vector with another.
     *
     * For 2D vectors, the "cross product" reduces to a scalar, which is conceptually
     * the Z-component of the 3D cross product.
     *
     * @param vector The other `Vector2D`.
     * @return The scalar cross product result.
     */
    float CrossProduct(const Vector2D& vector) const;

    /**
     * @brief Normalizes this vector such that its magnitude is 1 (if non-zero).
     * @return A unit circle vector pointing in the same direction.
     */
    Vector2D UnitCircle() const;

    /**
     * @brief Constrains each component of this vector between the specified minimum and maximum.
     * @param minimum The lower bound.
     * @param maximum The upper bound.
     * @return A new `Vector2D` with each component constrained.
     */
    Vector2D Constrain(const float& minimum, const float& maximum) const;

    /**
     * @brief Constrains each component of this vector between the corresponding components
     *        of two other `Vector2D` objects.
     * @param minimum The lower bound vector.
     * @param maximum The upper bound vector.
     * @return A new `Vector2D` with each component constrained.
     */
    Vector2D Constrain(const Vector2D& minimum, const Vector2D& maximum) const;

    /**
     * @brief Computes the minimum components between this vector and another `Vector2D`.
     * @param v The other `Vector2D`.
     * @return A new `Vector2D` taking the minimum of X and Y components.
     */
    Vector2D Minimum(const Vector2D& v) const;

    /**
     * @brief Computes the maximum components between this vector and another `Vector2D`.
     * @param v The other `Vector2D`.
     * @return A new `Vector2D` taking the maximum of X and Y components.
     */
    Vector2D Maximum(const Vector2D& v) const;

    /**
     * @brief Rotates this vector by a specified angle (in degrees or radians) around a given offset.
     * @param angle The angle of rotation.
     * @param offset The origin about which to rotate.
     * @return A new `Vector2D` representing the rotated vector.
     */
    Vector2D Rotate(const float& angle, const Vector2D& offset) const;

    /**
     * @brief Checks if this vector lies within the bounds of two other `Vector2D` objects.
     * @param minimum The lower bound `Vector2D`.
     * @param maximum The upper bound `Vector2D`.
     * @return `true` if within bounds, otherwise `false`.
     */
    bool CheckBounds(const Vector2D& minimum, const Vector2D& maximum) const;

    /**
     * @brief Computes the magnitude (length) of this vector using the formula sqrt(X^2 + Y^2).
     * @return The length of the vector.
     */
    float Magnitude() const;

    /**
     * @brief Computes the dot product of this vector with another `Vector2D`.
     * @param vector The other `Vector2D`.
     * @return The dot product result (X1*X2 + Y1*Y2).
     */
    float DotProduct(const Vector2D& vector) const;

    /**
     * @brief Calculates the Euclidean distance between this vector and another `Vector2D`.
     * @param vector The other `Vector2D`.
     * @return The distance between the two vectors.
     */
    float CalculateEuclideanDistance(const Vector2D& vector) const;

    /**
     * @brief Checks if this vector is equal to another `Vector2D` component-wise.
     * @param vector The `Vector2D` to compare.
     * @return `true` if equal, otherwise `false`.
     */
    bool IsEqual(const Vector2D& vector) const;

    /**
     * @brief Converts the vector to a string representation.
     * @return A `String` in the format "(X, Y)".
     */
    String ToString() const;


    // --- Static function declarations ---

    /**
     * @brief Returns the squared magnitude of a given vector (X^2 + Y^2) as a Vector2D.
     *
     * Note: This function name can be misleading since "Normal" typically implies a normalized vector.
     *       Here, it is used as in "square of the magnitude" or "norm".
     *
     * @param vector The input `Vector2D`.
     * @return A `Vector2D` containing squared values of each component.
     */
    static Vector2D Normal(const Vector2D& vector);

    /**
     * @brief Adds two vectors (component-wise).
     * @param v1 The first `Vector2D`.
     * @param v2 The second `Vector2D`.
     * @return A new `Vector2D` representing the sum.
     */
    static Vector2D Add(const Vector2D& v1, const Vector2D& v2);

    /**
     * @brief Subtracts one vector from another (component-wise).
     * @param v1 The first `Vector2D`.
     * @param v2 The second `Vector2D` to subtract from `v1`.
     * @return A new `Vector2D` representing the difference.
     */
    static Vector2D Subtract(const Vector2D& v1, const Vector2D& v2);

    /**
     * @brief Multiplies two vectors component-wise.
     * @param v1 The first `Vector2D`.
     * @param v2 The second `Vector2D`.
     * @return A new `Vector2D` representing the product.
     */
    static Vector2D Multiply(const Vector2D& v1, const Vector2D& v2);

    /**
     * @brief Divides two vectors component-wise.
     * @param v1 The first `Vector2D`.
     * @param v2 The second `Vector2D` (divisor).
     * @return A new `Vector2D` representing the quotient.
     */
    static Vector2D Divide(const Vector2D& v1, const Vector2D& v2);

    /**
     * @brief Scales a `Vector2D` by a float, component-wise.
     * @param vector The `Vector2D`.
     * @param scalar The scaling factor.
     * @return A new `Vector2D` scaled by `scalar`.
     */
    static Vector2D Multiply(const Vector2D& vector, const float& scalar);

    /**
     * @brief Scales a `Vector2D` by a float, component-wise (scalar on the left).
     * @param scalar The scaling factor.
     * @param vector The `Vector2D`.
     * @return A new `Vector2D` scaled by `scalar`.
     */
    static Vector2D Multiply(const float& scalar, const Vector2D& vector);

    /**
     * @brief Divides a `Vector2D` by a scalar, component-wise.
     * @param vector The `Vector2D`.
     * @param scalar The scalar divisor.
     * @return A new `Vector2D` after the division.
     */
    static Vector2D Divide(const Vector2D& vector, const float& scalar);

    /**
     * @brief Computes the 2D cross product of two vectors, returning a scalar (Z-component in 3D).
     * @param v1 The first `Vector2D`.
     * @param v2 The second `Vector2D`.
     * @return The scalar cross product (v1.x*v2.y - v1.y*v2.x).
     */
    static float CrossProduct(const Vector2D& v1, const Vector2D& v2);

    /**
     * @brief Computes the dot product of two `Vector2D`s.
     * @param v1 The first `Vector2D`.
     * @param v2 The second `Vector2D`.
     * @return The dot product (v1.x*v2.x + v1.y*v2.y).
     */
    static float DotProduct(const Vector2D& v1, const Vector2D& v2);

    /**
     * @brief Calculates the Euclidean distance between two `Vector2D`s.
     * @param v1 The first `Vector2D`.
     * @param v2 The second `Vector2D`.
     * @return The distance between `v1` and `v2`.
     */
    static float CalculateEuclideanDistance(const Vector2D& v1, const Vector2D& v2);

    /**
     * @brief Checks if two `Vector2D`s are equal component-wise.
     * @param v1 The first `Vector2D`.
     * @param v2 The second `Vector2D`.
     * @return `true` if equal, otherwise `false`.
     */
    static bool IsEqual(const Vector2D& v1, const Vector2D& v2);

    /**
     * @brief Returns a new vector with the minimum components of two `Vector2D`s.
     * @param v1 The first `Vector2D`.
     * @param v2 The second `Vector2D`.
     * @return A `Vector2D` with per-component minimums.
     */
    static Vector2D Minimum(const Vector2D& v1, const Vector2D& v2);

    /**
     * @brief Returns a new vector with the maximum components of two `Vector2D`s.
     * @param v1 The first `Vector2D`.
     * @param v2 The second `Vector2D`.
     * @return A `Vector2D` with per-component maximums.
     */
    static Vector2D Maximum(const Vector2D& v1, const Vector2D& v2);

    /**
     * @brief Performs linear interpolation between two `Vector2D`s.
     * @param start The start `Vector2D`.
     * @param finish The end `Vector2D`.
     * @param ratio A normalized factor (0 to 1).
     * @return A new `Vector2D` representing the linear interpolation result.
     */
    static Vector2D LERP(const Vector2D& start, const Vector2D& finish, const float& ratio);

    /**
     * @brief Converts a vector of degrees to radians (component-wise).
     * @param degrees The vector in degrees.
     * @return A `Vector2D` in radians.
     */
    static Vector2D DegreesToRadians(const Vector2D& degrees);

    /**
     * @brief Converts a vector of radians to degrees (component-wise).
     * @param radians The vector in radians.
     * @return A `Vector2D` in degrees.
     */
    static Vector2D RadiansToDegrees(const Vector2D& radians);

    /**
     * @brief Checks if two line segments defined by (p1, p2) and (q1, q2) intersect in 2D space.
     * @param p1 Start of the first segment.
     * @param p2 End of the first segment.
     * @param q1 Start of the second segment.
     * @param q2 End of the second segment.
     * @return `true` if the segments intersect, otherwise `false`.
     */
    static bool LineSegmentsIntersect(const Vector2D& p1, const Vector2D& p2,
                                      const Vector2D& q1, const Vector2D& q2);


    // --- Operator overloads ---

    /**
     * @brief Equality operator. Checks if two `Vector2D`s are equal (component-wise).
     * @param vector The vector to compare with.
     * @return `true` if equal, otherwise `false`.
     */
    bool operator ==(const Vector2D& vector) const;

    /**
     * @brief Inequality operator. Checks if two `Vector2D`s differ (component-wise).
     * @param vector The vector to compare with.
     * @return `true` if not equal, otherwise `false`.
     */
    bool operator !=(const Vector2D& vector) const;

    /**
     * @brief Assignment operator. Copies another `Vector2D` into this one.
     * @param vector The vector to copy.
     * @return A reference to this `Vector2D`.
     */
    Vector2D operator =(const Vector2D& vector);

    /**
     * @brief Assignment operator. Copies a `Vector3D` into this `Vector2D`, discarding Z.
     * @param vector The `Vector3D` to copy from.
     * @return A reference to this `Vector2D`.
     */
    Vector2D operator =(const Vector3D& vector);

    /**
     * @brief Addition operator. Adds two vectors component-wise.
     * @param vector The right-hand side `Vector2D`.
     * @return A new `Vector2D` representing the sum.
     */
    Vector2D operator +(const Vector2D& vector) const;

    /**
     * @brief Subtraction operator. Subtracts two vectors component-wise.
     * @param vector The right-hand side `Vector2D`.
     * @return A new `Vector2D` representing the difference.
     */
    Vector2D operator -(const Vector2D& vector) const;

    /**
     * @brief Multiplication operator. Multiplies two vectors component-wise.
     * @param vector The right-hand side `Vector2D`.
     * @return A new `Vector2D` representing the product.
     */
    Vector2D operator *(const Vector2D& vector) const;

    /**
     * @brief Division operator. Divides two vectors component-wise.
     * @param vector The right-hand side `Vector2D` (divisor).
     * @return A new `Vector2D` representing the quotient.
     */
    Vector2D operator /(const Vector2D& vector) const;

    /**
     * @brief Multiplication operator by a float scalar (on the right).
     * @param value The scalar factor.
     * @return A new `Vector2D` scaled by `value`.
     */
    Vector2D operator *(const float& value) const;

    /**
     * @brief Division operator by a float scalar.
     * @param value The scalar divisor.
     * @return A new `Vector2D` after division by `value`.
     */
    Vector2D operator /(const float& value) const;
};
