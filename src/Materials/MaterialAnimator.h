#pragma once

#include "..\Animation\EasyEaseAnimator.h"
#include "CombineMaterial.h"
#include "Material.h"

template<size_t materialCount>
class MaterialAnimator : public Material{
private:
    EasyEaseAnimator<materialCount> eEA = EasyEaseAnimator<materialCount>(EasyEaseInterpolation::Cosine);
    CombineMaterial<materialCount> combineMaterial;
    float materialRatios[materialCount];
    Material* dictionary[materialCount];
    uint8_t currentMaterials = 0;
    bool baseMaterialSet = false;

public:
    MaterialAnimator(){}

    void SetBaseMaterial(Material::Method method, Material* material){
        if (baseMaterialSet){
            combineMaterial.SetMaterial(0, material);
            combineMaterial.SetMethod(0, method);
            combineMaterial.SetOpacity(0, 1.0f);
        }
        else{
            baseMaterialSet = true;
            AddMaterial(method, material, 1, 1.0f, 1.0f);
        }
    }
    
    void AddMaterial(Material::Method method, Material* material, uint16_t frames, float minOpacity, float maxOpacity){
        if(currentMaterials <= materialCount && baseMaterialSet){
            bool addValue = true;
            for(uint16_t i = 1; i < currentMaterials; i++){
                if(dictionary[i] == material){
                    addValue = false;
                    break;
                }
            }

            if(addValue){
                eEA.AddParameter(&materialRatios[currentMaterials], currentMaterials, frames, minOpacity, maxOpacity);
                combineMaterial.AddMaterial(method, material, minOpacity);
                dictionary[currentMaterials] = material;
                currentMaterials++;
            }
        }
    }

    void AddMaterialFrame(Material &material, float opacity){
        for(uint8_t i = 0; i <= currentMaterials; i++){
            if(dictionary[i] == &material){
                eEA.AddParameterFrame(i, opacity);
                break;
            }
        }
    }

    float GetMaterialOpacity(Material &material){
        for(uint8_t i = 0; i <= currentMaterials; i++){
            if(dictionary[i] == &material){
                return eEA.GetValue(i);
                break;
            }
        }

        return 0.0f;
    }

    void Update(){
        eEA.Update();//update material opacities

        for(uint8_t i = 1; i <= currentMaterials; i++){//link opacities
            combineMaterial.SetOpacity(i, materialRatios[i]);
        }
    }
    
    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw){
        return combineMaterial.GetRGB(position, normal, uvw);
    };
};
