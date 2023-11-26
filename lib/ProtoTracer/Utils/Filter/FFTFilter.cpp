#include "FFTFilter.h"

FFTFilter::FFTFilter() {}

float FFTFilter::GetOutput() {
    return outputValue;
}

float FFTFilter::Filter(float value) {
    float valueAbs = fabs(value);
    float normalized = valueAbs - minKF.Filter(valueAbs);
    
    outputValue = Mathematics::Constrain(normalized * 2.0f, 0.0f, 1.0f);
    
    return outputValue;
}
