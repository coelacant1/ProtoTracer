#include "Quaternion.h"

// Default constructor
Quaternion::Quaternion() : W(1.0f), X(0.0f), Y(0.0f), Z(0.0f) {}

// Copy constructor
Quaternion::Quaternion(const Quaternion& quaternion) {
    this->W = quaternion.W;
    this->X = quaternion.X;
    this->Y = quaternion.Y;
    this->Z = quaternion.Z;
}

// Constructor from Vector3D
Quaternion::Quaternion(const Vector3D& vector) {
    this->W = 0;
    this->X = vector.X;
    this->Y = vector.Y;
    this->Z = vector.Z;
}

// Constructor with individual components
Quaternion::Quaternion(const float& w, const float& x, const float& y, const float& z) {
    this->W = w;
    this->X = x;
    this->Y = y;
    this->Z = z;
}

// Rotate vector
Vector2D Quaternion::RotateVector(const Vector2D& v) const {
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

// Rotate vector with a unit quaternion
Vector2D Quaternion::RotateVectorUnit(const Vector2D& v, const Quaternion& q) const {
    if (IsClose(Quaternion(), Mathematics::EPSILON)) return v;

    float s2 = q.W * 2.0f;
    float dPUV = (q.X * v.X + q.Y * v.Y) * 2.0f;
    float dPUU = q.W * q.W - (q.X * q.X + q.Y * q.Y + q.Z * q.Z);

    return Vector2D{
        X * dPUV + v.X * dPUU + (-(q.Z * v.Y)) * s2,
        Y * dPUV + v.Y * dPUU + ((q.Z * v.X)) * s2
    };
}

// Unrotate vector
Vector2D Quaternion::UnrotateVector(const Vector2D& coordinate) const {
    if (IsClose(Quaternion(), Mathematics::EPSILON)) return coordinate;

    return Conjugate().RotateVector(coordinate);
}

// Rotate vector
Vector3D Quaternion::RotateVector(const Vector3D& v) const {
    if (IsClose(Quaternion(), Mathematics::EPSILON)) return v;
	
    Quaternion qV = Quaternion(0.0f, v.X, v.Y, v.Z);
    Quaternion q = UnitQuaternion();
    Quaternion qConj = q.Conjugate();
    Quaternion rotated = q * qV * qConj;

    return Vector3D(rotated.X, rotated.Y, rotated.Z);
}

// Unrotate vector
Vector3D Quaternion::UnrotateVector(const Vector3D& coordinate) const {
    if (IsClose(Quaternion(), Mathematics::EPSILON)) return coordinate;

    return UnitQuaternion().Conjugate().RotateVector(coordinate);
}

// Get Bivector
Vector3D Quaternion::GetBiVector() const {
    return Vector3D{
        this->X,
        this->Y,
        this->Z
    };
}

Vector3D Quaternion::GetNormal() const {
    return this->RotateVector(Vector3D(0, 0, 1.0f));
}

// Spherical interpolation
Quaternion Quaternion::SphericalInterpolation(const Quaternion& q1, const Quaternion& q2, const float& ratio) {
    if (ratio <= Mathematics::EPSILON) return q1;
    if (ratio >= 1.0f - Mathematics::EPSILON) return q2; 

    Quaternion q1U = q1;
    Quaternion q2U = q2;

    q1U = q1U.UnitQuaternion();
    q2U = q2U.UnitQuaternion();

    float dot = q1U.DotProduct(q2U);//Cosine between the two quaternions

    if (dot < 0.0f){//Shortest path correction
        q1U = q1U.AdditiveInverse();
        dot = -dot;
    }

    if (dot > 0.999f){//Linearly interpolates if results are close
        return (q1U.Add( (q2U.Subtract(q1U)).Multiply(ratio) )).UnitQuaternion();
    }
    else
    {
        dot = Mathematics::Constrain<float>(dot, -1, 1);

        float theta0 = acosf(dot);
        float theta = theta0 * ratio;

        //Quaternion q3 = (q2.Subtract(q1.Multiply(dot))).UnitQuaternion();//UQ for orthonomal 
        float f1 = cosf(theta) - dot * sinf(theta) / sinf(theta0);
        float f2 = sinf(theta) / sinf(theta0);

        return q1U.Multiply(f1).Add(q2U.Multiply(f2)).UnitQuaternion();
    }
}

// Delta rotation
Quaternion Quaternion::DeltaRotation(const Vector3D& angularVelocity, const float& timeDelta) const {
    Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);
    Vector3D angularVelocityL = angularVelocity;
    Vector3D halfAngle = angularVelocityL * (timeDelta / 2.0f);
    float halfAngleLength = halfAngle.Magnitude();

    if(halfAngleLength > Mathematics::EPSILON){//exponential map
        halfAngle = halfAngle * (sinf(halfAngleLength) / halfAngleLength);
        return (current * Quaternion(cosf(halfAngleLength), halfAngle.X, halfAngle.Y, halfAngle.Z)).UnitQuaternion();
    }
    else{//first taylor series
        return (current * Quaternion(1.0f, halfAngle.X, halfAngle.Y, halfAngle.Z)).UnitQuaternion();
    }
}

