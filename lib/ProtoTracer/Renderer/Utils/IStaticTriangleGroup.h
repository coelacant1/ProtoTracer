#pragma once

#include "Triangle3D.h"
#include "IndexGroup.h"

class IStaticTriangleGroup {
public:
    virtual const bool HasUV() = 0;
    virtual const IndexGroup* GetIndexGroup() = 0;
    virtual const int GetTriangleCount() = 0;
    virtual const Vector3D* GetVertices() = 0;
    virtual const int GetVertexCount() = 0;
    virtual Triangle3D* GetTriangles() = 0;
    virtual const Vector2D* GetUVVertices() = 0;
    virtual const IndexGroup* GetUVIndexGroup() = 0;
};
