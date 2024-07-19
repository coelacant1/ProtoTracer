#include "EulerConstants.h"

namespace EulerConstants {

// Static frame of reference, inertial reference frame
const EulerOrder EulerOrderXYZS{EulerOrder::Axis::XYZ, EulerOrder::AxisFrame::Static, Vector3D(0, 1, 2)};
const EulerOrder EulerOrderXZYS{EulerOrder::Axis::XZY, EulerOrder::AxisFrame::Static, Vector3D(0, 2, 1)};
const EulerOrder EulerOrderYXZS{EulerOrder::Axis::YXZ, EulerOrder::AxisFrame::Static, Vector3D(1, 2, 0)};
const EulerOrder EulerOrderYZXS{EulerOrder::Axis::YZX, EulerOrder::AxisFrame::Static, Vector3D(1, 0, 2)};
const EulerOrder EulerOrderZXYS{EulerOrder::Axis::ZXY, EulerOrder::AxisFrame::Static, Vector3D(2, 0, 1)};
const EulerOrder EulerOrderZYXS{EulerOrder::Axis::ZYX, EulerOrder::AxisFrame::Static, Vector3D(2, 1, 0)};

// Rotating frame of reference, non-inertial reference frame
const EulerOrder EulerOrderZYXR{EulerOrder::Axis::XYZ, EulerOrder::AxisFrame::Rotating, Vector3D(0, 1, 2)};
const EulerOrder EulerOrderYZXR{EulerOrder::Axis::XZY, EulerOrder::AxisFrame::Rotating, Vector3D(0, 2, 1)};
const EulerOrder EulerOrderXZYR{EulerOrder::Axis::YXZ, EulerOrder::AxisFrame::Rotating, Vector3D(1, 2, 0)};
const EulerOrder EulerOrderZXYR{EulerOrder::Axis::YZX, EulerOrder::AxisFrame::Rotating, Vector3D(1, 0, 2)};
const EulerOrder EulerOrderYXZR{EulerOrder::Axis::ZXY, EulerOrder::AxisFrame::Rotating, Vector3D(2, 0, 1)};
const EulerOrder EulerOrderXYZR{EulerOrder::Axis::ZYX, EulerOrder::AxisFrame::Rotating, Vector3D(2, 1, 0)};

} // namespace EulerConstants
