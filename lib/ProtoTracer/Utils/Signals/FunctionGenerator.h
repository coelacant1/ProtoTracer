#pragma once

#include <Arduino.h>
#include "..\Math\Mathematics.h"

class FunctionGenerator{
public:
    enum Function{
        Triangle,
        Square,
        Sine,
        Sawtooth
    };

private:
    Function function;
    float minimum = 0.0f;
    float maximum = 0.0f;
    float period = 0.0f;

    float TriangleWave(float ratio){
        float wave = (ratio > 0.5f ? 1.0f - ratio : ratio) * 2.0f;

        return Mathematics::Map(wave, 0.0f, 1.0f, minimum, maximum);
    }

    float SquareWave(float ratio){
        float wave = ratio > 0.5f ? 1.0f : 0.0f;

        return Mathematics::Map(wave, 0.0f, 1.0f, minimum, maximum);
    }

    float SineWave(float ratio){
        float wave = sinf(ratio * 360.0f * 3.14159f / 180.0f);

        return Mathematics::Map(wave, -1.0f, 1.0f, minimum, maximum);
    }

    float SawtoothWave(float ratio){
        return Mathematics::Map(ratio, 0.0f, 1.0f, minimum, maximum);
    }

public:
    FunctionGenerator(Function function, float minimum, float maximum, float period){
        this->function = function;
        this->minimum = minimum;
        this->maximum = maximum;
        this->period = period;
    }

    void SetPeriod(float period){
        this->period = period;
    }

    void SetFunction(Function function){
        this->function = function;
    }

    float Update(){
        float currentTime = fmod(micros() / 1000000.0f, period);
        float ratio = currentTime / period;
        
        switch(function){
            case Triangle:
                return TriangleWave(ratio);
                break;
            case Square:
                return SquareWave(ratio);
                break;
            case Sine:
                return SineWave(ratio);
                break;
            case Sawtooth:
                return SawtoothWave(ratio);
                break;
            default:
                return 0.0f;
                break;
        }
    }
};
