#pragma once

#include "..\Render\Camera.h"

class Controller {
private:
    const float softStart = 3000000;//microseconds
    long previousTime;
    Camera** cameras;
    uint8_t count = 0;
    float renderTime = 0.0f;
    uint8_t maxBrightness;
    bool isOn = false;

protected:
    uint8_t brightness;

    Controller(Camera** cameras, uint8_t count, uint8_t maxBrightness){
        this->cameras = cameras;
        this->count = count;
        this->maxBrightness = maxBrightness;
        previousTime = micros();
    }

public:
    void Render(Scene* scene){
        previousTime = micros();

        if (!isOn && previousTime < softStart){
            brightness = map(previousTime, 0, softStart, 0, maxBrightness);
        }
        else if (!isOn){
            brightness = maxBrightness;
            isOn = true;
        }

        for (int i = 0; i < count; i++){
            cameras[i]->Rasterize(scene);
        }

        renderTime = ((float)(micros() - previousTime)) / 1000000.0f;
    }

    void SetBrightness(uint8_t maxBrightness){
        this->maxBrightness = maxBrightness;
        
        if(isOn){//past soft start
            this->brightness = maxBrightness;
        }
    }

    virtual void Initialize() = 0;
    virtual void Display() = 0;

    float GetRenderTime(){
        return renderTime;
    }

};
