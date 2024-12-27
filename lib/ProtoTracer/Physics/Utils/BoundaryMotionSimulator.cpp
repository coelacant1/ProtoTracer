#include "BoundaryMotionSimulator.h"

BoundaryMotionSimulator::BoundaryMotionSimulator(Object3D** objects, int objectCount, BoundaryCube* bC, float radius, float elasticity) {
    this->bC = bC;
    this->sphereCount = objectCount;
    this->elasticity = elasticity;

    bS = new BoundarySphere*[objectCount];
    for (int i = 0; i < objectCount; i++) {
        bS[i] = new BoundarySphere(objects[i], radius);
    }
}

void BoundaryMotionSimulator::Randomize(float range) {
    for (int i = 0; i < sphereCount; i++) {
        bS[i]->velocity.X = ((float)random(0, 999) / 1000.0f) * range - range / 2.0f;
        bS[i]->velocity.Y = ((float)random(0, 999) / 1000.0f) * range - range / 2.0f;
        bS[i]->velocity.Z = ((float)random(0, 999) / 1000.0f) * range - range / 2.0f;
    }
}

Vector3D BoundaryMotionSimulator::RandomRatio(float range) {
    Vector3D vRand;
    vRand.X = 1.0f + ((float)random(0, 999) / 1000.0f) * range;
    vRand.Y = 1.0f + ((float)random(0, 999) / 1000.0f) * range;
    vRand.Z = 1.0f + ((float)random(0, 999) / 1000.0f) * range;
    return vRand;
}

void BoundaryMotionSimulator::Update(float dT, Vector3D acceleration, Quaternion rotation) {
    for (int i = 0; i < sphereCount; i++) {
        bS[i]->Update(dT, acceleration * RandomRatio(2.0f), rotation);

        for (int j = i + 1; j < sphereCount; j++) {
            bS[i]->Collide(elasticity, bS[j]);
        }

        bC->CollideSphere(elasticity, bS[i]);
        bS[i]->velocity = bS[i]->velocity * RandomRatio(0.0005f);
        bS[i]->GetObject3D()->ResetVertices();
        bS[i]->GetObject3D()->GetTransform()->SetPosition(bS[i]->position);
    }
}
