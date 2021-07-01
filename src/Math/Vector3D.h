#pragma once

#include "Mathematics.h"

typedef struct Vector3D {
public:
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;

	Vector3D();
	Vector3D(const Vector3D& vector);
	Vector3D(float x, float y, float z);
	Vector3D Absolute();
	Vector3D Normal();
	Vector3D Add(Vector3D vector);
	Vector3D Subtract(Vector3D vector);
	Vector3D Multiply(Vector3D vector);
	Vector3D Divide(Vector3D vector);
	Vector3D Multiply(float scalar);
	Vector3D Divide(float scalar);
	Vector3D CrossProduct(Vector3D vector);
	Vector3D UnitSphere();//unit sphere
	Vector3D Constrain(float minimum, float maximum);
	Vector3D Constrain(Vector3D minimum, Vector3D maximum);

	float Magnitude();
	float DotProduct(Vector3D vector);
	float CalculateEuclideanDistance(Vector3D vector);
	bool IsEqual(Vector3D vector);
	String ToString();
  
  static Vector3D Max(Vector3D max, Vector3D input) {
    return Vector3D(input.X > max.X ? input.X : max.X,
      input.Y > max.Y ? input.Y : max.Y,
      input.Z > max.Z ? input.Z : max.Z);
  }


  static Vector3D Min(Vector3D min, Vector3D input) {
    return Vector3D(input.X < min.X ? input.X : min.X,
      input.Y < min.Y ? input.Y : min.Y,
      input.Z < min.Z ? input.Z : min.Z);
  }

  static Vector3D LERP(Vector3D start, Vector3D finish, float ratio) {
    return finish * ratio + start * (1.0f - ratio);
  }

	static Vector3D DegreesToRadians(Vector3D degrees) {
		return degrees / (180.0f / Mathematics::MPI);
	}

	static Vector3D RadiansToDegrees(Vector3D radians) {
		return radians * (180.0f / Mathematics::MPI);
	}

	//Static function declaractions
	static Vector3D Normal(Vector3D vector) {
		return vector.Normal();
	}

	static Vector3D Add(Vector3D v1, Vector3D v2) {
		return v1.Add(v2);
	}

	static Vector3D Subtract(Vector3D v1, Vector3D v2) {
		return v1.Subtract(v2);
	}

	static Vector3D Multiply(Vector3D v1, Vector3D v2) {
		return v1.Multiply(v2);
	}

	static Vector3D Divide(Vector3D v1, Vector3D v2) {
		return v1.Divide(v2);
	}

	static Vector3D Multiply(Vector3D vector, float scalar) {
		return vector.Multiply(scalar);
	}

	static Vector3D Multiply(float scalar, Vector3D vector) {
		return vector.Multiply(scalar);
	}

	static Vector3D Divide(Vector3D vector, float scalar) {
		return vector.Divide(scalar);
	}

	static Vector3D CrossProduct(Vector3D v1, Vector3D v2) {
		return v1.CrossProduct(v2);
	}

	static float DotProduct(Vector3D v1, Vector3D v2) {
		return v1.DotProduct(v2);
	}

	static float CalculateEuclideanDistance(Vector3D v1, Vector3D v2) {
		return v1.CalculateEuclideanDistance(v2);
	}

	static bool IsEqual(Vector3D v1, Vector3D v2) {
		return v1.IsEqual(v2);
	}

	//Operator overloads
	bool operator ==(Vector3D vector) {
		return this->IsEqual(vector);
	}

	bool operator !=(Vector3D vector) {
		return !(this->IsEqual(vector));
	}

	Vector3D operator  =(Vector3D vector) {
		this->X = vector.X;
		this->Y = vector.Y;
		this->Z = vector.Z;

		return *this;
	}

	Vector3D operator  +(Vector3D vector) {
		Vector3D v = Vector3D(*this);

		return v.Add(vector);
	}

	Vector3D operator  -(Vector3D vector) {
		Vector3D v = Vector3D(*this);

		return v.Subtract(vector);
	}

	Vector3D operator  *(Vector3D vector) {
		Vector3D v = Vector3D(*this);

		return v.Multiply(vector);
	}

	Vector3D operator  /(Vector3D vector) {
		Vector3D v = Vector3D(*this);

		return v.Divide(vector);
	}

	Vector3D operator  *(float value) {
		Vector3D v = Vector3D(*this);

		return v.Multiply(value);
	}

	Vector3D operator  /(float value) {
		Vector3D v = Vector3D(*this);

		return v.Divide(value);
	}
} Vector3D;
