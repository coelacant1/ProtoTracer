#pragma once

#include "Material.h"
#include "GradientMaterial.h"
#include "..\Sensors\MicrophoneFourier_MAX9814.h"

class SpectrumAnalyzer : public Material {
private:
    Vector2D size;
    Vector2D offset;
    float angle = 0.0f;
    float hueAngle = 0.0f;
    uint8_t colors;
    GradientMaterial* gM;
    float* data;
    uint8_t bins;
    bool mirrorY;

public:
    SpectrumAnalyzer(uint8_t pin, Vector2D size, Vector2D offset, GradientMaterial* gM, bool mirrorY = false){
        this->size = size;
        this->offset = offset;
        this->gM = gM;
        this->mirrorY = mirrorY;

        MicrophoneFourier::Initialize(pin, 10000, 50.0f, 100.0f);// 10KHz sample rate, 30dB min, 90dB max
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
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override {
        Vector2D rPos = angle != 0.0f ? Vector2D(position.X, position.Y).Rotate(angle, offset) - offset : Vector2D(position.X, position.Y) - offset;

        if (rPos.X < -size.X / 2.0f || rPos.X > size.X / 2.0f || rPos.Y < -size.Y / 2.0f || rPos.Y > size.Y / 2.0f) return RGBColor();

        uint8_t x = (unsigned int)Mathematics::Map(rPos.X, size.X / -2.0f, size.X / 2.0f, bins, 0);

        if(x < 0 || x >= uint8_t(bins - 1)) return RGBColor();

        float xDistance = size.X / float(bins) * x - size.X / 2.0f;
        float xDistance2 = size.X / float(bins) * (x + 1) - size.X / 2.0f;
        float ratio = Mathematics::Map(rPos.X, xDistance, xDistance2, 0.0f, 1.0f);//ratio between two bins
        float height = Mathematics::CosineInterpolation(data[x], data[x + 1], ratio);//0->1.0f of max height of color

        float yColor = Mathematics::Map(rPos.Y, -size.Y / 2.0f, size.Y / 2.0f, 1.0f, 0.0f);

        RGBColor color;

        if (yColor >= 0.0f && yColor <= height){
            color = gM->GetRGB(Vector3D(1.0f - height - yColor, 0, 0), Vector3D(), Vector3D());
        }
        else{
            color = RGBColor();
        }


        return color;
    }
};