// Add quaternion
Quaternion Quaternion::Add(const Quaternion& quaternion) const {
    return Quaternion {
        W + quaternion.W,
        X + quaternion.X,
        Y + quaternion.Y,
        Z + quaternion.Z
    };
}

// Subtract quaternion
Quaternion Quaternion::Subtract(const Quaternion& quaternion) const {
    return Quaternion{
        W - quaternion.W,
        X - quaternion.X,
        Y - quaternion.Y,
        Z - quaternion.Z
    };
}

// Multiply quaternion
Quaternion Quaternion::Multiply(const Quaternion& quaternion) const {
    if(quaternion.IsClose(Quaternion(), Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);
    
    #ifndef _ARM_MATH_H
    return Quaternion{
        W * quaternion.W - X * quaternion.X - Y * quaternion.Y - Z * quaternion.Z,
        W * quaternion.X + X * quaternion.W + Y * quaternion.Z - Z * quaternion.Y,
        W * quaternion.Y - X * quaternion.Z + Y * quaternion.W + Z * quaternion.X,
        W * quaternion.Z + X * quaternion.Y - Y * quaternion.X + Z * quaternion.W
    };
    #else
    // 1    5   9   13
    // 2    6   10  14
    // 3    7   11  15
    // 4    8   12  16
    uint32_t multBlockSize = 16; // Increased to 4 for SIMD optimization

    // Input vectors with an additional zero for padding
    float32_t multA[multBlockSize] = {W, W, W, W, X, X, X, X, Y, Y, Y, Y, Z, Z, Z, Z};
    float32_t multB[multBlockSize] = {  quaternion.W, quaternion.X, quaternion.Y, quaternion.Z,
                                        quaternion.X, quaternion.W, quaternion.Z, quaternion.Y,
                                        quaternion.Y, quaternion.Z, quaternion.W, quaternion.X,
                                        quaternion.Z, quaternion.Y, quaternion.X, quaternion.W
    };

    // Output vector to store the result of the multiplication
    float32_t multDst[multBlockSize];

    // Call the function
    arm_mult_f32(multA, multB, multDst, multBlockSize);

    Quaternion q = Quaternion(  multDst[0] - multDst[4] - multDst[8]  - multDst[12],
                                multDst[1] + multDst[5] + multDst[9]  - multDst[13],
                                multDst[2] - multDst[6] + multDst[10] + multDst[14],
                                multDst[3] + multDst[7] - multDst[11] + multDst[15]
    );

    return q;

    #endif
}

// Multiply with scalar
Quaternion Quaternion::Multiply(const float& scalar) const {
    if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Quaternion();
    if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);

    return Quaternion{
        W * scalar,
        X * scalar,
        Y * scalar,
        Z * scalar
    };
}

