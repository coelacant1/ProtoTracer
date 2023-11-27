#include "RainbowSpiral.h"

void RainbowSpiral::Update(float ratio) {
    spiralMaterial.SetBend(fGenMatBend.Update());
    spiralMaterial.SetRotationAngle((1.0f - ratio) * 360.0f);
    spiralMaterial.SetPositionOffset(Vector2D(0.0f, 75.0f));
}

Material* RainbowSpiral::GetMaterial() {
    return &spiralMaterial;
}

RGBColor RainbowSpiral::GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) {
    return spiralMaterial.GetRGB(position, normal, uvw);
}
