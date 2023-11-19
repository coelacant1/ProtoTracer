#include "DerivativeFilter.h"

DerivativeFilter::DerivativeFilter() {}

float DerivativeFilter::GetOutput() {
    return outputValue;
}

float DerivativeFilter::Filter(float value) {
    float amplitude = fabs(value - previousReading);
    float normalized = output.Filter(amplitude);
    float minimum = minFilter.Filter(normalized);

    previousReading = value;
    outputValue = Mathematics::Constrain(normalized - minimum, 0.0f, 1.0f);

    return outputValue;
}
