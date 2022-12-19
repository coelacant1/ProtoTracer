#pragma once

#include "Mathematics.h"
#include "Vector2D.h"
#include "Vector3D.h"

struct Quaternion {
	float W = 1.0f;
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;

	Quaternion() {
		this->W = 1.0f;
		this->X = 0.0f;
		this->Y = 0.0f;
		this->Z = 0.0f;
	}

	Quaternion(const Quaternion& quaternion) {
		this->W = quaternion.W;
		this->X = quaternion.X;
		this->Y = quaternion.Y;
		this->Z = quaternion.Z;
	}

	Quaternion(Vector3D vector) {
		this->W = 0;
		this->X = vector.X;
		this->Y = vector.Y;
		this->Z = vector.Z;
	}

	Quaternion(float w, float x, float y, float z) {
		this->W = w;
		this->X = x;
		this->Y = y;
		this->Z = z;
	}

	Vector2D RotateVector(Vector2D v) {
		if (IsClose(Quaternion(), Mathematics::EPSILON)) return v;
		
		Quaternion q = UnitQuaternion();

		float s2 = q.W * 2.0f;
		float dPUV = (q.X * v.X + q.Y * v.Y) * 2.0f;
		float dPUU = q.W * q.W - (q.X * q.X + q.Y * q.Y + q.Z * q.Z);

		return Vector2D{
			X * dPUV + v.X * dPUU + (-(q.Z * v.Y)) * s2,
			Y * dPUV + v.Y * dPUU + ((q.Z * v.X)) * s2
		};
	}

    Vector2D RotateVectorUnit(Vector2D v, const Quaternion& q) {
        if (IsClose(Quaternion(), Mathematics::EPSILON)) return v;

        float s2 = q.W * 2.0f;
        float dPUV = (q.X * v.X + q.Y * v.Y) * 2.0f;
        float dPUU = q.W * q.W - (q.X * q.X + q.Y * q.Y + q.Z * q.Z);

        return Vector2D{
            X * dPUV + v.X * dPUU + (-(q.Z * v.Y)) * s2,
            Y * dPUV + v.Y * dPUU + ((q.Z * v.X)) * s2
        };
    }

	Vector2D UnrotateVector(Vector2D coordinate) {
		if (IsClose(Quaternion(), Mathematics::EPSILON)) return coordinate;

		return Conjugate().RotateVector(coordinate);
	}

	Vector3D RotateVector(Vector3D v) {
		if (IsClose(Quaternion(), Mathematics::EPSILON)) return v;
		
		Quaternion q = UnitQuaternion();

		float s2 = q.W * 2.0f;
		float dPUV = (q.X * v.X + q.Y * v.Y + q.Z * v.Z) * 2.0f;
		float dPUU = q.W * q.W - (q.X * q.X + q.Y * q.Y + q.Z * q.Z);

		return Vector3D{
			X * dPUV + v.X * dPUU + ((q.Y * v.Z) - (q.Z * v.Y)) * s2,
			Y * dPUV + v.Y * dPUU + ((q.Z * v.X) - (q.X * v.Z)) * s2,
			Z * dPUV + v.Z * dPUU + ((q.X * v.Y) - (q.Y * v.X)) * s2
		};
	}

	Vector3D UnrotateVector(Vector3D coordinate) {
		if (IsClose(Quaternion(), Mathematics::EPSILON)) return coordinate;

		return UnitQuaternion().Conjugate().RotateVector(coordinate);
	}

	Vector3D GetBiVector() {
		return Vector3D{
			this->X,
			this->Y,
			this->Z
		};
	}

	static Quaternion SphericalInterpolation(Quaternion q1, Quaternion q2, float ratio) {
		if (ratio <= Mathematics::EPSILON) return q1;
		if (ratio >= 1.0f - Mathematics::EPSILON) return q2; 

		q1 = q1.UnitQuaternion();
		q2 = q2.UnitQuaternion();

		float dot = q1.DotProduct(q2);//Cosine between the two quaternions

		if (dot < 0.0f){//Shortest path correction
			q1 = q1.AdditiveInverse();
			dot = -dot;
		}

		if (dot > 0.999f){//Linearly interpolates if results are close
			return (q1.Add( (q2.Subtract(q1)).Multiply(ratio) )).UnitQuaternion();
		}
		else
		{
			dot = Mathematics::Constrain<float>(dot, -1, 1);

			float theta0 = acosf(dot);
			float theta = theta0 * ratio;

			//Quaternion q3 = (q2.Subtract(q1.Multiply(dot))).UnitQuaternion();//UQ for orthonomal 
			float f1 = cosf(theta) - dot * sinf(theta) / sinf(theta0);
			float f2 = sinf(theta) / sinf(theta0);

			return q1.Multiply(f1).Add(q2.Multiply(f2)).UnitQuaternion();
		}
	}

	Quaternion DeltaRotation(Vector3D angularVelocity, float timeDelta){
		Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);
		Vector3D halfAngle = angularVelocity * (timeDelta / 2.0f);
		float halfAngleLength = halfAngle.Magnitude();

