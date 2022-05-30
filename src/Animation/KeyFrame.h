#pragma once

class KeyFrame{
public:
    float Time = 0.0f;
    float Value = 0.0f;

    KeyFrame(){}

    KeyFrame(float time, float value){
        this->Time = time;
        this->Value = value;
    }

    void Set(float time, float value){
        this->Time = time;
        this->Value = value;
    }
};
