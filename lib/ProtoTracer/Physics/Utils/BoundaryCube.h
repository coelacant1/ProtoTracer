#pragma once

#include "..\..\Utils\Math\Rotation.h"
#include "..\..\Utils\Math\Vector3D.h"
#include "..\..\Scene\Objects\Object3D.h"
#include "BoundarySphere.h"

class BoundaryCube {
private:
    Quaternion previousRotation;
    Vector3D centerPosition;
    Vector3D maximum;
    Vector3D minimum;

public:
    Vector3D velocity = Vector3D(0, 0, 0);
    Vector3D position = Vector3D(0, 0, 0);

    BoundaryCube(Object3D* object);
    BoundaryCube(Vector3D centerPosition, Vector3D objectSize);

    Vector3D GetPosition();
    Vector3D GetSize();
    Vector3D GetMaximum();
    Vector3D GetMinimum();

    void Update(float dT, Vector3D acceleration, Quaternion rotation);
    Vector3D IsIntersecting(BoundaryCube* bO);
    Vector3D IsIntersecting(BoundarySphere* bO);
    void CollideSphere(float elasticity, BoundarySphere* bO);
};
