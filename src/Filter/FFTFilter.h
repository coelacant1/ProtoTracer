#pragma once

#include <Arduino.h>
#include "KalmanFilter.h"
#include "..\Math\Mathematics.h"
#include "MinFilter.h"

class FFTFilter{
private:
    KalmanFilter mv = KalmanFilter(0.05f, 20);
    MinFilter minF = MinFilter(20);
    KalmanFilter output = KalmanFilter(0.1f, 10);
    float previousReading = 0.0f;

public:
    FFTFilter(){}

    float Update(float value){
        float changeRate = value - previousReading;
        float amplitude = mv.Filter(fabs(changeRate));//mv.Filter(fabs(changeRate));
        float minimum = minF.Filter(changeRate);
        float normalized = value - amplitude - minimum;
        float truncate = normalized < 0 ? 0 : output.Filter(normalized);//output.Filter(normalized);
        

        previousReading = value;
        
        return Mathematics::Constrain(truncate, 0.0f, 1.0f);
    }

};
