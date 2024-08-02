#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

class RotationMatrix {
private:
    Vector3D InitialVector;
    bool didRotate;

public:
    Vector3D XAxis;
    Vector3D YAxis;
    Vector3D ZAxis;

    Vector3D ConvertCoordinateToVector();
    void ReadjustMatrix();
    Vector3D Rotate(Vector3D rotation);
    Vector3D RotateX(float theta);
    Vector3D RotateY(float theta);
    Vector3D RotateZ(float theta);
    void RotateRelative(RotationMatrix rM);

    RotationMatrix();
    RotationMatrix(Vector3D axes);
    RotationMatrix(Vector3D X, Vector3D Y, Vector3D Z);

    RotationMatrix Multiply(float d);
    RotationMatrix Multiply(RotationMatrix rM);
    RotationMatrix Normalize();
    RotationMatrix Transpose();
    RotationMatrix Inverse();

    bool IsEqual(RotationMatrix rM);
    float Determinant();

    static Vector3D RotateVector(Vector3D rotate, Vector3D coordinates);
    String ToString();

    RotationMatrix operator =(RotationMatrix rM);
};
