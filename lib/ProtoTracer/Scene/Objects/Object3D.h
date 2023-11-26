#pragma once

#include "..\Materials\Material.h"
#include "..\..\Utils\Math\Transform.h"
#include "..\..\Renderer\Utils\TriangleGroup.h"

class Object3D {
private:
    Transform transform;
    TriangleGroup* originalTriangles;
    TriangleGroup* modifiedTriangles;
    Material* material;
    bool enabled = true;

public:
    Object3D(TriangleGroup* originalTriangles, Material* material);
    Object3D(Object3D** objects, int objectCount);
    ~Object3D();

    void Enable();
    void Disable();
    bool IsEnabled();
    Vector3D GetCenterOffset();
    void GetMinMaxDimensions(Vector3D& minimum, Vector3D& maximum);
    Vector3D GetSize();
    Transform* GetTransform();
    void ResetVertices();
    void UpdateTransform();
    TriangleGroup* GetTriangleGroup();
    Material* GetMaterial();
    void SetMaterial(Material* material);
};
