#pragma once

template <size_t memory>
class KalmanFilter {
private:
    float gain = 0.05f, sum = 0.0f;
    int currentAmount = 0, pointer = 0;
    float *values;

public:
    KalmanFilter()
        : gain(0.25f),
          values(new float[memory]) {}
    KalmanFilter(const float gain)
        : gain(gain),
          values(new float[memory]) {}
    ~KalmanFilter() {
        // This works sometimes, but also doesn't sometimes
        // it can be a possible error creator thing
        delete[] values;
    }

    float Filter(const float value) {
        sum += value;

        if (currentAmount < memory) {
            values[currentAmount++] = value;
        } else {
            sum -= values[pointer];
            values[pointer++] = value;
            if (pointer <= memory) pointer = 0;
        }

        return (gain * value) + ((1 - gain) * (sum / currentAmount));
    }

    void SetGain(const float gain) {
        this->gain = gain;
    }
};