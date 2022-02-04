#pragma once

#include "Material.h"
#include "..\Math\Mathematics.h"
#include "..\Math\Vector2D.h"
#include "..\Math\Rotation.h"

class StripeMaterial : public Material {
private:
    RGBColor* rgbColors;
    RGBColor* baseRGBColors;
    uint8_t colorCount;
    Vector2D positionOffset;
    Vector2D rotationOffset;//point to rotate about
    float stripeWidth;
    float wavePeriod;
    float waveAmplitude;
    float rotationAngle;//rotate input xyPosition
  
public:
    StripeMaterial(uint8_t colorCount, RGBColor* rgbColors, float stripeWidth, float wavePeriod, float waveAmplitude){
        this->colorCount = colorCount;
        this->stripeWidth = stripeWidth;
        this->wavePeriod = wavePeriod;
        this->waveAmplitude = waveAmplitude;

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

    void SetStripeWidth(float stripeWidth){
        this->stripeWidth = stripeWidth;
    }

    void SetWavePeriod(float wavePeriod){
        this->wavePeriod = wavePeriod;  
    }

    void SetWaveAmplitude(float waveAmplitude){
        this->waveAmplitude = waveAmplitude;  
    }

    void HueShift(float hueDeg){
        for(int i = 0; i < colorCount; i++){
            rgbColors[i] = baseRGBColors[i].HueShift(hueDeg);
        }
    }
    
    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override {
        if(rotationAngle != 0){
            Quaternion temp = Rotation(EulerAngles(Vector3D(0, 0, rotationAngle), EulerConstants::EulerOrderXYZS)).GetQuaternion();

            position = temp.RotateVector(position);
        }

        float pos = 0;
        position = position - Vector3D(positionOffset.X, positionOffset.Y, 0);
        
        //from x position, fit into bucket ratio
        //modulo x value into x range from start position to end position
        
        pos = fabs(fmodf(position.X + sinf(position.Y * Mathematics::MPI * 2.0f / wavePeriod) * waveAmplitude, stripeWidth));
        
        float ratio = Mathematics::Map(pos, 0, stripeWidth, 0, colorCount);
        
        //map from modulo'd x value to color count minimum
        int startBox = floor(ratio);

        RGBColor rgb = rgbColors[startBox];

        return rgb;
    }
};
