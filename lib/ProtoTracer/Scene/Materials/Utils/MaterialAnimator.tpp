#pragma once

template<size_t materialCount>
MaterialAnimator<materialCount>::MaterialAnimator() {}

template<size_t materialCount>
void MaterialAnimator<materialCount>::SetBaseMaterial(Material::Method method, Material* material) {
    if (baseMaterialSet) {
        combineMaterial.SetMaterial(0, material);
        combineMaterial.SetMethod(0, method);
        combineMaterial.SetOpacity(0, 1.0f);
    }
    else {
        baseMaterialSet = true;
        AddMaterial(method, material, 1, 1.0f, 1.0f);
    }
}

template<size_t materialCount>
void MaterialAnimator<materialCount>::AddMaterial(Material::Method method, Material* material, uint16_t frames, float minOpacity, float maxOpacity) {
    if (currentMaterials <= materialCount && baseMaterialSet) {
        bool addValue = true;
        for (uint16_t i = 1; i < currentMaterials; i++) {
            if (dictionary[i] == material) {
                addValue = false;
                break;
            }
        }

        if (addValue) {
            eEA.AddParameter(&materialRatios[currentMaterials], currentMaterials, frames, minOpacity, maxOpacity);
            combineMaterial.AddMaterial(method, material, minOpacity);
            dictionary[currentMaterials] = material;
            currentMaterials++;
        }
    }
}

template<size_t materialCount>
void MaterialAnimator<materialCount>::AddMaterialFrame(Material& material, float opacity) {
    for (uint8_t i = 0; i <= currentMaterials; i++) {
        if (dictionary[i] == &material) {
            eEA.AddParameterFrame(i, opacity);
            break;
        }
    }
}

template<size_t materialCount>
float MaterialAnimator<materialCount>::GetMaterialOpacity(Material& material) {
    for (uint8_t i = 0; i <= currentMaterials; i++) {
        if (dictionary[i] == &material) {
            return eEA.GetValue(i);
            break;
        }
    }

    return 0.0f;
}

template<size_t materialCount>
void MaterialAnimator<materialCount>::Update() {
    eEA.Update(); // update material opacities

    for (uint8_t i = 1; i <= currentMaterials; i++) { // link opacities
        combineMaterial.SetOpacity(i, materialRatios[i]);
    }
}

template<size_t materialCount>
RGBColor MaterialAnimator<materialCount>::GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) {
    return combineMaterial.GetRGB(position, normal, uvw);
};