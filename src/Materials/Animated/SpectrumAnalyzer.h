#pragma once

#include "..\Material.h"
#include "..\GradientMaterial.h"
#include "..\..\Sensors\MicrophoneFourier_MAX9814.h"
#include "..\..\Controls\BouncePhysics.h"

class SpectrumAnalyzer : public Material {
private:
    BouncePhysics* bPhy[128];
    Vector2D size;
    Vector2D offset;
    float angle = 0.0f;
    float hueAngle = 0.0f;
    uint8_t colors;
    float* data;
    float bounceData[128];
    uint8_t bins;
    bool mirrorY = false;
    bool flipY = false;
    bool bounce = false;
    
    RGBColor rainbowSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    GradientMaterial<6> gM = GradientMaterial<6>(rainbowSpectrum, 1.0f, false);

    Material* material;

public:
    SpectrumAnalyzer(uint8_t pin, Vector2D size, Vector2D offset, bool bounce = false, bool flipY = false, bool mirrorY = false){
        this->size = size;
        this->offset = offset;
        this->mirrorY = mirrorY;
        this->flipY = flipY;
        this->bounce = bounce;
        this->material = &gM;

        if (bounce){
            for (uint8_t i = 0; i < 128; i++){
                bPhy[i] = new BouncePhysics(35.0f, 15.0f);
            }
        }

        MicrophoneFourier::Initialize(pin, 8000, 50.0f, 120.0f);// 10KHz sample rate, 30dB min, 90dB max
    }

    ~SpectrumAnalyzer(){
        for (uint8_t i = 0; i < 128; i++){
            delete bPhy[i];
        }

    }

    void SetMaterial(Material* material){
        this->material = material;
    }

    float GetCurrentValue(){
        return MicrophoneFourier::GetCurrentValue();
    }

    float* GetFourierData(){
        if(bounce){
            return bounceData;
        }
        else{
            return data;
        }
    }

    void SetSize(Vector2D size){
        this->size = size;
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

    void Update(){
        MicrophoneFourier::Update();
        data = MicrophoneFourier::GetFourier(bins);

        if(bounce){
            for (uint8_t i = 0; i < 128; i++){
                bounceData[i] = bPhy[i]->Calculate(data[i], 0.1f);
            }
        }
    }

    void Update(float* readData){
        data = readData;
        
        for (uint8_t i = 0; i < 128; i++){
            bounceData[i] = *(readData + i);
        }
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override {
        Vector2D rPos = angle != 0.0f ? Vector2D(position.X, position.Y).Rotate(angle, offset) - offset : Vector2D(position.X, position.Y) - offset;

        if (rPos.X < -size.X / 2.0f || rPos.X > size.X / 2.0f || rPos.Y < -size.Y / 2.0f || rPos.Y > size.Y / 2.0f) return RGBColor();

        uint8_t x = (unsigned int)Mathematics::Map(rPos.X, size.X / -2.0f, size.X / 2.0f, bins, 0);

        if(x < 0 || x >= uint8_t(bins - 1)) return RGBColor();

        float xDistance = size.X / float(bins) * x - size.X / 2.0f;
        float xDistance2 = size.X / float(bins) * (x + 1) - size.X / 2.0f;
        float ratio = Mathematics::Map(rPos.X, xDistance, xDistance2, 0.0f, 1.0f);//ratio between two bins
        float height = bounce ? Mathematics::CosineInterpolation(bounceData[x], bounceData[x + 1], ratio) : Mathematics::CosineInterpolation(data[x], data[x + 1], ratio);//0->1.0f of max height of color
        float yColor;

        if(mirrorY){
            yColor = Mathematics::Map(fabs(rPos.Y), size.Y / 2.0f, 0.0f, 1.0f, 0.0f);
        }
        else{
            yColor = Mathematics::Map(rPos.Y, -size.Y / 2.0f, size.Y / 2.0f, 1.0f, 0.0f);
        }
        
        if(flipY) yColor = 1.0f - yColor;

        RGBColor color;

        if (yColor >= 0.0f && yColor <= height){
            color = material->GetRGB(Vector3D(1.0f - height - yColor, 0, 0), Vector3D(), Vector3D()).HueShift(hueAngle);
        }
        else{
            color = RGBColor();
        }


        return color;
    }
};
