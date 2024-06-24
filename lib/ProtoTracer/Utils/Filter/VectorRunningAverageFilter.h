#pragma once

#include "RunningAverageFilter.h"
#include "../Math/Vector3D.h"

template<size_t memory>
class VectorRunningAverageFilter {
private:
    RunningAverageFilter<memory> X;
    RunningAverageFilter<memory> Y;
    RunningAverageFilter<memory> Z;

public:
    VectorRunningAverageFilter();
    VectorRunningAverageFilter(float gain);

    Vector3D Filter(Vector3D input);
};
