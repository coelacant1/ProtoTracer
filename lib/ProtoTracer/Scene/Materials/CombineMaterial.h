#pragma once

#include "Material.h"
#include "..\..\Utils\Math\Vector2D.h"
#include "..\..\Utils\Math\Vector3D.h"

template<size_t materialCount>
class CombineMaterial : public Material {
private:
    Method method[materialCount];
    Material* materials[materialCount];
    float opacity[materialCount];
    uint8_t materialsAdded = 0;

public:
    CombineMaterial();

    void AddMaterial(Method method, Material* material, float opacity);
    void SetMethod(uint8_t index, Method method);
    void SetOpacity(uint8_t index, float opacity);
    void SetMaterial(uint8_t index, Material* material);

    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};

#include "CombineMaterial.tpp"

