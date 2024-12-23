/**
 * @file CameraBase.h
 * @brief Declares the CameraBase class for defining camera functionality.
 *
 * This file defines the CameraBase class, which serves as a base class for managing
 * camera transformations, layouts, and pixel groups in 2D or 3D space.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "CameraLayout.h" ///< Include for camera layout management.
#include "Pixels/IPixelGroup.h" ///< Include for pixel group interface.
#include "../Utils/Math/Transform.h" ///< Include for transformation utilities.

/**
 * @class CameraBase
 * @brief Base class for managing camera properties and transformations.
 *
 * The CameraBase class provides an abstract interface for camera operations,
 * including retrieving camera bounds and transformations, and managing associated
 * pixel groups.
 */
class CameraBase {
protected:
    Transform* transform; ///< Pointer to the camera's transformation data.
    CameraLayout* cameraLayout; ///< Pointer to the camera's layout information.
    Quaternion lookOffset; ///< Look offset for the camera's orientation.
    bool is2D = false; ///< Flag indicating whether the camera operates in 2D mode.

public:
    /**
     * @brief Default constructor.
     */
    CameraBase();

    /**
     * @brief Retrieves the minimum coordinate of the camera in 2D space.
     *
     * @return The minimum coordinate as a Vector2D.
     */
    virtual Vector2D GetCameraMinCoordinate() = 0;

    /**
     * @brief Retrieves the maximum coordinate of the camera in 2D space.
     *
     * @return The maximum coordinate as a Vector2D.
     */
    virtual Vector2D GetCameraMaxCoordinate() = 0;

    /**
     * @brief Retrieves the center coordinate of the camera in 2D space.
     *
     * @return The center coordinate as a Vector2D.
     */
    virtual Vector2D GetCameraCenterCoordinate() = 0;

    /**
     * @brief Retrieves the minimum transform of the camera in 3D space.
     *
     * @return The minimum transform as a Vector3D.
     */
    virtual Vector3D GetCameraTransformMin() = 0;

    /**
     * @brief Retrieves the maximum transform of the camera in 3D space.
     *
     * @return The maximum transform as a Vector3D.
     */
    virtual Vector3D GetCameraTransformMax() = 0;

    /**
     * @brief Retrieves the center transform of the camera in 3D space.
     *
     * @return The center transform as a Vector3D.
     */
    virtual Vector3D GetCameraTransformCenter() = 0;

    /**
     * @brief Retrieves the associated pixel group.
     *
     * @return Pointer to the IPixelGroup interface.
     */
    virtual IPixelGroup* GetPixelGroup() = 0;

    /**
     * @brief Retrieves the camera's layout.
     *
     * @return Pointer to the CameraLayout.
     */
    CameraLayout* GetCameraLayout();

    /**
     * @brief Retrieves the camera's transformation data.
     *
     * @return Pointer to the Transform object.
     */
    Transform* GetTransform();

    /**
     * @brief Checks if the camera operates in 2D mode.
     *
     * @return True if the camera is in 2D mode, otherwise false.
     */
    bool Is2D();

    /**
     * @brief Sets the camera's 2D mode.
     *
     * @param is2D True to enable 2D mode, otherwise false.
     */
    void Set2D(bool is2D);

    /**
     * @brief Sets the camera's look offset.
     *
     * @param lookOffset The new look offset as a Quaternion.
     */
    void SetLookOffset(Quaternion lookOffset);

    /**
     * @brief Retrieves the camera's look offset.
     *
     * @return The look offset as a Quaternion.
     */
    Quaternion GetLookOffset();
};
