#pragma once

#include "../../Physics/Utils/BoundingBox2D.h"
#include "Triangle2D.h"

class Node {
private:
    static const uint16_t maxEntities = 8;
    static const uint8_t maxDepth = 8;
    uint16_t count = 0;
    uint16_t capacity = 0;
    Node* childNodes = nullptr;
    Triangle2D** entities = nullptr;
    BoundingBox2D bbox;

    void CreateChildNodes();
    uint16_t DistributeEntities();
    bool ShouldSubdivide(uint16_t childEntitySum);

public:
    Node(const Vector2D& min, const Vector2D& max);
    ~Node();

    BoundingBox2D* GetBBox();
    Node* GetChildNodes();
    Triangle2D** GetEntities();
    uint16_t GetCount();
    void Expand(uint16_t newCount);
    bool Insert(Triangle2D* triangle);
    void Subdivide(uint8_t depth = 0);
    bool IsLeaf();
    
};
