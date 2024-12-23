/**
 * @file Camera.h
 * @brief Declares the Camera template class for managing camera behavior and pixel groups.
 *
 * This file defines the Camera class, which extends CameraBase to provide functionality
 * for camera operations and managing associated PixelGroup instances.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "CameraBase.h" ///< Include for base camera functionality.
#include "Pixels/PixelGroup.h" ///< Include for pixel group management.

/**
 * @class Camera
 * @brief Manages camera behavior and pixel groups.
 *
 * The Camera class extends CameraBase and incorporates pixel group handling, allowing
 * for advanced camera operations, including retrieving pixel data and coordinate transformations.
 *
 * @tparam pixelCount The total number of pixels managed by the camera.
 */
template<size_t pixelCount>
class Camera : public CameraBase {
private:
    PixelGroup<pixelCount>* pixelGroup; ///< Pointer to the associated PixelGroup instance.
    Vector2D maxC; ///< Cached maximum coordinate of the camera.
    Vector2D minC; ///< Cached minimum coordinate of the camera.
    bool calculatedMax = false; ///< Indicates if the maximum coordinate has been calculated.
    bool calculatedMin = false; ///< Indicates if the minimum coordinate has been calculated.

public:
    /**
     * @brief Constructs a Camera with a transform and pixel group.
     *
     * @param transform Pointer to the Transform associated with the camera.
     * @param pixelGroup Pointer to the PixelGroup associated with the camera.
     */
    Camera(Transform* transform, PixelGroup<pixelCount>* pixelGroup);

    /**
     * @brief Constructs a Camera with a transform, camera layout, and pixel group.
     *
     * @param transform Pointer to the Transform associated with the camera.
     * @param cameraLayout Pointer to the CameraLayout for the camera.
     * @param pixelGroup Pointer to the PixelGroup associated with the camera.
     */
    Camera(Transform* transform, CameraLayout* cameraLayout, PixelGroup<pixelCount>* pixelGroup);

    /**
     * @brief Retrieves the associated PixelGroup.
     *
     * @return Pointer to the PixelGroup.
     */
    PixelGroup<pixelCount>* GetPixelGroup() override;

    /**
     * @brief Retrieves the minimum coordinate of the camera.
     *
     * @return The minimum coordinate as a Vector2D.
     */
    Vector2D GetCameraMinCoordinate() override;

    /**
     * @brief Retrieves the maximum coordinate of the camera.
     *
     * @return The maximum coordinate as a Vector2D.
     */
    Vector2D GetCameraMaxCoordinate() override;

    /**
     * @brief Retrieves the center coordinate of the camera.
     *
     * @return The center coordinate as a Vector2D.
     */
    Vector2D GetCameraCenterCoordinate() override;

    /**
     * @brief Retrieves the minimum transform of the camera.
     *
     * @return The minimum transform as a Vector3D.
     */
    Vector3D GetCameraTransformMin() override;

    /**
     * @brief Retrieves the maximum transform of the camera.
     *
     * @return The maximum transform as a Vector3D.
     */
    Vector3D GetCameraTransformMax() override;

    /**
     * @brief Retrieves the center transform of the camera.
     *
     * @return The center transform as a Vector3D.
     */
    Vector3D GetCameraTransformCenter() override;
};

#include "Camera.tpp" ///< Include the template implementation.