#pragma once

#include "EulerOrder.h"
#include "Vector3D.h"

namespace EulerConstants {

// Static frame of reference, inertial reference frame
extern const EulerOrder EulerOrderXYZS;
extern const EulerOrder EulerOrderXZYS;
extern const EulerOrder EulerOrderYZXS;
extern const EulerOrder EulerOrderYXZS;
extern const EulerOrder EulerOrderZXYS;
extern const EulerOrder EulerOrderZYXS;

// Rotating frame of reference, non-inertial reference frame
extern const EulerOrder EulerOrderZYXR;
extern const EulerOrder EulerOrderYZXR;
extern const EulerOrder EulerOrderXZYR;
extern const EulerOrder EulerOrderZXYR;
extern const EulerOrder EulerOrderYXZR;
extern const EulerOrder EulerOrderXYZR;

} // namespace EulerConstants
