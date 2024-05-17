#pragma once

#include "../Material.h"
#include "../../../Utils/Math/Vector2D.h"
#include "GradientMaterial.h"

class NormalMaterial : public Material {
public:
    NormalMaterial();

    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
