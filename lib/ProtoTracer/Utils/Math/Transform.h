#pragma once

#include "Rotation.h"
#include "Vector3D.h"

class Transform {
private:
    Quaternion baseRotation;
    Quaternion rotation;
    Vector3D position;
    Vector3D scale;
    Quaternion scaleRotationOffset;

    Vector3D scaleOffset;
    Vector3D rotationOffset;

public:
    Transform();
    Transform(const Vector3D& eulerXYZS, const Vector3D& position, const Vector3D& scale);
    Transform(const Quaternion& rotation, const Vector3D& position, const Vector3D& scale);
    Transform(const Vector3D& eulerXYZS, const Vector3D& position, const Vector3D& scale, const Vector3D& rotationOffset, const Vector3D& scaleOffset);
    Transform(const Quaternion& rotation, const Vector3D& position, const Vector3D& scale, const Vector3D& rotationOffset, const Vector3D& scaleOffset);
    Transform(const Transform& transform);

    void SetBaseRotation(const Quaternion& baseRotation);
    Quaternion GetBaseRotation();

    void SetRotation(const Quaternion& rotation);
    void SetRotation(const Vector3D& eulerXYZS);
    Quaternion GetRotation();

    void SetPosition(const Vector3D& position);
    Vector3D GetPosition();

    void SetScale(const Vector3D& scale);
    Vector3D GetScale();

    void SetScaleRotationOffset(const Quaternion& scaleRotationOffset);
    Quaternion GetScaleRotationOffset();

    void SetRotationOffset(const Vector3D& rotationOffset);
    Vector3D GetRotationOffset();

    void SetScaleOffset(const Vector3D& scaleOffset);
    Vector3D GetScaleOffset();

    void Rotate(const Vector3D& eulerXYZS);
    void Rotate(const Quaternion& rotation);
    void Translate(const Vector3D& offset);
    void Scale(const Vector3D& scale);

    String ToString();
};
