#include "Morph.h"

Morph::Morph(int count, int* indexes, Vector3D* vertices) {
    this->count = count;
    this->indexes = indexes;
    this->vertices = vertices;
}

Morph::Morph(int count, const int* indexes, const Vector3D* vertices) {
    this->count = count;
    this->indexes = indexes;
    this->vertices = vertices;
}

void Morph::PrintMorphVertices() {
    for (int i = 0; i < count; i++) {
        Serial.print(vertices[i].ToString());
        Serial.print("\t");
    }
}

void Morph::MorphObject3D(ITriangleGroup* obj) {
    for (int i = 0; i < count; i++) {
        obj->GetVertices()[indexes[i]] = obj->GetVertices()[indexes[i]] + vertices[i] * Weight; // Add value of morph vertex to original vertex
    }
}
