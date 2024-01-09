#pragma once

#include "Triangle3D.h"
#include "IndexGroup.h"
#include "IStaticTriangleGroup.h"

template<int vertexCount, int triangleCount>
class StaticTriangleGroup : public IStaticTriangleGroup {
private:
    Triangle3D triangles[triangleCount];
    Vector3D* vertices;
    const IndexGroup* indexGroup;
    const IndexGroup* uvIndexGroup;
    const Vector2D* uvVertices;
    const bool hasUVB;

public:
    StaticTriangleGroup(Vector3D* vertices, const IndexGroup* indexGroup);
    StaticTriangleGroup(Vector3D* vertices, const IndexGroup* indexGroup, const IndexGroup* uvIndexGroup, const Vector2D* uvVertices);

    const bool HasUV() override;
    const IndexGroup* GetIndexGroup() override;
    const int GetTriangleCount() override;
    Vector3D* GetVertices() override;
    const int GetVertexCount() override;
    Triangle3D* GetTriangles() override;
    const Vector2D* GetUVVertices() override;
    const IndexGroup* GetUVIndexGroup() override;
};

#include "StaticTriangleGroup.tpp"