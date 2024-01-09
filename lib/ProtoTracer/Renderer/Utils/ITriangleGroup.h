#pragma once

#include "Triangle3D.h"
#include "IndexGroup.h"
#include "IStaticTriangleGroup.h"

class ITriangleGroup {
public:
    virtual const IndexGroup* GetIndexGroup() = 0;
    virtual int GetTriangleCount() = 0;
    virtual Vector3D* GetVertices() = 0;
    virtual int GetVertexCount() = 0;
    virtual Triangle3D* GetTriangles() = 0;
    virtual const Vector2D* GetUVVertices() = 0;
    virtual const IndexGroup* GetUVIndexGroup() = 0;
};
