#pragma once

#include "..\..\Utils\Math\Vector3D.h"

class Light {
public:
	Vector3D p;
	Vector3D intensity;//R, G, B
    float falloff = 1000.0f;
    float a = 0.0f;
    float b = 1.0f;
  
	Light(){}

	Light(Vector3D p, Vector3D intensity, float falloff, float a, float b) : p(p), intensity(intensity), falloff(falloff), a(a), b(b) {}

	void Set(Vector3D p, Vector3D intensity, float falloff, float a, float b) {
		this->p = p;
		this->intensity = intensity;
        this->falloff = falloff;
        this->a = a;
        this->b = b;
	}

    void SetIntensity(Vector3D intensity) {
        this->intensity = intensity;
    }

    void SetFalloff(float falloff, float a, float b) {
        this->falloff = falloff;
        this->a = a;
        this->b = b;
    }

    void MoveTo(Vector3D p) {
        this->p = p;
    }

    void Translate(Vector3D p) {
        this->p = this->p + p;
    }

    void SetFalloff(float falloff){
        this->falloff = fabs(falloff);
    }

    void SetCurve(float a, float b){
        this->a = a;
        this->b = b;
    }
};
