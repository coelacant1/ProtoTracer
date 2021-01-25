#pragma once

#include "OBJReader.h"
#include "Quaternion.h"
#include "Vector3D.h"

class Object3D {
private:
  Quaternion q = Quaternion(1, 0, 0, 0);
  Vector3D p = Vector3D(0, 0, 0);
  Vector3D s = Vector3D(1, 1, 1);
  Vector3D* verticesOriginal;
  Vector3D* vertices;
  Triangle3D* triangles;
  Vector3D* triangleVec;
  int vertexLength = 0;
  int triangleLength = 0;
  bool enabled = true;
  
public:
  Object3D(const int maxVertices, const int maxTriangles){
    vertices = new Vector3D[maxVertices];
    verticesOriginal = new Vector3D[maxVertices];
    triangles = new Triangle3D[maxTriangles];
    triangleVec = new Vector3D[maxTriangles];

    vertexLength = maxVertices;
    triangleLength = maxTriangles;
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
    vertices = new Vector3D[maxVertices]();
    verticesOriginal = new Vector3D[maxVertices];
    triangles = new Triangle3D[maxTriangles];
    triangleVec = new Vector3D[maxTriangles];
    
    OBJReader::GetTriangles(vertices, triangleVec, triangles, &vertexLength, &triangleLength, &dataset, flipX, flipY, maxVertices, maxTriangles);

    for(int i = 0; i < vertexLength; i++){
      verticesOriginal[i] = vertices[i];
    }
  }

  ~Object3D(){
    delete[] vertices;
    delete[] triangles;
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

  Quaternion GetRotation(){
    return Quaternion(q);
  }

  Vector3D GetPosition(){
    return Vector3D(p);
  }

  Triangle3D* GetTriangles(){
    return triangles;
  }

  Vector3D* GetVertices(){
    return vertices;
  }

  Vector3D* GetVerticesOriginal(){
    return verticesOriginal;
  }

  int GetTriangleAmount(){
    return triangleLength;
  }

  int GetVertexAmount(){
    return vertexLength;
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

    return center;
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

  void Move(Vector3D p){
    for (int i = 0; i < vertexLength; i++) {
      vertices[i] = vertices[i] + p;
    }

    this->p = p;
  }

};
