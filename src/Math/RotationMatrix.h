#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

typedef struct RotationMatrix {
private:
    Vector3D InitialVector;
    bool didRotate;

    Vector3D ConvertCoordinateToVector() {
        if (didRotate) return Vector3D((XAxis.X + YAxis.X + ZAxis.X), (XAxis.Y + YAxis.Y + ZAxis.Y), (XAxis.Z + YAxis.Z + ZAxis.Z));
        return InitialVector;
    }

    void ReadjustMatrix() {
        const float X = (XAxis.X + YAxis.X + ZAxis.X);
        const float Y = (XAxis.Y + YAxis.Y + ZAxis.Y);
        const float Z = (XAxis.Z + YAxis.Z + ZAxis.Z);

        XAxis = Vector3D(X, X, X);
        YAxis = Vector3D(Y, Y, Y);
        ZAxis = Vector3D(Z, Z, Z);
    }

    void Rotate(const Vector3D &rotation) {
        if (rotation.X != 0) {
            RotateX(rotation.X);
            didRotate = true;

            if (rotation.Y != 0 || rotation.Z != 0) ReadjustMatrix();
        }

        if (rotation.Y != 0) {
            RotateY(rotation.Y);
            didRotate = true;

            if (rotation.Z != 0) ReadjustMatrix();
        }

        if (rotation.Z != 0) {
            RotateZ(rotation.Z);
            didRotate = true;
        }
    }

    void RotateX(const float theta) {
        const float c = cosf(Mathematics::DegreesToRadians(theta));
        const float s = sinf(Mathematics::DegreesToRadians(theta));

        XAxis = Vector3D(1, 0, 0) * XAxis;
        YAxis = Vector3D(0, c, -s) * YAxis;
        ZAxis = Vector3D(0, s, c) * ZAxis;
    }

    void RotateY(const float theta) {
        const float c = cosf(Mathematics::DegreesToRadians(theta));
        const float s = sinf(Mathematics::DegreesToRadians(theta));

        XAxis = Vector3D(c, 0, s) * XAxis;
        YAxis = Vector3D(0, 1, 0) * YAxis;
        ZAxis = Vector3D(-s, 0, c) * ZAxis;
    }

    void RotateZ(const float theta) {
        const float c = cosf(Mathematics::DegreesToRadians(theta));
        const float s = sinf(Mathematics::DegreesToRadians(theta));

        XAxis = Vector3D(c, -s, 0) * XAxis;
        YAxis = Vector3D(s, c, 0) * YAxis;
        ZAxis = Vector3D(0, 0, 1) * ZAxis;
    }
    void RotateRelative(const RotationMatrix &rM) {
        Multiply(rM);
    }

public:
    Vector3D XAxis;
    Vector3D YAxis;
    Vector3D ZAxis;

    RotationMatrix(const Vector3D &axes)
        : XAxis(Vector3D(axes.X, axes.X, axes.X)),
          YAxis(Vector3D(axes.Y, axes.Y, axes.Y)),
          ZAxis(Vector3D(axes.Z, axes.Z, axes.Z)) {}

    RotationMatrix(const Vector3D &X, const Vector3D &Y, const Vector3D &Z)
        : XAxis(X),
          YAxis(Y),
          ZAxis(Z) {}

    RotationMatrix Normalize() const {
        const Vector3D vz = XAxis.CrossProduct(YAxis);
        const Vector3D vy = vz.CrossProduct(XAxis);

        return RotationMatrix(
            XAxis.UnitSphere(),
            vy.UnitSphere(),
            vz.UnitSphere());
    }
    RotationMatrix const Transpose() {
        const Vector3D X = XAxis;
        XAxis = Vector3D(XAxis.X, YAxis.X, ZAxis.X);
        const Vector3D Y = YAxis;
        YAxis = Vector3D(X.Y, YAxis.Y, ZAxis.Y);
        ZAxis = Vector3D(X.Z, Y.Z, ZAxis.Z);

        return *this;
    }

    RotationMatrix const Inverse() {

        RotationMatrix rM = RotationMatrix{
            YAxis.CrossProduct(ZAxis),
            ZAxis.CrossProduct(XAxis),
            XAxis.CrossProduct(YAxis)};

        rM = Transpose() * (1.0f / rM.Determinant());

        Transpose();
        return Multiply(1.0f / Determinant());
    }
    RotationMatrix Multiply(const float d) const {
        return RotationMatrix(
            XAxis * d,
            YAxis * d,
            ZAxis * d);
    }

    RotationMatrix Multiply(const RotationMatrix &rM) const {
        return RotationMatrix(
            XAxis * rM.XAxis,
            YAxis * rM.YAxis,
            ZAxis * rM.ZAxis);
    }

    bool IsEqual(const RotationMatrix &rM) const {
        return XAxis.IsEqual(rM.XAxis) && YAxis.IsEqual(rM.YAxis) && ZAxis.IsEqual(rM.ZAxis);
    }

    float Determinant() const {
        return XAxis.X * (YAxis.Y * ZAxis.Z - ZAxis.Y * YAxis.Z) -
               YAxis.X * (ZAxis.Z * XAxis.Y - ZAxis.Y * XAxis.Z) +
               ZAxis.X * (XAxis.Y * YAxis.Z - YAxis.Y * XAxis.Z);
    }

    static const Vector3D RotateVector(const Vector3D &rotate, const Vector3D &coordinates) {
        // calculate rotation matrix
        RotationMatrix matrix = RotationMatrix(coordinates);

        matrix.Rotate(rotate);

        if (rotate.X == 0 && rotate.Y == 0 && rotate.Z == 0) return coordinates;
        return matrix.ConvertCoordinateToVector();
    }

    String ToString() const {
        const String x = XAxis.ToString();
        const String y = YAxis.ToString();
        const String z = ZAxis.ToString();

        return x + "\n" + y + "\n" + z + "\n";
    }

    // Overload

    bool operator==(const RotationMatrix &rM) const {
        return IsEqual(rM);
    }
    bool operator!=(const RotationMatrix &rM) const {
        return !IsEqual(rM);
    }

    RotationMatrix &operator=(const RotationMatrix &rM) {
        this->XAxis = rM.XAxis;
        this->YAxis = rM.YAxis;
        this->ZAxis = rM.ZAxis;

        return *this;
    }

    RotationMatrix operator*(const RotationMatrix &rM) const {
        return Multiply(rM);
    }
    RotationMatrix operator*(const float d) const {
        return Multiply(d);
    }
} RotationMatrix;
