#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

class Vector2D {
public:
    float X;
    float Y;

    Vector2D();
    Vector2D(const Vector2D& vector);
    Vector2D(const float& X, const float& Y);
    Vector2D(const Vector3D& vector);

    Vector2D Absolute() const;
    Vector2D Normal() const;
    Vector2D Add(const Vector2D& vector) const;
    Vector2D Subtract(const Vector2D& vector) const;
    Vector2D Multiply(const Vector2D& vector) const;
    Vector2D Divide(const Vector2D& vector) const;
    Vector2D Multiply(const float& scalar) const;
    Vector2D Divide(const float& scalar) const;
    Vector3D CrossProduct(const Vector2D& vector) const;
    Vector2D UnitCircle() const;
    Vector2D Constrain(const float& minimum, const float& maximum) const;
    Vector2D Constrain(const Vector2D& minimum, const Vector2D& maximum) const;
    Vector2D Minimum(const Vector2D& v) const;
    Vector2D Maximum(const Vector2D& v) const;
    Vector2D Rotate(const float& angle, const Vector2D& offset) const;
    bool CheckBounds(const Vector2D& minimum, const Vector2D& maximum) const;
    float Magnitude() const;
    float DotProduct(const Vector2D& vector) const;
    float CalculateEuclideanDistance(const Vector2D& vector) const;
    bool IsEqual(const Vector2D& vector) const;
    String ToString() const;
	
	// Static function declarations
    static Vector2D Normal(const Vector2D& vector);
    static Vector2D Add(const Vector2D& v1, const Vector2D& v2);
    static Vector2D Subtract(const Vector2D& v1, const Vector2D& v2);
    static Vector2D Multiply(const Vector2D& v1, const Vector2D& v2);
    static Vector2D Divide(const Vector2D& v1, const Vector2D& v2);
    static Vector2D Multiply(const Vector2D& vector, const float& scalar);
    static Vector2D Multiply(const float& scalar, const Vector2D& vector);
    static Vector2D Divide(const Vector2D& vector, const float& scalar);
    static Vector3D CrossProduct(const Vector2D& v1, const Vector2D& v2);
    static float DotProduct(const Vector2D& v1, const Vector2D& v2);
    static float CalculateEuclideanDistance(const Vector2D& v1, const Vector2D& v2);
    static bool IsEqual(const Vector2D& v1, const Vector2D& v2);
    static Vector2D Minimum(const Vector2D& v1, const Vector2D& v2);
    static Vector2D Maximum(const Vector2D& v1, const Vector2D& v2);
    static Vector2D LERP(const Vector2D& start, const Vector2D& finish, const float& ratio);
    static Vector2D DegreesToRadians(const Vector2D& degrees);
    static Vector2D RadiansToDegrees(const Vector2D& radians);

    // Operator overloads
    bool operator ==(const Vector2D& vector) const;
    bool operator !=(const Vector2D& vector) const;
    Vector2D operator =(const Vector2D& vector);
    Vector2D operator =(const Vector3D& vector);
    Vector2D operator +(const Vector2D& vector) const;
    Vector2D operator -(const Vector2D& vector) const;
    Vector2D operator *(const Vector2D& vector) const;
    Vector2D operator /(const Vector2D& vector) const;
    Vector2D operator *(const float& value) const;
    Vector2D operator /(const float& value) const;
};
