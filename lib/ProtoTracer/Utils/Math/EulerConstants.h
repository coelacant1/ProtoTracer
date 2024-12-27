/**
 * @file EulerConstants.h
 * @brief Provides predefined constants for common Euler rotation orders.
 *
 * The `EulerConstants` namespace defines a collection of commonly used Euler rotation orders,
 * split into static (inertial) and rotating (non-inertial) reference frames.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "EulerOrder.h"
#include "Vector3D.h"

/**
 * @namespace EulerConstants
 * @brief A collection of predefined constants for Euler rotation orders.
 *
 * The `EulerConstants` namespace contains a variety of `EulerOrder` configurations
 * commonly used in 3D rotations. These orders are grouped into two categories:
 * - Static frame of reference (inertial).
 * - Rotating frame of reference (non-inertial).
 */
namespace EulerConstants {

// Static frame of reference, inertial reference frame
extern const EulerOrder EulerOrderXYZS; ///< Order: X → Y → Z, static frame.
extern const EulerOrder EulerOrderXZYS; ///< Order: X → Z → Y, static frame.
extern const EulerOrder EulerOrderYZXS; ///< Order: Y → Z → X, static frame.
extern const EulerOrder EulerOrderYXZS; ///< Order: Y → X → Z, static frame.
extern const EulerOrder EulerOrderZXYS; ///< Order: Z → X → Y, static frame.
extern const EulerOrder EulerOrderZYXS; ///< Order: Z → Y → X, static frame.

// Rotating frame of reference, non-inertial reference frame
extern const EulerOrder EulerOrderZYXR; ///< Order: Z → Y → X, rotating frame.
extern const EulerOrder EulerOrderYZXR; ///< Order: Y → Z → X, rotating frame.
extern const EulerOrder EulerOrderXZYR; ///< Order: X → Z → Y, rotating frame.
extern const EulerOrder EulerOrderZXYR; ///< Order: Z → X → Y, rotating frame.
extern const EulerOrder EulerOrderYXZR; ///< Order: Y → X → Z, rotating frame.
extern const EulerOrder EulerOrderXYZR; ///< Order: X → Y → Z, rotating frame.

} // namespace EulerConstants
