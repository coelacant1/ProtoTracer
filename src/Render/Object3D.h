#pragma once

#include "..\Materials\Material.h"
#include "..\Math\Transform.h"
#include "TriangleGroup.h"

class Object3D {
private:
    Transform transform;
    TriangleGroup* originalTriangles;
    TriangleGroup* modifiedTriangles;
    Material* material;
    bool enabled = true;

public:
    Object3D(TriangleGroup* originalTriangles, Material* material){
        this->originalTriangles = originalTriangles;
        this->material = material;

        modifiedTriangles = new TriangleGroup(originalTriangles);
    }

    Object3D(Object3D** objects, int objectCount){
        TriangleGroup** triangleGroups = new TriangleGroup*[objectCount];

        for (int i = 0; i < objectCount; i++){
            triangleGroups[i] = objects[i]->GetTriangleGroup();
        }

        modifiedTriangles = new TriangleGroup(triangleGroups, objectCount);

        delete[] triangleGroups;
    }

    ~Object3D(){
        delete modifiedTriangles;
    }

    void Enable(){
        enabled = true;
    }

    void Disable(){
        enabled = false;
    }

    bool IsEnabled(){
        return enabled;
    }

    Vector3D GetCenterOffset(){
        Vector3D center;
        
        for(int i = 0; i < modifiedTriangles->GetVertexCount(); i++) center = center + modifiedTriangles->GetVertices()[i];

        return center.Divide(modifiedTriangles->GetVertexCount());;
    }

    void GetMinMaxDimensions(Vector3D &minimum, Vector3D &maximum){
        for(int i = 0; i < modifiedTriangles->GetVertexCount(); i++){
            minimum = Vector3D::Min(minimum, modifiedTriangles->GetVertices()[i]);
            maximum = Vector3D::Max(maximum, modifiedTriangles->GetVertices()[i]);
        }
    }

    Vector3D GetSize(){
        Vector3D min, max;

        GetMinMaxDimensions(min, max);

        return max - min;
    }

    Transform* GetTransform(){
        return &transform;
    }

    void ResetVertices(){
        for (int i = 0; i < modifiedTriangles->GetVertexCount(); i++) {
            modifiedTriangles->GetVertices()[i] = originalTriangles->GetVertices()[i];
        }
    }

    void UpdateTransform(){
        for (int i = 0; i < modifiedTriangles->GetVertexCount(); i++) {
            Vector3D modifiedVector = modifiedTriangles->GetVertices()[i];
            
            modifiedVector = (modifiedVector - transform.GetScaleOffset()) * transform.GetScale() + transform.GetScaleOffset();//offset position, scale, reset position
            modifiedVector = transform.GetRotation().RotateVector(modifiedVector - transform.GetRotationOffset()) + transform.GetRotationOffset();//offset position, rotate, reset position
            modifiedVector = modifiedVector + transform.GetPosition();//offset posiition

            modifiedTriangles->GetVertices()[i] = modifiedVector;
        }
    }

    TriangleGroup* GetTriangleGroup(){
        return modifiedTriangles;
    }

    Material* GetMaterial(){
        return material;
    }

    void SetMaterial(Material* material){
        this->material = material;
    }

};
