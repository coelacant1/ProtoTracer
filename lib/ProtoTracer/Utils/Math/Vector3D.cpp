#include "Vector3D.h"

Vector3D::Vector3D() : X(0.0f), Y(0.0f), Z(0.0f) {}

Vector3D::Vector3D(const Vector3D& vector) : X(vector.X), Y(vector.Y), Z(vector.Z) {}

Vector3D::Vector3D(float X, float Y, float Z) : X(X), Y(Y), Z(Z) {}

// Implementations of non-static member functions
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

Vector3D Vector3D::Add(float value) {
    return Vector3D{
        this->X + value,
        this->Y + value,
        this->Z + value 
    };
}

Vector3D Vector3D::Subtract(float value) {
    return Vector3D {
        this->X - value,
        this->Y - value,
        this->Z - value
    };
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

// Implementations of static member functions
Vector3D Vector3D::Max(Vector3D max, Vector3D input) {
    return Vector3D(input.X > max.X ? input.X : max.X,
		input.Y > max.Y ? input.Y : max.Y,
		input.Z > max.Z ? input.Z : max.Z);
}

Vector3D Vector3D::Min(Vector3D min, Vector3D input) {
    return Vector3D(input.X < min.X ? input.X : min.X,
		input.Y < min.Y ? input.Y : min.Y,
		input.Z < min.Z ? input.Z : min.Z);
}

Vector3D Vector3D::LERP(Vector3D start, Vector3D finish, float ratio) {
    return finish * ratio + start * (1.0f - ratio);
}

Vector3D Vector3D::DegreesToRadians(Vector3D degrees) {
    return degrees * Mathematics::MPID180;
}

Vector3D Vector3D::RadiansToDegrees(Vector3D radians) {
    return radians * Mathematics::M180DPI;
}

Vector3D Vector3D::Normal(Vector3D vector) {
    return vector.Normal();
}

Vector3D Vector3D::Add(Vector3D v1, Vector3D v2) {
    return v1.Add(v2);
}

Vector3D Vector3D::Subtract(Vector3D v1, Vector3D v2) {
    return v1.Subtract(v2);
}

Vector3D Vector3D::Multiply(Vector3D v1, Vector3D v2) {
    return v1.Multiply(v2);
}

Vector3D Vector3D::Divide(Vector3D v1, Vector3D v2) {
    return v1.Divide(v2);
}

Vector3D Vector3D::Multiply(Vector3D vector, float scalar) {
    return vector.Multiply(scalar);
}

Vector3D Vector3D::Multiply(float scalar, Vector3D vector) {
    return vector.Multiply(scalar);
}

Vector3D Vector3D::Divide(Vector3D vector, float scalar) {
    return vector.Divide(scalar);
}

Vector3D Vector3D::CrossProduct(Vector3D v1, Vector3D v2) {
    return v1.CrossProduct(v2);
}

float Vector3D::DotProduct(Vector3D v1, Vector3D v2) {
    return v1.DotProduct(v2);
}

float Vector3D::CalculateEuclideanDistance(Vector3D v1, Vector3D v2) {
    return v1.CalculateEuclideanDistance(v2);
}

bool Vector3D::IsEqual(Vector3D v1, Vector3D v2) {
    return v1.IsEqual(v2);
}

// Operator overloads
bool Vector3D::operator ==(Vector3D vector) {
    return this->IsEqual(vector);
}

bool Vector3D::operator !=(Vector3D vector) {
    return !(this->IsEqual(vector));
}

Vector3D Vector3D::operator =(Vector3D vector) {
    this->X = vector.X;
    this->Y = vector.Y;
    this->Z = vector.Z;

    return *this;
}

Vector3D Vector3D::operator +(Vector3D vector) {
    return Add(vector);
}

Vector3D Vector3D::operator -(Vector3D vector) {
    return Subtract(vector);
}

Vector3D Vector3D::operator *(Vector3D vector) {
    return Multiply(vector);
}

Vector3D Vector3D::operator /(Vector3D vector) {
    return Divide(vector);
}

Vector3D Vector3D::operator +(float value) {
    return Add(value);
}

Vector3D Vector3D::operator -(float value) {
    return Subtract(value);
}

Vector3D Vector3D::operator *(float value) {
    return Multiply(value);
}

Vector3D Vector3D::operator /(float value) {
    return Divide(value);
}
