#pragma once

#include "Material.h"
#include "..\Shapes\Ellipse.h"

class MaterialMask : public Material{
private:
    Material* materialShape;
    Material* materialOuter;
    Shape* shape;
    float opacity = 1.0f;

public:
    MaterialMask(Material* materialShape, Material* materialOuter, Shape* shape){
        this->materialShape = materialShape;
        this->materialOuter = materialOuter;
        this->shape = shape;
    }

    void SetOpacity(float opacity){
        this->opacity = opacity;
    }

    float* GetOpacityReference(){
        return &opacity;
    }
    
    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        bool isInShape = shape->IsInShape(Vector2D(position.X, position.Y));

        if(opacity > 0.97f && isInShape){
            return materialShape->GetRGB(position, normal, uvw);
        }
        else if (isInShape){
            RGBColor shape = materialShape->GetRGB(position, normal, uvw);
            RGBColor outer = materialOuter->GetRGB(position, normal, uvw);

            return RGBColor::InterpolateColors(outer, shape, Mathematics::Constrain(opacity, 0.0f, 1.0f));
        }
        else{
            return materialOuter->GetRGB(position, normal, uvw);
        }
    }

};
