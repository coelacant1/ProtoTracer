#pragma once

#include "..\Math\Mathematics.h"
#include "..\Render\TriangleGroup.h"

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

    void PrintMorphVertices(){
        for(int i = 0; i < count; i++){
            Serial.print(vertices[i].ToString());
            Serial.print("\t");
        }
    }

    void MorphObject3D(TriangleGroup* obj){
        for (int i = 0; i < count; i++){
            obj->GetVertices()[indexes[i]] = obj->GetVertices()[indexes[i]] + vertices[i] * Weight;//add value of morph vertex to original vertex
        }
    }
};