// Divide quaternion
Quaternion Quaternion::Divide(const Quaternion& quaternion) const {
    if(quaternion.IsClose(Quaternion(), Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);

    return Quaternion(
        (W * quaternion.W - X * quaternion.X - Y * quaternion.Y - Z * quaternion.Z),
        (W * quaternion.X + X * quaternion.W + Y * quaternion.Z - Z * quaternion.Y),
        (W * quaternion.Y - X * quaternion.Z + Y * quaternion.W + Z * quaternion.X),
        (W * quaternion.Z + X * quaternion.Y - Y * quaternion.X + Z * quaternion.W)
    );
}

// Divide by scalar
Quaternion Quaternion::Divide(const float& scalar) const {
    if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Quaternion();
    if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);
    
    float invert = 1.0f / scalar;

    return Quaternion
    {
        W * invert,
        X * invert,
        Y * invert,
        Z * invert
    };
}

// Power of quaternion
Quaternion Quaternion::Power(const Quaternion& exponent) const {
    return Quaternion {
        Mathematics::Pow(W, exponent.W),
        Mathematics::Pow(X, exponent.X),
        Mathematics::Pow(Y, exponent.Y),
        Mathematics::Pow(Z, exponent.Z)
    };
}

// Power with scalar exponent
Quaternion Quaternion::Power(const float& exponent) const {
    return Quaternion {
        Mathematics::Pow(W, exponent),
        Mathematics::Pow(X, exponent),
        Mathematics::Pow(Y, exponent),
        Mathematics::Pow(Z, exponent)
    };
}

