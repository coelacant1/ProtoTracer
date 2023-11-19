#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

class Vector2D {
public:
    float X;
    float Y;

    Vector2D();
    Vector2D(const Vector2D& vector);
    Vector2D(float X, float Y);
    Vector2D(const Vector3D& vector);

    Vector2D Absolute();
    Vector2D Normal();
    Vector2D Add(Vector2D vector);
    Vector2D Subtract(Vector2D vector);
    Vector2D Multiply(Vector2D vector);
    Vector2D Divide(Vector2D vector);
    Vector2D Multiply(float scalar);
    Vector2D Divide(float scalar);
    Vector3D CrossProduct(Vector2D vector);
    Vector2D UnitCircle();
    Vector2D Constrain(float minimum, float maximum);
    Vector2D Constrain(Vector2D minimum, Vector2D maximum);
    Vector2D Minimum(Vector2D v);
    Vector2D Maximum(Vector2D v);
    Vector2D Rotate(float angle, Vector2D offset);
    bool CheckBounds(Vector2D minimum, Vector2D maximum);
    float Magnitude();
    float DotProduct(Vector2D vector);
    float CalculateEuclideanDistance(Vector2D vector);
    bool IsEqual(Vector2D vector);
    String ToString();
	
	// Static function declarations
    static Vector2D Normal(Vector2D vector);
    static Vector2D Add(Vector2D v1, Vector2D v2);
    static Vector2D Subtract(Vector2D v1, Vector2D v2);
    static Vector2D Multiply(Vector2D v1, Vector2D v2);
    static Vector2D Divide(Vector2D v1, Vector2D v2);
    static Vector2D Multiply(Vector2D vector, float scalar);
    static Vector2D Multiply(float scalar, Vector2D vector);
    static Vector2D Divide(Vector2D vector, float scalar);
    static Vector3D CrossProduct(Vector2D v1, Vector2D v2);
    static float DotProduct(Vector2D v1, Vector2D v2);
    static float CalculateEuclideanDistance(Vector2D v1, Vector2D v2);
    static bool IsEqual(Vector2D v1, Vector2D v2);
    static Vector2D Minimum(Vector2D v1, Vector2D v2);
    static Vector2D Maximum(Vector2D v1, Vector2D v2);
    static Vector2D LERP(Vector2D start, Vector2D finish, float ratio);
    static Vector2D DegreesToRadians(Vector2D degrees);
    static Vector2D RadiansToDegrees(Vector2D radians);

    // Operator overloads
    bool operator ==(Vector2D vector);
    bool operator !=(Vector2D vector);
    Vector2D operator =(Vector2D vector);
    Vector2D operator =(Vector3D vector);
    Vector2D operator +(Vector2D vector);
    Vector2D operator -(Vector2D vector);
    Vector2D operator *(Vector2D vector);
    Vector2D operator /(Vector2D vector);
    Vector2D operator *(float value);
    Vector2D operator /(float value);
};
