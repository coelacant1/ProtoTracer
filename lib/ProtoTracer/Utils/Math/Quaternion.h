/**
 * @file Quaternion.h
 * @brief Defines the Quaternion class for 3D rotations and transformations.
 *
 * This header provides a Quaternion class that supports various quaternion operations
 * (addition, multiplication, division, interpolation, etc.) as well as methods for
 * rotating 2D and 3D vectors. Quaternions are commonly used for representing rotations
 * in 3D space without suffering from some of the limitations of Euler angles (e.g.,
 * gimbal lock).
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Mathematics.h"
#include "Vector2D.h"
#include "Vector3D.h"

/**
 * @class Quaternion
 * @brief A mathematical construct representing a rotation in 3D space.
 *
 * Quaternions consist of a scalar part (W) and a vector part (X, Y, Z). They allow
 * smooth interpolation (slerp), concatenation of rotations, and are often used to
 * avoid gimbal lock problems that can occur when using Euler angles.
 */
class Quaternion {
public:
    float W; ///< Scalar part of the quaternion.
    float X; ///< X component of the quaternion's vector part.
    float Y; ///< Y component of the quaternion's vector part.
    float Z; ///< Z component of the quaternion's vector part.

    /**
     * @brief Default constructor. Initializes the quaternion to identity (1,0,0,0).
     */
    Quaternion();

    /**
     * @brief Copy constructor. Clones the values of another quaternion.
     * @param quaternion The quaternion to copy from.
     */
    Quaternion(const Quaternion& quaternion);

    /**
     * @brief Constructs a quaternion purely from a 3D vector (0, X, Y, Z).
     * @param vector The vector that forms the (X, Y, Z) part of the quaternion.
     *
     * The W component is initialized to 0.0f.
     */
    Quaternion(const Vector3D& vector);

    /**
     * @brief Constructs a quaternion with individual scalar and vector components.
     * @param w Scalar (real) component.
     * @param x X component of the vector part.
     * @param y Y component of the vector part.
     * @param z Z component of the vector part.
     */
    Quaternion(const float& w, const float& x, const float& y, const float& z);

    /**
     * @brief Rotates a 2D vector by this quaternion, projecting it in 2D.
     * @param v The 2D vector to rotate.
     * @return A new 2D vector that has been rotated.
     */
    Vector2D RotateVector(const Vector2D& v) const;

    /**
     * @brief Rotates a 2D vector by a unit quaternion (assumes normalized),
     *        allowing a different quaternion to be used if desired.
     * @param v The 2D vector to rotate.
     * @param q The (unit) quaternion to apply for the rotation.
     * @return A new 2D vector that has been rotated using \p q.
     */
    Vector2D RotateVectorUnit(const Vector2D& v, const Quaternion& q) const;

    /**
     * @brief Applies the inverse of this quaternion's rotation to a 2D vector.
     * @param coordinate The 2D vector to transform.
     * @return The unrotated 2D vector.
     */
    Vector2D UnrotateVector(const Vector2D& coordinate) const;

    /**
     * @brief Rotates a 3D vector by this quaternion.
     * @param v The 3D vector to rotate.
     * @return A new 3D vector that has been rotated.
     */
    Vector3D RotateVector(const Vector3D& v) const;

    /**
     * @brief Applies the inverse of this quaternion's rotation to a 3D vector.
     * @param coordinate The 3D vector to transform.
     * @return The unrotated 3D vector.
     */
    Vector3D UnrotateVector(const Vector3D& coordinate) const;

    /**
     * @brief Retrieves the bi-vector (X, Y, Z) portion of the quaternion (with W=0).
     * @return A 3D vector representing the (X, Y, Z) parts of this quaternion.
     */
    Vector3D GetBiVector() const;

    /**
     * @brief Retrieves the normal vector part of the quaternion, typically its axis of rotation.
     * @return A 3D vector representing the axis (X, Y, Z).
     */
    Vector3D GetNormal() const;

