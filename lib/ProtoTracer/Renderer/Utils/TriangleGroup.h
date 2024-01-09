#pragma once

#include "Triangle3D.h"
#include "ITriangleGroup.h"
#include "IndexGroup.h"
#include "IStaticTriangleGroup.h"

template<int vertexCount, int triangleCount>
class TriangleGroup : public ITriangleGroup {
private:
    Triangle3D triangles[triangleCount];
    Vector3D vertices[vertexCount];
    const IndexGroup* indexGroup;
    const IndexGroup* uvIndexGroup;
    const Vector2D* uvVertices;
    bool hasUV = false;

public:
    TriangleGroup(IStaticTriangleGroup* triangleGroup);

    const IndexGroup* GetIndexGroup() override;
    int GetTriangleCount() override;
    Vector3D* GetVertices() override;
    int GetVertexCount() override;
    Triangle3D* GetTriangles() override;
    const Vector2D* GetUVVertices() override;
    const IndexGroup* GetUVIndexGroup() override;
};

#include "TriangleGroup.tpp"