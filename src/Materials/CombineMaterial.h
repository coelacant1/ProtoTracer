#pragma once

#include "Material.h"
#include "..\Math\Vector2D.h"

template<size_t materialCount>
class CombineMaterial : public Material {
private:
    Method method[materialCount];
    Material* materials[materialCount];
    float opacity[materialCount];
    uint8_t materialsAdded = 0;
  
public:
    CombineMaterial(){}

    void AddMaterial(Method method, Material* material, float opacity){
        if (materialsAdded < materialCount){
            this->method[materialsAdded] = method;
            this->materials[materialsAdded] = material;
            this->opacity[materialsAdded] = opacity;
            
            materialsAdded++;
        }
    }

    void SetMethod(uint8_t index, Method method){
        if(index < materialsAdded){
            this->method[index] = method;
        }
    }

    void SetOpacity(uint8_t index, float opacity){
        if(index < materialsAdded){
            this->opacity[index] = opacity;
        }
    }

    void SetMaterial(uint8_t index, Material* material){
        if(index < materialsAdded){
            materials[index] = material;
        }
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        Vector3D rgb;
        Vector3D tempV;
        RGBColor temp;

        //Set base color
        temp = materials[0]->GetRGB(position, normal, uvw);
        rgb.X = temp.R;
        rgb.Y = temp.G;
        rgb.Z = temp.B;

        for(int i = 1; i < materialsAdded; i++){
            switch(method[i]){
                case Add:
                    //Add all colors to base color
                    temp = materials[i]->GetRGB(position, normal, uvw);
                    
                    rgb.X = (rgb.X + temp.R) * opacity[i] + rgb.X * (1.0f - opacity[i]);
                    rgb.Y = (rgb.Y + temp.G) * opacity[i] + rgb.Y * (1.0f - opacity[i]);
                    rgb.Z = (rgb.Z + temp.B) * opacity[i] + rgb.Z * (1.0f - opacity[i]);

                    break;
                case Subtract:                
                    //Subtract from base color
                    temp = materials[i]->GetRGB(position, normal, uvw);
                    
                    rgb.X = (rgb.X - temp.R) * opacity[i] + rgb.X * (1.0f - opacity[i]);
                    rgb.Y = (rgb.Y - temp.G) * opacity[i] + rgb.Y * (1.0f - opacity[i]);
                    rgb.Z = (rgb.Z - temp.B) * opacity[i] + rgb.Z * (1.0f - opacity[i]);

                    break;
                case Multiply:
                    //Subtract from base color
                    temp = materials[i]->GetRGB(position, normal, uvw);
                    
                    rgb.X = (rgb.X * temp.R) * opacity[i] + rgb.X * (1.0f - opacity[i]);
                    rgb.Y = (rgb.Y * temp.G) * opacity[i] + rgb.Y * (1.0f - opacity[i]);
                    rgb.Z = (rgb.Z * temp.B) * opacity[i] + rgb.Z * (1.0f - opacity[i]);

                    break;
                case Divide:
                    //Divide from base color
                    temp = materials[i]->GetRGB(position, normal, uvw);
                    
                    rgb.X = (rgb.X / temp.R) * opacity[i] + rgb.X * (1.0f - opacity[i]);
                    rgb.Y = (rgb.Y / temp.G) * opacity[i] + rgb.Y * (1.0f - opacity[i]);
                    rgb.Z = (rgb.Z / temp.B) * opacity[i] + rgb.Z * (1.0f - opacity[i]);

                    break;
                case Darken:
                    //Find minimum color in all cases
                    temp = materials[i]->GetRGB(position, normal, uvw);
                    tempV = Vector3D::Min(Vector3D(temp.R, temp.G, temp.B), rgb);
                    
                    rgb = Vector3D::LERP(rgb, tempV, opacity[i]);

                    break;
                case Lighten:
                    //Find maximum color in all cases
                    temp = materials[i]->GetRGB(position, normal, uvw);
                    tempV = Vector3D::Max(Vector3D(temp.R, temp.G, temp.B), rgb);
                    
                    rgb = Vector3D::LERP(rgb, tempV, opacity[i]);

                    break;
                case Screen:
                    // 1 - (1 - a)(1 - b)
                    temp = materials[i]->GetRGB(position, normal, uvw);

                    tempV.X = 255.0f - (255.0f - rgb.X) * (255.0f - temp.R);
                    tempV.Y = 255.0f - (255.0f - rgb.Y) * (255.0f - temp.G);
                    tempV.Z = 255.0f - (255.0f - rgb.Z) * (255.0f - temp.B);
                    
                    rgb = Vector3D::LERP(rgb, tempV, opacity[i]);

                    break;
                case Overlay:
                    // if a < 0.5, 2ab
                    // else 1 - 2(1 - a)(1 - b)
                    temp = materials[i]->GetRGB(position, normal, uvw);

                    if(rgb.X < 128) tempV.X = 2.0f * rgb.X * temp.R;
                    else tempV.X = 255.0f - 2.0f * (255.0f - rgb.X) * (255.0f - temp.R);

                    if(rgb.Y < 128) tempV.Y = 2.0f * rgb.Y * temp.G;
                    else tempV.Y = 255.0f - 2.0f * (255.0f - rgb.Y) * (255.0f - temp.G);

                    if(rgb.Z < 128) tempV.Z = 2.0f * rgb.Z * temp.B;
                    else tempV.Z = 255.0f - 2.0f * (255.0f - rgb.Z) * (255.0f - temp.B);

                    rgb = Vector3D::LERP(rgb, tempV, opacity[i]);

                    break;
                case SoftLight:
                    // (1 - 2b)a^2 + 2ba
                    temp = materials[i]->GetRGB(position, normal, uvw);

                    tempV.X = (255.0f - 2.0f * temp.R) * (rgb.X * rgb.X) + 2.0f * (temp.R * rgb.X);
                    tempV.Y = (255.0f - 2.0f * temp.G) * (rgb.Y * rgb.Y) + 2.0f * (temp.G * rgb.Y);
                    tempV.Z = (255.0f - 2.0f * temp.B) * (rgb.Z * rgb.Z) + 2.0f * (temp.B * rgb.Z);

                    rgb = Vector3D::LERP(rgb, tempV, opacity[i]);

                    break;
                case Replace:
                    temp = materials[i]->GetRGB(position, normal, uvw);

                    tempV.X = temp.R;
                    tempV.Y = temp.G;
                    tempV.Z = temp.B;

                    rgb = Vector3D::LERP(rgb, tempV, opacity[i]);

                    break;
                default:

                    break;
            }
        }

        return RGBColor(rgb.Constrain(0, 255));
    }
};
