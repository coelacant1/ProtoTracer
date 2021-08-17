#include "Vector3D.h"

Vector3D::Vector3D() {
	this->X = 0.0;
	this->Y = 0.0;
	this->Z = 0.0;
}

Vector3D::Vector3D(const Vector3D& vector) {
	this->X = vector.X;
	this->Y = vector.Y;
	this->Z = vector.Z;
}

Vector3D::Vector3D(float X, float Y, float Z) {
	this->X = X;
	this->Y = Y;
	this->Z = Z;
}

Vector3D Vector3D::Absolute() {
	return Vector3D{
		fabsf(this->X),
		fabsf(this->Y),
		fabsf(this->Z)
	};
}

Vector3D Vector3D::Normal() {
	float magn = Magnitude();
	
	if (Mathematics::IsClose(magn, 1.0f, Mathematics::EPSILON)){
		return (*this);
	}
	else if (Mathematics::IsClose(magn, 0.0f, Mathematics::EPSILON)){
		return Multiply(3.40282e+038f);
	}
	else{
		return Multiply(1.0f / magn);
	}
}

Vector3D Vector3D::Add(Vector3D vector) {
	return Vector3D{
		this->X + vector.X,
		this->Y + vector.Y,
		this->Z + vector.Z 
	};
}

Vector3D Vector3D::Subtract(Vector3D vector) {
	return Vector3D {
		this->X - vector.X,
		this->Y - vector.Y,
		this->Z - vector.Z 
	};
}

Vector3D Vector3D::Multiply(Vector3D vector) {
	return Vector3D {
		this->X * vector.X,
		this->Y * vector.Y,
		this->Z * vector.Z 
	};
}

Vector3D Vector3D::Divide(Vector3D vector) {
	return Vector3D {
		this->X / vector.X,
		this->Y / vector.Y,
		this->Z / vector.Z 
	};
}

Vector3D Vector3D::Multiply(float scalar) {

	return Vector3D {
		this->X * scalar,
		this->Y * scalar,
		this->Z * scalar 
	};
}

Vector3D Vector3D::Divide(float scalar) {
	
	return Vector3D {
		this->X / scalar,
		this->Y / scalar,
		this->Z / scalar
	};

}

Vector3D Vector3D::CrossProduct(Vector3D vector) {
	return Vector3D {
		(this->Y * vector.Z) - (this->Z * vector.Y),
		(this->Z * vector.X) - (this->X * vector.Z),
		(this->X * vector.Y) - (this->Y * vector.X) 
	};
}

Vector3D Vector3D::UnitSphere() {
	Vector3D vector = Vector3D(this->X, this->Y, this->Z);
	float length = vector.Magnitude();

	if (Mathematics::IsClose(length, 1.0f, Mathematics::EPSILON)) return Vector3D(this->X, this->Y, this->Z);
	if (length == 0) return Vector3D(0, 1, 0);

	return Vector3D {
		vector.X / length,
		vector.Y / length,
		vector.Z / length 
	};
}

Vector3D Vector3D::Constrain(float minimum, float maximum) {
	return Vector3D{
		Mathematics::Constrain(X, minimum, maximum),
		Mathematics::Constrain(Y, minimum, maximum),
		Mathematics::Constrain(Z, minimum, maximum)
	};
}

Vector3D Vector3D::Constrain(Vector3D minimum, Vector3D maximum) {
	return Vector3D{
		Mathematics::Constrain(X, minimum.X, maximum.X),
		Mathematics::Constrain(Y, minimum.Y, maximum.Y),
		Mathematics::Constrain(Z, minimum.Z, maximum.Z)
	};
}

float Vector3D::Magnitude() {
	return Mathematics::Sqrt(X * X + Y * Y + Z * Z);
}

float Vector3D::DotProduct(Vector3D vector) {
	return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z);
}

float Vector3D::CalculateEuclideanDistance(Vector3D vector) {
	vector = Subtract(vector);

	return vector.Magnitude();
}

bool Vector3D::IsEqual(Vector3D vector) {
	return (this->X == vector.X) && (this->Y == vector.Y) && (this->Z == vector.Z);
}

String Vector3D::ToString() {
	String x = Mathematics::DoubleToCleanString(this->X);
	String y = Mathematics::DoubleToCleanString(this->Y);
	String z = Mathematics::DoubleToCleanString(this->Z);

	return "[" + x + ", " + y + ", " + z + "]";
}