    /**
     * @brief Performs spherical linear interpolation (slerp) between two quaternions.
     * @param q1 The start quaternion.
     * @param q2 The end quaternion.
     * @param ratio A normalized value (0 to 1) indicating how far to interpolate from \p q1 to \p q2.
     * @return A new quaternion representing the slerped result.
     */
    static Quaternion SphericalInterpolation(const Quaternion& q1, const Quaternion& q2, const float& ratio);

    /**
     * @brief Computes a small rotation quaternion given an angular velocity and time delta.
     * @param angularVelocity A 3D vector representing the angular velocity (e.g., degrees/sec or radians/sec).
     * @param timeDelta The time step.
     * @return A new quaternion representing the rotation over the given time delta.
     */
    Quaternion DeltaRotation(const Vector3D& angularVelocity, const float& timeDelta) const;

    /**
     * @brief Adds two quaternions component-wise.
     * @param quaternion The quaternion to add to the current one.
     * @return A new quaternion representing the sum.
     */
    Quaternion Add(const Quaternion& quaternion) const;

    /**
     * @brief Subtracts a quaternion from this quaternion component-wise.
     * @param quaternion The quaternion to subtract.
     * @return A new quaternion representing the difference.
     */
    Quaternion Subtract(const Quaternion& quaternion) const;

    /**
     * @brief Multiplies (composes) this quaternion with another (order matters).
     * @param quaternion The right-hand side quaternion.
     * @return The resulting quaternion from the multiplication.
     */
    Quaternion Multiply(const Quaternion& quaternion) const;

    /**
     * @brief Scales this quaternion by a scalar factor.
     * @param scalar The scalar to multiply.
     * @return A new quaternion scaled by \p scalar.
     */
    Quaternion Multiply(const float& scalar) const;

    /**
     * @brief Divides this quaternion by another quaternion component-wise (not a typical quaternion operation).
     * @param quaternion The quaternion to divide by.
     * @return A new quaternion representing the component-wise result.
     */
    Quaternion Divide(const Quaternion& quaternion) const;

    /**
     * @brief Divides this quaternion by a scalar.
     * @param scalar The scalar divisor.
     * @return A new quaternion scaled by the reciprocal of \p scalar.
     */
    Quaternion Divide(const float& scalar) const;

    /**
     * @brief Raises this quaternion to the power of another quaternion (component-wise).
     * @param exponent The quaternion exponent.
     * @return A new quaternion representing the powered result.
     */
    Quaternion Power(const Quaternion& exponent) const;

    /**
     * @brief Raises this quaternion to a scalar power.
     * @param exponent The exponent (e.g., 2.0f).
     * @return A new quaternion representing this^exponent.
     */
    Quaternion Power(const float& exponent) const;

    /**
     * @brief Performs a permutation operation using a 3D vector (custom transform).
     * @param permutation A vector used for permuting the quaternion's components.
     * @return The permuted quaternion.
     */
    Quaternion Permutate(const Vector3D& permutation) const;

    /**
     * @brief Returns a quaternion where each component is the absolute value of the original.
     * @return A quaternion with absolute-valued components.
     */
    Quaternion Absolute() const;

    /**
     * @brief Negates each component (an additive inverse).
     * @return A quaternion representing -this.
     */
    Quaternion AdditiveInverse() const;

    /**
     * @brief Returns the multiplicative inverse of this quaternion, such that q * q^-1 = identity.
     * @return The multiplicative inverse.
     */
    Quaternion MultiplicativeInverse() const;

    /**
     * @brief Returns the conjugate of this quaternion (W stays the same, X/Y/Z get negated).
     * @return The conjugated quaternion.
     */
    Quaternion Conjugate() const;

    /**
     * @brief Returns a unit quaternion (normalized) version of this quaternion.
     * @return A normalized quaternion.
     */
    Quaternion UnitQuaternion() const;

    /**
     * @brief Computes the magnitude (length) of this quaternion.
     * @return The magnitude (sqrt(W^2 + X^2 + Y^2 + Z^2)).
     */
    float Magnitude() const;

