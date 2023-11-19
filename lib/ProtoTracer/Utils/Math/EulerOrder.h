#pragma once

#include "Vector3D.h"

class EulerOrder {
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

    // Default constructor.
    EulerOrder();

    // Parameterized constructor.
    EulerOrder(Axis axis, Parity parity, AxisRepetition axisRepetition, AxisFrame axisFrame, Vector3D permutation);

    // Convert EulerOrder to a string representation.
    String ToString();
};
