#pragma once

#include "BoundingBox2D.h"
#include "Triangle2D.h"

class Node {
private:
    static const int maxEntities = 16; //The maximum number of entities in a leaf node before subdividing
    static constexpr float maxSubdivRatio = 0.5f;
    static const int maxDepth = 8;
    uint16_t count = 0;
    uint16_t capacity = 0;
    Node* childNodes = NULL;
    Triangle2D** entities = NULL;

public:
    Node() {};

    ~Node() {
        if(entities)
            delete[] entities;

        if(childNodes)
            delete[] childNodes;
    }

    Node* GetChildNodes(){
        return childNodes;
    }

    Triangle2D** GetEntities(){
        return entities;
    }

    uint16_t GetCount(){
        return count;
    }

    void Expand(unsigned int newCount) {
        //printf("expanding node, new capacity: %d\n", newCount);
        Triangle2D** tmp = entities;
        entities = new Triangle2D*[newCount];
        for (unsigned int i = 0; i < newCount; ++i) {
            if (i < count)
                entities[i] = tmp[i];
            else
                entities[i] = NULL;
        }

        delete[] tmp;
        capacity = newCount;
    }

    //Note: node bboxes are implicit so we dont store them, therefore they need to be supplied externally whenever needed
    bool Insert(Triangle2D* triangle, BoundingBox2D& bbox, unsigned int depth = 0) {
        if (!triangle->DidIntersect(bbox)) {
            //printf("no intersection\n");
            return false;
        }
        /* printf("inserting at depth: %d\n", depth);
        printf("bbox: %.2f, %.2f, %.2f, %.2f\n", bbox.GetMinimum().X, bbox.GetMinimum().Y, bbox.GetMaximum().X, bbox.GetMaximum().Y);*/

        if (count == capacity)
            Expand(capacity? 2 * capacity : maxEntities);

        entities[count] = triangle;
        ++count;
        //printf("inserted, count: %d\n", count);

        return true;
    }

    void Subdivide(BoundingBox2D& bbox, unsigned int depth = 0) {
        //printf("subdividing node at depth %d\n", depth);
        if (depth == maxDepth)
            return;

        Vector2D mid = (bbox.GetMinimum() + bbox.GetMaximum()) * 0.5f;

        BoundingBox2D bboxes[] = { {bbox.GetMinimum(), mid}, {{mid.X, bbox.GetMinimum().Y}, {bbox.GetMaximum().X, mid.Y} },
                                    {{bbox.GetMinimum().X, mid.Y}, {mid.X, bbox.GetMaximum().Y}}, {mid, bbox.GetMaximum()} };

        childNodes = new Node[4];

        for (int j = 0; j < count; ++j) {
            int entityCount = 0;
            for (int i = 0; i < 4; ++i) {
                entityCount += childNodes[i].Insert(entities[j], bboxes[i], depth + 1);
            }
        }

        delete[] entities;
        entities = NULL;

        //edge case: stop subdividing if we cant improve the average entity counts (eg due to suboptimal mesh topology)
        float avgEntities = 0.0f;
        for (int i = 0; i < 4; ++i)
            avgEntities += 0.25f * (float)childNodes[i].count;

        bool canSubdiv = avgEntities < maxSubdivRatio * (float)count;

        //printf("avg entities: %.2f, count: %d\n", avgEntities, count);

        if (!canSubdiv) {
            /*printf("cant improve subdiv ratio, stopping subdiv\n");
            printf("avg entities: %.2f, count: %d\n", avgEntities, count);*/
            count = 0;
            return;
        }

        count = 0;

        for (int i = 0; i < 4; ++i) {
            if(childNodes[i].count > maxEntities)
                childNodes[i].Subdivide(bboxes[i], depth + 1);
        }
    }

    bool IsLeaf() {
        return !childNodes;
    }

    /*
    void PrintStats(int& totalCount, BoundingBox2D& bbox) {
        if (IsLeaf()) {
            //printf("count: %d\n", count);
            totalCount += count;
        }
        else {
            Vector2D mid = (bbox.GetMinimum() + bbox.GetMaximum()) * 0.5f;
            BoundingBox2D bboxes[] = { {bbox.GetMinimum(), mid}, {{mid.X, bbox.GetMinimum().Y}, {bbox.GetMaximum().X, mid.Y} },
                                {{bbox.GetMinimum().X, mid.Y}, {mid.X, bbox.GetMaximum().Y}}, {mid, bbox.GetMaximum()} };
            for (int i = 0; i < 4; ++i) {
                childNodes[i].PrintStats(totalCount, bboxes[i]);
            }
        }
    }
    */
};