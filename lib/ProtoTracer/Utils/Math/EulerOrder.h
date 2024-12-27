/**
 * @file EulerOrder.h
 * @brief Defines the EulerOrder class for specifying rotation orders in 3D space.
 *
 * The EulerOrder class allows for flexible specification of the order of axes used
 * in rotations, along with the frame of reference (static or rotating).
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Vector3D.h"

/**
 * @class EulerOrder
 * @brief Specifies the order and frame of reference for Euler rotations.
 *
 * The `EulerOrder` class provides a way to define the sequence of axes
 * for performing rotations in 3D space. It also differentiates between
 * static and rotating reference frames.
 */
class EulerOrder {
public:
    /**
     * @enum Axis
     * @brief Enumeration of possible axis orders for rotations.
     *
     * - `XYZ`: Rotate about X, then Y, then Z.
     * - `XZY`: Rotate about X, then Z, then Y.
     * - `YXZ`: Rotate about Y, then X, then Z.
     * - `YZX`: Rotate about Y, then Z, then X.
     * - `ZXY`: Rotate about Z, then X, then Y.
     * - `ZYX`: Rotate about Z, then Y, then X.
     */
    enum Axis {
        XYZ, ///< X → Y → Z rotation order.
        XZY, ///< X → Z → Y rotation order.
        YXZ, ///< Y → X → Z rotation order.
        YZX, ///< Y → Z → X rotation order.
        ZXY, ///< Z → X → Y rotation order.
        ZYX  ///< Z → Y → X rotation order.
    };

    /**
     * @enum AxisFrame
     * @brief Enumeration of possible reference frames for rotations.
     *
     * - `Static`: Rotations are applied relative to a static (inertial) frame.
     * - `Rotating`: Rotations are applied relative to a rotating (non-inertial) frame.
     */
    enum AxisFrame {
        Static,   ///< Rotations relative to a static frame.
        Rotating  ///< Rotations relative to a rotating frame.
    };

    Axis AxisOrder;       ///< The sequence of axes for the rotation order.
    AxisFrame FrameTaken; ///< The frame of reference (static or rotating).
    Vector3D Permutation; ///< Permutation vector for axis reordering.

    /**
     * @brief Default constructor.
     *
     * Creates an `EulerOrder` object with default values.
     */
    EulerOrder();

    /**
     * @brief Parameterized constructor.
     *
     * Initializes an `EulerOrder` object with the specified axis order, frame, and permutation.
     *
     * @param axisOrder The sequence of axes for the rotation order.
     * @param axisFrame The frame of reference (static or rotating).
     * @param permutation The permutation vector for axis reordering.
     */
    EulerOrder(Axis axisOrder, AxisFrame axisFrame, Vector3D permutation);

    /**
     * @brief Converts the EulerOrder object to a string representation.
     *
     * @return A string describing the axis order, frame, and permutation.
     */
    String ToString();
};
