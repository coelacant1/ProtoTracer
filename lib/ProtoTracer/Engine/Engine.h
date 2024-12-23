/**
 * @file RenderingEngine.h
 * @brief Declares the RenderingEngine class for rendering and display operations.
 *
 * This file defines the RenderingEngine class, which provides static methods
 * for rasterizing scenes and managing display operations, such as rendering a white fill.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../Camera/CameraManager/CameraManager.h" ///< Include for camera management.
#include "../Scene/Scene.h" ///< Include for scene management.
#include "../Renderer/Rasterizer/Rasterizer.h" ///< Include for rasterization operations.
#include "../Renderer/DisplayTest/DisplayTest.h" ///< Include for display test utilities.

/**
 * @class RenderingEngine
 * @brief Provides static methods for rendering and display operations.
 *
 * The RenderingEngine class offers functionality for rasterizing scenes using cameras
 * and managing display operations such as filling the screen with a white color.
 */
class RenderingEngine {
public:
    /**
     * @brief Rasterizes the given scene using the cameras managed by the CameraManager.
     *
     * This method iterates through all cameras in the CameraManager and rasterizes the scene
     * for each camera. If the scene includes a post-processing effect, it applies the effect
     * to the corresponding pixel group.
     *
     * @param scene Pointer to the Scene to be rasterized.
     * @param cameraManager Pointer to the CameraManager managing the cameras.
     */
    static void Rasterize(Scene* scene, CameraManager* cameraManager);

    /**
     * @brief Fills the display with white for all cameras in the CameraManager.
     *
     * This method iterates through all cameras in the CameraManager and fills their displays
     * with white using the DisplayTest utility.
     *
     * @param cameraManager Pointer to the CameraManager managing the cameras.
     */
    static void DisplayWhite(CameraManager* cameraManager);
};
