#pragma once

#include "..\..\Static\SimpleMaterial.h"
#include "..\Overlays\TextEngine.h"

class Clock : public Material {
private:
    TextEngine<3,12> tE = TextEngine<3,12>(false);
    SimpleMaterial mat = SimpleMaterial(RGBColor(255, 255, 255));
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t wDay;
    bool hour24 = false;

public: 
    Clock(bool hour24){
        this->hour24 = hour24;

        tE.SetMaterial(&mat);

        tE.SetBlinkTime(200);
    }

    void SetMaterial(Material* material){
        tE.SetMaterial(material);
    }

    void SetTime(uint8_t hour, uint8_t minute, uint8_t second){
        this->hour = hour;
        this->minute = minute;
        this->second = second;
    }

    void SetDate(uint8_t day, uint8_t month, uint8_t year, uint8_t wDay){
        this->day = day;
        this->month = month;
        this->year = year;
        this->wDay = wDay;
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
        String secondString = second < 10 ? "0" + String(second) : String(second);
        String minuteString = minute < 10 ? "0" + String(minute) : String(minute);
        String hourMinSec = String(hour) + ":" + minuteString + ":" + secondString;
        String date = String(month) + "/" + String(day) + "/" + String(year);
        
        String day;

        switch(wDay){
            case 0: day = "SATURDAY"; break;
            case 1: day = "SUNDAY"; break;
            case 2: day = "MONDAY"; break;
            case 3: day = "TUESDAY"; break;
            case 4: day = "WEDNESDAY"; break;
            case 5: day = "THURSDAY"; break;
            case 6: day = "FRIDAY"; break;
            default: day = "GLEENDAY"; break;
        }

        tE.SetText(0, hourMinSec, false);
        tE.SetText(1, date, false);
        tE.SetText(2, day, false);
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        return tE.GetRGB(position, normal, uvw);
    }

};
