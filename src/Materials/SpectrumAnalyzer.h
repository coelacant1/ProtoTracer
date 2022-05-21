#pragma once

#include "Material.h"
#include "GradientMaterial.h"
#include "..\Sensors\MicrophoneFourier_MAX9814.h"
#include "..\Controls\BouncePhysics.h"

class SpectrumAnalyzer : public Material {
private:
    BouncePhysics* bPhy[64];
    Vector2D size;
    Vector2D offset;
    float angle = 0.0f;
    float hueAngle = 0.0f;
    uint8_t colors;
    GradientMaterial* gM;
    float* data;
    float bounceData[64];
    uint8_t bins;
    bool mirrorY = false;
    bool flipY = false;
    bool bounce = false;

public:
    SpectrumAnalyzer(uint8_t pin, Vector2D size, Vector2D offset, GradientMaterial* gM, bool bounce = false, bool flipY = false, bool mirrorY = false){
        this->size = size;
        this->offset = offset;
        this->gM = gM;
        this->mirrorY = mirrorY;
        this->flipY = flipY;
        this->bounce = bounce;

        if (bounce){
            for (uint8_t i = 0; i < 64; i++){
                bPhy[i] = new BouncePhysics(3.5f);
            }
        }

        MicrophoneFourier::Initialize(pin, 20000, 50.0f, 100.0f);// 10KHz sample rate, 30dB min, 90dB max
    }

    ~SpectrumAnalyzer(){
        for (uint8_t i = 0; i < 64; i++){
            delete bPhy[i];
        }

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
            for (uint8_t i = 0; i < 64; i++){
                bounceData[i] = bPhy[i]->Calculate(data[i], 0.1f);
            }
        }
    }

    void Update(float* readData){
        data = readData;
        
        for (uint8_t i = 0; i < 64; i++){
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
            color = gM->GetRGB(Vector3D(1.0f - height - yColor, 0, 0), Vector3D(), Vector3D()).HueShift(hueAngle);
        }
        else{
            color = RGBColor();
        }


        return color;
    }
};
