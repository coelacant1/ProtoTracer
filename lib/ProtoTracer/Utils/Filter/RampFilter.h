#pragma once

#include "..\Math\Mathematics.h"

class RampFilter {
private:
    float increment;
    float filter;
    float epsilon;

public:
    RampFilter();
    RampFilter(int frames, float epsilon = 0.01f);

    float Filter(float value);
    void SetIncrement(float increment);
    void SetFrames(int frames);
};
