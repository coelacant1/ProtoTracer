#pragma once
#include "..\Math\Vector3D.h"
#include "..\Math\Mathematics.h"
#include "..\Render\Object3D.h"

class Morph{
private:
    int count = 0;

    int* indexes;
    Vector3D* vertices;

public:
    float Weight = 0.0f;

    Morph(int count, int* indexes, Vector3D* vertices){
        this->count = count;
        this->indexes = indexes;
        this->vertices = vertices;
    }

    void MorphObject3D(Object3D* obj){
        for (int i = 0; i < count; i++){
            if (indexes[i] < obj->GetTriangleAmount()){// make sure the index is within the bounds of available triangles
                obj->GetVertices()[indexes[i]] = obj->GetVertices()[indexes[i]] + vertices[i] * Mathematics::Constrain(Weight, 0.0f, 1.0f);//add value of morph vertex to original vertex
            }
        }
    }
};
