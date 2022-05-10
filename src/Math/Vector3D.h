#pragma once

#include "Mathematics.h"

typedef struct Vector3D {
public:
    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;

    Vector3D() {}

    Vector3D(const Vector3D &vector)
        : X(vector.X),
          Y(vector.Y),
          Z(vector.Z) {}

    Vector3D(const float X, const float Y, const float Z)
        : X(X),
          Y(Y),
          Z(Z) {}

    Vector3D Absolute() const {
        return Vector3D(
            fabsf(this->X),
            fabsf(this->Y),
            fabsf(this->Z));
    }

    Vector3D Normal() const {
        const float magn = Magnitude();

        if (Mathematics::IsClose(magn, 1.0f, Mathematics::EPSILON)) return *this;
        if (Mathematics::IsClose(magn, 0.0f, Mathematics::EPSILON)) return Vector3D(Mathematics::INF, Mathematics::INF, Mathematics::INF);
        return Multiply(1.0f / magn);
    }

    Vector3D Add(const float value) const {
        return Vector3D(
            this->X + value,
            this->Y + value,
            this->Z + value);
    }

    Vector3D Subtract(const float value) const {
        return Vector3D(
            this->X - value,
            this->Y - value,
            this->Z - value);
    }

    Vector3D Add(const Vector3D &vector) const {
        return Vector3D(
            this->X + vector.X,
            this->Y + vector.Y,
            this->Z + vector.Z);
    }

    Vector3D Subtract(const Vector3D &vector) const {
        return Vector3D{
            this->X - vector.X,
            this->Y - vector.Y,
            this->Z - vector.Z};
    }

    Vector3D Multiply(const Vector3D &vector) const {
        return Vector3D{
            this->X * vector.X,
            this->Y * vector.Y,
            this->Z * vector.Z};
    }

    Vector3D Divide(const Vector3D &vector) const {
        return Vector3D{
            this->X / vector.X,
            this->Y / vector.Y,
            this->Z / vector.Z};
    }

    Vector3D Multiply(const float scalar) const {
        return Vector3D(
            this->X * scalar,
            this->Y * scalar,
            this->Z * scalar);
    }

    Vector3D Divide(const float scalar) const {
        const float divisor = 1.0f / scalar;
        return Vector3D(
            this->X * divisor,
            this->Y * divisor,
            this->Z * divisor);
    }

    Vector3D CrossProduct(const Vector3D &vector) const {
        return Vector3D(
            (this->Y * vector.Z) - (this->Z * vector.Y),
            (this->Z * vector.X) - (this->X * vector.Z),
            (this->X * vector.Y) - (this->Y * vector.X));
    }

    Vector3D UnitSphere() const {
        const float length = Magnitude();

        if (Mathematics::IsClose(length, 1.0f, Mathematics::EPSILON)) return Vector3D(X, Y, Z);
        if (length == 0) return Vector3D(0, 1, 0);

        return Vector3D(
            X / length,
            Y / length,
            Z / length);
    }

    Vector3D Constrain(const float minimum, const float maximum) const {
        return Vector3D(
            Mathematics::Constrain(X, minimum, maximum),
            Mathematics::Constrain(Y, minimum, maximum),
            Mathematics::Constrain(Z, minimum, maximum));
    }

    Vector3D Constrain(const Vector3D &minimum, const Vector3D &maximum) const {
        return Vector3D(
            Mathematics::Constrain(X, minimum.X, maximum.X),
            Mathematics::Constrain(Y, minimum.Y, maximum.Y),
            Mathematics::Constrain(Z, minimum.Z, maximum.Z));
    }

    float Magnitude() const {
        return Mathematics::Sqrt(X * X + Y * Y + Z * Z);
    }

    float DotProduct(const Vector3D &vector) const {
        return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z);
    }

    float CalculateEuclideanDistance(const Vector3D &vector) const {
        return Subtract(vector).Magnitude();
    }

    bool IsEqual(const Vector3D &vector) const {
        return (this->X == vector.X) && (this->Y == vector.Y) && (this->Z == vector.Z);
    }

    String ToString() const {
        const String x = Mathematics::DoubleToCleanString(this->X);
        const String y = Mathematics::DoubleToCleanString(this->Y);
        const String z = Mathematics::DoubleToCleanString(this->Z);

        return "[" + x + ", " + y + ", " + z + "]";
    }

    static const Vector3D Max(const Vector3D &max, const Vector3D &input) {
        return Vector3D(input.X > max.X ? input.X : max.X,
                        input.Y > max.Y ? input.Y : max.Y,
                        input.Z > max.Z ? input.Z : max.Z);
    }

    static const Vector3D Min(const Vector3D &min, const Vector3D &input) {
        return Vector3D(input.X < min.X ? input.X : min.X,
                        input.Y < min.Y ? input.Y : min.Y,
                        input.Z < min.Z ? input.Z : min.Z);
    }

    static const Vector3D LERP(const Vector3D &start, const Vector3D &finish, const float ratio) {
        return finish * ratio + start * (1.0f - ratio);
    }

    static const Vector3D DegreesToRadians(const Vector3D &degrees) {
        return degrees * Mathematics::MPID180;
    }

    static const Vector3D RadiansToDegrees(const Vector3D &radians) {
        return radians * Mathematics::M180DPI;
    }

    // Operator overloads
    bool operator==(const Vector3D &vector) const {
        return IsEqual(vector);
    }

    bool operator!=(const Vector3D &vector) const {
        return !(this->IsEqual(vector));
    }

    Vector3D &operator=(const Vector3D &vector) {
        this->X = vector.X;
        this->Y = vector.Y;
        this->Z = vector.Z;

        return *this;
    }

    Vector3D operator+(const Vector3D &vector) const {
        return Add(vector);
    }

    Vector3D operator-(const Vector3D &vector) const {
        return Subtract(vector);
    }

    Vector3D operator*(const Vector3D &vector) const {
        return Multiply(vector);
    }

    Vector3D operator/(const Vector3D &vector) const {
        return Divide(vector);
    }

    Vector3D operator+(const float value) const {
        return Add(value);
    }

    Vector3D operator-(const float value) const {
        return Subtract(value);
    }

    Vector3D operator*(float value) const {
        return Multiply(value);
    }

    Vector3D operator/(float value) const {
        return Divide(value);
    }

    Vector3D& operator+=(const Vector3D &vector){
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;

        return *this;
    }
    Vector3D& operator-=(const Vector3D &vector){
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;

        return *this;
    }
    Vector3D& operator*=(const Vector3D &vector){
        X *= vector.X;
        Y *= vector.Y;
        Z *= vector.Z;

        return *this;
    }
    Vector3D& operator/=(const Vector3D &vector){
        X /= vector.X;
        Y /= vector.Y;
        Z /= vector.Z;

        return *this;
    }

    Vector3D& operator*=(const float value){
        X *= value;
        Y *= value;
        Z *= value;

        return *this;
    }
    Vector3D& operator/=(const float value){
        const float d = 1.0f / value;
        X *= d;
        Y *= d;
        Z *= d;

        return *this;
    }
} Vector3D;