// Permutate quaternion
Quaternion Quaternion::Permutate(const Vector3D& permutation) const {
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

// Absolute value of quaternion
Quaternion Quaternion::Absolute() const {
    return Quaternion {
        fabsf(W),
        fabsf(X),
        fabsf(Y),
        fabsf(Z)
    };
}

// Additive inverse of quaternion
Quaternion Quaternion::AdditiveInverse() const {
    return Quaternion {
        -W,
        -X,
        -Y,
        -Z
    };
}

// Multiplicative inverse of quaternion
Quaternion Quaternion::MultiplicativeInverse() const {
    float invNorm = 1.0f / Normal();

    if(Mathematics::IsClose(invNorm, 0.0f, Mathematics::EPSILON)) return Quaternion();
    if(Mathematics::IsClose(invNorm, 1.0f, Mathematics::EPSILON)) return *this;

    return Conjugate().Multiply(invNorm);
}

// Conjugate of quaternion
Quaternion Quaternion::Conjugate() const {
    return Quaternion {
         W,
        -X,
        -Y,
        -Z
    };
}

// Normalize quaternion to unit quaternion
Quaternion Quaternion::UnitQuaternion() const {
    float n = 1.0f / Normal();

    return Quaternion{
        W * n,
        X * n,
        Y * n,
        Z * n
    };
}

// Magnitude of quaternion
float Quaternion::Magnitude() const {
    return Mathematics::Sqrt(Normal());
}

// Dot product of two quaternions
float Quaternion::DotProduct(const Quaternion& q) const {
    return (W * q.W) + (X * q.X) + (Y * q.Y) + (Z * q.Z);
}

// Norm of quaternion
float Quaternion::Normal() const {
    return Mathematics::Sqrt(W * W + X * X + Y * Y + Z * Z);
}

// Check if quaternion is NaN
bool Quaternion::IsNaN() const {
    return Mathematics::IsNaN(W) || Mathematics::IsNaN(X) || Mathematics::IsNaN(Y) || Mathematics::IsNaN(Z);
}

// Check if quaternion is finite
bool Quaternion::IsFinite() const {
	return Mathematics::IsInfinite(W) || Mathematics::IsInfinite(X) || Mathematics::IsInfinite(Y) || Mathematics::IsInfinite(Z);
}

// Check if quaternion is infinite
bool Quaternion::IsInfinite() const {
	return Mathematics::IsFinite(W) || Mathematics::IsFinite(X) || Mathematics::IsFinite(Y) || Mathematics::IsFinite(Z);
}

// Check if quaternion is non-zero
bool Quaternion::IsNonZero() const {
    return W != 0 && X != 0 && Y != 0 && Z != 0;
}

// Check if two quaternions are equal
bool Quaternion::IsEqual(const Quaternion& quaternion) const {
    return !IsNaN() && !quaternion.IsNaN() &&
        W == quaternion.W &&
        X == quaternion.X &&
        Y == quaternion.Y &&
        Z == quaternion.Z;
}

// Check if two quaternions are close within an epsilon
bool Quaternion::IsClose(const Quaternion& quaternion, const float& epsilon) const {
    return fabsf(W - quaternion.W) < epsilon &&
        fabsf(X - quaternion.X) < epsilon &&
        fabsf(Y - quaternion.Y) < epsilon &&
        fabsf(Z - quaternion.Z) < epsilon;
}

// Convert quaternion to string
String Quaternion::ToString() const {
    String w = Mathematics::DoubleToCleanString(this->W);
    String x = Mathematics::DoubleToCleanString(this->X);
    String y = Mathematics::DoubleToCleanString(this->Y);
    String z = Mathematics::DoubleToCleanString(this->Z);
    
    return "[" + w + ", " + x + ", " + y + ", " + z + "]";
}

// Operator overloads
bool Quaternion::operator ==(const Quaternion& quaternion) const {
    return this->IsEqual(quaternion);
}

bool Quaternion::operator !=(const Quaternion& quaternion) const {
    return !(this->IsEqual(quaternion));
}

Quaternion Quaternion::operator =(const Quaternion& quaternion) {
    this->W = quaternion.W;
    this->X = quaternion.X;
    this->Y = quaternion.Y;
    this->Z = quaternion.Z;
    
    return quaternion;
}

Quaternion Quaternion::operator +(const Quaternion& quaternion) const {
    return Add(quaternion);
}

Quaternion Quaternion::operator -(const Quaternion& quaternion) const {
    return Subtract(quaternion);
}

Quaternion Quaternion::operator *(const Quaternion& quaternion) const {
    return Multiply(quaternion);
}

Quaternion Quaternion::operator /(const Quaternion& quaternion) const {
    return Divide(quaternion);
}

Quaternion Quaternion::operator /(const float& scalar) const {
    return Divide(scalar);
}

// Friend operator overloads
Quaternion operator *(const float& scalar, const Quaternion& q) {
    return q.Multiply(scalar);
}

Quaternion operator *(const Quaternion& q, const float& scalar) {
    return q.Multiply(scalar);
}


// Static function definitions

Quaternion Quaternion::Add(const Quaternion& q1, const Quaternion& q2) {
    return q1.Add(q2);
}

Quaternion Quaternion::Subtract(const Quaternion& q1, const Quaternion& q2) {
    return q1.Subtract(q2);
}

Quaternion Quaternion::Multiply(const Quaternion& q1, const Quaternion& q2) {
    return q1.Multiply(q2);
}

Quaternion Quaternion::Divide(const Quaternion& q1, const Quaternion& q2) {
    return q1.Divide(q2);
}

Quaternion Quaternion::Power(const Quaternion& q1, const Quaternion& q2) {
    return q1.Power(q2);
}

float Quaternion::DotProduct(const Quaternion& q1, const Quaternion& q2) {
    return q1.DotProduct(q2);
}

Quaternion Quaternion::Power(const Quaternion& quaternion, const float& exponent) {
    return quaternion.Power(exponent);
}

Quaternion Quaternion::Permutate(const Quaternion& quaternion, const Vector3D& vector) {
    return quaternion.Permutate(vector);
}

Quaternion Quaternion::Absolute(const Quaternion& quaternion) {
    return quaternion.Absolute();
}

Quaternion Quaternion::AdditiveInverse(const Quaternion& quaternion) {
    return quaternion.AdditiveInverse();
}

Quaternion Quaternion::MultiplicativeInverse(const Quaternion& quaternion) {
    return quaternion.MultiplicativeInverse();
}

Quaternion Quaternion::Conjugate(const Quaternion& quaternion) {
    return quaternion.Conjugate();
}

Quaternion Quaternion::UnitQuaternion(const Quaternion& quaternion) {
    return quaternion.UnitQuaternion();
}

float Quaternion::Magnitude(const Quaternion& quaternion) {
    return quaternion.Magnitude();
}

float Quaternion::Normal(const Quaternion& quaternion) {
    return quaternion.Normal();
}
