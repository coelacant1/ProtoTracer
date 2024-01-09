#pragma once

#include "..\..\Scene\Materials\Material.h"
#include "..\..\Utils\Math\Transform.h"
#include "..\..\Utils\Math\Vector2D.h"
#include "..\..\Physics\Utils\BoundingBox2D.h"
#include "Triangle3D.h"

class Triangle2D {
public:
    float denominator = 0.0f;
    float p1X, p1Y, p2X, p2Y, p3X, p3Y, v0X, v0Y, v1X, v1Y, v2X, v2Y;
    Vector2D min, max;

    Vector3D* normal;
    Material* material;

    Vector3D* t3p1;
    Vector3D* t3p2;
    Vector3D* t3p3;

    const Vector2D* p1UV;
    const Vector2D* p2UV;
    const Vector2D* p3UV;

    bool hasUV = false;
    float averageDepth = 0.0f;

    Triangle2D();
    Triangle2D(const Vector2D& p1, const Vector2D& p2, const Vector2D& p3);
    Triangle2D(const Quaternion& lookDirection, Transform* camT, Triangle3D* t, Material* material);
    Triangle2D(Triangle3D* t);

    Vector2D GetP1();
    Vector2D GetP2();
    Vector2D GetP3();
    Material* GetMaterial();
    bool DidIntersect(const float& x, const float& y, float& u, float& v, float& w);
    bool DidIntersect(BoundingBox2D* bbox);
    bool DidIntersectSAT(BoundingBox2D* bbox);
    String ToString();
};
