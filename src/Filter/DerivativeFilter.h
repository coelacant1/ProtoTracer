#pragma once

#include <Arduino.h>
#include "RunningAverageFilter.h"
#include "MinFilter.h"
#include "..\Math\Mathematics.h"

class DerivativeFilter{
private:
    RunningAverageFilter<10> output = RunningAverageFilter<10>(0.2f);
    MinFilter<40> minFilter;
    float previousReading = 0.0f;
    float outputValue = 0.0f;

public:
    DerivativeFilter(){}

    float GetOutput(){
        return outputValue;
    }

    float Filter(float value){
        float amplitude = fabs(value - previousReading);
        float normalized = output.Filter(amplitude);
        float minimum = minFilter.Filter(normalized);
        
        previousReading = value;
        outputValue = Mathematics::Constrain(normalized - minimum, 0.0f, 1.0f);
        
        return outputValue;
    }

};
