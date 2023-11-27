#pragma once

#include "..\..\Physics\Utils\BoundingBox2D.h"
#include "Triangle2D.h"

class Node {
private:
    static const int maxEntities = 16;
    static constexpr float maxSubdivRatio = 0.5f;
    static const int maxDepth = 8;
    uint16_t count = 0;
    uint16_t capacity = 0;
    Node* childNodes = nullptr;
    Triangle2D** entities = nullptr;

public:
    Node();
    ~Node();

    Node* GetChildNodes();
    Triangle2D** GetEntities();
    uint16_t GetCount();
    void Expand(unsigned int newCount);
    bool Insert(Triangle2D* triangle, BoundingBox2D* bbox, unsigned int depth = 0);
    void Subdivide(BoundingBox2D* bbox, unsigned int depth = 0);
    bool IsLeaf();
    void PrintStats(int& totalCount, BoundingBox2D* bbox);
};
