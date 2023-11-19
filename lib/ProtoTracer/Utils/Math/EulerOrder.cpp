#include "EulerOrder.h"

// Default constructor.
EulerOrder::EulerOrder()
    : InitialAxis(Axis::X),
      AxisPermutation(Parity::Even),
      InitialAxisRepetition(AxisRepetition::No),
      FrameTaken(AxisFrame::Static),
      Permutation(0, 1, 2) {}

// Parameterized constructor.
EulerOrder::EulerOrder(Axis axis, Parity parity, AxisRepetition axisRepetition, AxisFrame axisFrame, Vector3D permutation)
    : InitialAxis(axis),
      AxisPermutation(parity),
      InitialAxisRepetition(axisRepetition),
      FrameTaken(axisFrame),
      Permutation(permutation) {}

// Convert EulerOrder to a string representation.
String EulerOrder::ToString() {
    return Permutation.ToString();
}
