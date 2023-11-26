#pragma once

#include "Triangle3D.h"
#include "IndexGroup.h"

class TriangleGroup {
private:
    Vector3D* vertices;
    Triangle3D* triangles;
    IndexGroup* indexGroup;
    IndexGroup* uvIndexGroup;
    Vector2D* uvVertices;
    int vertexCount;
    int triangleCount;
    int uvVertexCount;
    bool hasUV = false;

public:
    TriangleGroup(Vector3D* vertices, IndexGroup* indexGroup, int vertexCount, int triangleCount);
    TriangleGroup(Vector3D* vertices, IndexGroup* indexGroup, IndexGroup* uvIndexGroup, Vector2D* uvVertices, int vertexCount, int triangleCount, int uvVertexCount);
    TriangleGroup(TriangleGroup* triangleGroup);
    TriangleGroup(TriangleGroup** triangleGroups, const int triangleGroupCount);
    ~TriangleGroup();

    IndexGroup* GetIndexGroup();
    int GetTriangleCount();
    Vector3D* GetVertices();
    int GetVertexCount();
    Triangle3D* GetTriangles();
    Vector2D* GetUVVertices();
};
