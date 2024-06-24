#pragma once

#include <Arduino.h>
#include "../Math/Mathematics.h"

class FunctionGenerator {
public:
    enum Function {
        Triangle,
        Square,
        Sine,
        Sawtooth,
        Gravity
    };

private:
    Function function;
    float minimum = 0.0f;
    float maximum = 0.0f;
    float period = 0.0f;

    float TriangleWave(float ratio);
    float SquareWave(float ratio);
    float SineWave(float ratio);
    float SawtoothWave(float ratio);
    float GravityFunction(float ratio);

public:
    FunctionGenerator(Function function, float minimum, float maximum, float period);

    void SetPeriod(float period);
    void SetFunction(Function function);
    float Update();
};
