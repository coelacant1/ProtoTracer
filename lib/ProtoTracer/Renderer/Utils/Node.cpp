#include "Node.h"

Node::Node() {}

Node::~Node() {
    if (entities)
        delete[] entities;

    if (childNodes)
        delete[] childNodes;
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

void Node::Expand(unsigned int newCount) {
    Triangle2D** tmp = entities;
    entities = new Triangle2D*[newCount];
    for (unsigned int i = 0; i < newCount; ++i) {
        if (i < count)
            entities[i] = tmp[i];
        else
            entities[i] = nullptr;
    }

    delete[] tmp;
    capacity = newCount;
}

bool Node::Insert(Triangle2D* triangle, BoundingBox2D* bbox, unsigned int depth) {
    if (!triangle->DidIntersect(bbox)) {
        return false;
    }

    if (count == capacity)
        Expand(capacity ? 2 * capacity : maxEntities);

    entities[count] = triangle;
    ++count;

    return true;
}

void Node::Subdivide(BoundingBox2D* bbox, unsigned int depth) {
    if (depth == maxDepth)
        return;

    BoundingBox2D bboxes[] = {  
        BoundingBox2D(bbox->GetMinimum(), bbox->GetCenter()),
        BoundingBox2D(Vector2D(bbox->GetCenter().X, bbox->GetMinimum().Y), Vector2D(bbox->GetMaximum().X, bbox->GetCenter().Y)),
        BoundingBox2D(Vector2D(bbox->GetMinimum().X, bbox->GetCenter().Y), Vector2D(bbox->GetCenter().X, bbox->GetMaximum().Y)),
        BoundingBox2D(bbox->GetCenter(), bbox->GetMaximum())
    };

    childNodes = new Node[4];

    for (int j = 0; j < count; ++j) {
        int entityCount = 0;
        for (int i = 0; i < 4; ++i) {
            entityCount += childNodes[i].Insert(entities[j], &bboxes[i], depth + 1);
        }
    }

    delete[] entities;
    entities = nullptr;

    float avgEntities = 0.0f;
    for (int i = 0; i < 4; ++i)
        avgEntities += 0.25f * static_cast<float>(childNodes[i].count);

    bool canSubdiv = avgEntities < maxSubdivRatio * static_cast<float>(count);

    if (!canSubdiv) {
        count = 0;
        return;
    }

    count = 0;

    for (int i = 0; i < 4; ++i) {
        if (childNodes[i].count > maxEntities)
            childNodes[i].Subdivide(&bboxes[i], depth + 1);
    }
}

bool Node::IsLeaf() {
    return !childNodes;
}

void Node::PrintStats(int& totalCount, BoundingBox2D* bbox) {
    if (IsLeaf()) {
        totalCount += count;
    }
    else {
        Vector2D mid = (bbox->GetMinimum() + bbox->GetMaximum()) * 0.5f;
        BoundingBox2D bboxes[] = { {bbox->GetMinimum(), mid}, {{mid.X, bbox->GetMinimum().Y}, {bbox->GetMaximum().X, mid.Y}},
            {{bbox->GetMinimum().X, mid.Y}, {mid.X, bbox->GetMaximum().Y}}, {mid, bbox->GetMaximum()} };
        for (int i = 0; i < 4; ++i) {
            childNodes[i].PrintStats(totalCount, &bboxes[i]);
        }
    }
}
