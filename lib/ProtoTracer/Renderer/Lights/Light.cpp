#include "Light.h"

Light::Light() {
    // Default constructor
}

Light::Light(Vector3D p, Vector3D intensity, float falloff, float a, float b)
    : p(p), intensity(intensity), falloff(falloff), a(a), b(b) {
}

void Light::Set(Vector3D p, Vector3D intensity, float falloff, float a, float b) {
    this->p = p;
    this->intensity = intensity;
    this->falloff = falloff;
    this->a = a;
    this->b = b;
}

void Light::SetIntensity(Vector3D intensity) {
    this->intensity = intensity;
}

void Light::SetFalloff(float falloff, float a, float b) {
    this->falloff = falloff;
    this->a = a;
    this->b = b;
}

void Light::MoveTo(Vector3D p) {
    this->p = p;
}

void Light::Translate(Vector3D p) {
    this->p = this->p + p;
}

void Light::SetFalloff(float falloff) {
    this->falloff = fabs(falloff);
}

void Light::SetCurve(float a, float b) {
    this->a = a;
    this->b = b;
}
