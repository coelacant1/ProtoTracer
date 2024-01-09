#include "Object3D.h"

Object3D::Object3D(IStaticTriangleGroup* originalTriangles, ITriangleGroup* modifiedTriangles, Material* material) : originalTriangles(originalTriangles), modifiedTriangles(modifiedTriangles) {
    this->material = material;
}

Object3D::~Object3D() {}

void Object3D::Enable() {
    enabled = true;
}

void Object3D::Disable() {
    enabled = false;
}

bool Object3D::IsEnabled() {
    return enabled;
}

Vector3D Object3D::GetCenterOffset() {
    Vector3D center;

    for (int i = 0; i < modifiedTriangles->GetVertexCount(); i++) {
        center = center + modifiedTriangles->GetVertices()[i];
    }

    return center.Divide(modifiedTriangles->GetVertexCount());
}

void Object3D::GetMinMaxDimensions(Vector3D& minimum, Vector3D& maximum) {
    for (int i = 0; i < modifiedTriangles->GetVertexCount(); i++) {
        minimum = Vector3D::Min(minimum, modifiedTriangles->GetVertices()[i]);
        maximum = Vector3D::Max(maximum, modifiedTriangles->GetVertices()[i]);
    }
}

Vector3D Object3D::GetSize() {
    Vector3D min, max;

    GetMinMaxDimensions(min, max);

    return max - min;
}

Transform* Object3D::GetTransform() {
    return &transform;
}

void Object3D::SetTransform(Transform& t) {
    transform = t;
}

void Object3D::ResetVertices() {
    for (int i = 0; i < modifiedTriangles->GetVertexCount(); i++) {
        modifiedTriangles->GetVertices()[i] = originalTriangles->GetVertices()[i];
    }
}

void Object3D::UpdateTransform() {
    for (int i = 0; i < modifiedTriangles->GetVertexCount(); i++) {
        Vector3D modifiedVector = modifiedTriangles->GetVertices()[i];

        modifiedVector = (modifiedVector - transform.GetScaleOffset()) * transform.GetScale() + transform.GetScaleOffset();
        modifiedVector = transform.GetRotation().RotateVector(modifiedVector - transform.GetRotationOffset()) + transform.GetRotationOffset();
        modifiedVector = modifiedVector + transform.GetPosition();

        modifiedTriangles->GetVertices()[i] = modifiedVector;
    }
}

ITriangleGroup* Object3D::GetTriangleGroup() {
    return modifiedTriangles;
}

Material* Object3D::GetMaterial() {
    return material;
}

void Object3D::SetMaterial(Material* material) {
    this->material = material;
}
