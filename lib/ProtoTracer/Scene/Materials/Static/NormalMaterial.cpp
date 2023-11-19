#include "NormalMaterial.h"

NormalMaterial::NormalMaterial() {}

RGBColor NormalMaterial::GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) {
    normal = normal.UnitSphere();

    normal = (normal + 1.0f) * 0.5f * 255.0f;

    return RGBColor(normal);
}
