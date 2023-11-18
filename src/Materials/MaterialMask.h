#pragma once

#include "Material.h"
#include "..\Shapes\Shape.h"

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

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override;
};
