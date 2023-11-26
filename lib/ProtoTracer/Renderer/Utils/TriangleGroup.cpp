#include "TriangleGroup.h"

TriangleGroup::TriangleGroup(Vector3D* vertices, IndexGroup* indexGroup, int vertexCount, int triangleCount)
    : vertexCount(vertexCount), triangleCount(triangleCount) {
    this->vertices = vertices;
    this->indexGroup = indexGroup;

    triangles = new Triangle3D[triangleCount];

    for (int i = 0; i < triangleCount; i++) {
        triangles[i].p1 = &vertices[indexGroup[i].A];
        triangles[i].p2 = &vertices[indexGroup[i].B];
        triangles[i].p3 = &vertices[indexGroup[i].C];
    }
}

TriangleGroup::TriangleGroup(Vector3D* vertices, IndexGroup* indexGroup, IndexGroup* uvIndexGroup, Vector2D* uvVertices, int vertexCount, int triangleCount, int uvVertexCount)
    : vertexCount(vertexCount), triangleCount(triangleCount), uvVertexCount(uvVertexCount) {
    this->vertices = vertices;
    this->indexGroup = indexGroup;
    this->uvIndexGroup = uvIndexGroup;
    this->uvVertices = uvVertices;
    this->hasUV = true;

    triangles = new Triangle3D[triangleCount];

    for (int i = 0; i < triangleCount; i++) {
        triangles[i].p1 = &vertices[indexGroup[i].A];
        triangles[i].p2 = &vertices[indexGroup[i].B];
        triangles[i].p3 = &vertices[indexGroup[i].C];
        triangles[i].p1UV = &uvVertices[uvIndexGroup[i].A];
        triangles[i].p2UV = &uvVertices[uvIndexGroup[i].B];
        triangles[i].p3UV = &uvVertices[uvIndexGroup[i].C];

        triangles[i].hasUV = true;
    }
}

TriangleGroup::TriangleGroup(TriangleGroup* triangleGroup)
    : vertexCount(triangleGroup->GetVertexCount()), triangleCount(triangleGroup->GetTriangleCount()) {
    indexGroup = triangleGroup->GetIndexGroup();

    vertices = new Vector3D[vertexCount];

    triangles = new Triangle3D[triangleCount];

    if (triangleGroup->hasUV) {
        this->hasUV = triangleGroup->hasUV;

        uvVertices = triangleGroup->uvVertices;
        uvIndexGroup = triangleGroup->uvIndexGroup;
    }

    for (int i = 0; i < vertexCount; i++) {
        vertices[i] = Vector3D(triangleGroup->GetVertices()[i]);
    }

    for (int i = 0; i < triangleCount; i++) {
        triangles[i].p1 = &vertices[indexGroup[i].A];
        triangles[i].p2 = &vertices[indexGroup[i].B];
        triangles[i].p3 = &vertices[indexGroup[i].C];

        if (triangleGroup->hasUV) {
            triangles[i].p1UV = &uvVertices[uvIndexGroup[i].A];
            triangles[i].p2UV = &uvVertices[uvIndexGroup[i].B];
            triangles[i].p3UV = &uvVertices[uvIndexGroup[i].C];

            triangles[i].hasUV = true;
        }
    }
}

TriangleGroup::TriangleGroup(TriangleGroup** triangleGroups, const int triangleGroupCount) {
    vertexCount = 0;
    triangleCount = 0;

    for (int i = 0; i < triangleGroupCount; i++) {
        vertexCount += triangleGroups[i]->GetVertexCount();
        triangleCount += triangleGroups[i]->GetTriangleCount();
    }

    indexGroup = new IndexGroup[triangleCount];
    vertices = new Vector3D[vertexCount];
    triangles = new Triangle3D[triangleCount];

    int vCounter = 0, tCounter = 0, vOffset = 0;

    for (int i = 0; i < triangleGroupCount; i++) {
        for (int j = 0; j < triangleGroups[i]->GetVertexCount(); j++) {
            vertices[vCounter] = Vector3D(triangleGroups[i]->GetVertices()[j]);
            vCounter++;
        }

        for (int j = 0; j < triangleGroups[i]->GetTriangleCount(); j++) {
            triangles[tCounter] = Triangle3D();
            indexGroup[tCounter] = IndexGroup(triangleGroups[i]->GetIndexGroup()[j]).Add(IndexGroup(vOffset, vOffset, vOffset));

            triangles[tCounter].p1 = &vertices[indexGroup[tCounter].A];
            triangles[tCounter].p2 = &vertices[indexGroup[tCounter].B];
            triangles[tCounter].p3 = &vertices[indexGroup[tCounter].C];

            tCounter++;
        }

        vOffset = vOffset + triangleGroups[i]->GetVertexCount();
    }
}

TriangleGroup::~TriangleGroup() {
    delete[] vertices;
    delete[] triangles;
    delete[] indexGroup;
}

IndexGroup* TriangleGroup::GetIndexGroup() {
    return indexGroup;
}

int TriangleGroup::GetTriangleCount() {
    return triangleCount;
}

Vector3D* TriangleGroup::GetVertices() {
    return vertices;
}

int TriangleGroup::GetVertexCount() {
    return vertexCount;
}

Triangle3D* TriangleGroup::GetTriangles() {
    return triangles;
}

Vector2D* TriangleGroup::GetUVVertices() {
    return uvVertices;
}
