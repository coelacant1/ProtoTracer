#pragma once

#include "..\Math\Vector3D.h"
#include "KalmanFilter.h"

template <size_t XMem, size_t YMem, size_t ZMem>
class VectorKalmanFilter {
private:
    KalmanFilter<XMem> X;
    KalmanFilter<YMem> Y;
    KalmanFilter<ZMem> Z;

public:
    VectorKalmanFilter()
        : X(KalmanFilter<XMem>()),
          Y(KalmanFilter<YMem>()),
          Z(KalmanFilter<ZMem>()) {}
    VectorKalmanFilter(const float gain)
        : X(KalmanFilter<XMem>(gain)),
          Y(KalmanFilter<YMem>(gain)),
          Z(KalmanFilter<ZMem>(gain)) {}
    VectorKalmanFilter(const Vector3D &gain)
        : X(KalmanFilter<XMem>(gain.X)),
          Y(KalmanFilter<YMem>(gain.Y)),
          Z(KalmanFilter<ZMem>(gain.Z)) {}

    Vector3D Filter(const Vector3D &input) {
        return Vector3D(
            X.Filter(input.X),
            Y.Filter(input.Y),
            Z.Filter(input.Z));
    }
};
