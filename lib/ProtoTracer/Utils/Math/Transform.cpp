#include "Transform.h"
#include "Mathematics.h" // Assuming this header contains necessary utility functions like DegreesToRadians

Transform::Transform() 
    : baseRotation(1, 0, 0, 0), rotation(1, 0, 0, 0), position(0, 0, 0), scale(1, 1, 1), scaleRotationOffset(1, 0, 0, 0) {}

Transform::Transform(Vector3D eulerXYZS, Vector3D position, Vector3D scale) {
    this->rotation = Rotation(EulerAngles(eulerXYZS, EulerConstants::EulerOrderXZYS)).GetQuaternion();
    this->position = position;
    this->scale = scale;
}

Transform::Transform(Quaternion rotation, Vector3D position, Vector3D scale) {
    this->rotation = rotation;
    this->position = position;
    this->scale = scale;
}

Transform::Transform(Vector3D eulerXYZS, Vector3D position, Vector3D scale, Vector3D rotationOffset, Vector3D scaleOffset) {
    this->rotation = Rotation(EulerAngles(eulerXYZS, EulerConstants::EulerOrderXZYS)).GetQuaternion();
    this->position = position;
    this->scale = scale;
    this->rotationOffset = rotationOffset;
    this->scaleOffset = scaleOffset;
}

Transform::Transform(Quaternion rotation, Vector3D position, Vector3D scale, Vector3D rotationOffset, Vector3D scaleOffset) {
    this->rotation = rotation;
    this->position = position;
    this->scale = scale;
    this->rotationOffset = rotationOffset;
    this->scaleOffset = scaleOffset;
}

Transform::Transform(const Transform& transform) {
    this->baseRotation = transform.baseRotation;
    this->rotation = transform.rotation;
    this->position = transform.position;
    this->scale = transform.scale;
    this->scaleRotationOffset = transform.scaleRotationOffset;
    this->rotationOffset = transform.rotationOffset;
    this->scaleOffset = transform.scaleOffset;
}

void Transform::SetBaseRotation(Quaternion baseRotation) {
    this->baseRotation = baseRotation;
}

Quaternion Transform::GetBaseRotation() {
    return baseRotation;
}

void Transform::SetRotation(Quaternion rotation) {
    this->rotation = rotation;
}

void Transform::SetRotation(Vector3D eulerXYZS) {
    this->rotation = Rotation(EulerAngles(eulerXYZS, EulerConstants::EulerOrderXYZS)).GetQuaternion();
}

Quaternion Transform::GetRotation() {
    return rotation * baseRotation;
}

void Transform::SetPosition(Vector3D position) {
    this->position = position;
}

Vector3D Transform::GetPosition() {
    return position;
}

void Transform::SetScale(Vector3D scale) {
    this->scale = scale;
}

Vector3D Transform::GetScale() {
    return scale;
}

void Transform::SetScaleRotationOffset(Quaternion scaleRotationOffset) {
    this->scaleRotationOffset = scaleRotationOffset;
}

Quaternion Transform::GetScaleRotationOffset() {
    return scaleRotationOffset;
}

void Transform::SetRotationOffset(Vector3D rotationOffset) {
    this->rotationOffset = rotationOffset;
}

Vector3D Transform::GetRotationOffset() {
    return rotationOffset;
}

void Transform::SetScaleOffset(Vector3D scaleOffset) {
    this->scaleOffset = scaleOffset;
}

Vector3D Transform::GetScaleOffset() {
    return scaleOffset;
}

void Transform::Rotate(Vector3D eulerXYZS) {
    this->rotation = this->rotation * Rotation(EulerAngles(eulerXYZS, EulerConstants::EulerOrderXYZS)).GetQuaternion();
}

void Transform::Rotate(Quaternion rotation) {
    this->rotation = this->rotation * rotation;
}

void Transform::Translate(Vector3D offset) {
    this->position = this->position + offset;
}

void Transform::Scale(Vector3D scale) {
    this->scale = this->scale * scale;
}
