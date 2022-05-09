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

	Quaternion(const Quaternion& quaternion) 
		: W(quaternion.W),
		  X(quaternion.X),
		  Y(quaternion.Y),
		  Z(quaternion.Z) {}

	Quaternion(const Vector3D vector) 
		: W(0.0f),
		  X(vector.X),
		  Y(vector.Y),
		  Z(vector.Z) {}

	Quaternion(const float w, const float x, const float y, const float z) 
		: W(w),
		  X(x),
		  Y(y),
		  Z(z) {}

	Vector2D RotateVector(const Vector2D v) const {
		if (IsClose(Quaternion(), Mathematics::EPSILON)) return v;
		
		Quaternion q = UnitQuaternion();

		const float s2 = q.W * 2.0f;
		const float dPUV = (q.X * v.X + q.Y * v.Y) * 2.0f;
		const float dPUU = q.W * q.W - (q.X * q.X + q.Y * q.Y + q.Z * q.Z);

		return Vector2D{
			X * dPUV + v.X * dPUU + (-(q.Z * v.Y)) * s2,
			Y * dPUV + v.Y * dPUU + ((q.Z * v.X)) * s2
		};
	}

	Vector2D UnrotateVector(const Vector2D coordinate) const {
		if (IsClose(Quaternion(), Mathematics::EPSILON)) return coordinate;

		return Conjugate().RotateVector(coordinate);
	}

	Vector3D RotateVector(const Vector3D v) const {
		if (IsClose(Quaternion(), Mathematics::EPSILON)) return v;
		
		Quaternion q = UnitQuaternion();

		const float s2 = q.W * 2.0f;
		const float dPUV = (q.X * v.X + q.Y * v.Y + q.Z * v.Z) * 2.0f;
		const float dPUU = q.W * q.W - (q.X * q.X + q.Y * q.Y + q.Z * q.Z);

		return Vector3D{
			X * dPUV + v.X * dPUU + ((q.Y * v.Z) - (q.Z * v.Y)) * s2,
			Y * dPUV + v.Y * dPUU + ((q.Z * v.X) - (q.X * v.Z)) * s2,
			Z * dPUV + v.Z * dPUU + ((q.X * v.Y) - (q.Y * v.X)) * s2
		};
	}

	Vector3D UnrotateVector(const Vector3D coordinate) const {
		if (IsClose(Quaternion(), Mathematics::EPSILON)) return coordinate;

		return UnitQuaternion().Conjugate().RotateVector(coordinate);
	}

	Vector3D GetBiVector() const {
		return Vector3D(X, Y, Z);
	}

	Quaternion SphericalInterpolation(const Quaternion q1, const Quaternion q2, const float ratio) const {
		if (ratio <= Mathematics::EPSILON) return q1;
		if (ratio >= 1.0f - Mathematics::EPSILON) return q2; 

		q1 = q1.UnitQuaternion();
		q2 = q2.UnitQuaternion();

		float dot = q1.DotProduct(q2);//Cosine between the two quaternions

		if (dot < 0.0f)//Shortest path correction
		{
			q1 = q1.AdditiveInverse();
			dot = -dot;
		}

		//Linearly interpolates if results are close
		if (dot > 0.999) return (q1 + (q2 - q1) * ratio).UnitQuaternion();

		dot = Mathematics::Constrain(dot, -1, 1);

		const float theta0 = acosf(dot);
		const float theta = theta0 * ratio;

		//Quaternion q3 = (q2.Subtract(q1.Multiply(dot))).UnitQuaternion();//UQ for orthonomal 
		const float f1 = cosf(theta) - dot * sinf(theta) / sinf(theta0);
		const float f2 = sinf(theta) / sinf(theta0);

		return (q1 * f1 + q2 * f2).UnitQuaternion();
	}

	Quaternion DeltaRotation(const Vector3D angularVelocity, const float timeDelta){
		Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);
		Vector3D halfAngle = angularVelocity * (timeDelta / 2.0f);
		float halfAngleLength = halfAngle.Magnitude();

		if(halfAngleLength > Mathematics::EPSILON){//exponential map
			halfAngle = halfAngle * (sinf(halfAngleLength) / halfAngleLength);
			return (current * Quaternion(cosf(halfAngleLength), halfAngle.X, halfAngle.Y, halfAngle.Z)).UnitQuaternion();
		}
		//first taylor series
		return (current * Quaternion(1.0f, halfAngle.X, halfAngle.Y, halfAngle.Z)).UnitQuaternion();
	}

	Quaternion Add(Quaternion quaternion) {
		return Quaternion {
			W + quaternion.W,
			X + quaternion.X,
			Y + quaternion.Y,
			Z + quaternion.Z
		};
	}

	Quaternion Subtract(Quaternion quaternion) {
		return Quaternion{
			W - quaternion.W,
			X - quaternion.X,
			Y - quaternion.Y,
			Z - quaternion.Z
		};
	}

	Quaternion Multiply(Quaternion quaternion) {
		if(quaternion.IsClose(Quaternion(), Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);
		
		return Quaternion{
			W * quaternion.W - X * quaternion.X - Y * quaternion.Y - Z * quaternion.Z,
			W * quaternion.X + X * quaternion.W + Y * quaternion.Z - Z * quaternion.Y,
			W * quaternion.Y - X * quaternion.Z + Y * quaternion.W + Z * quaternion.X,
			W * quaternion.Z + X * quaternion.Y - Y * quaternion.X + Z * quaternion.W
		};
	}

	Quaternion Multiply(float scalar) {
		if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Quaternion();
		if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);

		return Quaternion{
			W * scalar,
			X * scalar,
			Y * scalar,
			Z * scalar
		};
	}

	Quaternion Divide(Quaternion quaternion) {
		if(quaternion.IsClose(Quaternion(), Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);

		float scale = 1.0f / (quaternion.W * quaternion.W + quaternion.X * quaternion.X + quaternion.Y * quaternion.Y + quaternion.Z * quaternion.Z);

		return Quaternion
		{
			( W * quaternion.W + X * quaternion.X + Y * quaternion.Y + Z * quaternion.Z) * scale,
			(-W * quaternion.X + X * quaternion.W + Y * quaternion.Z - Z * quaternion.Y) * scale,
			(-W * quaternion.Y - X * quaternion.Z + Y * quaternion.W + Z * quaternion.X) * scale,
			(-W * quaternion.Z + X * quaternion.Y - Y * quaternion.X + Z * quaternion.W) * scale
		};
	}

	Quaternion Divide(float scalar) {
		if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Quaternion();
		if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);
		
		scalar = 1.0f / scalar;

		return Quaternion
		{
			W * scalar,
			X * scalar,
			Y * scalar,
			Z * scalar
		};
	}

	Quaternion Power(Quaternion exponent) {
		return Quaternion
		{
			Mathematics::Pow(W, exponent.W),
			Mathematics::Pow(X, exponent.X),
			Mathematics::Pow(Y, exponent.Y),
			Mathematics::Pow(Z, exponent.Z)
		};
	}

	Quaternion Power(float exponent) {
		return Quaternion
		{
			Mathematics::Pow(W, exponent),
			Mathematics::Pow(X, exponent),
			Mathematics::Pow(Y, exponent),
			Mathematics::Pow(Z, exponent)
		};
	}

	Quaternion Permutate(Vector3D permutation) {
		Quaternion q = Quaternion(this->W, this->X, this->Y, this->Z);
		float perm[3];

		perm[(int)permutation.X] = q.X;
		perm[(int)permutation.Y] = q.Y;
		perm[(int)permutation.Z] = q.Z;

		q.X = perm[0];
		q.Y = perm[1];
		q.Z = perm[2];

		return q;
	}

	Quaternion Absolute() {
		return Quaternion
		{
			fabsf(W),
			fabsf(X),
			fabsf(Y),
			fabsf(Z)
		};
	}

	Quaternion AdditiveInverse() {
		return Quaternion
		{
			-W,
			-X,
			-Y,
			-Z
		};
	}

	Quaternion MultiplicativeInverse() {
		const float invNorm = 1.0f / Normal();

		if(Mathematics::IsClose(invNorm, 0.0f, Mathematics::EPSILON)) return Quaternion();
		if(Mathematics::IsClose(invNorm, 1.0f, Mathematics::EPSILON)) return *this;

		return Conjugate().Multiply(invNorm);

	}

	Quaternion Conjugate() {
		return Quaternion(W, -X, -Y, -Z);
	}

	Quaternion UnitQuaternion() {
		const float n = 1.0f / Normal();

		return Quaternion(W * n, X * n, Y * n, Z * n);
	}

	float Magnitude() {
		return Mathematics::Sqrt(Normal());
	}

	float DotProduct(Quaternion q) {
		return (W * q.W) + (X * q.X) + (Y * q.Y) + (Z * q.Z);
	}

	float Normal() {
		return Mathematics::Sqrt(W * W + X * X + Y * Y + Z * Z);
	}

	bool IsNaN() {
		return Mathematics::IsNaN(W) || Mathematics::IsNaN(X) || Mathematics::IsNaN(Y) || Mathematics::IsNaN(Z);
	}

	bool IsFinite() bool {
		return Mathematics::IsInfinite(W) || Mathematics::IsInfinite(X) || Mathematics::IsInfinite(Y) || Mathematics::IsInfinite(Z);
	}

	bool IsInfinite() bool {
		return Mathematics::IsFinite(W) || Mathematics::IsFinite(X) || Mathematics::IsFinite(Y) || Mathematics::IsFinite(Z);
	}

	bool IsNonZero() {
		return W != 0 && X != 0 && Y != 0 && Z != 0;
	}

	bool IsEqual(const Quaternion quaternion) {
		return !IsNaN() && !quaternion.IsNaN() &&
			W == quaternion.W &&
			X == quaternion.X &&
			Y == quaternion.Y &&
			Z == quaternion.Z;
	}

	bool IsClose(const Quaternion quaternion, const float epsilon) const {
		return fabs(W - quaternion.W) < epsilon &&
			fabs(X - quaternion.X) < epsilon &&
			fabs(Y - quaternion.Y) < epsilon &&
			fabs(Z - quaternion.Z) < epsilon;
	}

	String ToString() const {
		String w = Mathematics::DoubleToCleanString(this->W);
		String x = Mathematics::DoubleToCleanString(this->X);
		String y = Mathematics::DoubleToCleanString(this->Y);
		String z = Mathematics::DoubleToCleanString(this->Z);
		
		return "[" + w + ", " + x + ", " + y + ", " + z + "]";
		
	}

	//operator overloads
	bool operator==(const Quaternion& quaternion) const  {
		return IsEqual(quaternion);
	}

	bool operator!=(const Quaternion& quaternion) const {
		return !IsEqual(quaternion);
	}

	Quaternion& operator=(const Quaternion& quaternion) const {
		W = quaternion.W;
		X = quaternion.X;
		Y = quaternion.Y;
		Z = quaternion.Z;
		
		return quaternion;
	}

	Quaternion operator+(const Quaternion& quaternion) const {
		return Add(quaternion);
	}
	Quaternion operator+(const float scalar) const {
		return Add(scalar);
	}

	Quaternion operator-(Quaternion quaternion) const {
		return Subtract(quaternion);
	}
	Quaternion operator-(const float scalar) const {
		return Subtract(scalar);
	}

	Quaternion operator*(Quaternion quaternion) const {
		return Multiply(quaternion);
	}
	Quaternion operator*(const float scalar) const {
		return Multiply(scalar);
	}

	Quaternion operator/(Quaternion quaternion) const {
		return Divide(quaternion);
	}

	Quaternion operator/(float value) const {
		return Divide(value);
	}

} Quaternion;
