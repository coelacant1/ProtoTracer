#include "BoundaryCube.h"

BoundaryCube::BoundaryCube(Object3D* object) {
    this->centerPosition = object->GetTransform()->GetPosition() + object->GetCenterOffset();
    object->GetMinMaxDimensions(minimum, maximum);
}

BoundaryCube::BoundaryCube(Vector3D centerPosition, Vector3D objectSize) {
    this->centerPosition = centerPosition;
    this->minimum = centerPosition - objectSize / 2.0f;
    this->maximum = centerPosition + objectSize / 2.0f;
}

Vector3D BoundaryCube::GetPosition() {
    return centerPosition;
}

Vector3D BoundaryCube::GetSize() {
    return maximum - minimum;
}

Vector3D BoundaryCube::GetMaximum() {
    return maximum;
}

Vector3D BoundaryCube::GetMinimum() {
    return minimum;
}

void BoundaryCube::Update(float dT, Vector3D acceleration, Quaternion rotation) {
    Quaternion rotationChange = rotation.Multiply(previousRotation.MultiplicativeInverse());
    velocity = rotationChange.RotateVector(velocity) + acceleration * dT; // maintain momentum of existing velocity, apply local acceleration
    position = position + velocity * dT;

    previousRotation = rotation;
}

Vector3D BoundaryCube::IsIntersecting(BoundaryCube* bO) {
    Vector3D collision;

    collision.X = maximum.X >= bO->GetMinimum().X ? 0 : 1;
    collision.X = bO->GetMaximum().X >= minimum.X ? 0 : -1;
    collision.Y = maximum.Y >= bO->GetMinimum().Y ? 0 : 1;
    collision.Y = bO->GetMaximum().Y >= minimum.Y ? 0 : -1;
    collision.Z = maximum.Z >= bO->GetMinimum().Z ? 0 : 1;
    collision.Z = bO->GetMaximum().Z >= minimum.Z ? 0 : -1;

    return collision;
}

Vector3D BoundaryCube::IsIntersecting(BoundarySphere* bO) {
    Vector3D collision;
    Vector3D minimumExt, maximumExt;
    Vector3D sphereSize = Vector3D(bO->GetRadius(), bO->GetRadius(), bO->GetRadius());

    minimumExt = bO->position - sphereSize;
    maximumExt = bO->position + sphereSize;

    collision.X = minimum.X <= maximumExt.X && maximum.X >= minimumExt.X;
    collision.Y = minimum.Y <= maximumExt.Y && maximum.Y >= minimumExt.Y;
    collision.Z = minimum.Z <= maximumExt.Z && maximum.Z >= minimumExt.Z;

    return collision;
}

void BoundaryCube::CollideSphere(float elasticity, BoundarySphere* bO) {
    // if sphere is not within the bounds of the prism, collide
    Vector3D collision = IsIntersecting(bO);
    Vector3D shiftCorrection;

    if (collision.X)
        shiftCorrection.X = bO->velocity.X * -0.01f;
    if (collision.Y)
        shiftCorrection.Y = bO->velocity.Y * -0.01f;
    if (collision.Z)
        shiftCorrection.Z = bO->velocity.Z * -0.01f;

    bO->velocity.X = collision.X == 1 ? bO->velocity.X : -bO->velocity.X * elasticity;
    bO->velocity.Y = collision.Y == 1 ? bO->velocity.Y : -bO->velocity.Y * elasticity;
    bO->velocity.Z = collision.Z == 1 ? bO->velocity.Z : -bO->velocity.Z * elasticity;

    bO->position.X = Mathematics::Constrain(bO->position.X, minimum.X - bO->GetRadius(), maximum.X + bO->GetRadius());
    bO->position.Y = Mathematics::Constrain(bO->position.Y, minimum.Y - bO->GetRadius(), maximum.Y + bO->GetRadius());
    bO->position.Z = Mathematics::Constrain(bO->position.Z, minimum.Z - bO->GetRadius(), maximum.Z + bO->GetRadius());

    bO->position = bO->position + shiftCorrection;
}
