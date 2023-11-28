#include "Node.h"

Node::Node(const Vector2D& min, const Vector2D& max) : bbox(min, max) {}

Node::~Node() {
    if (entities) delete[] entities;

    if (childNodes) delete[] childNodes;
}


BoundingBox2D* Node::GetBBox(){
    return &bbox;
}

Node* Node::GetChildNodes() {
    return childNodes;
}

Triangle2D** Node::GetEntities() {
    return entities;
}

uint16_t Node::GetCount() {
    return count;
}

void Node::Expand(uint16_t newCount) {
    Triangle2D** tmp = entities;
    entities = new Triangle2D*[newCount];

    for (uint8_t i = 0; i < newCount; ++i) {
        if (i < count) entities[i] = tmp[i];
        else entities[i] = nullptr;
    }

    delete[] tmp;
    capacity = newCount;
}

bool Node::Insert(Triangle2D* triangle) {
    if (!triangle->DidIntersect(&bbox)) return false;

    if (count == capacity) Expand(capacity ? 2 * capacity : maxEntities);

    entities[count] = triangle;
    ++count;

    return true;
}

void Node::Subdivide(uint8_t depth) {
    if (depth == maxDepth) return;

    childNodes = new Node[4]{
        Node(bbox.GetMinimum(), bbox.GetCenter()),
        Node(Vector2D(bbox.GetCenter().X, bbox.GetMinimum().Y), Vector2D(bbox.GetMaximum().X, bbox.GetCenter().Y)),
        Node(Vector2D(bbox.GetMinimum().X, bbox.GetCenter().Y), Vector2D(bbox.GetCenter().X, bbox.GetMaximum().Y)),
        Node(bbox.GetCenter(), bbox.GetMaximum())
    };

    for (uint16_t i = 0; i < 4; ++i) {
        for (uint16_t j = 0; j < count; ++j) {
            childNodes[i].Insert(entities[j]);
        }

        if (childNodes[i].count > maxEntities) childNodes[i].Subdivide(depth + 1);
    }


    delete[] entities;
    entities = nullptr;
    count = 0;
}

bool Node::IsLeaf() {
    return !childNodes;
}
