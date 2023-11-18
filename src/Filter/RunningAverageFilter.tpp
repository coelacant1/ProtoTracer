#pragma once

template<size_t memory>
RunningAverageFilter<memory>::RunningAverageFilter() {
    gain = 0.1f;
    currentAmount = 0;
}

template<size_t memory>
RunningAverageFilter<memory>::RunningAverageFilter(float gain) {
    this->gain = gain;
    currentAmount = 0;
}

template<size_t memory>
void RunningAverageFilter<memory>::SetGain(float gain) {
    this->gain = gain;
}

template<size_t memory>
float RunningAverageFilter<memory>::Filter(float value) {
    float sum = 0.0f;
    float avg = 0.0f;
    float gainInverse = (1.0f - gain);

    if (currentAmount < memory) {
        values[currentAmount++] = value;
    } else {
        for (uint8_t i = 0; i < memory - 1; i++) {
            values[i] = values[i + 1];
        }

        values[memory - 1] = value;
    }

    for (uint8_t i = 0; i < currentAmount; i++) {
        sum += values[i];
    }

    if (currentAmount > 0) {
        avg = sum / currentAmount;
    }

    return (gain * value) + (gainInverse * avg);
}
