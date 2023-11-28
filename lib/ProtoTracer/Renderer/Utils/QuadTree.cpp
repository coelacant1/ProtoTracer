#include "QuadTree.h"

QuadTree::QuadTree(const Vector2D& min, const Vector2D& max) : root(min, max) {}

QuadTree::~QuadTree() {}

bool QuadTree::Insert(Triangle2D* triangle) {
    bool inserted = root.Insert(triangle);

    if (inserted) ++count;

    return inserted;
}

Node* QuadTree::Intersect(Node* node, const Vector2D& p){
    if (node->IsLeaf()) return node;

    for (uint8_t i = 0; i < 4; ++i) {
        if (node->GetChildNodes()[i].GetBBox()->Contains(p)) return Intersect(&node->GetChildNodes()[i], p);
    }

    return nullptr;
}

Node* QuadTree::Intersect(const Vector2D& p) {
    return Intersect(&root, p);
}

void QuadTree::Rebuild() {
    root.Subdivide();
}
