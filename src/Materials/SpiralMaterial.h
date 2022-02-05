#pragma once

#include "Material.h"
#include "..\Math\Mathematics.h"
#include "..\Math\Vector2D.h"
#include "..\Math\Rotation.h"

class SpiralMaterial : public Material {
private:
    RGBColor* rgbColors;
    RGBColor* baseRGBColors;
    uint8_t colorCount;
    Vector2D positionOffset;
    Vector2D rotationOffset;//point to rotate about
    float width;
    float bend;
    float rotationAngle;//rotate input xyPosition
  
public:
    SpiralMaterial(uint8_t colorCount, RGBColor* rgbColors, float width, float bend){
        this->colorCount = colorCount;
        this->width = width;
        this->bend = bend;

        this->rgbColors = new RGBColor[colorCount];
        this->baseRGBColors = new RGBColor[colorCount];

        for(int i = 0; i < colorCount; i++){
            this->rgbColors[i] = rgbColors[i];
            this->baseRGBColors[i] = rgbColors[i];
        }
    }

    void SetPositionOffset(Vector2D positionOffset){
        this->positionOffset = positionOffset;
    }
    
    void SetRotationOffset(Vector2D rotationOffset){
        this->rotationOffset = rotationOffset;
    }

    void SetRotationAngle(float rotationAngle){
        this->rotationAngle = rotationAngle;
    }

    void SetWidth(float width){
        this->width = width;
    }

    void SetBend(float bend){
        this->bend = bend;  
    }


    void HueShift(float hueDeg){
        for(int i = 0; i < colorCount; i++){
            rgbColors[i] = baseRGBColors[i].HueShift(hueDeg);
        }
    }
    
    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override {
        if(rotationAngle != 0){
            Quaternion temp = Rotation(EulerAngles(Vector3D(0, 0, rotationAngle), EulerConstants::EulerOrderXYZS)).GetQuaternion();
            
            position = position - Vector3D(positionOffset.X, positionOffset.Y, 0);

            position = temp.RotateVector(position);
        }

        
        //from x position, fit into bucket ratio
        //modulo x value into x range from start position to end position

        float radius = Vector2D(position).Magnitude();
        float angle = atan2(position.Y, position.X);
        float ratio = Mathematics::Fract(width * angle / Mathematics::MPI + bend * powf(radius, 0.3f));
        
        int startBox = floor(ratio * colorCount);

        RGBColor rgb = rgbColors[startBox];

        return rgb;
    }
};
