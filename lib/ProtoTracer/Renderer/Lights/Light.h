#pragma once

#include "..\..\Utils\Math\Vector3D.h"

class Light {
public:
    Light();
    Light(Vector3D p, Vector3D intensity, float falloff, float a, float b);

    void Set(Vector3D p, Vector3D intensity, float falloff, float a, float b);
    void SetIntensity(Vector3D intensity);
    void SetFalloff(float falloff, float a, float b);
    void MoveTo(Vector3D p);
    void Translate(Vector3D p);
    void SetFalloff(float falloff);
    void SetCurve(float a, float b);

    Vector3D GetPosition();
    float GetFalloff();
    float GetCurveA();
    float GetCurveB();
    Vector3D GetIntensity();

private:
    Vector3D p;
    Vector3D intensity;
    float falloff;
    float a;
    float b;
};
