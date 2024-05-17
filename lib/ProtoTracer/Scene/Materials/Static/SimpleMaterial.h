#pragma once

#include "../Material.h"
#include "../../../Utils/Math/Vector2D.h"

class SimpleMaterial : public Material {
private:
    RGBColor rgb;
    RGBColor baseRGB;

public:
    SimpleMaterial(RGBColor rgb);

    void HueShift(float hueDeg);

    void SetRGB(RGBColor rgb);

    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
