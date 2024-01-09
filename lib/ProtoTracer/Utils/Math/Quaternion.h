#pragma once

#include "Mathematics.h"
#include "Vector2D.h"
#include "Vector3D.h"

//#include <arm_math.h>

class Quaternion {
public:
    float W;
    float X;
    float Y;
    float Z;

    Quaternion();
    Quaternion(const Quaternion& quaternion);
    Quaternion(const Vector3D& vector);
    Quaternion(const float& w, const float& x, const float& y, const float& z);

    Vector2D RotateVector(const Vector2D& v) const;
    Vector2D RotateVectorUnit(const Vector2D& v, const Quaternion& q) const;
    Vector2D UnrotateVector(const Vector2D& coordinate) const;
    Vector3D RotateVector(const Vector3D& v) const;
    Vector3D UnrotateVector(const Vector3D& coordinate) const;
    Vector3D GetBiVector() const;

    static Quaternion SphericalInterpolation(const Quaternion& q1, const Quaternion& q2, const float& ratio);
    Quaternion DeltaRotation(const Vector3D& angularVelocity, const float& timeDelta) const;
    
    Quaternion Add(const Quaternion& quaternion) const;
    Quaternion Subtract(const Quaternion& quaternion) const;
    Quaternion Multiply(const Quaternion& quaternion) const;
    Quaternion Multiply(const float& scalar) const;
    Quaternion Divide(const Quaternion& quaternion) const;
    Quaternion Divide(const float& scalar) const;
    Quaternion Power(const Quaternion& exponent) const;
    Quaternion Power(const float& exponent) const;
    Quaternion Permutate(const Vector3D& permutation) const;
    Quaternion Absolute() const;
    Quaternion AdditiveInverse() const;
    Quaternion MultiplicativeInverse() const;
    Quaternion Conjugate() const;
    Quaternion UnitQuaternion() const;

    float Magnitude() const;
    float DotProduct(const Quaternion& q) const;
    float Normal() const;

    bool IsNaN() const;
    bool IsFinite() const;
    bool IsInfinite() const;
    bool IsNonZero() const;
    bool IsEqual(const Quaternion& quaternion) const;
    bool IsClose(const Quaternion& quaternion, const float& epsilon) const;

    String ToString() const;

    // Operator overloads
    bool operator ==(const Quaternion& quaternion) const;
    bool operator !=(const Quaternion& quaternion) const;
    Quaternion operator =(const Quaternion& quaternion);
    Quaternion operator +(const Quaternion& quaternion) const;
    Quaternion operator -(const Quaternion& quaternion) const;
    Quaternion operator *(const Quaternion& quaternion) const;
    Quaternion operator /(const Quaternion& quaternion) const;
    Quaternion operator /(const float& value) const;

    friend Quaternion operator *(const float& scalar, const Quaternion& q);
    friend Quaternion operator *(const Quaternion& q, const float& scalar);

    // Static functions
    static Quaternion Add(const Quaternion& q1, const Quaternion& q2);
    static Quaternion Subtract(const Quaternion& q1, const Quaternion& q2);
    static Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);
    static Quaternion Divide(const Quaternion& q1, const Quaternion& q2);
    static Quaternion Power(const Quaternion& q1, const Quaternion& q2);
    static float DotProduct(const Quaternion& q1, const Quaternion& q2);
    static Quaternion Power(const Quaternion& quaternion, const float& exponent);
    static Quaternion Permutate(const Quaternion& quaternion, const Vector3D& vector);
    static Quaternion Absolute(const Quaternion& quaternion);
    static Quaternion AdditiveInverse(const Quaternion& quaternion);
    static Quaternion MultiplicativeInverse(const Quaternion& quaternion);
    static Quaternion Conjugate(const Quaternion& quaternion);
    static Quaternion UnitQuaternion(const Quaternion& quaternion);
    static float Magnitude(const Quaternion& quaternion);
    static float Normal(const Quaternion& quaternion);
};
