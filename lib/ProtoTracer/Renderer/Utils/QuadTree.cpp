#include "QuadTree.h"

QuadTree::QuadTree(const BoundingBox2D& bounds) : bbox(bounds) {}

QuadTree::~QuadTree() {
    free(entities);
}

bool QuadTree::Insert(Triangle2D* triangle) {
    bool inserted = root.Insert(triangle, &bbox);
    if (inserted)
        ++count;
    return inserted;
}

void QuadTree::Expand(int newCapacity) {
    entities = (Triangle2D*)realloc(entities, newCapacity * sizeof(Triangle2D));
    capacity = newCapacity;
}

bool QuadTree::Insert(const Triangle2D& triangle) {
    if (count == capacity)
        Expand(capacity ? (1.5f * capacity) : maxEntities);

    entities[count] = triangle;

    bool inserted = root.Insert(&entities[count], &bbox);

    if (inserted)
        ++count;

    return inserted;
}

Node* QuadTree::Intersect(const Vector2D& p) {
    Node* currentNode = &root;
    BoundingBox2D currentBbox = bbox;

    while (true) {
        if (currentNode->IsLeaf())
            return currentNode;

        BoundingBox2D bboxes[] = {  
            BoundingBox2D(currentBbox.GetMinimum(), currentBbox.GetCenter()),
            BoundingBox2D(Vector2D(currentBbox.GetCenter().X, currentBbox.GetMinimum().Y), Vector2D(currentBbox.GetMaximum().X, currentBbox.GetCenter().Y)),
            BoundingBox2D(Vector2D(currentBbox.GetMinimum().X, currentBbox.GetCenter().Y), Vector2D(currentBbox.GetCenter().X, currentBbox.GetMaximum().Y)),
            BoundingBox2D(currentBbox.GetCenter(), currentBbox.GetMaximum())
        };

        bool found = false;

        for (int i = 0; i < 4; ++i) {
            if (bboxes[i].Contains(p)) {
                currentNode = &(currentNode->GetChildNodes()[i]);
                currentBbox = bboxes[i];
                found = true;
                break;
            }
        }

        if (!found)
            return nullptr;
    }
}

void QuadTree::Rebuild() {
    for (int i = 0; i < count; ++i)
        root.GetEntities()[i] = &entities[i];

    root.Subdivide(&bbox);
}

void QuadTree::PrintStats() {
    int totalCount = 0;
    //printf("total inserts: %d\n", count);
    //printf("node stats: \n");
    root.PrintStats(totalCount, &bbox);
    //printf("total entities: %d \n", totalCount);
}
