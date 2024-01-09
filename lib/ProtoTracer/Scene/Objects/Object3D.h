#pragma once

#include "..\Materials\Material.h"
#include "..\..\Utils\Math\Transform.h"
#include "..\..\Renderer\Utils\TriangleGroup.h"
#include "..\..\Renderer\Utils\StaticTriangleGroup.h"

class Object3D {
private:
    Transform transform;
    IStaticTriangleGroup* originalTriangles;
    ITriangleGroup* modifiedTriangles;
    Material* material;
    bool enabled = true;

public:
    Object3D(IStaticTriangleGroup* originalTriangles, ITriangleGroup* modifiedTriangles, Material* material);
    ~Object3D();

    void Enable();
    void Disable();
    bool IsEnabled();
    Vector3D GetCenterOffset();
    void GetMinMaxDimensions(Vector3D& minimum, Vector3D& maximum);
    Vector3D GetSize();
    Transform* GetTransform();
    void SetTransform(Transform& t);
    void ResetVertices();
    void UpdateTransform();
    ITriangleGroup* GetTriangleGroup();
    Material* GetMaterial();
    void SetMaterial(Material* material);
};
