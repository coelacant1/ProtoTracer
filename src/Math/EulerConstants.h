#pragma once

#include "EulerOrder.h"

namespace EulerConstants {
    // Static frame of reference, inertial reference frame
    const EulerOrder EulerOrderXYZS = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(0, 1, 2));
    const EulerOrder EulerOrderXYXS = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(0, 1, 2));
    const EulerOrder EulerOrderXZYS = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(0, 2, 1));
    const EulerOrder EulerOrderXZXS = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(0, 2, 1));
    const EulerOrder EulerOrderYZXS = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(1, 2, 0));
    const EulerOrder EulerOrderYZYS = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(1, 2, 0));
    const EulerOrder EulerOrderYXZS = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(1, 0, 2));
    const EulerOrder EulerOrderYXYS = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(1, 0, 2));
    const EulerOrder EulerOrderZXYS = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(2, 0, 1));
    const EulerOrder EulerOrderZXZS = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(2, 0, 1));
    const EulerOrder EulerOrderZYXS = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(2, 1, 0));
    const EulerOrder EulerOrderZYZS = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(2, 1, 0));

    // Rotating frame of reference, non-inertial reference frame
    const EulerOrder EulerOrderZYXR = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(0, 1, 2));
    const EulerOrder EulerOrderXYXR = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(0, 1, 2));
    const EulerOrder EulerOrderYZXR = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(0, 2, 1));
    const EulerOrder EulerOrderXZXR = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(0, 2, 1));
    const EulerOrder EulerOrderXZYR = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(1, 2, 0));
    const EulerOrder EulerOrderYZYR = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(1, 2, 0));
    const EulerOrder EulerOrderZXYR = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(1, 0, 2));
    const EulerOrder EulerOrderYXYR = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(1, 0, 2));
    const EulerOrder EulerOrderYXZR = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(2, 0, 1));
    const EulerOrder EulerOrderZXZR = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(2, 0, 1));
    const EulerOrder EulerOrderXYZR = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(2, 1, 0));
    const EulerOrder EulerOrderZYZR = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(2, 1, 0));

};
