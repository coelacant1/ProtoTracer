#pragma once

#include "../Material.h"
#include "../../../Renderer/Primitives/2D/Shape.h"

class MaterialMask : public Material {
private:
    Material* materialShape;
    Material* materialOuter;
    Shape* shape;
    float opacity = 1.0f;

public:
    MaterialMask(Material* materialShape, Material* materialOuter, Shape* shape);

    void SetOpacity(float opacity);

    float* GetOpacityReference();

    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
