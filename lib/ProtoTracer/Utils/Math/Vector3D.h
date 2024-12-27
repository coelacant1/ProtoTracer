/**
 * @file Vector3D.h
 * @brief Defines a 3D vector and various related operations.
 *
 * The `Vector3D` class provides a 3D vector representation along with utilities
 * for common vector arithmetic, constraints, and geometric operations.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Mathematics.h"

/**
 * @class Vector3D
 * @brief Represents a 3D vector (X, Y, Z) and provides methods for vector arithmetic.
 *
 * The `Vector3D` class defines basic 3D vector operations such as addition, subtraction,
 * multiplication, division, dot product, cross product, and geometric queries. It also
 * includes static functions to perform operations on multiple `Vector3D` objects without
 * requiring an instance.
 */
class Vector3D {
public:
    float X; ///< The X-component of the 3D vector.
    float Y; ///< The Y-component of the 3D vector.
    float Z; ///< The Z-component of the 3D vector.

    /**
     * @brief Constructs a default `Vector3D` with X = 0, Y = 0, and Z = 0.
     */
    Vector3D();

    /**
     * @brief Copy constructor. Initializes this vector with the same values as another `Vector3D`.
     * @param vector The `Vector3D` to copy from.
     */
    Vector3D(const Vector3D& vector);

    /**
     * @brief Constructs a `Vector3D` by copying the components of another `Vector3D` pointer.
     * @param vector Pointer to the `Vector3D` to copy from.
     */
    Vector3D(const Vector3D* vector);

    /**
     * @brief Constructs a `Vector3D` using specified float components.
     * @param X The X-component of the vector.
     * @param Y The Y-component of the vector.
     * @param Z The Z-component of the vector.
     */
    Vector3D(const float& X, const float& Y, const float& Z);

    /**
     * @brief Returns a vector with the absolute value of each component.
     * @return A `Vector3D` where each component is `abs(X)`, `abs(Y)`, and `abs(Z)`.
     */
    Vector3D Absolute() const;

    /**
     * @brief Computes the squared magnitude of the vector (X^2 + Y^2 + Z^2).
     * @return A `Vector3D` containing squared values of each component.
     *
     * Note: This naming follows the pattern in other classes but can be
     * confusing; some might expect `Normal()` to return a normalized vector.
     */
    Vector3D Normal() const;

    /**
     * @brief Adds a scalar value to each component of the vector.
     * @param value The scalar to add.
     * @return A new `Vector3D` with components incremented by `value`.
     */
    Vector3D Add(const float& value) const;

    /**
     * @brief Subtracts a scalar value from each component of the vector.
     * @param value The scalar to subtract.
     * @return A new `Vector3D` with components decremented by `value`.
     */
    Vector3D Subtract(const float& value) const;

    /**
     * @brief Adds another `Vector3D` to this one component-wise.
     * @param vector The vector to add.
     * @return A new `Vector3D` representing the sum.
     */
    Vector3D Add(const Vector3D& vector) const;

    /**
     * @brief Subtracts another `Vector3D` from this one component-wise.
     * @param vector The vector to subtract.
     * @return A new `Vector3D` representing the difference.
     */
    Vector3D Subtract(const Vector3D& vector) const;

    /**
     * @brief Multiplies this vector by another `Vector3D` component-wise.
     * @param vector The vector to multiply with.
     * @return A new `Vector3D` representing the product.
     */
    Vector3D Multiply(const Vector3D& vector) const;

    /**
     * @brief Divides this vector by another `Vector3D` component-wise.
     * @param vector The vector to divide by.
     * @return A new `Vector3D` representing the quotient.
     */
    Vector3D Divide(const Vector3D& vector) const;

    /**
     * @brief Scales this vector by a float (each component multiplied by `scalar`).
     * @param scalar The scaling factor.
     * @return A new `Vector3D` scaled by `scalar`.
     */
    Vector3D Multiply(const float& scalar) const;

    /**
     * @brief Divides this vector by a float (each component divided by `scalar`).
     * @param scalar The scalar divisor.
     * @return A new `Vector3D` after the division.
     */
    Vector3D Divide(const float& scalar) const;

    /**
     * @brief Computes the cross product of this vector with another `Vector3D`.
     * @param vector The other `Vector3D`.
     * @return A new `Vector3D` representing the cross product.
     */
    Vector3D CrossProduct(const Vector3D& vector) const;

    /**
     * @brief Normalizes this vector such that its magnitude is 1 (if non-zero).
     * @return A new `Vector3D` representing the unit sphere position.
     */
    Vector3D UnitSphere() const;

    /**
     * @brief Constrains each component of this vector between two scalar bounds.
     * @param minimum The lower bound.
     * @param maximum The upper bound.
     * @return A new `Vector3D` with each component constrained between [min, max].
     */
    Vector3D Constrain(const float& minimum, const float& maximum) const;

    /**
     * @brief Constrains each component of this vector between the corresponding components
     *        of two other `Vector3D` objects.
     * @param minimum The lower bound vector.
     * @param maximum The upper bound vector.
     * @return A new `Vector3D` with each component constrained.
     */
    Vector3D Constrain(const Vector3D& minimum, const Vector3D& maximum) const;

