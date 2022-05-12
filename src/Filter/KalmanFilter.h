#pragma once

class KalmanFilter {
private:
    float gain = 0.05f, sum = 0.0f;
    int memory = 90, currentAmount = 0, pointer = 0;
    float *values;

public:
    KalmanFilter()
        : gain(0.25f),
          memory(25),
          values(new float[25]) {}
    KalmanFilter(const float gain, const int memory)
        : gain(gain),
          memory(memory),
          values(new float[memory]) {}
    ~KalmanFilter(){
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
    void SetMemory(const int newMemory) {
        // transfer old stuff to new stuff via extremely convoluted means
        float *newValues = new float[newMemory];

        if (newMemory > memory) {
            for (int i = 0; i < memory; i++)
                newValues[i] = values[i];
        } else {
            if (currentAmount > newMemory) currentAmount = newMemory;
            const int start = (pointer > newMemory) ? pointer - newMemory : memory - (newMemory - pointer) ;
            const int end = start + newMemory;
            sum = 0.0f;
            int j = 0;
            for (int i = start; i < end; i++)
                sum += newValues[j++] = values[i % memory];
            pointer = newMemory - (memory - newMemory);
        }

        memory = newMemory;

        delete[] values; // Let's be memory safe at least...
        values = newValues;
    }
};