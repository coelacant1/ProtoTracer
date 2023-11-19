#pragma once

#include "..\..\..\Animation\EasyEaseAnimator.h"
#include "..\CombineMaterial.h"
#include "..\Material.h"

template<size_t materialCount>
class MaterialAnimator : public Material {
private:
    EasyEaseAnimator<materialCount> eEA = EasyEaseAnimator<materialCount>(EasyEaseInterpolation::Cosine);
    CombineMaterial<materialCount> combineMaterial;
    float materialRatios[materialCount];
    Material* dictionary[materialCount];
    uint8_t currentMaterials = 0;
    bool baseMaterialSet = false;

public:
    MaterialAnimator();

    void SetBaseMaterial(Material::Method method, Material* material);

    void AddMaterial(Material::Method method, Material* material, uint16_t frames, float minOpacity, float maxOpacity);

    void AddMaterialFrame(Material& material, float opacity);

    float GetMaterialOpacity(Material& material);

    void Update();

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override;
};

#include "MaterialAnimator.tpp"