    /**
     * @brief Computes the dot product between this quaternion and another.
     * @param q Another quaternion.
     * @return The dot product (W*W' + X*X' + Y*Y' + Z*Z').
     */
    float DotProduct(const Quaternion& q) const;

    /**
     * @brief Computes the quaternion's norm (equivalent to squared magnitude).
     * @return (W^2 + X^2 + Y^2 + Z^2).
     */
    float Normal() const;

    /**
     * @brief Checks if any component of this quaternion is NaN.
     * @return \c true if any component is NaN, otherwise \c false.
     */
    bool IsNaN() const;

    /**
     * @brief Checks if all components are finite.
     * @return \c true if finite, otherwise \c false.
     */
    bool IsFinite() const;

    /**
     * @brief Checks if any component is infinite.
     * @return \c true if infinite, otherwise \c false.
     */
    bool IsInfinite() const;

    /**
     * @brief Checks if the quaternion is non-zero (i.e., any component != 0).
     * @return \c true if non-zero, otherwise \c false.
     */
    bool IsNonZero() const;

    /**
     * @brief Checks if two quaternions are exactly equal (component-wise).
     * @param quaternion The quaternion to compare to.
     * @return \c true if all components match exactly.
     */
    bool IsEqual(const Quaternion& quaternion) const;

    /**
     * @brief Checks if two quaternions are nearly equal within a tolerance.
     * @param quaternion The quaternion to compare to.
     * @param epsilon The tolerance for comparison.
     * @return \c true if each component differs by less than \p epsilon.
     */
    bool IsClose(const Quaternion& quaternion, const float& epsilon) const;

    /**
     * @brief Converts this quaternion to a string representation (e.g. "(W, X, Y, Z)").
     * @return A \c String displaying the quaternion's components.
     */
    String ToString() const;

    // --- Operator Overloads ---

    /**
     * @brief Equality operator. Checks if two quaternions match exactly (component-wise).
     * @param quaternion The quaternion to compare.
     * @return \c true if equal, otherwise \c false.
     */
    bool operator ==(const Quaternion& quaternion) const;

    /**
     * @brief Inequality operator. Checks if two quaternions differ in any component.
     * @param quaternion The quaternion to compare.
     * @return \c true if not equal, otherwise \c false.
     */
    bool operator !=(const Quaternion& quaternion) const;

    /**
     * @brief Assignment operator. Copies another quaternion's components to this one.
     * @param quaternion The quaternion to copy.
     * @return A reference to this quaternion.
     */
    Quaternion operator =(const Quaternion& quaternion);

    /**
     * @brief Adds two quaternions (component-wise).
     * @param quaternion The right-hand side quaternion to add.
     * @return A new quaternion representing the sum.
     */
    Quaternion operator +(const Quaternion& quaternion) const;

    /**
     * @brief Subtracts one quaternion from another (component-wise).
     * @param quaternion The right-hand side quaternion to subtract.
     * @return A new quaternion representing the difference.
     */
    Quaternion operator -(const Quaternion& quaternion) const;

    /**
     * @brief Multiplies (composes) two quaternions.
     * @param quaternion The right-hand side quaternion.
     * @return A new quaternion representing the multiplication result.
     */
    Quaternion operator *(const Quaternion& quaternion) const;

    /**
     * @brief Divides this quaternion by another quaternion, component-wise.
     * @param quaternion The right-hand side quaternion divisor.
     * @return A new quaternion after division.
     */
    Quaternion operator /(const Quaternion& quaternion) const;

    /**
     * @brief Divides this quaternion by a scalar.
     * @param value The scalar divisor.
     * @return A new quaternion scaled by 1.0 / \p value.
     */
    Quaternion operator /(const float& value) const;

    /**
     * @brief Scalar multiplication operator (on the left).
     * @param scalar The scalar to multiply.
     * @param q The quaternion to scale.
     * @return A new quaternion scaled by \p scalar.
     */
    friend Quaternion operator *(const float& scalar, const Quaternion& q);

