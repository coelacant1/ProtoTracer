#pragma once

#include "Arduino.h"
#include "Math\Mathematics.h"

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
    float minimum = 0.0f, maximum = 0.0f, period = 0.0f;

    float TriangleWave(float ratio){
        const float wave = (ratio > 0.5f ? 1.0f - ratio : ratio) * 2.0f;

        return Mathematics::Map(wave, 0.0f, 1.0f, minimum, maximum);
    }

    float SquareWave(float ratio){
        const float wave = ratio > 0.5f ? 1.0f : 0.0f;

        return Mathematics::Map(wave, 0.0f, 1.0f, minimum, maximum);
    }

    float SineWave(float ratio){
        float wave = sinf(ratio * 2.0f * Mathematics::MPI);

        return Mathematics::Map(wave, -1.0f, 1.0f, minimum, maximum);
    }

    float SawtoothWave(float ratio){
        return Mathematics::Map(ratio, 0.0f, 1.0f, minimum, maximum);
    }

public:
    FunctionGenerator(const Function function, const float minimum, const float maximum, const float period)
        : function(function),
          minimum(minimum),
          maximum(maximum),
          period(period) {}

    float Update(){
        const float currentTime = fmod(micros() / 1000000.0f, period);
        const float ratio = currentTime / period;
        
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
