#pragma once

#include "Triangle3D.h"
#include "IndexGroup.h"

class TriangleGroup{
private:
    Vector3D* vertices;
    Triangle3D* triangles;
    IndexGroup* indexGroup;
    int vertexCount;
    int triangleCount;

public:
    TriangleGroup(Vector3D* vertices, IndexGroup* indexGroup, int vertexCount, int triangleCount) : vertexCount(vertexCount), triangleCount(triangleCount){
        this->vertices = vertices;
        this->indexGroup = indexGroup;

        triangles = new Triangle3D[triangleCount];
        
        for (int i = 0; i < triangleCount; i++) {
            triangles[i].p1 = &vertices[indexGroup[i].A];
            triangles[i].p2 = &vertices[indexGroup[i].B];
            triangles[i].p3 = &vertices[indexGroup[i].C];
        }
    }

    TriangleGroup(TriangleGroup* triangleGroup) : vertexCount(triangleGroup->GetVertexCount()), triangleCount(triangleGroup->GetTriangleCount()){
        indexGroup = triangleGroup->GetIndexGroup();//use existing reference, will not change
        vertices = new Vector3D[vertexCount];//copy to new array
        triangles = new Triangle3D[triangleCount];//copy to new array

        for (int i = 0; i < vertexCount; i++){
            vertices[i] = Vector3D(triangleGroup->GetVertices()[i]);
        }

        for (int i = 0; i < triangleCount; i++) {
            triangles[i].p1 = &vertices[indexGroup[i].A];
            triangles[i].p2 = &vertices[indexGroup[i].B];
            triangles[i].p3 = &vertices[indexGroup[i].C];
        }
    }

    TriangleGroup(TriangleGroup** triangleGroups, const int triangleGroupCount){
        vertexCount = 0;
        triangleCount = 0;

        for (int i = 0; i < triangleGroupCount; i++){
            vertexCount += triangleGroups[i]->GetVertexCount();
            triangleCount += triangleGroups[i]->GetTriangleCount();
        }
        
        indexGroup = new IndexGroup[triangleCount];//use existing reference, will not change
        vertices = new Vector3D[vertexCount];//copy to new array
        triangles = new Triangle3D[triangleCount];//copy to new array

        int vCounter = 0, tCounter = 0, vOffset = 0;
        
        for(int i = 0; i < triangleGroupCount; i++){
            for(int j = 0; j < triangleGroups[i]->GetVertexCount(); j++){
                vertices[vCounter] = Vector3D(triangleGroups[i]->GetVertices()[j]);
                vCounter++;
            }

            for(int j = 0; j < triangleGroups[i]->GetTriangleCount(); j++){
                triangles[tCounter] = Triangle3D();
                indexGroup[tCounter] = IndexGroup(triangleGroups[i]->GetIndexGroup()[j]).Add(IndexGroup(vOffset, vOffset, vOffset));
                tCounter++;
            }
            
            vOffset = vOffset + triangleGroups[i]->GetVertexCount();
        }
    }

    ~TriangleGroup(){
        delete[] vertices;
        delete[] triangles;
    }

    IndexGroup* GetIndexGroup(){
        return indexGroup;
    }

    int GetTriangleCount(){
        return triangleCount;
    }

    Vector3D* GetVertices(){
        return vertices;
    }

    int GetVertexCount(){
        return vertexCount;
    }

    Triangle3D* GetTriangles(){
        return triangles;
    }

};
