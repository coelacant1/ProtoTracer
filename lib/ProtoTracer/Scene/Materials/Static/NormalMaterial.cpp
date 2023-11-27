#include "NormalMaterial.h"

NormalMaterial::NormalMaterial() {}

RGBColor NormalMaterial::GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) {
    Vector3D normalL = normal;

    normalL = normalL.UnitSphere();

    normalL = (normalL + 1.0f) * 0.5f * 255.0f;

    return RGBColor(normalL);
}
