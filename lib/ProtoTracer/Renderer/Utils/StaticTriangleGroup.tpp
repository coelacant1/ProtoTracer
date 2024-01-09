#pragma once

template<int vertexCount, int triangleCount>
StaticTriangleGroup<vertexCount, triangleCount>::StaticTriangleGroup(Vector3D* vertices, const IndexGroup* indexGroup)
    : vertices(vertices), indexGroup(indexGroup), hasUVB(false) {

    for (int i = 0; i < triangleCount; i++) {
        triangles[i].p1 = &vertices[indexGroup[i].A];
        triangles[i].p2 = &vertices[indexGroup[i].B];
        triangles[i].p3 = &vertices[indexGroup[i].C];
    }
}

template<int vertexCount, int triangleCount>
StaticTriangleGroup<vertexCount, triangleCount>::StaticTriangleGroup(Vector3D* vertices, const IndexGroup* indexGroup, const IndexGroup* uvIndexGroup, const Vector2D* uvVertices)
    : vertices(vertices), indexGroup(indexGroup), uvIndexGroup(uvIndexGroup), uvVertices(uvVertices), hasUVB(true) {

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

template<int vertexCount, int triangleCount>
const bool StaticTriangleGroup<vertexCount, triangleCount>::HasUV(){
    return hasUVB;
}

template<int vertexCount, int triangleCount>
const IndexGroup* StaticTriangleGroup<vertexCount, triangleCount>::GetIndexGroup() {
    return indexGroup;
}

template<int vertexCount, int triangleCount>
const int StaticTriangleGroup<vertexCount, triangleCount>::GetTriangleCount() {
    return triangleCount;
}

template<int vertexCount, int triangleCount>
Vector3D* StaticTriangleGroup<vertexCount, triangleCount>::GetVertices() {
    return vertices;
}

template<int vertexCount, int triangleCount>
const int StaticTriangleGroup<vertexCount, triangleCount>::GetVertexCount() {
    return vertexCount;
}

template<int vertexCount, int triangleCount>
Triangle3D* StaticTriangleGroup<vertexCount, triangleCount>::GetTriangles() {
    return triangles;
}

template<int vertexCount, int triangleCount>
const Vector2D* StaticTriangleGroup<vertexCount, triangleCount>::GetUVVertices() {
    return uvVertices;
}

template<int vertexCount, int triangleCount>
const IndexGroup* StaticTriangleGroup<vertexCount, triangleCount>::GetUVIndexGroup() {
    return uvIndexGroup;
}
