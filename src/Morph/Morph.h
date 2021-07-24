#pragma once
#include "..\Math\Vector3D.h"
#include "..\Math\Mathematics.h"
#include "..\Render\Object3D.h"

class Morph{
private:
    int count = 0;

    int* indexes;
    Vector3D* vertices;

    float weight = 0.0f;

public:
    Morph(int count, int* indexes, Vector3D* vertices){
        this->count = count;
        this->indexes = indexes;
        this->vertices = vertices;
    }

    float GetWeight(){
        return weight;
    }

    void SetWeight(float weight){
        this->weight = Mathematics::Constrain(weight, 0.0f, 1.0f);
    }

    void MorphObject3D(Object3D* obj){
        for (int i = 0; i < count; i++){
            if (indexes[i] < obj->GetTriangleAmount()){// make sure the index is within the bounds of available triangles
                obj->GetVertices()[indexes[i]] = obj->GetVertices()[indexes[i]] + vertices[i] * weight;//add value of morph vertex to original vertex
            }
        }
    }
};
