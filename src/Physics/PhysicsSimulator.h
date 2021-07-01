#pragma once

#include "BoundaryMotionSimulator.h"
#include "..\Flash\MiscObjs.h"
#include "..\Render\Object3D.h"
#include "..\Math\Quaternion.h"
#include "..\Render\Scene.h"

class PhysicsSimulator{
private:
  BoundaryCube bC = BoundaryCube(Vector3D(0, 0, 0), Vector3D(300, 200, 100));
  BoundaryMotionSimulator* bMS;
  Scene* scene;
  Light lights[6];
  Object3D* objects[12];
  Object3D icosaSphere1Obj = Object3D(icosaSphereString, 25, 25);
  Object3D icosaSphere2Obj = Object3D(icosaSphereString, 25, 25);
  Object3D icosaSphere3Obj = Object3D(icosaSphereString, 25, 25);
  Object3D icosaSphere4Obj = Object3D(icosaSphereString, 25, 25);
  Object3D icosaSphere5Obj = Object3D(icosaSphereString, 25, 25);
  Object3D icosaSphere6Obj = Object3D(icosaSphereString, 25, 25);
  Object3D icosaSphere7Obj = Object3D(icosaSphereString, 25, 25);
  Object3D icosaSphere8Obj = Object3D(icosaSphereString, 25, 25);
  Object3D icosaSphere9Obj = Object3D(icosaSphereString, 25, 25);
  Object3D icosaSphere10Obj = Object3D(icosaSphereString, 25, 25);
  Object3D icosaSphere11Obj = Object3D(icosaSphereString, 25, 25);
  Object3D icosaSphere12Obj = Object3D(icosaSphereString, 25, 25);
  long previousTime;
  bool startedSim = false;
  
public:
  PhysicsSimulator(){
    lights[0].Set(Vector3D(1000, 0, 0), Vector3D(255, 0, 0), 1000.0f, 0.75f, 0.25f);//Set lights position, color intensity, falloff distance, and falloff curvature
    lights[1].Set(Vector3D(0, 1000, 0), Vector3D(0, 255, 0), 1000.0f, 0.75f, 0.25f);
    lights[2].Set(Vector3D(0, 0, 1000), Vector3D(0, 0, 255), 1000.0f, 0.75f, 0.25f);
    lights[3].Set(Vector3D(-2000, 0, 0), Vector3D(120, 0, 120), 1000.0f, 0.75f, 0.25f);
    lights[4].Set(Vector3D(0, -1000, 0), Vector3D(120, 120, 0), 1000.0f, 0.75f, 0.25f);
    lights[5].Set(Vector3D(0, 0, -1000), Vector3D(0, 120, 120), 1000.0f, 0.75f, 0.25f);
    
    objects[0] = &icosaSphere1Obj;
    objects[1] = &icosaSphere2Obj;
    objects[2] = &icosaSphere3Obj;
    objects[3] = &icosaSphere4Obj;
    objects[4] = &icosaSphere5Obj;
    objects[5] = &icosaSphere6Obj;
    objects[6] = &icosaSphere7Obj;
    objects[7] = &icosaSphere8Obj;
    objects[8] = &icosaSphere9Obj;
    objects[9] = &icosaSphere10Obj;
    objects[10] = &icosaSphere11Obj;
    objects[11] = &icosaSphere12Obj;
    
    icosaSphere1Obj.MoveRelative(Vector3D(-125, 150, 0));
    icosaSphere2Obj.MoveRelative(Vector3D(-75, 150, 0));
    icosaSphere3Obj.MoveRelative(Vector3D(-25, 150, 0));
    icosaSphere4Obj.MoveRelative(Vector3D(25, 150, 0));
    icosaSphere5Obj.MoveRelative(Vector3D(75, 150, 0));
    icosaSphere6Obj.MoveRelative(Vector3D(125, 150, 0));
    icosaSphere7Obj.MoveRelative(Vector3D(-125, 75, 0));
    icosaSphere8Obj.MoveRelative(Vector3D(-75, 75, 0));
    icosaSphere9Obj.MoveRelative(Vector3D(-25, 75, 0));
    icosaSphere10Obj.MoveRelative(Vector3D(25, 75, 0));
    icosaSphere11Obj.MoveRelative(Vector3D(75, 75, 0));
    icosaSphere12Obj.MoveRelative(Vector3D(125, 75, 0));
    
    scene = new Scene(objects, lights, 12, 6);
    bMS = new BoundaryMotionSimulator(objects, 12, &bC, 25.0f, 0.95f);

    bMS->Randomize(1500.0f);
  }
  
  Scene* GetScene(){
    return scene;
  }

  void Update(Vector3D acceleration, Quaternion rotation){
    if(!startedSim){
      previousTime = micros();
      startedSim = true;
    }
    
    long currentTime = micros();
    float dT = (float)(currentTime - previousTime) / 1000000.0f;

    //Vector3D accelNormalized = Vector3D(-acceleration.Y, acceleration.Z, -acceleration.X) * 200.0f;
    Vector3D accelNormalized = Vector3D(acceleration.X, acceleration.Z, acceleration.Y);

    bMS->Update(dT, accelNormalized, rotation);
    
    icosaSphere1Obj.MoveRelative(Vector3D(0, 150, 0));
    icosaSphere2Obj.MoveRelative(Vector3D(0, 150, 0));
    icosaSphere3Obj.MoveRelative(Vector3D(0, 150, 0));
    icosaSphere4Obj.MoveRelative(Vector3D(0, 150, 0));
    icosaSphere5Obj.MoveRelative(Vector3D(0, 150, 0));
    icosaSphere6Obj.MoveRelative(Vector3D(0, 150, 0));
    icosaSphere7Obj.MoveRelative(Vector3D(0, 150, 0));
    icosaSphere8Obj.MoveRelative(Vector3D(0, 150, 0));
    icosaSphere9Obj.MoveRelative(Vector3D(0, 150, 0));
    icosaSphere10Obj.MoveRelative(Vector3D(0, 150, 0));
    icosaSphere11Obj.MoveRelative(Vector3D(0, 150, 0));

    for (int i = 0; i < 12; i++){
      float positionZ = objects[i]->GetPosition().Z;
      float scaleRatio = Mathematics::Map(positionZ, -50, 50, 1.2f, 0.8f);
      
      objects[i]->ScaleCenter(Vector3D(scaleRatio, scaleRatio, scaleRatio));
    }

    previousTime = currentTime;

    //Serial.println(icosaSphere1Obj.GetPosition().ToString());
    //Serial.println(accelNormalized.ToString());
  }
  
};
