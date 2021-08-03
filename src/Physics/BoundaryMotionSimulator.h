#pragma once

#include "..\Render\Object3D.h"
#include "..\Math\Rotation.h"
#include "..\Math\Vector3D.h"

class BoundarySphere{
private:
  Object3D* object;
  Vector3D centerPosition;
  Quaternion previousRotation;
  float radius = 1.0f;
  
public:
  Vector3D velocity = Vector3D(0, 0, 0);
  Vector3D position = Vector3D(0, 0, 0);
  
  BoundarySphere(Object3D* object, float radius){
    this->object = object;
    this->position = object->GetTransform()->GetPosition();
    this->radius = radius;
  }
  
  BoundarySphere(Object3D* object, Vector3D position, float radius){
    this->object = object;
    this->position = position;
    this->radius = radius;
  }

  float GetRadius(){
    return radius;
  }

  Object3D* GetObject3D(){
    return object;
  }

  void Update(float dT, Vector3D acceleration, Quaternion rotation){
    Quaternion rotationChange = rotation.Multiply(previousRotation.MultiplicativeInverse());
    velocity = rotationChange.RotateVector(velocity) * 0.999f + acceleration * dT;//maintain momentum of existing velocity, apply local acceleration
    velocity = velocity.Constrain(-2500, 2500);
    position = position + velocity * dT;

    previousRotation = rotation;
  }
  
  bool IsIntersecting(BoundarySphere *bO){
    return radius + bO->GetRadius() > fabs((position - bO->position).Magnitude());
  }
  
  void Collide(float elasticity, BoundarySphere *bO){
    if(IsIntersecting(bO)){
      //collision
      Vector3D direction = (position - bO->position).Normal();
      Vector3D vDiff = velocity - bO->velocity;
      float fellingSpeed = vDiff.DotProduct(direction);

      if(fellingSpeed >= 0){
        return;
      }

      float mass1 = 1.0f;
      float mass2 = 1.0f;

      float speed1 = (2 * mass2 * fellingSpeed) / (mass1 + mass2);
      float speed2 = (fellingSpeed * (mass2 - mass1)) / (mass1 + mass2);

      bO->velocity = bO->velocity + direction * speed1;
      this->velocity = this->velocity + direction * (speed2 - fellingSpeed);
    }//else{//no collision}
  }
};

class BoundaryCube{
private:
  Quaternion previousRotation;
  Vector3D centerPosition;
  Vector3D maximum;
  Vector3D minimum;
  
public:
  Vector3D velocity = Vector3D(0, 0, 0);
  Vector3D position = Vector3D(0, 0, 0);
  
  BoundaryCube(Object3D* object){//calculates center position and object size
    this->centerPosition = object->GetTransform()->GetPosition() + object->GetCenterOffset();
    object->GetMinMaxDimensions(minimum, maximum);
  }
  
  BoundaryCube(Vector3D centerPosition, Vector3D objectSize){
    this->centerPosition = centerPosition;

    minimum = centerPosition - objectSize / 2.0f;
    maximum = centerPosition + objectSize / 2.0f;
  }

  Vector3D GetPosition(){
    return centerPosition;
  }
  
  Vector3D GetSize(){
    return maximum - minimum;
  }

  Vector3D GetMaximum(){
    return maximum;
  }

  Vector3D GetMinimum(){
    return minimum;
  }

  void Update(float dT, Vector3D acceleration, Quaternion rotation){
    Quaternion rotationChange = rotation.Multiply(previousRotation.MultiplicativeInverse());
    velocity = rotationChange.RotateVector(velocity) + acceleration * dT;//maintain momentum of existing velocity, apply local acceleration
    position = position + velocity * dT;

    previousRotation = rotation;
  }
  
  Vector3D IsIntersecting(BoundaryCube *bO){
    Vector3D collision;

    collision.X = maximum.X >= bO->GetMinimum().X ? 0 : 1;
    collision.X = bO->GetMaximum().X >= minimum.X ? 0 : -1;
    collision.Y = maximum.Y >= bO->GetMinimum().Y ? 0 : 1;
    collision.Y = bO->GetMaximum().Y >= minimum.Y ? 0 : -1;
    collision.Z = maximum.Z >= bO->GetMinimum().Z ? 0 : 1;
    collision.Z = bO->GetMaximum().Z >= minimum.Z ? 0 : -1;
    
    return collision;
  }
  
