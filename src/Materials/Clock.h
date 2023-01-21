#pragma once

#include "SimpleMaterial.h"
#include "Menu\TextEngine.h"

class Clock : public Material {
private:
    TextEngine<2,12> tE = TextEngine<2,12>();
    SimpleMaterial mat = SimpleMaterial(RGBColor(255, 255, 255));
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    bool hour24 = false;

public: 
    Clock(bool hour24){
        this->hour24 = hour24;

        tE.SetMaterial(&mat);

        tE.SetBlinkTime(200);
    }

    void SetTime(uint8_t hour, uint8_t minute, uint8_t second){

    }

    void SetSize(Vector2D size){
        tE.SetSize(size);
    }

    void SetPosition(Vector2D position){
        tE.SetPositionOffset(position);
    }

    void SetRotation(float rotation){
        tE.SetRotationAngle(rotation);
    }

    void Update(){
        String txt = "2:53:" + String(millis() / 1000 % 60);
        tE.SetText(0, txt, false);
        tE.SetText(1, "SATURDAY", false);
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        return tE.GetRGB(position, normal, uvw);
    }

};