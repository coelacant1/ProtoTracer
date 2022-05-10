#pragma once

#include "Rotation.h"
#include "Vector3D.h"

class Transform {
private:
    Quaternion baseRotation = Quaternion(1, 0, 0, 0);
    Quaternion rotation = Quaternion(1, 0, 0, 0);
    Vector3D position = Vector3D(0, 0, 0);
    Vector3D scale = Vector3D(1, 1, 1);

    Vector3D rotationOffset = Vector3D(0, 0, 0);
    Vector3D scaleOffset = Vector3D(0, 0, 0);

public:
    Transform() {}
    Transform(const Vector3D &eulerXYZS, const Vector3D &position, const Vector3D &scale)
        : rotation(Rotation(EulerAngles(eulerXYZS, EulerConstants::EulerOrderXZYS)).GetQuaternion()),
          position(position),
          scale(scale) {}
    Transform(const Quaternion &rotation, const Vector3D &position, const Vector3D &scale)
        : rotation(rotation),
          position(position),
          scale(scale) {}
    Transform(const Vector3D &eulerXYZS, const Vector3D &position, const Vector3D &scale, const Vector3D rotationOffset, const Vector3D &scaleOffset)
        : rotation(Rotation(EulerAngles(eulerXYZS, EulerConstants::EulerOrderXZYS)).GetQuaternion()),
          position(position),
          scale(scale),
          rotationOffset(rotationOffset),
          scaleOffset(scaleOffset) {}
    Transform(const Quaternion &rotation, const Vector3D &position, const Vector3D &scale, const Vector3D &rotationOffset, const Vector3D &scaleOffset)
        : rotation(rotation),
          position(position),
          scale(scale),
          rotationOffset(rotationOffset),
          scaleOffset(scaleOffset) {}
    Transform(const Transform &transform)
        : baseRotation(transform.baseRotation),
          rotation(transform.rotation),
          position(transform.position),
          scale(transform.scale) {}

    void SetBaseRotation(const Quaternion &baseRotation) {
        this->baseRotation = baseRotation;
    }

    Quaternion GetBaseRotation() const {
        return baseRotation;
    }

    void SetRotation(const Quaternion &rotation) {
        this->rotation = rotation;
    }

    void SetRotation(const Vector3D &eulerXYZS) {
        this->rotation = Rotation(EulerAngles(eulerXYZS, EulerConstants::EulerOrderXYZS)).GetQuaternion();
    }

    Quaternion GetRotation() const {
        return rotation * baseRotation;
    }

    void SetPosition(const Vector3D &position) {
        this->position = position;
    }

    Vector3D GetPosition() const {
        return position;
    }

    void SetScale(const Vector3D &scale) {
        this->scale = scale;
    }

    Vector3D GetScale() const {
        return scale;
    }

    void SetRotationOffset(const Vector3D &rotationOffset) {
        this->rotationOffset = rotationOffset;
    }

    Vector3D GetRotationOffset() const {
        return rotationOffset;
    }

    void SetScaleOffset(const Vector3D &scaleOffset) {
        this->scaleOffset = scaleOffset;
    }

    Vector3D GetScaleOffset() const {
        return scaleOffset;
    }

    void Rotate(const Vector3D &eulerXYZS) {
        this->rotation *= Rotation(EulerAngles(eulerXYZS, EulerConstants::EulerOrderXYZS)).GetQuaternion();
    }

    void Rotate(const Quaternion &rotation) {
        this->rotation *= rotation;
    }

    void Translate(const Vector3D &offset) {
        this->position += offset;
    }

    void Scale(const Vector3D &scale) {
        this->scale *= scale;
    }
};
