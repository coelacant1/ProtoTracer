#pragma once

#include "Mathematics.h"

class Vector3D {
public:
    float X;
    float Y;
    float Z;

    Vector3D();
    Vector3D(const Vector3D& vector);
    Vector3D(const Vector3D* vector);
    Vector3D(const float& X, const float& Y, const float& Z);

    Vector3D Absolute() const;
    Vector3D Normal() const;
    Vector3D Add(const float& value) const;
    Vector3D Subtract(const float& value) const;
    Vector3D Add(const Vector3D& vector) const;
    Vector3D Subtract(const Vector3D& vector) const;
    Vector3D Multiply(const Vector3D& vector) const;
    Vector3D Divide(const Vector3D& vector) const;
    Vector3D Multiply(const float& scalar) const;
    Vector3D Divide(const float& scalar) const;
    Vector3D CrossProduct(const Vector3D& vector) const;
    Vector3D UnitSphere() const;
    Vector3D Constrain(const float& minimum, const float& maximum) const;
    Vector3D Constrain(const Vector3D& minimum, const Vector3D& maximum) const;
    Vector3D Permutate(const Vector3D& permutation) const;
    float Magnitude() const;
    float DotProduct(const Vector3D& vector) const;
    float CalculateEuclideanDistance(const Vector3D& vector) const;
    float AverageHighestTwoComponents() const;
    float Max() const;
    float Min() const;
    bool IsEqual(const Vector3D& vector) const;
    String ToString() const;

    static Vector3D Max(const Vector3D& max, const Vector3D& input);
    static Vector3D Min(const Vector3D& min, const Vector3D& input);
    static Vector3D LERP(const Vector3D& start, const Vector3D& finish, const float& ratio);
    static Vector3D DegreesToRadians(const Vector3D& degrees);
    static Vector3D RadiansToDegrees(const Vector3D& radians);

    // Static function declarations
    static Vector3D Normal(const Vector3D& vector);
    static Vector3D Add(const Vector3D& v1, const Vector3D& v2);
    static Vector3D Subtract(const Vector3D& v1, const Vector3D& v2);
    static Vector3D Multiply(const Vector3D& v1, const Vector3D& v2);
    static Vector3D Divide(const Vector3D& v1, const Vector3D& v2);
    static Vector3D Multiply(const Vector3D& vector, const float& scalar);
    static Vector3D Multiply(const float& scalar, const Vector3D& vector);
    static Vector3D Divide(const Vector3D& vector, const float& scalar);
    static Vector3D CrossProduct(const Vector3D& v1, const Vector3D& v2);
    static float DotProduct(const Vector3D& v1, const Vector3D& v2);
    static float CalculateEuclideanDistance(const Vector3D& v1, const Vector3D& v2);
    static bool IsEqual(const Vector3D& v1, const Vector3D& v2);

    // Operator overloads
    bool operator ==(const Vector3D& vector) const;
    bool operator !=(const Vector3D& vector) const;
    Vector3D operator +=(const Vector3D& vector);
    Vector3D operator =(const Vector3D& vector);
    Vector3D operator +(const Vector3D& vector) const;
    Vector3D operator -(const Vector3D& vector) const;
    Vector3D operator *(const Vector3D& vector) const;
    Vector3D operator /(const Vector3D& vector) const;
    Vector3D operator +(const float& value) const;
    Vector3D operator -(const float& value) const;
    Vector3D operator *(const float& value) const;
    Vector3D operator /(const float& value) const;
};
