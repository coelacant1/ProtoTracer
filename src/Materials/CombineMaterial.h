#pragma once

#include "Material.h"
#include "..\Math\Vector2D.h"

class CombineMaterial : public Material {
public:
    enum Method{
        Add,
        Subtract,
        Multiply,
        Divide,
        Darken,
        Lighten,
        Screen,
        Overlay,
        SoftLight,
        Replace
    };

private:
    uint8_t combineMethod;
    uint8_t materialCount;
    Material** materials;
    float opacity;
  
public:
    CombineMaterial(Method combineMethod, uint8_t materialCount, Material** materials){
        this->combineMethod = combineMethod;
        this->materialCount = materialCount;
        this->materials = materials;
        this->opacity = 0.0f;
    }

    void SetFirstLayerOpacity(float opacity){
        this->opacity = opacity;
    }

    void SetCombineMethod(uint8_t combineMethod){
        this->combineMethod = combineMethod;
    }

    void SetCombineMethod(Method combineMethod){
        this->combineMethod = combineMethod;
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        Vector3D rgb;
        Vector3D baseRgb;
        RGBColor temp;

        //Set base color
        temp = materials[0]->GetRGB(position, normal, uvw);
        rgb.X = temp.R;
        rgb.Y = temp.G;
        rgb.Z = temp.B;

        baseRgb = rgb;

        switch(combineMethod){
            case Add:
                //Add all colors to base color
                for(int i = 1; i < materialCount; i++){
                    temp = materials[i]->GetRGB(position, normal, uvw);
                    
                    rgb.X = rgb.X + temp.R;
                    rgb.Y = rgb.Y + temp.G;
                    rgb.Z = rgb.Z + temp.B;
                }

                break;
            case Subtract:                
                //Subtract from base color
                for(int i = 1; i < materialCount; i++){
                    temp = materials[i]->GetRGB(position, normal, uvw);
                    
                    rgb.X = rgb.X - temp.R;
                    rgb.Y = rgb.Y - temp.G;
                    rgb.Z = rgb.Z - temp.B;
                }

                break;
            case Multiply:
                //Subtract from base color
                for(int i = 1; i < materialCount; i++){
                    temp = materials[i]->GetRGB(position, normal, uvw);
                    
                    rgb.X = rgb.X * temp.R;
                    rgb.Y = rgb.Y * temp.G;
                    rgb.Z = rgb.Z * temp.B;
                }

                break;
            case Divide:
                //Divide from base color
                for(int i = 1; i < materialCount; i++){
                    temp = materials[i]->GetRGB(position, normal, uvw);
                    
                    rgb.X = rgb.X / temp.R;
                    rgb.Y = rgb.Y / temp.G;
                    rgb.Z = rgb.Z / temp.B;
                }

                break;
            case Darken:
                //Find minimum color in all cases
                for(int i = 1; i < materialCount; i++){
                    temp = materials[i]->GetRGB(position, normal, uvw);

                    rgb = Vector3D::Min(Vector3D(temp.R, temp.G, temp.B), rgb);
                }

                break;
            case Lighten:
                //Find maximum color in all cases
                for(int i = 1; i < materialCount; i++){
                    temp = materials[i]->GetRGB(position, normal, uvw);

                    rgb = Vector3D::Max(Vector3D(temp.R, temp.G, temp.B), rgb);
                }

                break;
            case Screen:
                // 1 - (1 - a)(1 - b)
                for(int i = 1; i < materialCount; i++){
                    temp = materials[i]->GetRGB(position, normal, uvw);

                    rgb.X = 255.0f - (255.0f - rgb.X) * (255.0f - temp.R);
                    rgb.Y = 255.0f - (255.0f - rgb.Y) * (255.0f - temp.G);
                    rgb.Z = 255.0f - (255.0f - rgb.Z) * (255.0f - temp.B);
                }

                break;
            case Overlay:
                // if a < 0.5, 2ab
                // else 1 - 2(1 - a)(1 - b)
                for(int i = 1; i < materialCount; i++){
                    temp = materials[i]->GetRGB(position, normal, uvw);

                    if(rgb.X < 128) rgb.X = 2.0f * rgb.X * temp.R;
                    else rgb.X = 255.0f - 2.0f * (255.0f - rgb.X) * (255.0f - temp.R);

                    if(rgb.Y < 128) rgb.Y = 2.0f * rgb.Y * temp.G;
                    else rgb.Y = 255.0f - 2.0f * (255.0f - rgb.Y) * (255.0f - temp.G);

                    if(rgb.Z < 128) rgb.Z = 2.0f * rgb.Z * temp.B;
                    else rgb.Z = 255.0f - 2.0f * (255.0f - rgb.Z) * (255.0f - temp.B);
                }

                break;
            case SoftLight:
                // (1 - 2b)a^2 + 2ba
                for(int i = 1; i < materialCount; i++){
                    temp = materials[i]->GetRGB(position, normal, uvw);

                    rgb.X = (255.0f - 2.0f * temp.R) * (rgb.X * rgb.X) + 2.0f * (temp.R * rgb.X);
                    rgb.Y = (255.0f - 2.0f * temp.G) * (rgb.Y * rgb.Y) + 2.0f * (temp.G * rgb.Y);
                    rgb.Z = (255.0f - 2.0f * temp.B) * (rgb.Z * rgb.Z) + 2.0f * (temp.B * rgb.Z);
                }

                break;
            case Replace:
                temp = materials[materialCount - 1]->GetRGB(position, normal, uvw);

                rgb.X = temp.R;
                rgb.Y = temp.G;
                rgb.Z = temp.B;

                break;
            default:

                break;
        }
        
        return RGBColor(Vector3D::LERP(rgb, baseRgb, opacity).Constrain(0, 255));
    }
};
