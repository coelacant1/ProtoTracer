#pragma once

#include "Node.h"

class QuadTree {
private:
    BoundingBox2D bbox;
    Node root;
    uint16_t count = 0;

    Node* Intersect(Node* node, const Vector2D& p);

public:
    QuadTree(const Vector2D& min, const Vector2D& max);
    ~QuadTree();

    bool Insert(Triangle2D* triangle);
    Node* Intersect(const Vector2D& p);
    void Rebuild();
    
};
