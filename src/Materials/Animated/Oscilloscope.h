#pragma once

#include "..\Material.h"
#include "..\GradientMaterial.h"
#include "..\..\Filter\MaxFilter.h"
#include "..\..\Filter\MinFilter.h"

class Oscilloscope : public Material {
private:
    BouncePhysics* bPhy[128];
    Vector2D size;
    Vector2D offset;
    float angle = 0.0f;
    float hueAngle = 0.0f;
    float radius = 40.0f;
    uint8_t colors;
    float* data;
    float midPoint = 0.0f;
    uint8_t bins = 128;

    MaxFilter<40> maxF = MaxFilter<40>();
    MinFilter<40> minF = MinFilter<40>();
    
    RGBColor rainbowSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    GradientMaterial<6> gM = GradientMaterial<6>(rainbowSpectrum, 1.0f, false);

    Material* material;

    float minValue, maxValue;

public:
    Oscilloscope(Vector2D size, Vector2D offset){
        this->size = size.Divide(2.0f);
        this->offset = offset;
        this->material = &gM;
    }

    ~Oscilloscope(){
        for (uint8_t i = 0; i < 128; i++){
            delete bPhy[i];
        }

    }

    void SetMaterial(Material* material){
        this->material = material;
    }

    float* GetSampleData(){
        return data;
    }

    void SetSize(Vector2D size){
        this->size = size.Divide(2.0f);
    }

    void SetPosition(Vector2D offset){
        this->offset = offset;
    }

    void SetRotation(float angle){
        this->angle = angle;
    }

    void SetHueAngle(float hueAngle){
        this->hueAngle = hueAngle;
    }

    void Update(float* data){
        this->data = data;

        minValue = minF.Filter(data[bins / 2 + 1]);
        maxValue = maxF.Filter(data[bins / 2 + 1]);

        midPoint = (maxValue - minValue) / 2.0f + minValue;
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override {
        Vector2D rPos = Mathematics::IsClose(angle, 0.0f, 0.1f) ? Vector2D(position.X, position.Y) - offset : Vector2D(position.X, position.Y).Rotate(angle, offset) - offset;
        
        //Outside of size bounds
        if (rPos.X < -size.X || rPos.X > size.X) return RGBColor();
        if (rPos.Y < -size.Y || rPos.Y > size.Y) return RGBColor();
        
        uint8_t x = uint8_t(Mathematics::Map(rPos.X, -size.X, size.X, float(bins - 1), float(bins - 1) / 2));

        if(bins > x && 0 > x) return RGBColor();

        float xDistance = size.X / float(bins) * x - size.X;
        float xDistance2 = size.X / float(bins) * (x + 2) - size.X;
        float ratio = Mathematics::Map(rPos.X, xDistance, xDistance2, 0.0f, 1.0f);//ratio between two bins

        float firstPoint = Mathematics::Map(data[x], minValue, maxValue, 0.0f, 0.75f);
        float secondPoint = Mathematics::Map(data[x + 2], minValue, maxValue, 0.0f, 0.75f);
        
        //float firstPoint = (data[x] - midPoint) / 1024.0f;
        //float secondPoint = (data[x + 2] - midPoint) / 1024.0f;

        float height = Mathematics::CosineInterpolation(firstPoint, secondPoint, ratio);//0->1.0f of max height of color
        float yColor = Mathematics::Map(rPos.Y, 0.0f, size.Y, 1.0f, 0.0f);
        
        if (rPos.Y < height * size.Y / 2.0f && rPos.Y > height  * size.Y / 2.0f - size.Y * 0.1f){
            return material->GetRGB(Vector3D(1.0f + height - yColor, 0, 0), Vector3D(), Vector3D()).HueShift(hueAngle);
        }
        else {
            return RGBColor(0, 0, 0);
        }
    }
};
