#pragma once

#include "Material.h"
#include "..\Math\Vector2D.h"
#include "GradientMaterial.h"

//Converts gif to RGB XY pixel matrix
class NormalMaterial : public Material {
public:
    NormalMaterial(){}
    
    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        normal = normal.UnitSphere();

        normal = (normal + 1.0f) * 0.5f * 255.0f;
        
        return RGBColor(normal);
    }
};
