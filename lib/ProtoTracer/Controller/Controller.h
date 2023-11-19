#pragma once

#include <Arduino.h>
#include "..\Utils\Math\Mathematics.h"
#include "..\Camera\CameraManager\CameraManager.h"

class Controller {
private:
    const float softStart = 3000000;//microseconds
    long previousTime;
    float renderTime = 0.0f;
    uint8_t maxBrightness;
    uint8_t maxAccentBrightness;
    bool isOn = false;

    void UpdateBrightness(){
        if (!isOn && previousTime < softStart){
            brightness = Mathematics::Map(float(previousTime), 0.0f, softStart, 0.0f, float(maxBrightness));
            accentBrightness = Mathematics::Map(float(previousTime), 0.0f, softStart, 0.0f, float(maxAccentBrightness));
        }
        else if (!isOn){
            brightness = maxBrightness;
            accentBrightness = maxAccentBrightness;
            isOn = true;
        }
    }

protected:
    CameraManager* cameras;
    uint8_t brightness;
    uint8_t accentBrightness;

    Controller(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness){
        this->cameras = cameras;
        this->maxBrightness = maxBrightness;
        this->maxAccentBrightness = maxAccentBrightness;

        previousTime = micros();
    }

public:
    uint8_t GetBrightness(){
        return brightness;
    }

    uint8_t GetAccentBrightness(){
        return accentBrightness;
    }

    void SetBrightness(uint8_t maxBrightness){
        this->maxBrightness = maxBrightness;
        
        if(isOn){//past soft start
            this->brightness = maxBrightness;
        }
    }

    void SetAccentBrightness(uint8_t maxAccentBrightness){
        this->maxAccentBrightness = maxAccentBrightness;
        
        if(isOn){//past soft start
            this->accentBrightness = maxAccentBrightness;
        }
    }

    virtual void Initialize() = 0;
    virtual void Display() = 0;

    float GetRenderTime(){
        return renderTime;
    }

};
