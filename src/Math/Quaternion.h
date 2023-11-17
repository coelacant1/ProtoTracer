#pragma once

#include "Vector2D.h"
#include "Vector3D.h"

class Quaternion {
public:
    float W;
    float X;
    float Y;
    float Z;

    Quaternion();
    Quaternion(const Quaternion& quaternion);
    Quaternion(Vector3D vector);
    Quaternion(float w, float x, float y, float z);

    Vector2D RotateVector(Vector2D v);
    Vector2D RotateVectorUnit(Vector2D v, const Quaternion& q);
    Vector2D UnrotateVector(Vector2D coordinate);
    Vector3D RotateVector(Vector3D v);
    Vector3D UnrotateVector(Vector3D coordinate);
    Vector3D GetBiVector();

    static Quaternion SphericalInterpolation(Quaternion q1, Quaternion q2, float ratio);
    Quaternion DeltaRotation(Vector3D angularVelocity, float timeDelta);
    
    Quaternion Add(Quaternion quaternion);
    Quaternion Subtract(Quaternion quaternion);
    Quaternion Multiply(Quaternion quaternion);
    Quaternion Multiply(float scalar);
    Quaternion Divide(Quaternion quaternion);
    Quaternion Divide(float scalar);
    Quaternion Power(Quaternion exponent);
    Quaternion Power(float exponent);
    Quaternion Permutate(Vector3D permutation);
    Quaternion Absolute();
    Quaternion AdditiveInverse();
    Quaternion MultiplicativeInverse();
    Quaternion Conjugate();
    Quaternion UnitQuaternion();

    float Magnitude();
    float DotProduct(Quaternion q);
    float Normal();

    bool IsNaN();
    bool IsFinite();
    bool IsInfinite();
    bool IsNonZero();
    bool IsEqual(Quaternion quaternion);
    bool IsClose(Quaternion quaternion, float epsilon);

    String ToString();

    // Operator overloads
    bool operator ==(Quaternion quaternion);
    bool operator !=(Quaternion quaternion);
    Quaternion operator =(Quaternion quaternion);
    Quaternion operator +(Quaternion quaternion);
    Quaternion operator -(Quaternion quaternion);
    Quaternion operator *(Quaternion quaternion);
    Quaternion operator /(Quaternion quaternion);
    Quaternion operator /(float value);

    friend Quaternion operator *(float scalar, Quaternion q);
    friend Quaternion operator *(Quaternion q, float scalar);

    // Static functions
    static Quaternion Add(Quaternion q1, Quaternion q2);
    static Quaternion Subtract(Quaternion q1, Quaternion q2);
    static Quaternion Multiply(Quaternion q1, Quaternion q2);
    static Quaternion Divide(Quaternion q1, Quaternion q2);
    static Quaternion Power(Quaternion q1, Quaternion q2);
    static float DotProduct(Quaternion q1, Quaternion q2);
    static Quaternion Power(Quaternion quaternion, float exponent);
    static Quaternion Permutate(Quaternion quaternion, Vector3D vector);
    static Quaternion Absolute(Quaternion quaternion);
    static Quaternion AdditiveInverse(Quaternion quaternion);
    static Quaternion MultiplicativeInverse(Quaternion quaternion);
    static Quaternion Conjugate(Quaternion quaternion);
    static Quaternion UnitQuaternion(Quaternion quaternion);
    static float Magnitude(Quaternion quaternion);
    static float Normal(Quaternion quaternion);
};
