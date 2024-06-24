#pragma once

#include "../../Utils/Math/Quaternion.h"
#include "../../Utils/Math/Vector3D.h"

class Triangle3D {
public:
    Vector3D* p1;
    Vector3D* p2;
    Vector3D* p3;

    const Vector2D* p1UV;
    const Vector2D* p2UV;
    const Vector2D* p3UV;

    Vector3D edge1;
    Vector3D edge2;
    Vector3D normal;

    bool hasUV = false;

    Triangle3D();
    Triangle3D(Vector3D* p1, Vector3D* p2, Vector3D* p3);

    Vector3D* Normal();
    bool DidIntersect(Vector3D ray, Vector3D direction, Vector3D* intersect, Vector3D* color);
    String ToString();
};
