#pragma once

#include "Node.h"

class QuadTree {
private:
    static const int maxEntities = 16;
    Triangle2D* entities = nullptr;
    BoundingBox2D bbox;
    Node root;
    int count = 0;
    int capacity = 0;

public:
    QuadTree(const BoundingBox2D& bounds);
    ~QuadTree();

    bool Insert(Triangle2D* triangle);
    void Expand(int newCapacity);
    bool Insert(const Triangle2D& triangle);
    Node* Intersect(const Vector2D& p);
    void Rebuild();
    void PrintStats();
};
