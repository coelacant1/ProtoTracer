/**
 * @file CameraLayout.h
 * @brief Declares the CameraLayout class for managing camera orientation and axis alignment.
 *
 * This file defines the CameraLayout class, which provides functionality for configuring
 * camera orientation based on forward and up axes, and calculates the necessary transformations.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../Utils/Math/Transform.h" // Include for mathematical transformations.

/**
 * @class CameraLayout
 * @brief Manages camera orientation and axis alignment.
 *
 * The CameraLayout class defines the camera's orientation using forward and up axes.
 * It provides methods for retrieving orientation vectors and rotation information.
 */
class CameraLayout {
public:
    /**
     * @enum ForwardAxis
     * @brief Defines possible forward axes for the camera.
     */
    enum ForwardAxis {
        XForward,  ///< Forward along the positive X-axis.
        YForward,  ///< Forward along the positive Y-axis.
        ZForward,  ///< Forward along the positive Z-axis.
        XNForward, ///< Forward along the negative X-axis.
        YNForward, ///< Forward along the negative Y-axis.
        ZNForward  ///< Forward along the negative Z-axis.
    };

    /**
     * @enum UpAxis
     * @brief Defines possible up axes for the camera.
     */
    enum UpAxis {
        XUp,  ///< Up along the positive X-axis.
        YUp,  ///< Up along the positive Y-axis.
        ZUp,  ///< Up along the positive Z-axis.
        XNUp, ///< Up along the negative X-axis.
        YNUp, ///< Up along the negative Y-axis.
        ZNUp  ///< Up along the negative Z-axis.
    };

private:
    Quaternion rotation; ///< Rotation representing the camera's orientation.
    ForwardAxis forwardAxis; ///< The camera's forward axis.
    UpAxis upAxis; ///< The camera's up axis.

    /**
     * @brief Verifies the validity of the camera's transformation.
     *
     * @return True if the transformation is valid, otherwise false.
     */
    bool VerifyTransform();

    /**
     * @brief Calculates the camera's transformation based on its axes.
     */
    void CalculateTransform();

public:
    /**
     * @brief Constructs a CameraLayout with specified forward and up axes.
     *
     * @param forwardAxis The forward axis of the camera.
     * @param upAxis The up axis of the camera.
     */
    CameraLayout(ForwardAxis forwardAxis, UpAxis upAxis);

    /**
     * @brief Retrieves the camera's forward axis.
     *
     * @return The camera's forward axis.
     */
    ForwardAxis GetForwardAxis();

    /**
     * @brief Retrieves the camera's up axis.
     *
     * @return The camera's up axis.
     */
    UpAxis GetUpAxis();

    /**
     * @brief Retrieves the camera's forward vector.
     *
     * @return The forward vector as a Vector3D.
     */
    Vector3D GetForwardVector();

    /**
     * @brief Retrieves the camera's up vector.
     *
     * @return The up vector as a Vector3D.
     */
    Vector3D GetUpVector();

    /**
     * @brief Retrieves the camera's rotation.
     *
     * @return The rotation as a Quaternion.
     */
    Quaternion GetRotation();
};
