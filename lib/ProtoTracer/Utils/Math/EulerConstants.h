#pragma once

#include "EulerOrder.h"
#include "Vector3D.h"

namespace EulerConstants {

// Static frame of reference, inertial reference frame
extern const EulerOrder EulerOrderXYZS;
extern const EulerOrder EulerOrderXYXS;
extern const EulerOrder EulerOrderXZYS;
extern const EulerOrder EulerOrderXZXS;
extern const EulerOrder EulerOrderYZXS;
extern const EulerOrder EulerOrderYZYS;
extern const EulerOrder EulerOrderYXZS;
extern const EulerOrder EulerOrderYXYS;
extern const EulerOrder EulerOrderZXYS;
extern const EulerOrder EulerOrderZXZS;
extern const EulerOrder EulerOrderZYXS;
extern const EulerOrder EulerOrderZYZS;

// Rotating frame of reference, non-inertial reference frame
extern const EulerOrder EulerOrderZYXR;
extern const EulerOrder EulerOrderXYXR;
extern const EulerOrder EulerOrderYZXR;
extern const EulerOrder EulerOrderXZXR;
extern const EulerOrder EulerOrderXZYR;
extern const EulerOrder EulerOrderYZYR;
extern const EulerOrder EulerOrderZXYR;
extern const EulerOrder EulerOrderYXYR;
extern const EulerOrder EulerOrderYXZR;
extern const EulerOrder EulerOrderZXZR;
extern const EulerOrder EulerOrderXYZR;
extern const EulerOrder EulerOrderZYZR;

} // namespace EulerConstants
