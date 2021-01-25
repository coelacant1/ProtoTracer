#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

typedef struct RotationMatrix {
private:
	Vector3D InitialVector;
	bool didRotate;

	Vector3D ConvertCoordinateToVector();
	void ReadjustMatrix();
	void Rotate(Vector3D rotation);
	void RotateX(float theta);
	void RotateY(float theta);
	void RotateZ(float theta);
	void RotateRelative(RotationMatrix rM);

public:
	Vector3D XAxis;
	Vector3D YAxis;
	Vector3D ZAxis;

	RotationMatrix(Vector3D axes);
	RotationMatrix(Vector3D X, Vector3D Y, Vector3D Z);
	
	RotationMatrix Normalize();
	RotationMatrix Transpose();
	RotationMatrix Inverse();
	RotationMatrix Multiply(float d);
	RotationMatrix Multiply(RotationMatrix rM);

	bool IsEqual(RotationMatrix rM);
	float Determinant();

	static Vector3D RotateVector(Vector3D rotate, Vector3D coordinates);

	String ToString();

	RotationMatrix operator =(RotationMatrix rM) {
		this->XAxis = rM.XAxis;
		this->YAxis = rM.YAxis;
		this->ZAxis = rM.ZAxis;

		return *this;
	}
} RotationMatrix;
