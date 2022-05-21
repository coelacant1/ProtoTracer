#pragma once

#include "Mathematics.h"
#include "Vector2D.h"
#include "Vector3D.h"

typedef struct Quaternion {
public:
    float W = 1.0f;
    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;

    Quaternion() {}

    Quaternion(const Quaternion &quaternion)
        : W(quaternion.W),
          X(quaternion.X),
          Y(quaternion.Y),
          Z(quaternion.Z) {}

    Quaternion(const Vector3D &vector)
        : W(0.0f),
          X(vector.X),
          Y(vector.Y),
          Z(vector.Z) {}

    Quaternion(const float w, const float x, const float y, const float z)
        : W(w),
          X(x),
          Y(y),
          Z(z) {}

    Vector2D RotateVector(const Vector2D &v) const {
        if (this->IsClose(Quaternion(), Mathematics::EPSILON)) return v;

        const Quaternion q = UnitQuaternion();

        const float s2 = q.W * 2.0f;
        const float dPUV = (q.X * v.X + q.Y * v.Y) * 2.0f;
        const float dPUU = q.W * q.W - (q.X * q.X + q.Y * q.Y + q.Z * q.Z);

        return Vector2D(
            X * dPUV + v.X * dPUU + (-(q.Z * v.Y)) * s2,
            Y * dPUV + v.Y * dPUU + ((q.Z * v.X)) * s2);
    }

    Vector2D UnrotateVector(const Vector2D &coordinate) const {
        if (IsClose(Quaternion(), Mathematics::EPSILON)) return coordinate;

        return Conjugate().RotateVector(coordinate);
    }

    Vector3D RotateVector(const Vector3D &v) const {
        if (IsClose(Quaternion(), Mathematics::EPSILON)) return v;

        const Quaternion q = UnitQuaternion();

        const float s2 = q.W * 2.0f;
        const float dPUV = (q.X * v.X + q.Y * v.Y + q.Z * v.Z) * 2.0f;
        const float dPUU = q.W * q.W - (q.X * q.X + q.Y * q.Y + q.Z * q.Z);

        return Vector3D(
            X * dPUV + v.X * dPUU + ((q.Y * v.Z) - (q.Z * v.Y)) * s2,
            Y * dPUV + v.Y * dPUU + ((q.Z * v.X) - (q.X * v.Z)) * s2,
            Z * dPUV + v.Z * dPUU + ((q.X * v.Y) - (q.Y * v.X)) * s2);
    }

    Vector3D UnrotateVector(const Vector3D &coordinate) const {
        if (IsClose(Quaternion(), Mathematics::EPSILON)) return coordinate;

        return UnitQuaternion().Conjugate().RotateVector(coordinate);
    }

    Vector3D GetBiVector() const {
        return Vector3D(X, Y, Z);
    }

    static const Quaternion SphericalInterpolation(Quaternion q1, Quaternion q2, const float ratio) {
        if (ratio <= Mathematics::EPSILON) return q1;
        if (ratio >= 1.0f - Mathematics::EPSILON) return q2;

        q1 = q1.UnitQuaternion();
        q2 = q2.UnitQuaternion();

        float dot = q1.DotProduct(q2); // Cosine between the two quaternions

        if (dot < 0.0f) // Shortest path correction
        {
            q1 = q1.AdditiveInverse();
            dot = -dot;
        }

        // Linearly interpolates if results are close
        if (dot > 0.999) return (q1 + (q2 - q1) * ratio).UnitQuaternion();

        dot = Mathematics::Constrain(dot, -1, 1);

        const float theta0 = acosf(dot);
        const float theta = theta0 * ratio;

        //Quaternion q3 = (q2 - (q1 * dot)).UnitQuaternion();//UQ for orthonomal
        const float f1 = cosf(theta) - dot * sinf(theta) / sinf(theta0);
        const float f2 = sinf(theta) / sinf(theta0);

        return (q1 * f1 + q2 * f2).UnitQuaternion();
    }

    Quaternion DeltaRotation(const Vector3D &angularVelocity, const float timeDelta) const {
        const Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);
        Vector3D halfAngle = angularVelocity * (timeDelta / 2.0f);
        const float halfAngleLength = halfAngle.Magnitude();

        if (halfAngleLength > Mathematics::EPSILON) { // exponential map
            halfAngle *= sinf(halfAngleLength) / halfAngleLength;
            return (current * Quaternion(cosf(halfAngleLength), halfAngle.X, halfAngle.Y, halfAngle.Z)).UnitQuaternion();
        }
        // first taylor series
        return (current * Quaternion(1.0f, halfAngle.X, halfAngle.Y, halfAngle.Z)).UnitQuaternion();
    }

    Quaternion Add(const Quaternion &quaternion) const {
        return Quaternion(
            W + quaternion.W,
            X + quaternion.X,
            Y + quaternion.Y,
            Z + quaternion.Z);
    }

    Quaternion Subtract(const Quaternion &quaternion) const {
        return Quaternion(
            W - quaternion.W,
            X - quaternion.X,
            Y - quaternion.Y,
            Z - quaternion.Z);
    }

    Quaternion Multiply(const Quaternion &quaternion) const {
        if (quaternion.IsClose(Quaternion(), Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);

        return Quaternion(
            W * quaternion.W - X * quaternion.X - Y * quaternion.Y - Z * quaternion.Z,
            W * quaternion.X + X * quaternion.W + Y * quaternion.Z - Z * quaternion.Y,
            W * quaternion.Y - X * quaternion.Z + Y * quaternion.W + Z * quaternion.X,
            W * quaternion.Z + X * quaternion.Y - Y * quaternion.X + Z * quaternion.W);
    }

    Quaternion Multiply(const float scalar) const {
        if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Quaternion();
        if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);

        return Quaternion(
            W * scalar,
            X * scalar,
            Y * scalar,
            Z * scalar);
    }

    Quaternion Divide(const Quaternion &quaternion) const {
        if (quaternion.IsClose(Quaternion(), Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);

        const float scale = 1.0f / (quaternion.W * quaternion.W + quaternion.X * quaternion.X + quaternion.Y * quaternion.Y + quaternion.Z * quaternion.Z);

        return Quaternion{
            (W * quaternion.W + X * quaternion.X + Y * quaternion.Y + Z * quaternion.Z) * scale,
            (-W * quaternion.X + X * quaternion.W + Y * quaternion.Z - Z * quaternion.Y) * scale,
            (-W * quaternion.Y - X * quaternion.Z + Y * quaternion.W + Z * quaternion.X) * scale,
            (-W * quaternion.Z + X * quaternion.Y - Y * quaternion.X + Z * quaternion.W) * scale};
    }

    Quaternion Divide(const float scalar) const {
        if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Quaternion();
        if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);

        const float d = 1.0f / scalar;

        return Quaternion{
            W * d,
            X * d,
            Y * d,
            Z * d};
    }

    Quaternion Power(const Quaternion &exponent) const {
        return Quaternion{
            Mathematics::Pow(W, exponent.W),
            Mathematics::Pow(X, exponent.X),
            Mathematics::Pow(Y, exponent.Y),
            Mathematics::Pow(Z, exponent.Z)};
    }

    Quaternion Power(const float &exponent) const {
        return Quaternion{
            Mathematics::Pow(W, exponent),
            Mathematics::Pow(X, exponent),
            Mathematics::Pow(Y, exponent),
            Mathematics::Pow(Z, exponent)};
    }

    Quaternion Permutate(const Vector3D &permutation) const {
        Quaternion q = Quaternion(W, X, Y, Z);
        float perm[3];

        perm[(int)permutation.X] = q.X;
        perm[(int)permutation.Y] = q.Y;
        perm[(int)permutation.Z] = q.Z;

        q.X = perm[0];
        q.Y = perm[1];
        q.Z = perm[2];

        return q;
    }

    Quaternion Absolute() const {
        return Quaternion(
            fabsf(W),
            fabsf(X),
            fabsf(Y),
            fabsf(Z));
    }

    Quaternion AdditiveInverse() const {
        return Quaternion(-W, -X, -Y, -Z);
    }

    Quaternion MultiplicativeInverse() const {
        const float invNorm = 1.0f / Normal();

        if (Mathematics::IsClose(invNorm, 0.0f, Mathematics::EPSILON)) return Quaternion();
        if (Mathematics::IsClose(invNorm, 1.0f, Mathematics::EPSILON)) return *this;

        return Conjugate() * invNorm;
    }

    Quaternion Conjugate() const {
        return Quaternion(W, -X, -Y, -Z);
    }

    Quaternion UnitQuaternion() const {
        const float n = 1.0f / Normal();

        return Quaternion(W * n, X * n, Y * n, Z * n);
    }

    float Magnitude() const {
        return Mathematics::Sqrt(Normal());
    }

    float DotProduct(const Quaternion &q) const {
        return (W * q.W) + (X * q.X) + (Y * q.Y) + (Z * q.Z);
    }

    float Normal() const {
        return Mathematics::Sqrt(W * W + X * X + Y * Y + Z * Z);
    }

    bool IsNaN() const {
        return Mathematics::IsNaN(W) || Mathematics::IsNaN(X) || Mathematics::IsNaN(Y) || Mathematics::IsNaN(Z);
    }

    bool IsFinite() const {
        return Mathematics::IsInfinite(W) || Mathematics::IsInfinite(X) || Mathematics::IsInfinite(Y) || Mathematics::IsInfinite(Z);
    }

    bool IsInfinite() const {
        return Mathematics::IsFinite(W) || Mathematics::IsFinite(X) || Mathematics::IsFinite(Y) || Mathematics::IsFinite(Z);
    }

    bool IsNonZero() const {
        return W != 0 && X != 0 && Y != 0 && Z != 0;
    }

    bool IsEqual(const Quaternion &quaternion) const {
        return !IsNaN() && !quaternion.IsNaN() &&
               W == quaternion.W &&
               X == quaternion.X &&
               Y == quaternion.Y &&
               Z == quaternion.Z;
    }

    bool IsClose(const Quaternion &quaternion, const float epsilon) const {
        return fabs(W - quaternion.W) < epsilon &&
               fabs(X - quaternion.X) < epsilon &&
               fabs(Y - quaternion.Y) < epsilon &&
               fabs(Z - quaternion.Z) < epsilon;
    }

    String ToString() const {
        const String w = Mathematics::DoubleToCleanString(this->W);
        const String x = Mathematics::DoubleToCleanString(this->X);
        const String y = Mathematics::DoubleToCleanString(this->Y);
        const String z = Mathematics::DoubleToCleanString(this->Z);

        return "[" + w + ", " + x + ", " + y + ", " + z + "]";
    }

    // operator overloads
    bool operator==(const Quaternion &quaternion) const {
        return IsEqual(quaternion);
    }

    bool operator!=(const Quaternion &quaternion) const {
        return !IsEqual(quaternion);
    }

    Quaternion &operator=(const Quaternion &quaternion) {
        W = quaternion.W;
        X = quaternion.X;
        Y = quaternion.Y;
        Z = quaternion.Z;

        return *this;
    }

    Quaternion operator+(const Quaternion &quaternion) const {
        return Add(quaternion);
    }
    Quaternion &operator+=(const Quaternion &quaternion) {
        const Quaternion t = Add(quaternion);

        W = t.W;
        X = t.X;
        Y = t.Y;
        Z = t.Z;

        return *this;
    }

    Quaternion operator-(const Quaternion &quaternion) const {
        return Subtract(quaternion);
    }
    Quaternion &operator-=(const Quaternion &quaternion) {
        const Quaternion t = Subtract(quaternion);

        W = t.W;
        X = t.X;
        Y = t.Y;
        Z = t.Z;

        return *this;
    }

    Quaternion operator*(const Quaternion &quaternion) const {
        return Multiply(quaternion);
    }
    Quaternion &operator*=(const Quaternion &quaternion) {
        const Quaternion t = Multiply(quaternion);

        W = t.W;
        X = t.X;
        Y = t.Y;
        Z = t.Z;

        return *this;
    }
    Quaternion operator*(const float scalar) const {
        return Multiply(scalar);
    }
    Quaternion &operator*=(const float scalar) {
        const Quaternion t = Multiply(scalar);

        W = t.W;
        X = t.X;
        Y = t.Y;
        Z = t.Z;

        return *this;
    }

    Quaternion operator/(const Quaternion &quaternion) const {
        return Divide(quaternion);
    }
    Quaternion &operator/=(const Quaternion &quaternion) {
        const Quaternion t = Divide(quaternion);

        W = t.W;
        X = t.X;
        Y = t.Y;
        Z = t.Z;

        return *this;
    }
    Quaternion operator/(const float scalar) const {
        return Divide(scalar);
    }
    Quaternion &operator/=(const float scalar) {
        const Quaternion t = Divide(scalar);

        W = t.W;
        X = t.X;
        Y = t.Y;
        Z = t.Z;

        return *this;
    }

} Quaternion;
