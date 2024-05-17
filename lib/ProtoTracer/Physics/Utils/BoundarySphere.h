#pragma once

#include "../../Utils/Math/Rotation.h"
#include "../../Utils/Math/Vector3D.h"
#include "../../Scene/Objects/Object3D.h"

class BoundarySphere {
private:
    Object3D* object;
    Vector3D centerPosition;
    Quaternion previousRotation;
    float radius = 1.0f;

public:
    Vector3D velocity = Vector3D(0, 0, 0);
    Vector3D position = Vector3D(0, 0, 0);

    BoundarySphere(Object3D* object, float radius);
    BoundarySphere(Object3D* object, Vector3D position, float radius);

    float GetRadius();
    Object3D* GetObject3D();

    void Update(float dT, Vector3D acceleration, Quaternion rotation);
    bool IsIntersecting(BoundarySphere* bO);
    void Collide(float elasticity, BoundarySphere* bO);
};
