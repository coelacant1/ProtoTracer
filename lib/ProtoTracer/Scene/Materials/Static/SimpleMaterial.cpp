#include "SimpleMaterial.h"

SimpleMaterial::SimpleMaterial(RGBColor rgb) {
    this->rgb = rgb;
    this->baseRGB = rgb;
}

void SimpleMaterial::HueShift(float hueDeg) {
    rgb = baseRGB.HueShift(hueDeg);
}

void SimpleMaterial::SetRGB(RGBColor rgb) {
    this->rgb = rgb;
    this->baseRGB = rgb;
}

RGBColor SimpleMaterial::GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) {
    return rgb;
}
