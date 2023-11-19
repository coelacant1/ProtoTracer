#pragma once

#include "Node.h"

class QuadTree {
private:
    static const int maxEntities = 16; //The maximum number of entities in a leaf node before subdividing
    Triangle2D* entities = NULL;
    BoundingBox2D bbox;
    Node root;
    int count = 0;
    int capacity = 0;

public:
    QuadTree(const BoundingBox2D& bounds): bbox(bounds){}

    ~QuadTree() {
        free(entities);
    }

    bool Insert(Triangle2D* triangle){
        bool inserted = root.Insert(triangle, bbox);
        if (inserted)
            ++count;
        return inserted;
    }

    void Expand(int newCapacity) {
        entities = (Triangle2D*)realloc(entities, newCapacity * sizeof(Triangle2D));
        capacity = newCapacity;
    }

    bool Insert(Triangle2D triangle) {
        if (count == capacity)
            Expand(capacity ? (1.5f * capacity) : maxEntities);

        entities[count] = triangle;

        bool inserted = root.Insert(&entities[count], bbox);

        if (inserted)
            ++count;

        return inserted;
    }

    Node* Intersect(const Vector2D& p) {
        Node* currentNode = &root;
        BoundingBox2D currentBbox = bbox;
        while (true) {
            if (currentNode->IsLeaf())
                return currentNode;

            Vector2D mid = {(currentBbox.GetMinimum().X + currentBbox.GetMaximum().X) * 0.5f, (currentBbox.GetMinimum().Y + currentBbox.GetMaximum().Y) * 0.5f};

            BoundingBox2D bboxes[] = { {currentBbox.GetMinimum(), mid}, {{mid.X, currentBbox.GetMinimum().Y}, {currentBbox.GetMaximum().X, mid.Y} },
                                       {{currentBbox.GetMinimum().X, mid.Y}, {mid.X, currentBbox.GetMaximum().Y}}, {mid, currentBbox.GetMaximum()} };

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
                return NULL;
        }
    }

    void Rebuild() {
        for (int i = 0; i < count; ++i)
            root.GetEntities()[i] = &entities[i];

        root.Subdivide(bbox);
    }

    /*
    void PrintStats() {
        int totalCount = 0;
        printf("total inserts: %d\n", count);
        printf("node stats: \n");
        root.PrintStats(totalCount, bbox);
        printf("total entities: %d \n", totalCount);
    }
    */

};
