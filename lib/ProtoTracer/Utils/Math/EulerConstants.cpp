#include "EulerConstants.h"

namespace EulerConstants {

// Static frame of reference, inertial reference frame
const EulerOrder EulerOrderXYZS{EulerOrder::Axis::X, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(0, 1, 2)};
const EulerOrder EulerOrderXYXS{EulerOrder::Axis::X, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(0, 1, 2)};
const EulerOrder EulerOrderXZYS{EulerOrder::Axis::X, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(0, 2, 1)};
const EulerOrder EulerOrderXZXS{EulerOrder::Axis::X, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(0, 2, 1)};
const EulerOrder EulerOrderYZXS{EulerOrder::Axis::Y, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(1, 2, 0)};
const EulerOrder EulerOrderYZYS{EulerOrder::Axis::Y, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(1, 2, 0)};
const EulerOrder EulerOrderYXZS{EulerOrder::Axis::Y, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(1, 0, 2)};
const EulerOrder EulerOrderYXYS{EulerOrder::Axis::Y, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(1, 0, 2)};
const EulerOrder EulerOrderZXYS{EulerOrder::Axis::Z, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(2, 0, 1)};
const EulerOrder EulerOrderZXZS{EulerOrder::Axis::Z, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(2, 0, 1)};
const EulerOrder EulerOrderZYXS{EulerOrder::Axis::Z, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(2, 1, 0)};
const EulerOrder EulerOrderZYZS{EulerOrder::Axis::Z, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(2, 1, 0)};

// Rotating frame of reference, non-inertial reference frame
const EulerOrder EulerOrderZYXR{EulerOrder::Axis::X, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(0, 1, 2)};
const EulerOrder EulerOrderXYXR{EulerOrder::Axis::X, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(0, 1, 2)};
const EulerOrder EulerOrderYZXR{EulerOrder::Axis::X, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(0, 2, 1)};
const EulerOrder EulerOrderXZXR{EulerOrder::Axis::X, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(0, 2, 1)};
const EulerOrder EulerOrderXZYR{EulerOrder::Axis::Y, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(1, 2, 0)};
const EulerOrder EulerOrderYZYR{EulerOrder::Axis::Y, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(1, 2, 0)};
const EulerOrder EulerOrderZXYR{EulerOrder::Axis::Y, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(1, 0, 2)};
const EulerOrder EulerOrderYXYR{EulerOrder::Axis::Y, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(1, 0, 2)};
const EulerOrder EulerOrderYXZR{EulerOrder::Axis::Z, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(2, 0, 1)};
const EulerOrder EulerOrderZXZR{EulerOrder::Axis::Z, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(2, 0, 1)};
const EulerOrder EulerOrderXYZR{EulerOrder::Axis::Z, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(2, 1, 0)};
const EulerOrder EulerOrderZYZR{EulerOrder::Axis::Z, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(2, 1, 0)};

} // namespace EulerConstants
