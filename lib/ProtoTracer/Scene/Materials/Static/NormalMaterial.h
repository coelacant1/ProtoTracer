#pragma once

#include "..\Material.h"
#include "..\..\..\Utils\Math\Vector2D.h"
#include "GradientMaterial.h"

class NormalMaterial : public Material {
public:
    NormalMaterial();

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override;
};
