#pragma once

#include "../Renderer/Lights/Light.h"
#include "Utils/BoundaryMotionSimulator.h"
#include "../Scene/Objects/Object3D.h"
#include "../Utils/Math/Quaternion.h"
#include "../Scene/Scene.h"

class PhysicsSimulator {
private:
    BoundaryCube bC;
    BoundaryMotionSimulator* bMS;
    Scene* scene;
    Light lights[6];
    Object3D* objects[12];
    
    long previousTime;
    bool startedSim;

public:
    PhysicsSimulator();

    Scene* GetScene();

    void Update(Vector3D acceleration, Quaternion rotation);
};