		if(halfAngleLength > Mathematics::EPSILON){//exponential map
			halfAngle = halfAngle * (sinf(halfAngleLength) / halfAngleLength);
			return (current * Quaternion(cosf(halfAngleLength), halfAngle.X, halfAngle.Y, halfAngle.Z)).UnitQuaternion();
		}
		else{//first taylor series
			return (current * Quaternion(1.0f, halfAngle.X, halfAngle.Y, halfAngle.Z)).UnitQuaternion();
		}
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
		float invNorm = 1.0f / Normal();

		if(Mathematics::IsClose(invNorm, 0.0f, Mathematics::EPSILON)) return Quaternion();
		if(Mathematics::IsClose(invNorm, 1.0f, Mathematics::EPSILON)) return *this;

		return Conjugate().Multiply(invNorm);

	}

	Quaternion Conjugate() {
		return Quaternion
		{
			W,
			-X,
			-Y,
			-Z
		};
	}

	Quaternion UnitQuaternion() {
		float n = 1.0f / Normal();

		return Quaternion{
			W * n,
			X * n,
			Y * n,
			Z * n
		};
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

	bool IsFinite() {
		return Mathematics::IsInfinite(W) || Mathematics::IsInfinite(X) || Mathematics::IsInfinite(Y) || Mathematics::IsInfinite(Z);
	}

	bool IsInfinite() {
		return Mathematics::IsFinite(W) || Mathematics::IsFinite(X) || Mathematics::IsFinite(Y) || Mathematics::IsFinite(Z);
	}

	bool IsNonZero() {
		return W != 0 && X != 0 && Y != 0 && Z != 0;
	}

	bool IsEqual(Quaternion quaternion) {
		return !IsNaN() && !quaternion.IsNaN() &&
			W == quaternion.W &&
			X == quaternion.X &&
			Y == quaternion.Y &&
			Z == quaternion.Z;
	}

	bool IsClose(Quaternion quaternion, float epsilon) {
		return fabs(W - quaternion.W) < epsilon &&
			fabs(X - quaternion.X) < epsilon &&
			fabs(Y - quaternion.Y) < epsilon &&
			fabs(Z - quaternion.Z) < epsilon;
	}

	String ToString() {
		String w = Mathematics::DoubleToCleanString(this->W);
		String x = Mathematics::DoubleToCleanString(this->X);
		String y = Mathematics::DoubleToCleanString(this->Y);
		String z = Mathematics::DoubleToCleanString(this->Z);
		
		return "[" + w + ", " + x + ", " + y + ", " + z + "]";
		
	}

	static Quaternion Add(Quaternion q1, Quaternion q2) {
		return q1.Add(q2);
	}

	static Quaternion Subtract(Quaternion q1, Quaternion q2) {
		return q1.Subtract(q2);
	}

	static Quaternion Multiply(Quaternion q1, Quaternion q2) {
		return q1.Multiply(q2);
	}

	static Quaternion Divide(Quaternion q1, Quaternion q2) {
		return q1.Divide(q2);
	}

	static Quaternion Power(Quaternion q1, Quaternion q2) {
		return q1.Power(q2);
	}

	static float DotProduct(Quaternion q1, Quaternion q2) {
		return q1.DotProduct(q2);
	}


	static Quaternion Power(Quaternion quaternion, float exponent) {
		return quaternion.Power(exponent);
	}

	static Quaternion Permutate(Quaternion quaternion, Vector3D vector) {
		return quaternion.Permutate(vector);
	}

	static Quaternion Absolute(Quaternion quaternion) {
		return quaternion.Absolute();
	}

	static Quaternion AdditiveInverse(Quaternion quaternion) {
		return quaternion.AdditiveInverse();
	}

	static Quaternion MultiplicativeInverse(Quaternion quaternion) {
		return quaternion.MultiplicativeInverse();
	}

	static Quaternion Conjugate(Quaternion quaternion) {
		return quaternion.Conjugate();
	}

	static Quaternion UnitQuaternion(Quaternion quaternion) {
		return quaternion.UnitQuaternion();
	}

	static float Magnitude(Quaternion quaternion) {
		return quaternion.Magnitude();
	}

	static float Normal(Quaternion quaternion) {
		return quaternion.Normal();
	}

	//Operator overloads
	bool operator ==(Quaternion quaternion) {
		return this->IsEqual(quaternion);
	}

	bool operator !=(Quaternion quaternion) {
		return !(this->IsEqual(quaternion));
	}

	Quaternion operator =(Quaternion quaternion) {
		this->W = quaternion.W;
		this->X = quaternion.X;
		this->Y = quaternion.Y;
		this->Z = quaternion.Z;
		
		return quaternion;
	}

	Quaternion operator  +(Quaternion quaternion) {
		return Add(quaternion);
	}

	Quaternion operator  -(Quaternion quaternion) {
		return Subtract(quaternion);
	}

	Quaternion operator  *(Quaternion quaternion) {
		return Multiply(quaternion);
	}

	Quaternion operator  /(Quaternion quaternion) {
		return Divide(quaternion);
	}


	Quaternion operator  /(float value) {
		return Divide(value);
	}

	friend Quaternion operator *(float scalar, Quaternion q);
	friend Quaternion operator *(Quaternion q, float scalar);
};

Quaternion operator *(float scalar, Quaternion q) {
	return q.Multiply(scalar);
}

Quaternion operator *(Quaternion q, float scalar) {
	return q.Multiply(scalar);
}