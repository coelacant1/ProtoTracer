#pragma once

#include "Mathematics.h"

class Vector3D {
public:
    float X;
    float Y;
    float Z;

    Vector3D();
    Vector3D(const Vector3D& vector);
    Vector3D(float X, float Y, float Z);

    Vector3D Absolute();
    Vector3D Normal();
    Vector3D Add(float value);
    Vector3D Subtract(float value);
    Vector3D Add(Vector3D vector);
    Vector3D Subtract(Vector3D vector);
    Vector3D Multiply(Vector3D vector);
    Vector3D Divide(Vector3D vector);
    Vector3D Multiply(float scalar);
    Vector3D Divide(float scalar);
    Vector3D CrossProduct(Vector3D vector);
    Vector3D UnitSphere();
    Vector3D Constrain(float minimum, float maximum);
    Vector3D Constrain(Vector3D minimum, Vector3D maximum);
    float Magnitude();
    float DotProduct(Vector3D vector);
    float CalculateEuclideanDistance(Vector3D vector);
    bool IsEqual(Vector3D vector);
    String ToString();

    static Vector3D Max(Vector3D max, Vector3D input);
    static Vector3D Min(Vector3D min, Vector3D input);
    static Vector3D LERP(Vector3D start, Vector3D finish, float ratio);
    static Vector3D DegreesToRadians(Vector3D degrees);
    static Vector3D RadiansToDegrees(Vector3D radians);

    // Static function declarations
    static Vector3D Normal(Vector3D vector);
    static Vector3D Add(Vector3D v1, Vector3D v2);
    static Vector3D Subtract(Vector3D v1, Vector3D v2);
    static Vector3D Multiply(Vector3D v1, Vector3D v2);
    static Vector3D Divide(Vector3D v1, Vector3D v2);
    static Vector3D Multiply(Vector3D vector, float scalar);
    static Vector3D Multiply(float scalar, Vector3D vector);
    static Vector3D Divide(Vector3D vector, float scalar);
    static Vector3D CrossProduct(Vector3D v1, Vector3D v2);
    static float DotProduct(Vector3D v1, Vector3D v2);
    static float CalculateEuclideanDistance(Vector3D v1, Vector3D v2);
    static bool IsEqual(Vector3D v1, Vector3D v2);

    // Operator overloads
    bool operator ==(Vector3D vector);
    bool operator !=(Vector3D vector);
    Vector3D operator =(Vector3D vector);
    Vector3D operator +(Vector3D vector);
    Vector3D operator -(Vector3D vector);
    Vector3D operator *(Vector3D vector);
    Vector3D operator /(Vector3D vector);
    Vector3D operator +(float value);
    Vector3D operator -(float value);
    Vector3D operator *(float value);
    Vector3D operator /(float value);
};
