#include "Vector2D.h"

Vector2D::Vector2D() : X(0.0f), Y(0.0f) {}

Vector2D::Vector2D(const Vector2D& vector) : X(vector.X), Y(vector.Y) {}

Vector2D::Vector2D(const float& X, const float& Y) : X(X), Y(Y) {}

Vector2D::Vector2D(const Vector3D& vector) : X(vector.X), Y(vector.Y) {}

Vector2D Vector2D::Absolute() const {
    return Vector2D{
        fabsf(X),
        fabsf(Y)
    };
}

Vector2D Vector2D::Normal() const {
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

Vector2D Vector2D::Add(const Vector2D& vector) const {
    return Vector2D{
        X + vector.X,
        Y + vector.Y
    };
}

Vector2D Vector2D::Subtract(const Vector2D& vector) const {
    return Vector2D{
        X - vector.X,
        Y - vector.Y
    };
}

Vector2D Vector2D::Multiply(const Vector2D& vector) const {
    return Vector2D{
        X * vector.X,
        Y * vector.Y
    };
}

Vector2D Vector2D::Divide(const Vector2D& vector) const {
    return Vector2D{
        X / vector.X,
        Y / vector.Y
    };
}

Vector2D Vector2D::Multiply(const float& scalar) const {
    if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return (*this);
    if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Vector3D();

    return Vector2D{
        X * scalar,
        Y * scalar
    };
}

Vector2D Vector2D::Divide(const float& scalar) const {
    if (Mathematics::IsClose(scalar, 1.0f, Mathematics::EPSILON)) return (*this);
    if (Mathematics::IsClose(scalar, 0.0f, Mathematics::EPSILON)) return Vector3D();
    
    return Vector2D{
        X / scalar,
        Y / scalar
    };
}

Vector3D Vector2D::CrossProduct(const Vector2D& vector) const {
    return Vector3D{
        0.0f,
        0.0f,
        (X * vector.Y) - (Y * vector.X)
    };
}

Vector2D Vector2D::UnitCircle() const {
    float length = Magnitude();

    if (Mathematics::IsClose(length, 1.0f, Mathematics::EPSILON)) return Vector2D(this->X, this->Y);
    if (length == 0) return Vector2D(0, 1);

    return Vector2D{
        X / length,
        Y / length
    };
}

Vector2D Vector2D::Constrain(const float& minimum, const float& maximum) const {
    return Vector2D{
        Mathematics::Constrain(X, minimum, maximum),
        Mathematics::Constrain(Y, minimum, maximum)
    };
}

Vector2D Vector2D::Constrain(const Vector2D& minimum, const Vector2D& maximum) const {
    return Vector2D{
        Mathematics::Constrain(X, minimum.X, maximum.X),
        Mathematics::Constrain(Y, minimum.Y, maximum.Y)
    };
}

Vector2D Vector2D::Minimum(const Vector2D& v) const {
    return Vector2D{
        X < v.X ? X : v.X,
        Y < v.Y ? Y : v.Y
    };
}

Vector2D Vector2D::Maximum(const Vector2D& v) const {
    return Vector2D{
        X > v.X ? X : v.X,
        Y > v.Y ? Y : v.Y
    };
}

Vector2D Vector2D::Rotate(const float& angle, const Vector2D& offset) const {
    Vector2D v = Vector2D(X, Y).Subtract(offset);

    float angleMPD18 = angle * Mathematics::MPID180;

    float cs = cosf(angleMPD18);
    float sn = sinf(angleMPD18);

    return Vector2D{
        v.X * cs - v.Y * sn + offset.X,
        v.X * sn + v.Y * cs + offset.Y
    };
}

bool Vector2D::CheckBounds(const Vector2D& minimum, const Vector2D& maximum) const {
    return X > minimum.X && X < maximum.X && Y > minimum.Y && Y < maximum.Y;
}

float Vector2D::Magnitude() const {
    return Mathematics::Sqrt(X * X + Y * Y);
}

float Vector2D::DotProduct(const Vector2D& vector) const {
    return (X * vector.X) + (Y * vector.Y);
}

float Vector2D::CalculateEuclideanDistance(const Vector2D& vector) const {
    Vector2D offset = Vector2D(X - vector.X, Y - vector.Y);

    return offset.Magnitude();
}

bool Vector2D::IsEqual(const Vector2D& vector) const {
    return (X == vector.X) && (Y == vector.Y);
}

String Vector2D::ToString() const {
    String x = Mathematics::DoubleToCleanString(X);
    String y = Mathematics::DoubleToCleanString(Y);

    return "[" + x + ", " + y + "]";
}


// Implementations of static member functions
Vector2D Vector2D::Minimum(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D{
        v1.X < v2.X ? v1.X : v2.X,
        v1.Y < v2.Y ? v1.Y : v2.Y
    };
}

Vector2D Vector2D::Maximum(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D{
        v1.X > v2.X ? v1.X : v2.X,
        v1.Y > v2.Y ? v1.Y : v2.Y
    };
}

Vector2D Vector2D::LERP(const Vector2D& start, const Vector2D& finish, const float& ratio) {
    Vector2D startL = start, finishL = finish;

    return finishL * ratio + startL * (1.0f - ratio);
}

Vector2D Vector2D::DegreesToRadians(const Vector2D& degrees) {
    return Vector2D(degrees.X * Mathematics::MPID180, degrees.Y * Mathematics::MPID180);
}

Vector2D Vector2D::RadiansToDegrees(const Vector2D& radians) {
    return Vector2D(radians.X * Mathematics::M180DPI, radians.Y * Mathematics::M180DPI);
}

Vector2D Vector2D::Normal(const Vector2D& vector) {
    Vector2D normal = vector;

    return normal.Normal();
}

Vector2D Vector2D::Add(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.X + v2.X, v1.Y + v2.Y);
}