    /**
     * @brief Permutates the components of this vector using another `Vector3D` as an index/offset.
     * @param permutation A vector whose components may dictate a specific reordering or transformation.
     * @return A new `Vector3D` based on the permutation logic.
     */
    Vector3D Permutate(const Vector3D& permutation) const;

    /**
     * @brief Computes the magnitude (length) of this vector using the formula sqrt(X^2 + Y^2 + Z^2).
     * @return The length of the vector.
     */
    float Magnitude() const;

    /**
     * @brief Computes the dot product of this vector with another `Vector3D`.
     * @param vector The other `Vector3D`.
     * @return The dot product result (X1*X2 + Y1*Y2 + Z1*Z2).
     */
    float DotProduct(const Vector3D& vector) const;

    /**
     * @brief Calculates the Euclidean distance between this vector and another `Vector3D`.
     * @param vector The other `Vector3D`.
     * @return The distance between the two vectors.
     */
    float CalculateEuclideanDistance(const Vector3D& vector) const;

    /**
     * @brief Computes the average of the highest two components of this vector.
     *
     * For example, if (X, Y, Z) = (3, 7, 5), the highest two are 7 and 5,
     * whose average is 6.
     *
     * @return The average of the top two components.
     */
    float AverageHighestTwoComponents() const;

    /**
     * @brief Returns the maximum component value among X, Y, Z.
     * @return The maximum component.
     */
    float Max() const;

    /**
     * @brief Returns the minimum component value among X, Y, Z.
     * @return The minimum component.
     */
    float Min() const;

    /**
     * @brief Checks if this vector is equal to another `Vector3D` component-wise.
     * @param vector The `Vector3D` to compare.
     * @return `true` if equal, otherwise `false`.
     */
    bool IsEqual(const Vector3D& vector) const;

    /**
     * @brief Converts the vector to a string representation.
     * @return A `String` in the format "(X, Y, Z)".
     */
    String ToString() const;


    // --- Static function declarations ---

    /**
     * @brief Returns a new vector composed of the maximum components of `max` and `input`.
     * @param max The first `Vector3D` to compare.
     * @param input The second `Vector3D` to compare.
     * @return A `Vector3D` taking the maximum of each component.
     */
    static Vector3D Max(const Vector3D& max, const Vector3D& input);

    /**
     * @brief Returns a new vector composed of the minimum components of `min` and `input`.
     * @param min The first `Vector3D` to compare.
     * @param input The second `Vector3D` to compare.
     * @return A `Vector3D` taking the minimum of each component.
     */
    static Vector3D Min(const Vector3D& min, const Vector3D& input);

    /**
     * @brief Performs linear interpolation between two `Vector3D`s.
     * @param start The start `Vector3D`.
     * @param finish The end `Vector3D`.
     * @param ratio A normalized factor (0 to 1).
     * @return A new `Vector3D` representing the linear interpolation result.
     */
    static Vector3D LERP(const Vector3D& start, const Vector3D& finish, const float& ratio);

    /**
     * @brief Converts a `Vector3D` of degrees to radians (component-wise).
     * @param degrees The vector in degrees.
     * @return A `Vector3D` in radians.
     */
    static Vector3D DegreesToRadians(const Vector3D& degrees);

    /**
     * @brief Converts a `Vector3D` of radians to degrees (component-wise).
     * @param radians The vector in radians.
     * @return A `Vector3D` in degrees.
     */
    static Vector3D RadiansToDegrees(const Vector3D& radians);

    /**
     * @brief Returns the squared magnitude of a given vector (X^2 + Y^2 + Z^2) as a Vector3D.
     * @param vector The input `Vector3D`.
     * @return A `Vector3D` containing squared values of each component.
     */
    static Vector3D Normal(const Vector3D& vector);

    /**
     * @brief Adds two vectors (component-wise).
     * @param v1 The first `Vector3D`.
     * @param v2 The second `Vector3D`.
     * @return A new `Vector3D` representing the sum.
     */
    static Vector3D Add(const Vector3D& v1, const Vector3D& v2);

    /**
     * @brief Subtracts one vector from another (component-wise).
     * @param v1 The first `Vector3D`.
     * @param v2 The second `Vector3D` to subtract from `v1`.
     * @return A new `Vector3D` representing the difference.
     */
    static Vector3D Subtract(const Vector3D& v1, const Vector3D& v2);

    /**
     * @brief Multiplies two vectors component-wise.
     * @param v1 The first `Vector3D`.
     * @param v2 The second `Vector3D`.
     * @return A new `Vector3D` representing the product.
     */
    static Vector3D Multiply(const Vector3D& v1, const Vector3D& v2);

    /**
     * @brief Divides two vectors component-wise.
     * @param v1 The first `Vector3D`.
     * @param v2 The second `Vector3D` (divisor).
     * @return A new `Vector3D` representing the quotient.
     */
    static Vector3D Divide(const Vector3D& v1, const Vector3D& v2);

