#include "RampFilter.h"
#include "..\Math\Mathematics.h"

RampFilter::RampFilter() {
    increment = 0.05f;
    filter = 0.0f;
    epsilon = 0.01f;
}

RampFilter::RampFilter(int frames, float epsilon) {
    increment = 1.0f / float(frames);
    this->epsilon = epsilon;
}

float RampFilter::Filter(float value) {
    if (Mathematics::IsClose(value, filter, epsilon)) return filter;

    if (value > filter) {
        filter = filter + increment < 1.0f ? filter + increment : 1.0f;
    } else if (value < filter) {
        filter = filter - increment > 0.0f ? filter - increment : 0.0f;
    }

    return filter;
}

void RampFilter::SetIncrement(float increment) {
    this->increment = increment;
}

void RampFilter::SetFrames(int frames) {
    increment = 1.0f / float(frames);
}
