#pragma once

class RampFilter {
private:
    float increment = 0.05f;
    float filter = 0.0f;

public:
    RampFilter() {}

    RampFilter(const int frames)
        : increment(1.0f / ((float)frames)) {}

    float Filter(const float value) {
        if (value > filter && filter + increment < 1.0f) {
            filter = filter + increment;
        } else if (value < filter && filter - increment > 0.0f) {
            filter = filter - increment;
        }

        return filter;
    }

    void SetIncrement(const float increment) {
        this->increment = increment;
    }
};
