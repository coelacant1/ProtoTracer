#pragma once

#include "Vector3D.h"

class EulerOrder {
public:
    enum Axis {
        XYZ,
        XZY,
        YXZ,
        YZX,
        ZXY,
        ZYX
    };

    enum AxisFrame {
        Static,
        Rotating
    };

    Axis AxisOrder;
    AxisFrame FrameTaken;
    Vector3D Permutation;

    // Default constructor.
    EulerOrder();

    // Parameterized constructor.
    EulerOrder(Axis axisOrder, AxisFrame axisFrame, Vector3D permutation);

    // Convert EulerOrder to a string representation.
    String ToString();
};