  Vector3D IsIntersecting(BoundarySphere *bO){
    Vector3D collision;
    Vector3D minimumExt, maximumExt;
    Vector3D sphereSize = Vector3D(bO->GetRadius(), bO->GetRadius(), bO->GetRadius());

    minimumExt = bO->position - sphereSize;
    maximumExt = bO->position + sphereSize;

    collision.X = minimum.X <= maximumExt.X && maximum.X >= minimumExt.X;
    collision.Y = minimum.Y <= maximumExt.Y && maximum.Y >= minimumExt.Y;
    collision.Z = minimum.Z <= maximumExt.Z && maximum.Z >= minimumExt.Z;

    return collision;
  }
  
  void CollideSphere(float elasticity, BoundarySphere *bO){
    //if sphere is not within the bounds of the prism, collide
    Vector3D collision = IsIntersecting(bO);
    Vector3D shiftCorrection;
    
    if(collision.X) shiftCorrection.X = bO->velocity.X * -0.01f;
    if(collision.Y) shiftCorrection.Y = bO->velocity.Y * -0.01f;
    if(collision.Z) shiftCorrection.Z = bO->velocity.Z * -0.01f;
    
    bO->velocity.X = collision.X == 1 ? bO->velocity.X : -bO->velocity.X * elasticity;
    bO->velocity.Y = collision.Y == 1 ? bO->velocity.Y : -bO->velocity.Y * elasticity;
    bO->velocity.Z = collision.Z == 1 ? bO->velocity.Z : -bO->velocity.Z * elasticity;

    bO->position.X = Mathematics::Constrain(bO->position.X, minimum.X - bO->GetRadius(), maximum.X + bO->GetRadius());
    bO->position.Y = Mathematics::Constrain(bO->position.Y, minimum.Y - bO->GetRadius(), maximum.Y + bO->GetRadius());
    bO->position.Z = Mathematics::Constrain(bO->position.Z, minimum.Z - bO->GetRadius(), maximum.Z + bO->GetRadius());

    
    bO->position = bO->position + shiftCorrection;
    
    //Serial.println(bO->velocity.ToString());
    //Serial.println(bO->position.ToString());
  }
};

class BoundaryMotionSimulator{
private:
  BoundaryCube* bC;
  BoundarySphere** bS;
  int sphereCount;
  float elasticity = 0.8f;
  
public:
  BoundaryMotionSimulator(Object3D** objects, int objectCount, BoundaryCube* bC, float radius, float elasticity){
    this->bC = bC;
    this->sphereCount = objectCount;
    this->elasticity = elasticity;

    bS = new BoundarySphere*[objectCount];
    
    for(int i = 0; i < objectCount; i++){
      bS[i] = new BoundarySphere(objects[i], radius);
    }
  }

  void Randomize(float range){//mm/s
    //randomize velocities
    for (int i = 0; i < sphereCount; i++){
      bS[i]->velocity.X = ((float)random(0, 999) / 1000.0f) * range - range / 2.0f;
      bS[i]->velocity.Y = ((float)random(0, 999) / 1000.0f) * range - range / 2.0f;
      bS[i]->velocity.Z = ((float)random(0, 999) / 1000.0f) * range - range / 2.0f;
    }
  }

  Vector3D RandomRatio(float range){
    Vector3D vRand;

    vRand.X = 1.0f + ((float)random(0, 999) / 1000.0f) * range;
    vRand.Y = 1.0f + ((float)random(0, 999) / 1000.0f) * range;
    vRand.Z = 1.0f + ((float)random(0, 999) / 1000.0f) * range;

    return vRand;
  }

  void Update(float dT, Vector3D acceleration, Quaternion rotation){
    
    for (int i = 0; i < sphereCount; i++){
      bS[i]->Update(dT, acceleration * RandomRatio(2.0f), rotation);
      
      //object to object collisions
      for (int j = i + 1; j < sphereCount; j++){//ignore determinant line, only one side
        bS[i]->Collide(elasticity, bS[j]);
      }
      
      //box collisions
      bC->CollideSphere(elasticity, bS[i]);

      bS[i]->velocity = bS[i]->velocity * RandomRatio(0.0005f);
      
      bS[i]->GetObject3D()->ResetVertices();
      bS[i]->GetObject3D()->GetTransform()->SetPosition(bS[i]->position);
      
      //Serial.println(bS[i]->position.ToString());
    }
  }
};
