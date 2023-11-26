#pragma once

#include "..\..\Utils\Math\Rotation.h"
#include "..\..\Utils\Math\Vector3D.h"
#include "..\..\Scene\Objects\Object3D.h"
#include "BoundaryCube.h"
#include "BoundarySphere.h"

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
