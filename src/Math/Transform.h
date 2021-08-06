#pragma once

#include "Rotation.h"
#include "Vector3D.h"

class Transform{
private:
    Quaternion baseRotation = Quaternion(1, 0, 0, 0);
    Quaternion rotation = Quaternion(1, 0, 0, 0);
    Vector3D position = Vector3D(0, 0, 0);
    Vector3D scale = Vector3D(1, 1, 1);

public:
    Transform(){}

    Transform(Vector3D eulerXYZS, Vector3D position, Vector3D scale){
        this->rotation = Rotation(EulerAngles(eulerXYZS, EulerConstants::EulerOrderXZYS)).GetQuaternion();
        this->position = position;
        this->scale = scale;
    }

    Transform(Quaternion rotation, Vector3D position, Vector3D scale){
        this->rotation = rotation;
        this->position = position;
        this->scale = scale;
    }

    Transform(const Transform& transform) {
        this->baseRotation = transform.baseRotation;
        this->rotation = transform.rotation;
        this->position = transform.position;
        this->scale = transform.scale;
    }

    void SetBaseRotation(Quaternion baseRotation){
        this->baseRotation = baseRotation;
    }

    const Quaternion GetBaseRotation(){
        return baseRotation;
    }

    void SetRotation(Quaternion rotation){
        this->rotation = rotation;
    }

    void SetRotation(Vector3D eulerXYZS){
        this->rotation = Rotation(EulerAngles(eulerXYZS, EulerConstants::EulerOrderXYZS)).GetQuaternion();
    }

    Quaternion GetRotation(){
        return rotation * baseRotation;
    }

    void SetPosition(Vector3D position){
        this->position = position;
    }

    Vector3D GetPosition(){
        return position;
    }

    void SetScale(Vector3D scale){
        this->scale = scale;
    }

    Vector3D GetScale(){
        return scale;
    }

    void Rotate(Vector3D eulerXYZS){
        this->rotation = this->rotation * Rotation(EulerAngles(eulerXYZS, EulerConstants::EulerOrderXYZS)).GetQuaternion();
    }

    void Rotate(Quaternion rotation){
        this->rotation = this->rotation * rotation;
    }

    void Translate(Vector3D offset){
        this->position = this->position + offset;
    }

    void Scale(Vector3D scale){
        this->scale = this->scale * scale;
    }
};
