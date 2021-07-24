#pragma once

#include "..\Materials\Material.h"
#include "OBJReader.h"
#include "..\Math\Quaternion.h"
#include "..\Math\Vector3D.h"

class Object3D {
private:
  Quaternion q = Quaternion(1, 0, 0, 0);
  Vector3D p = Vector3D(0, 0, 0);
  Vector3D s = Vector3D(1, 1, 1);
  Vector3D* verticesOriginal;
  Vector3D* vertices;
  Triangle3D* triangles;
  Vector3D* triangleVec;
  Material* material;
  int vertexLength = 0;
  int triangleLength = 0;
  bool enabled = true;
  bool invert = false;
  bool useMaterial = false;
  
public:
  Object3D(const int maxVertices, const int maxTriangles){
    vertices = new Vector3D[maxVertices];
    verticesOriginal = new Vector3D[maxVertices];
    triangles = new Triangle3D[maxTriangles];
    triangleVec = new Vector3D[maxTriangles];

    vertexLength = maxVertices;
    triangleLength = maxTriangles;
  }

  Object3D(const int maxVertices, const int maxTriangles, Vector3D* vertices, Vector3D* indexes){
    this->vertices = vertices;
    verticesOriginal = new Vector3D[maxVertices];
    triangles = new Triangle3D[maxTriangles];
    this->triangleVec = indexes;

    vertexLength = maxVertices;
    triangleLength = maxTriangles;

    for(int i = 0; i < vertexLength; i++){
      verticesOriginal[i] = vertices[i];
    }

    for (int i = 0; i < maxTriangles; i++) {
      triangles[i].p1 = &vertices[(int)indexes[i].X];
      triangles[i].p2 = &vertices[(int)indexes[i].Y];
      triangles[i].p3 = &vertices[(int)indexes[i].Z];
    }
  }

  Object3D(String dataset, const int maxVertices, const int maxTriangles){
    vertices = new Vector3D[maxVertices];
    verticesOriginal = new Vector3D[maxVertices];
    triangles = new Triangle3D[maxTriangles];
    triangleVec = new Vector3D[maxTriangles];

    OBJReader::GetTriangles(vertices, triangleVec, triangles, &vertexLength, &triangleLength, &dataset, false, false, maxVertices, maxTriangles);

    for(int i = 0; i < vertexLength; i++){
      verticesOriginal[i] = vertices[i];
    }
  }
  
  Object3D(String dataset, bool flipX, bool flipY, const int maxVertices, const int maxTriangles){
    vertices = new Vector3D[maxVertices];
    verticesOriginal = new Vector3D[maxVertices];
    triangles = new Triangle3D[maxTriangles];
    triangleVec = new Vector3D[maxTriangles];
    
    OBJReader::GetTriangles(vertices, triangleVec, triangles, &vertexLength, &triangleLength, &dataset, flipX, flipY, maxVertices, maxTriangles);

    for(int i = 0; i < vertexLength; i++){
      verticesOriginal[i] = vertices[i];
    }
  }

  void SetMaterial(Material* material){
    this->material = material;
    useMaterial = true;
  }

  void Copy(Object3D** objects, int objectCount){
    //copy existing to memory
    int vCounter = 0;
    int tCounter = 0;
    int vOffset = 0;

    for(int i = 0; i < objectCount; i++){
      for(int j = 0; j < objects[i]->GetVertexAmount(); j++){
        vertices[vCounter] = Vector3D(objects[i]->GetVertices()[j]);
        verticesOriginal[vCounter] = Vector3D(vertices[vCounter]);
        vCounter++;
      }

      for(int j = 0; j < objects[i]->GetTriangleAmount(); j++){
        triangles[tCounter] = Triangle3D();
        triangleVec[tCounter] = Vector3D(objects[i]->GetTriangleVector()[j]).Add(Vector3D(vOffset, vOffset, vOffset));
        tCounter++;
      }
      
      vOffset = vOffset + objects[i]->GetVertexAmount();
    }
    
    for (int i = 0; i < triangleLength; i++) {
      triangles[i].p1 = &vertices[(int)triangleVec[i].X];
      triangles[i].p2 = &vertices[(int)triangleVec[i].Y];
      triangles[i].p3 = &vertices[(int)triangleVec[i].Z];
    }
  }

  ~Object3D(){
    delete[] vertices;
    delete[] verticesOriginal;
    delete[] triangles;
    delete[] triangleVec;
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

  void Invert(){
    invert = true;
  }

  void Revert(){
    invert = false;
  }

  bool IsInverted(){
    return invert;
  }

  Quaternion GetRotation(){
    return Quaternion(q);
  }

  Vector3D GetPosition(){
    return Vector3D(p);
  }

  Triangle3D* GetTriangles(){
    return triangles;
  }
  
  Vector3D* GetTriangleVector(){
    return triangleVec;
  }

  Vector3D* GetVertices(){
    return vertices;
  }

  Vector3D* GetVerticesOriginal(){
    return verticesOriginal;
  }

  Material* GetMaterial(){
    return material;
  }

  int GetTriangleAmount(){
    return triangleLength;
  }

  int GetVertexAmount(){
    return vertexLength;
  }

  bool HasMaterial(){
    return useMaterial;
  }

  void ResetVertices(){
    for(int i = 0; i < vertexLength; i++){
      vertices[i] = verticesOriginal[i];
    }
  }
  
  Vector3D GetVertexCenter(){
    Vector3D center;
    
    for(int i = 0; i < vertexLength; i++){
      center = center + vertices[i];
    }

    center = center.Divide(vertexLength);

    p = center;

    return center;
  }

  void GetMinMaxDimensions(Vector3D &minimum, Vector3D &maximum){
    for(int i = 0; i < vertexLength; i++){
      minimum = Vector3D::Min(minimum, vertices[i]);
      maximum = Vector3D::Max(maximum, vertices[i]);
    }
  }
  
  void Rotate(Quaternion q) {
    this->q = Quaternion(q);

    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = this->q.RotateVector(vertices[i]);
    }
  }
  
  void Rotate(Vector3D eAXYZR, Vector3D p) {
    Quaternion q = Rotation(EulerAngles(eAXYZR, EulerConstants::EulerOrderXYZR)).GetQuaternion();
    
    this->q = Quaternion(q);
  
    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = this->q.RotateVector(vertices[i] - p) + p;
    }
  }
  
  void Rotate(Quaternion q, Vector3D p) {
    this->q = Quaternion(q);

    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = this->q.RotateVector(vertices[i] - p) + p;
    }
  }

  void RotateCenter(Quaternion q){
    Rotate(q, GetVertexCenter());
  }

  void RotateCenter(Vector3D v){
    Rotate(v, GetVertexCenter());
  }

  void Scale(Vector3D s){
    this->s = Vector3D(s);
    
    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = (vertices[i]) / this->s;
    }
  }
  
  void Scale(Vector3D s, Vector3D p) {
    this->s = Vector3D(s);
    
    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = (vertices[i] - p) * this->s + p;
    }
  }

  void ScaleCenter(Vector3D s){
    Scale(s, GetVertexCenter());
  }
  
  void Translate(Vector3D p) {
    this->p = this->p + p;
    
    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = vertices[i] + p;
    }
  }

  void MoveRelative(Vector3D p){
    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = vertices[i] + p;
    }

    this->p = this->p + p;
  }
  
  void MoveAbsolute(Vector3D p){
    Vector3D center = GetVertexCenter();

    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = vertices[i] + p - center;
    }
    
    this->p = p - center;
  }

};
