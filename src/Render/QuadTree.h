#pragma once
#include "BoundingBox2D.h"
#include "Triangle2D.h"


class QuadTree {
public:
    class Node {
    public:
        Node() {
            entities = new Triangle2D*[QuadTree::maxEntities]; //slightly inefficient since we always store the max number of pointers, could be optimized
            for (int i = 0; i < QuadTree::maxEntities; ++i)
                entities[i] = NULL;
        };
        ~Node() {
            if(entities)
                delete[] entities;

            for (Node* childNode : childNodes) {
                if (childNode)
                    delete childNode;
            }
        }

        void expand(unsigned int newCount) {
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
        bool insert(Triangle2D* triangle, BoundingBox2D& bbox, unsigned int depth = 0) {
            if (!triangle->DidIntersect(bbox)) {
                //printf("no intersection\n");
                return false;
            }
           /* printf("inserting at depth: %d\n", depth);
            printf("bbox: %.2f, %.2f, %.2f, %.2f\n", bbox.GetMinimum().X, bbox.GetMinimum().Y, bbox.GetMaximum().X, bbox.GetMaximum().Y);*/

            if (count == capacity)
                expand(2 * capacity);

            entities[count] = triangle;
            ++count;
            //printf("inserted, count: %d\n", count);

            return true;
        }

        void subdivide(BoundingBox2D& bbox, unsigned int depth = 0) {
            //printf("subdividing node at depth %d\n", depth);
            if (depth == QuadTree::maxDepth)
                return;

            Vector2D mid = (bbox.GetMinimum() + bbox.GetMaximum()) * 0.5f;

            BoundingBox2D bboxes[] = { {bbox.GetMinimum(), mid}, {{mid.X, bbox.GetMinimum().Y}, {bbox.GetMaximum().X, mid.Y} },
                                       {{bbox.GetMinimum().X, mid.Y}, {mid.X, bbox.GetMaximum().Y}}, {mid, bbox.GetMaximum()} };

            for (int i = 0; i < 4; ++i) {
                childNodes[i] = new Node();
                for (int j = 0; j < count; ++j) {
                    if (entities[j])
                        childNodes[i]->insert(entities[j], bboxes[i], depth + 1);
                }
            }

            delete[] entities;
            entities = NULL;

            //edge case: stop subdividing if we cant improve the average entity counts (eg due to suboptimal mesh topology)
            float avgEntities = 0.0f;
            for (int i = 0; i < 4; ++i)
                avgEntities += 0.25f * (float)childNodes[i]->count;

            bool canSubdiv = avgEntities < QuadTree::maxSubdivRatio * (float)count;

            //printf("avg entities: %.2f, count: %d\n", avgEntities, count);

            if (!canSubdiv) {
                /*printf("cant improve subdiv ratio, stopping subdiv\n");
                printf("avg entities: %.2f, count: %d\n", avgEntities, count);*/
                count = 0;
                return;
            }

            count = 0;

            for (int i = 0; i < 4; ++i) {
                if(childNodes[i]->count > QuadTree::maxEntities)
                    childNodes[i]->subdivide(bboxes[i], depth + 1);
            }
        }

        bool isLeaf() {
            for (Node* childNode : childNodes) {
                if (childNode)
                    return false;
            }

            return true;
        }

        void PrintStats(int& totalCount) {
            if (isLeaf()) {
                printf("count: %d\n", count);
                totalCount += count;
            }
            else {
                for (Node* childNode : childNodes)
                    childNode->PrintStats(totalCount);
            }
        }

        uint16_t count = 0;
        uint16_t capacity = QuadTree::maxEntities;
        Node* childNodes[4] = {NULL, NULL, NULL, NULL};
        Triangle2D** entities = NULL;
    };

public:
    QuadTree(const BoundingBox2D& bounds): bbox(bounds){
    }

    bool insert(Triangle2D* triangle){
        bool inserted = root.insert(triangle, bbox);
        if (inserted)
            ++count;
        return inserted;
    }

    Node* intersect(const Vector2D& p) {
        Node* currentNode = &root;
        BoundingBox2D currentBbox = bbox;
        while (1) {
            if (currentNode->isLeaf())
                return currentNode;

            Vector2D mid = (currentBbox.GetMinimum() + currentBbox.GetMaximum()) * 0.5f;

            BoundingBox2D bboxes[] = { {currentBbox.GetMinimum(), mid}, {{mid.X, currentBbox.GetMinimum().Y}, {currentBbox.GetMaximum().X, mid.Y} },
                                       {{currentBbox.GetMinimum().X, mid.Y}, {mid.X, currentBbox.GetMaximum().Y}}, {mid, currentBbox.GetMaximum()} };

            bool found = false;
            for (int i = 0; i < 4; ++i) {
                if (bboxes[i].Contains(p)) {
                    currentNode = currentNode->childNodes[i];
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
        root.subdivide(bbox);
    }

    void PrintStats() {
        int totalCount = 0;
        printf("total inserts: %d\n", count);
        printf("node stats: \n");
        root.PrintStats(totalCount);
        printf("total entities: %d \n", totalCount);
    }

private:
    int count = 0;
    Node root;
    BoundingBox2D bbox;
    static const int maxEntities = 16; //The maximum number of entities in a leaf node before subdividing
    static const int maxDepth = 8;
    static constexpr float maxSubdivRatio = 0.5f;
};
