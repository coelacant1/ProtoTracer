#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

typedef struct Vector2D {
public:
    float X = 0.0f;
    float Y = 0.0f;

    Vector2D() {}
    Vector2D(const Vector2D &vector)
        : X(vector.X),
          Y(vector.Y) {}
    Vector2D(const float X, const float Y)
        : X(X),
          Y(Y) {}
    Vector2D(const Vector3D &vector)
        : X(vector.X),
          Y(vector.Y) {}

    Vector2D Absolute() const {
        return Vector2D(
            fabsf(X),
            fabsf(Y));
    }

    Vector2D Normal() const {
        const float magn = Magnitude();

        if (Mathematics::IsClose(magn, 1.0f, Mathematics::EPSILON)) return *this;
        if (Mathematics::IsClose(magn, 0.0f, Mathematics::EPSILON)) return Vector2D(Mathematics::INF, Mathematics::INF);
        return Multiply(1.0f / magn);
    }

    Vector2D Add(const Vector2D &vector) const {
        return Vector2D(
            X + vector.X,
            Y + vector.Y);
    }

    Vector2D Subtract(const Vector2D &vector) const {
        return Vector2D(
            X - vector.X,
            Y - vector.Y);
    }

    Vector2D Multiply(const Vector2D &vector) const {
        return Vector2D(
            X * vector.X,
            Y * vector.Y);
    }

    Vector2D Divide(const Vector2D &vector) const {
        return Vector2D(
            X / vector.X,
            Y / vector.Y);
    }

    Vector2D Multiply(const float scalar) const {
        if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return *this;
        if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Vector2D();

        return Vector2D(
            X * scalar,
            Y * scalar);
    }

    Vector2D Divide(const float scalar) const {
        if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return (*this);
        if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Vector2D();

        const float divisor = 1.0f / scalar; 
        return Vector2D(
            X * divisor,
            Y * divisor);
    }

    Vector3D CrossProduct(const Vector2D &vector) const {
        return Vector3D(
            0.0f,
            0.0f,
            (X * vector.Y) - (Y * vector.X));
    }

    Vector2D UnitCircle() const {
        const float length = Magnitude();

        if (Mathematics::IsClose(length, 1.0f, Mathematics::EPSILON)) return Vector2D(X, Y);
        if (length == 0) return Vector2D(0, 1);

        const float divisor = 1.0f / length; 
        return Vector2D(
            X * divisor,
            Y * divisor);
    }

    Vector2D Constrain(const float minimum, const float maximum) const {
        return Vector2D(
            Mathematics::Constrain(X, minimum, maximum),
            Mathematics::Constrain(Y, minimum, maximum));
    }

    Vector2D Constrain(const Vector2D &minimum, const Vector2D &maximum) const {
        return Vector2D(
            Mathematics::Constrain(X, minimum.X, maximum.X),
            Mathematics::Constrain(Y, minimum.Y, maximum.Y));
    }

    Vector2D Minimum(const Vector2D &v) const {
        return Vector2D(
            X < v.X ? X : v.X,
            Y < v.Y ? Y : v.Y);
    }

    Vector2D Maximum(const Vector2D &v) const {
        return Vector2D(
            X > v.X ? X : v.X,
            Y > v.Y ? Y : v.Y);
    }

    Vector2D Rotate(float angle, const Vector2D &offset) const {
        const Vector2D v = Vector2D(X, Y) - offset;

        angle *= Mathematics::MPID180;

        const float cs = cosf(angle);
        const float sn = sinf(angle);

        return Vector2D(
            v.X * cs - v.Y * sn + offset.X,
            v.X * sn + v.Y * cs + offset.Y);
    }

    bool CheckBounds(const Vector2D &minimum, const Vector2D &maximum) const {
        return X > minimum.X && X < maximum.X && Y > minimum.Y && Y < maximum.Y;
    }

    float Magnitude() const {
        return Mathematics::Sqrt(X * X + Y * Y);
    }

    float DotProduct(const Vector2D &vector) const {
        return (X * vector.X) + (Y * vector.Y);
    }

    float CalculateEuclideanDistance(const Vector2D &vector) const {
        return Subtract(vector).Magnitude();
    }

    bool IsEqual(const Vector2D &vector) const {
        return (X == vector.X) && (Y == vector.Y);
    }

    String ToString() const {
        const String x = Mathematics::DoubleToCleanString(X);
        const String y = Mathematics::DoubleToCleanString(Y);

        return "[" + x + ", " + y + "]";
    }

    static const Vector2D Minimum(const Vector2D &v1, const Vector2D &v2) {
        return Vector2D(
            v1.X < v2.X ? v1.X : v2.X,
            v1.Y < v2.Y ? v1.Y : v2.Y);
    }

    static const Vector2D Maximum(const Vector2D &v1, const Vector2D &v2) {
        return Vector2D(
            v1.X > v2.X ? v1.X : v2.X,
            v1.Y > v2.Y ? v1.Y : v2.Y);
    }

    static const Vector2D LERP(const Vector2D &start, const Vector2D &finish, const float ratio) {
        return finish * ratio + start * (1.0f - ratio);
    }

    static const Vector2D DegreesToRadians(const Vector2D &degrees) {
        return degrees * Mathematics::MPID180;
    }

    static const Vector2D RadiansToDegrees(const Vector2D &radians) {
        return radians * Mathematics::M180DPI;
    }

    // Operator overloads
    bool operator==(const Vector2D &vector) const {
        return IsEqual(vector);
    }

    bool operator!=(const Vector2D &vector) const {
        return !IsEqual(vector);
    }

    Vector2D &operator=(const Vector2D &vector) {
        X = vector.X;
        Y = vector.Y;

        return *this;
    }

    Vector2D &operator=(const Vector3D &vector) {
        X = vector.X;
        Y = vector.Y;

        return *this;
    }

    Vector2D operator+(const Vector2D &vector) const {
        return Add(vector);
    }

    Vector2D operator-(const Vector2D &vector) const {
        return Subtract(vector);
    }

    Vector2D operator*(const Vector2D &vector) const {
        return Multiply(vector);
    }

    Vector2D operator/(const Vector2D &vector) const {
        return Divide(vector);
    }

    Vector2D operator*(const float value) const {
        return Multiply(value);
    }

    Vector2D operator/(const float value) const {
        return Divide(value);
    }
} Vector2D;
