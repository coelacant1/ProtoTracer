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
    Transform(Vector3D eulerXYZS, Vector3D position, Vector3D scale);
    Transform(Quaternion rotation, Vector3D position, Vector3D scale);
    Transform(Vector3D eulerXYZS, Vector3D position, Vector3D scale, Vector3D rotationOffset, Vector3D scaleOffset);
    Transform(Quaternion rotation, Vector3D position, Vector3D scale, Vector3D rotationOffset, Vector3D scaleOffset);
    Transform(const Transform& transform);

    void SetBaseRotation(Quaternion baseRotation);
    Quaternion GetBaseRotation();

    void SetRotation(Quaternion rotation);
    void SetRotation(Vector3D eulerXYZS);
    Quaternion GetRotation();

    void SetPosition(Vector3D position);
    Vector3D GetPosition();

    void SetScale(Vector3D scale);
    Vector3D GetScale();

    void SetScaleRotationOffset(Quaternion scaleRotationOffset);
    Quaternion GetScaleRotationOffset();

    void SetRotationOffset(Vector3D rotationOffset);
    Vector3D GetRotationOffset();

    void SetScaleOffset(Vector3D scaleOffset);
    Vector3D GetScaleOffset();

    void Rotate(Vector3D eulerXYZS);
    void Rotate(Quaternion rotation);
    void Translate(Vector3D offset);
    void Scale(Vector3D scale);
};
