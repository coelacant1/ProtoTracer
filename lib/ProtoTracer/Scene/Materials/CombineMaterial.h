#pragma once

#include "Material.h"
#include "..\..\Utils\Math\Vector2D.h"

template<size_t materialCount>
class CombineMaterial : public Material {
private:
    Method method[materialCount];
    Material* materials[materialCount];
    float opacity[materialCount];
    uint8_t materialsAdded = 0;

public:
    CombineMaterial() {}

    void AddMaterial(Method method, Material* material, float opacity) {
        if (materialsAdded < materialCount) {
            this->method[materialsAdded] = method;
            this->materials[materialsAdded] = material;
            this->opacity[materialsAdded] = opacity;

            materialsAdded++;
        }
    }

    void SetMethod(uint8_t index, Method method) {
        if (index < materialsAdded) {
            this->method[index] = method;
        }
    }

    void SetOpacity(uint8_t index, float opacity) {
        if (index < materialsAdded) {
            this->opacity[index] = opacity;
        }
    }

    void SetMaterial(uint8_t index, Material* material) {
        if (index < materialsAdded) {
            materials[index] = material;
        }
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override;
};

#include "CombineMaterial.tpp"