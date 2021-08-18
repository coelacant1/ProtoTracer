#include "Vector2D.h"

Vector2D::Vector2D() {
	this->X = 0.0;
	this->Y = 0.0;
}

Vector2D::Vector2D(const Vector2D& vector) {
	this->X = vector.X;
	this->Y = vector.Y;
}

Vector2D::Vector2D(float X, float Y) {
	this->X = X;
	this->Y = Y;
}

Vector2D::Vector2D(const Vector3D& vector) {
	this->X = vector.X;
	this->Y = vector.Y;
}

Vector2D Vector2D::Absolute() {
	return Vector2D{
		fabsf(X),
		fabsf(Y)
	};
}

Vector2D Vector2D::Normal() {
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

Vector2D Vector2D::Add(Vector2D vector) {
	return Vector2D{
		X + vector.X,
		Y + vector.Y
	};
}

Vector2D Vector2D::Subtract(Vector2D vector) {
	return Vector2D{
		X - vector.X,
		Y - vector.Y
	};
}

Vector2D Vector2D::Multiply(Vector2D vector) {
	return Vector2D{
		X * vector.X,
		Y * vector.Y
	};
}

Vector2D Vector2D::Divide(Vector2D vector) {
	return Vector2D{
		X / vector.X,
		Y / vector.Y
	};
}

Vector2D Vector2D::Multiply(float scalar) {
	if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return (*this);
	if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Vector3D();

	return Vector2D{
		X * scalar,
		Y * scalar
	};
}

Vector2D Vector2D::Divide(float scalar) {
	if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return (*this);
	if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Vector3D();
	
	return Vector2D{
		X / scalar,
		Y / scalar
	};

}

Vector3D Vector2D::CrossProduct(Vector2D vector) {
	return Vector3D{
		0.0f,
		0.0f,
		(X * vector.Y) - (Y * vector.X)
	};
}

Vector2D Vector2D::UnitCircle() {
	float length = Magnitude();

	if (Mathematics::IsClose(length, 1.0f, Mathematics::EPSILON)) return Vector2D(this->X, this->Y);
	if (length == 0) return Vector2D(0, 1);

	return Vector2D{
		X / length,
		Y / length
	};
}

Vector2D Vector2D::Constrain(float minimum, float maximum) {
	return Vector2D{
		Mathematics::Constrain(X, minimum, maximum),
		Mathematics::Constrain(Y, minimum, maximum)
	};
}

Vector2D Vector2D::Constrain(Vector2D minimum, Vector2D maximum) {
	return Vector2D{
		Mathematics::Constrain(X, minimum.X, maximum.X),
		Mathematics::Constrain(Y, minimum.Y, maximum.Y)
	};
}

Vector2D Vector2D::Minimum(Vector2D v) {
	return Vector2D{
		X < v.X ? X : v.X,
		Y < v.Y ? Y : v.Y
	};
}

Vector2D Vector2D::Maximum(Vector2D v) {
	return Vector2D{
		X > v.X ? X : v.X,
		Y > v.Y ? Y : v.Y
	};
}

Vector2D Vector2D::Rotate(float angle, Vector2D offset){
	Vector2D v = Vector2D(X, Y).Subtract(offset);

	angle = angle * Mathematics::MPID180;

	float cs = cosf(angle);
	float sn = sinf(angle);

	return Vector2D{
		v.X * cs - v.Y * sn + offset.X,
		v.X * sn + v.Y * cs + offset.Y
	};
}

bool Vector2D::CheckBounds(Vector2D minimum, Vector2D maximum) {
	return X > minimum.X && X < maximum.X && Y > minimum.Y && Y < maximum.Y;
}

float Vector2D::Magnitude() {
	return Mathematics::Sqrt(X * X + Y * Y);
}

float Vector2D::DotProduct(Vector2D vector) {
	return (X * vector.X) + (Y * vector.Y);
}

float Vector2D::CalculateEuclideanDistance(Vector2D vector) {
	vector = Subtract(vector);

	return vector.Magnitude();
}

bool Vector2D::IsEqual(Vector2D vector) {
	return (X == vector.X) && (Y == vector.Y);
}

String Vector2D::ToString() {
	String x = Mathematics::DoubleToCleanString(X);
	String y = Mathematics::DoubleToCleanString(Y);

	return "[" + x + ", " + y + "]";
}
