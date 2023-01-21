#pragma once

#include "..\Math\Mathematics.h"
#include "..\Math\Quaternion.h"
#include "..\Math\Vector3D.h"

class RGBColor {
public:
    uint16_t color = 0;

    RGBColor(){}

    RGBColor(uint8_t R, uint8_t G, uint8_t B){
        R = (R >> 3) & 0x1F; 
        G = (G >> 2) & 0x3F; 
        B = (B >> 3) & 0x1F;

        color = (R << 11) | (G << 5) | B;
    }
    
    RGBColor(const RGBColor& rgbColor){
        this->R = rgbColor.R;
        this->G = rgbColor.G;
        this->B = rgbColor.B;
    }

    RGBColor(Vector3D color){
        this->R = color.X;
        this->G = color.Y;
        this->B = color.Z;
    }

    void SetColor(uint8_t R, uint8_t G, uint8_t B){
        this->R = R;
        this->G = G;
        this->B = B;
    }

    RGBColor Scale(uint8_t maxBrightness){
        uint8_t sR, sG, sB;
        
        sR = (uint8_t)R * (uint8_t)maxBrightness / 255;
        sG = (uint8_t)G * (uint8_t)maxBrightness / 255;
        sB = (uint8_t)B * (uint8_t)maxBrightness / 255;
        
        sR = sR > 255 ? 255 : sR;
        sG = sG > 255 ? 255 : sG;
        sB = sB > 255 ? 255 : sB;
        
        sR = sR < 0 ? 0 : sR;
        sG = sG < 0 ? 0 : sG;
        sB = sB < 0 ? 0 : sB;
        
        return RGBColor(sR, sG, sB);
    }

    RGBColor Add(uint8_t value){
        int sR, sG, sB;
        
        sR = (uint8_t)R + (uint8_t)value;
        sG = (uint8_t)G + (uint8_t)value;
        sB = (uint8_t)B + (uint8_t)value;
        
        sR = sR > 255 ? 255 : sR;
        sG = sG > 255 ? 255 : sG;
        sB = sB > 255 ? 255 : sB;
        
        sR = sR < 0 ? 0 : sR;
        sG = sG < 0 ? 0 : sG;
        sB = sB < 0 ? 0 : sB;
        
        return RGBColor(sR, sG, sB);
    }

    RGBColor HueShift(float hueDeg){
        //hueDeg = (int)hueDeg % 360;
        //shift color space by rotating rgb vector about diagonal vector (1, 1, 1)
        float hueRad = hueDeg * Mathematics::MPI / 180.0f;
        float hueRat = 0.5f * sinf(hueRad / 2.0f);//2.0f for quaternion creation
        Vector3D rgbVec = Vector3D(R, G, B);
        Quaternion q = Quaternion(cosf(hueRad / 2.0f), hueRat, hueRat, hueRat);

        rgbVec = q.RotateVector(rgbVec).Constrain(0.0f, 255.0f);
        
        return RGBColor(rgbVec.X, rgbVec.Y, rgbVec.Z);
    }

    static RGBColor InterpolateColors(RGBColor a, RGBColor b, float ratio){
        RGBColor c;

        c.R = a.R * (1.0f - ratio) + b.R * ratio;
        c.G = a.G * (1.0f - ratio) + b.G * ratio;
        c.B = a.B * (1.0f - ratio) + b.B * ratio;

        return c;
    }
    
    String ToString(){
        String r = String(this->R);
        String g = String(this->G);
        String b = String(this->B);
        
        return "[" + r + ", " + g + ", " + b + "]";
    }
};
