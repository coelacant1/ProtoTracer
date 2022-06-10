#pragma once

#include <Arduino.h>
#include "KalmanFilter.h"
#include "..\Math\Mathematics.h"

class FFTFilter{
private:
    KalmanFilter<20> minKF = KalmanFilter<20>(0.05f);
    float outputValue = 0.0f;

public:
    FFTFilter(){}

    float GetOutput(){
        return outputValue;
    }

    float Filter(float value){
        float valueAbs = fabs(value);
        float normalized = valueAbs - minKF.Filter(valueAbs);//minimum;
        
        outputValue = Mathematics::Constrain(normalized * 2.0f, 0.0f, 1.0f);
        
        return outputValue;
    }

};