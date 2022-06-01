#pragma once

#include <Arduino.h>
#include "KalmanFilter.h"
#include "..\Math\Mathematics.h"
#include "MinFilter.h"

class FFTFilter{
private:
    MinFilter<40> minF = MinFilter<40>();
    KalmanFilter<5> output = KalmanFilter<5>(0.5f);
    float previousReading = 0.0f;
    float outputValue = 0.0f;

public:
    FFTFilter(){}

    float GetOutput(){
        return outputValue;
    }

    float Filter(float value){
        float changeRate = value - previousReading;
        float amplitude = fabs(changeRate);//mv.Filter(fabs(changeRate));
        float minimum = minF.Filter(value);
        float normalized = value - amplitude - minimum;
        float truncate = normalized < 0 ? 0 : normalized;//output.Filter(normalized);
        
        previousReading = value;
        outputValue = Mathematics::Constrain(truncate, 0.0f, 1.0f);
        
        return outputValue;
    }

};