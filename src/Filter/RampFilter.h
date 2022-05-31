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
        if (value > filter && filter + increment < 1.0f) return filter += increment;
        if (value < filter && filter - increment > 0.0f) return filter -= increment;

        return filter;
    }

    void SetIncrement(const float increment) {
        this->increment = increment;
    }

    void SetFrames(const int frames) {
        increment = 1.0f / ((float)frames);
    }
};