    /**
     * @brief Scalar multiplication operator (on the right).
     * @param q The quaternion to scale.
     * @param scalar The scalar to multiply.
     * @return A new quaternion scaled by \p scalar.
     */
    friend Quaternion operator *(const Quaternion& q, const float& scalar);

    // --- Static Utility Functions ---

    /**
     * @brief Static convenience function: Adds two quaternions.
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @return A new quaternion representing the sum.
     */
    static Quaternion Add(const Quaternion& q1, const Quaternion& q2);

    /**
     * @brief Static convenience function: Subtracts one quaternion from another.
     * @param q1 The first quaternion.
     * @param q2 The second quaternion to subtract from \p q1.
     * @return A new quaternion representing the difference.
     */
    static Quaternion Subtract(const Quaternion& q1, const Quaternion& q2);

    /**
     * @brief Static convenience function: Multiplies (composes) two quaternions.
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @return The resulting quaternion composition.
     */
    static Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);

    /**
     * @brief Static convenience function: Divides one quaternion by another (component-wise).
     * @param q1 The first quaternion.
     * @param q2 The second quaternion (divisor).
     * @return A new quaternion representing the division result.
     */
    static Quaternion Divide(const Quaternion& q1, const Quaternion& q2);

    /**
     * @brief Static convenience function: Raises one quaternion to the power of another (component-wise).
     * @param q1 The base quaternion.
     * @param q2 The exponent quaternion.
     * @return A new quaternion representing the power result.
     */
    static Quaternion Power(const Quaternion& q1, const Quaternion& q2);

    /**
     * @brief Static convenience function: Computes the dot product of two quaternions.
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @return The scalar dot product.
     */
    static float DotProduct(const Quaternion& q1, const Quaternion& q2);

    /**
     * @brief Static convenience function: Raises a quaternion to a scalar power.
     * @param quaternion The base quaternion.
     * @param exponent The scalar exponent.
     * @return A new quaternion representing the power result.
     */
    static Quaternion Power(const Quaternion& quaternion, const float& exponent);

    /**
     * @brief Static convenience function: Permutates a quaternion with a 3D vector input.
     * @param quaternion The base quaternion.
     * @param vector A 3D vector used for permutation.
     * @return The permuted quaternion.
     */
    static Quaternion Permutate(const Quaternion& quaternion, const Vector3D& vector);

    /**
     * @brief Static convenience function: Returns a quaternion with absolute values of its components.
     * @param quaternion The input quaternion.
     * @return A quaternion whose components are the absolute values of \p quaternion's components.
     */
    static Quaternion Absolute(const Quaternion& quaternion);

    /**
     * @brief Static convenience function: Returns the additive inverse of a quaternion.
     * @param quaternion The input quaternion.
     * @return A quaternion representing -q.
     */
    static Quaternion AdditiveInverse(const Quaternion& quaternion);

    /**
     * @brief Static convenience function: Returns the multiplicative inverse of a quaternion.
     * @param quaternion The input quaternion.
     * @return A quaternion such that q * q^-1 = identity.
     */
    static Quaternion MultiplicativeInverse(const Quaternion& quaternion);

    /**
     * @brief Static convenience function: Returns the conjugate of a quaternion.
     * @param quaternion The input quaternion.
     * @return A quaternion with (W, -X, -Y, -Z).
     */
    static Quaternion Conjugate(const Quaternion& quaternion);

    /**
     * @brief Static convenience function: Normalizes a quaternion, returning a unit quaternion.
     * @param quaternion The input quaternion.
     * @return A normalized quaternion.
     */
    static Quaternion UnitQuaternion(const Quaternion& quaternion);

    /**
     * @brief Static convenience function: Computes the magnitude of a quaternion.
     * @param quaternion The input quaternion.
     * @return The magnitude (length) of \p quaternion.
     */
    static float Magnitude(const Quaternion& quaternion);

    /**
     * @brief Static convenience function: Computes the norm (squared magnitude) of a quaternion.
     * @param quaternion The input quaternion.
     * @return The squared length of \p quaternion.
     */
    static float Normal(const Quaternion& quaternion);
};
