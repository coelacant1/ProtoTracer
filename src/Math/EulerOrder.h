#pragma once

#include "Vector3D.h"

typedef struct EulerOrder {
public:
    enum Axis {
        X,
        Y,
        Z
    };

    enum Parity {
        Even,
        Odd
    };

    enum AxisRepetition {
        Yes,
        No
    };

    enum AxisFrame {
        Static,
        Rotating
    };

    Axis InitialAxis;
    Parity AxisPermutation;
    AxisRepetition InitialAxisRepetition;
    AxisFrame FrameTaken;
    Vector3D Permutation;

    EulerOrder() // XYZ static/inertial frame of reference
        : InitialAxis(Axis::X),
          AxisPermutation(Parity::Even),
          InitialAxisRepetition(AxisRepetition::No),
          FrameTaken(AxisFrame::Static),
          Permutation(Vector3D(0, 1, 2)) {}

    EulerOrder(
        const Axis axis,
        const Parity parity,
        const AxisRepetition axisRepetition,
        const AxisFrame axisFrame,
        const Vector3D permutation)
        : InitialAxis(axis),
          AxisPermutation(parity),
          InitialAxisRepetition(axisRepetition),
          FrameTaken(axisFrame),
          Permutation(permutation) {}

    String ToString() const {
        return Permutation.ToString();
    }

} EulerOrder;