    /**
     * @brief Scales a `Vector3D` by a float, component-wise.
     * @param vector The `Vector3D`.
     * @param scalar The scaling factor.
     * @return A new `Vector3D` scaled by `scalar`.
     */
    static Vector3D Multiply(const Vector3D& vector, const float& scalar);

    /**
     * @brief Scales a `Vector3D` by a float, component-wise (scalar on the left).
     * @param scalar The scaling factor.
     * @param vector The `Vector3D`.
     * @return A new `Vector3D` scaled by `scalar`.
     */
    static Vector3D Multiply(const float& scalar, const Vector3D& vector);

    /**
     * @brief Divides a `Vector3D` by a float, component-wise.
     * @param vector The `Vector3D`.
     * @param scalar The scalar divisor.
     * @return A new `Vector3D` after the division.
     */
    static Vector3D Divide(const Vector3D& vector, const float& scalar);

    /**
     * @brief Computes the cross product of two `Vector3D`s.
     * @param v1 The first `Vector3D`.
     * @param v2 The second `Vector3D`.
     * @return A new `Vector3D` representing the cross product.
     */
    static Vector3D CrossProduct(const Vector3D& v1, const Vector3D& v2);

    /**
     * @brief Computes the dot product of two `Vector3D`s.
     * @param v1 The first `Vector3D`.
     * @param v2 The second `Vector3D`.
     * @return The dot product (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z).
     */
    static float DotProduct(const Vector3D& v1, const Vector3D& v2);

    /**
     * @brief Calculates the Euclidean distance between two `Vector3D`s.
     * @param v1 The first `Vector3D`.
     * @param v2 The second `Vector3D`.
     * @return The distance between `v1` and `v2`.
     */
    static float CalculateEuclideanDistance(const Vector3D& v1, const Vector3D& v2);

    /**
     * @brief Checks if two `Vector3D`s are equal component-wise.
     * @param v1 The first `Vector3D`.
     * @param v2 The second `Vector3D`.
     * @return `true` if equal, otherwise `false`.
     */
    static bool IsEqual(const Vector3D& v1, const Vector3D& v2);


    // --- Operator overloads ---

    /**
     * @brief Equality operator. Checks if two `Vector3D`s are equal (component-wise).
     * @param vector The vector to compare with.
     * @return `true` if equal, otherwise `false`.
     */
    bool operator ==(const Vector3D& vector) const;

    /**
     * @brief Inequality operator. Checks if two `Vector3D`s differ (component-wise).
     * @param vector The vector to compare with.
     * @return `true` if not equal, otherwise `false`.
     */
    bool operator !=(const Vector3D& vector) const;

    /**
     * @brief In-place addition operator. Adds another vector to this one component-wise.
     * @param vector The right-hand side `Vector3D`.
     * @return A reference to this `Vector3D` after addition.
     */
    Vector3D operator +=(const Vector3D& vector);

    /**
     * @brief Assignment operator. Copies another `Vector3D` into this one.
     * @param vector The vector to copy.
     * @return A reference to this `Vector3D`.
     */
    Vector3D operator =(const Vector3D& vector);

    /**
     * @brief Addition operator. Adds two vectors component-wise.
     * @param vector The right-hand side `Vector3D`.
     * @return A new `Vector3D` representing the sum.
     */
    Vector3D operator +(const Vector3D& vector) const;

    /**
     * @brief Subtraction operator. Subtracts two vectors component-wise.
     * @param vector The right-hand side `Vector3D`.
     * @return A new `Vector3D` representing the difference.
     */
    Vector3D operator -(const Vector3D& vector) const;

    /**
     * @brief Multiplication operator. Multiplies two vectors component-wise.
     * @param vector The right-hand side `Vector3D`.
     * @return A new `Vector3D` representing the product.
     */
    Vector3D operator *(const Vector3D& vector) const;

    /**
     * @brief Division operator. Divides two vectors component-wise.
     * @param vector The right-hand side `Vector3D` (divisor).
     * @return A new `Vector3D` representing the quotient.
     */
    Vector3D operator /(const Vector3D& vector) const;

    /**
     * @brief Addition operator with a float scalar. Adds the scalar to each component.
     * @param value The scalar to add.
     * @return A new `Vector3D` incremented by `value`.
     */
    Vector3D operator +(const float& value) const;

    /**
     * @brief Subtraction operator with a float scalar. Subtracts the scalar from each component.
     * @param value The scalar to subtract.
     * @return A new `Vector3D` decremented by `value`.
     */
    Vector3D operator -(const float& value) const;

    /**
     * @brief Multiplication operator with a float scalar. Scales each component.
     * @param value The scalar factor.
     * @return A new `Vector3D` scaled by `value`.
     */
    Vector3D operator *(const float& value) const;

    /**
     * @brief Division operator with a float scalar. Divides each component by `value`.
     * @param value The scalar divisor.
     * @return A new `Vector3D` after division.
     */
    Vector3D operator /(const float& value) const;
};
