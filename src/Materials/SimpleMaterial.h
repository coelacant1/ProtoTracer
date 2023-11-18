#pragma once

#include "Material.h"
#include "..\Math\Vector2D.h"

class SimpleMaterial : public Material {
private:
    RGBColor rgb;
    RGBColor baseRGB;

public:
    SimpleMaterial(RGBColor rgb);

    void HueShift(float hueDeg);

    void SetRGB(RGBColor rgb);

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override;
};
