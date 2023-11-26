#include "VectorRunningAverageFilter.h"

template<size_t memory>
VectorRunningAverageFilter<memory>::VectorRunningAverageFilter() {
    X = RunningAverageFilter<memory>();
    Y = RunningAverageFilter<memory>();
    Z = RunningAverageFilter<memory>();
}

template<size_t memory>
VectorRunningAverageFilter<memory>::VectorRunningAverageFilter(float gain) {
    X = RunningAverageFilter<memory>(gain);
    Y = RunningAverageFilter<memory>(gain);
    Z = RunningAverageFilter<memory>(gain);
}

template<size_t memory>
Vector3D VectorRunningAverageFilter<memory>::Filter(Vector3D input) {
    return Vector3D{
        X.Filter(input.X),
        Y.Filter(input.Y),
        Z.Filter(input.Z)
    };
}