Vector2D Vector2D::Subtract(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.X - v2.X, v1.Y - v2.Y);
}

Vector2D Vector2D::Multiply(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.X * v2.X, v1.Y * v2.Y);
}

Vector2D Vector2D::Divide(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.X / v2.X, v1.Y / v2.Y);
}

Vector2D Vector2D::Multiply(const Vector2D& vector, const float& scalar) {
    return Vector2D(vector.X * scalar, vector.Y * scalar);
}

Vector2D Vector2D::Multiply(const float& scalar, const Vector2D& vector) {
    return Vector2D(vector.X * scalar, vector.Y * scalar);
}

Vector2D Vector2D::Divide(const Vector2D& vector, const float& scalar) {
    return Vector2D(vector.X / scalar, vector.Y / scalar);
}

Vector3D Vector2D::CrossProduct(const Vector2D& v1, const Vector2D& v2) {
    return Vector3D{
        0.0f,
        0.0f,
        (v1.X * v2.Y) - (v1.Y * v2.X)
    };
}

float Vector2D::DotProduct(const Vector2D& v1, const Vector2D& v2) {
    return (v1.X * v2.X) + (v1.Y * v2.Y);
}

float Vector2D::CalculateEuclideanDistance(const Vector2D& v1, const Vector2D& v2) {
    Vector2D offset = Vector2D(v1.X - v2.X, v1.Y - v2.Y);

    return offset.Magnitude();
}

bool Vector2D::IsEqual(const Vector2D& v1, const Vector2D& v2) {
    return (v1.X == v2.X) && (v1.Y == v2.Y);
}

// Operator overloads
bool Vector2D::operator ==(const Vector2D& vector) const {
    return this->IsEqual(vector);
}

bool Vector2D::operator !=(const Vector2D& vector) const {
    return !(this->IsEqual(vector));
}

Vector2D Vector2D::operator =(const Vector2D& vector) {
    this->X = vector.X;
    this->Y = vector.Y;

    return *this;
}

Vector2D Vector2D::operator =(const Vector3D& vector) {
    this->X = vector.X;
    this->Y = vector.Y;

    return *this;
}

Vector2D Vector2D::operator +(const Vector2D& vector) const {
    return Add(vector);
}

Vector2D Vector2D::operator -(const Vector2D& vector) const {
    return Subtract(vector);
}

Vector2D Vector2D::operator *(const Vector2D& vector) const {
    return Multiply(vector);
}

Vector2D Vector2D::operator /(const Vector2D& vector) const {
    return Divide(vector);
}

Vector2D Vector2D::operator *(const float& value) const {
    return Multiply(value);
}

Vector2D Vector2D::operator /(const float& value) const {
    return Divide(value);
}