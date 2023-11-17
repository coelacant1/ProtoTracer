#include "Quaternion.h"
#include "Mathematics.h"

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
Quaternion::Quaternion(Vector3D vector) {
    this->W = 0;
    this->X = vector.X;
    this->Y = vector.Y;
    this->Z = vector.Z;
}

// Constructor with individual components
Quaternion::Quaternion(float w, float x, float y, float z) {
    this->W = w;
    this->X = x;
    this->Y = y;
    this->Z = z;
}

// Rotate vector
Vector2D Quaternion::RotateVector(Vector2D v) {
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
Vector2D Quaternion::RotateVectorUnit(Vector2D v, const Quaternion& q) {
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
Vector2D Quaternion::UnrotateVector(Vector2D coordinate) {
    if (IsClose(Quaternion(), Mathematics::EPSILON)) return coordinate;

    return Conjugate().RotateVector(coordinate);
}

// Rotate vector
Vector3D Quaternion::RotateVector(Vector3D v) {
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

// Unrotate vector
Vector3D Quaternion::UnrotateVector(Vector3D coordinate) {
    if (IsClose(Quaternion(), Mathematics::EPSILON)) return coordinate;

    return UnitQuaternion().Conjugate().RotateVector(coordinate);
}

// Get Bivector
Vector3D Quaternion::GetBiVector() {
    return Vector3D{
        this->X,
        this->Y,
        this->Z
    };
}

// Spherical interpolation
Quaternion Quaternion::SphericalInterpolation(Quaternion q1, Quaternion q2, float ratio) {
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

// Delta rotation
Quaternion Quaternion::DeltaRotation(Vector3D angularVelocity, float timeDelta) {
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

// Add quaternion
Quaternion Quaternion::Add(Quaternion quaternion) {
    return Quaternion {
        W + quaternion.W,
        X + quaternion.X,
        Y + quaternion.Y,
        Z + quaternion.Z
    };
}

// Subtract quaternion
Quaternion Quaternion::Subtract(Quaternion quaternion) {
    return Quaternion{
        W - quaternion.W,
        X - quaternion.X,
        Y - quaternion.Y,
        Z - quaternion.Z
    };
}

// Multiply quaternion
Quaternion Quaternion::Multiply(Quaternion quaternion) {
    if(quaternion.IsClose(Quaternion(), Mathematics::EPSILON)) return Quaternion(W, X, Y, Z);
    
    return Quaternion{
        W * quaternion.W - X * quaternion.X - Y * quaternion.Y - Z * quaternion.Z,
        W * quaternion.X + X * quaternion.W + Y * quaternion.Z - Z * quaternion.Y,
        W * quaternion.Y - X * quaternion.Z + Y * quaternion.W + Z * quaternion.X,
        W * quaternion.Z + X * quaternion.Y - Y * quaternion.X + Z * quaternion.W
    };
}

// Multiply with scalar
Quaternion Quaternion::Multiply(float scalar) {
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
Quaternion Quaternion::Divide(Quaternion quaternion) {
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

// Divide by scalar
Quaternion Quaternion::Divide(float scalar) {
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

// Power of quaternion
Quaternion Quaternion::Power(Quaternion exponent) {
    return Quaternion {
        Mathematics::Pow(W, exponent.W),
        Mathematics::Pow(X, exponent.X),
        Mathematics::Pow(Y, exponent.Y),
        Mathematics::Pow(Z, exponent.Z)
    };
}

// Power with scalar exponent
Quaternion Quaternion::Power(float exponent) {
    return Quaternion {
        Mathematics::Pow(W, exponent),
        Mathematics::Pow(X, exponent),
        Mathematics::Pow(Y, exponent),
        Mathematics::Pow(Z, exponent)
    };
}

// Permutate quaternion
Quaternion Quaternion::Permutate(Vector3D permutation) {
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
Quaternion Quaternion::Absolute() {
    return Quaternion {
        fabsf(W),
        fabsf(X),
        fabsf(Y),
        fabsf(Z)
    };
}

// Additive inverse of quaternion
Quaternion Quaternion::AdditiveInverse() {
    return Quaternion {
        -W,
        -X,
        -Y,
        -Z
    };
}

// Multiplicative inverse of quaternion
Quaternion Quaternion::MultiplicativeInverse() {
    float invNorm = 1.0f / Normal();

    if(Mathematics::IsClose(invNorm, 0.0f, Mathematics::EPSILON)) return Quaternion();
    if(Mathematics::IsClose(invNorm, 1.0f, Mathematics::EPSILON)) return *this;

    return Conjugate().Multiply(invNorm);
}

// Conjugate of quaternion
Quaternion Quaternion::Conjugate() {
    return Quaternion {
         W,
        -X,
        -Y,
        -Z
    };
}

// Normalize quaternion to unit quaternion
Quaternion Quaternion::UnitQuaternion() {
    float n = 1.0f / Normal();

    return Quaternion{
        W * n,
        X * n,
        Y * n,
        Z * n
    };
}

// Magnitude of quaternion
float Quaternion::Magnitude() {
    return Mathematics::Sqrt(Normal());
}

// Dot product of two quaternions
float Quaternion::DotProduct(Quaternion q) {
    return (W * q.W) + (X * q.X) + (Y * q.Y) + (Z * q.Z);
}

// Norm of quaternion
float Quaternion::Normal() {
    return Mathematics::Sqrt(W * W + X * X + Y * Y + Z * Z);
}

// Check if quaternion is NaN
bool Quaternion::IsNaN() {
    return Mathematics::IsNaN(W) || Mathematics::IsNaN(X) || Mathematics::IsNaN(Y) || Mathematics::IsNaN(Z);
}

// Check if quaternion is finite
bool Quaternion::IsFinite() {
	return Mathematics::IsInfinite(W) || Mathematics::IsInfinite(X) || Mathematics::IsInfinite(Y) || Mathematics::IsInfinite(Z);
}

// Check if quaternion is infinite
bool Quaternion::IsInfinite() {
	return Mathematics::IsFinite(W) || Mathematics::IsFinite(X) || Mathematics::IsFinite(Y) || Mathematics::IsFinite(Z);
}

// Check if quaternion is non-zero
bool Quaternion::IsNonZero() {
    return W != 0 && X != 0 && Y != 0 && Z != 0;
}

// Check if two quaternions are equal
bool Quaternion::IsEqual(Quaternion quaternion) {
    return !IsNaN() && !quaternion.IsNaN() &&
        W == quaternion.W &&
        X == quaternion.X &&
        Y == quaternion.Y &&
        Z == quaternion.Z;
}

// Check if two quaternions are close within an epsilon
bool Quaternion::IsClose(Quaternion quaternion, float epsilon) {
    return fabs(W - quaternion.W) < epsilon &&
        fabs(X - quaternion.X) < epsilon &&
        fabs(Y - quaternion.Y) < epsilon &&
        fabs(Z - quaternion.Z) < epsilon;
}

// Convert quaternion to string
String Quaternion::ToString() {
    String w = Mathematics::DoubleToCleanString(this->W);
    String x = Mathematics::DoubleToCleanString(this->X);
    String y = Mathematics::DoubleToCleanString(this->Y);
    String z = Mathematics::DoubleToCleanString(this->Z);
    
    return "[" + w + ", " + x + ", " + y + ", " + z + "]";
}

// Operator overloads
bool Quaternion::operator ==(Quaternion quaternion) {
    return this->IsEqual(quaternion);
}

bool Quaternion::operator !=(Quaternion quaternion) {
    return !(this->IsEqual(quaternion));
}

Quaternion Quaternion::operator =(Quaternion quaternion) {
    this->W = quaternion.W;
    this->X = quaternion.X;
    this->Y = quaternion.Y;
    this->Z = quaternion.Z;
    
    return quaternion;
}

Quaternion Quaternion::operator +(Quaternion quaternion) {
    return Add(quaternion);
}

Quaternion Quaternion::operator -(Quaternion quaternion) {
    return Subtract(quaternion);
}

Quaternion Quaternion::operator *(Quaternion quaternion) {
    return Multiply(quaternion);
}

Quaternion Quaternion::operator /(Quaternion quaternion) {
    return Divide(quaternion);
}

Quaternion Quaternion::operator /(float scalar) {
    return Divide(scalar);
}

// Friend operator overloads
Quaternion operator *(float scalar, Quaternion q) {
    return q.Multiply(scalar);
}

Quaternion operator *(Quaternion q, float scalar) {
    return q.Multiply(scalar);
}


// Static function definitions

Quaternion Quaternion::Add(Quaternion q1, Quaternion q2) {
    return q1.Add(q2);
}

Quaternion Quaternion::Subtract(Quaternion q1, Quaternion q2) {
    return q1.Subtract(q2);
}

Quaternion Quaternion::Multiply(Quaternion q1, Quaternion q2) {
    return q1.Multiply(q2);
}

Quaternion Quaternion::Divide(Quaternion q1, Quaternion q2) {
    return q1.Divide(q2);
}

Quaternion Quaternion::Power(Quaternion q1, Quaternion q2) {
    return q1.Power(q2);
}

float Quaternion::DotProduct(Quaternion q1, Quaternion q2) {
    return q1.DotProduct(q2);
}

Quaternion Quaternion::Power(Quaternion quaternion, float exponent) {
    return quaternion.Power(exponent);
}

Quaternion Quaternion::Permutate(Quaternion quaternion, Vector3D vector) {
    return quaternion.Permutate(vector);
}

Quaternion Quaternion::Absolute(Quaternion quaternion) {
    return quaternion.Absolute();
}

Quaternion Quaternion::AdditiveInverse(Quaternion quaternion) {
    return quaternion.AdditiveInverse();
}

Quaternion Quaternion::MultiplicativeInverse(Quaternion quaternion) {
    return quaternion.MultiplicativeInverse();
}

Quaternion Quaternion::Conjugate(Quaternion quaternion) {
    return quaternion.Conjugate();
}

Quaternion Quaternion::UnitQuaternion(Quaternion quaternion) {
    return quaternion.UnitQuaternion();
}

float Quaternion::Magnitude(Quaternion quaternion) {
    return quaternion.Magnitude();
}

float Quaternion::Normal(Quaternion quaternion) {
    return quaternion.Normal();
}
