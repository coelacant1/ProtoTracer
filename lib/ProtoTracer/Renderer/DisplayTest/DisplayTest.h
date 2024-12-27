/**
 * @file DisplayTest.h
 * @brief Defines the DisplayTest class for testing camera displays with various patterns.
 *
 * The DisplayTest class provides static methods for generating test patterns such as
 * filling the display with white or alternating white and black pixels.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../Camera/Camera.h"
#include "../../Scene/Scene.h"

/**
 * @class DisplayTest
 * @brief Provides static methods for testing and verifying camera displays.
 */
class DisplayTest {
public:
    /**
     * @brief Fills the camera display entirely with white pixels.
     * @param camera Pointer to the CameraBase object representing the camera.
     */
    static void FillWhite(CameraBase* camera);

    /**
     * @brief Fills the camera display with an alternating pattern of white and black pixels.
     * @param camera Pointer to the CameraBase object representing the camera.
     */
    static void FillAltWhiteBlack(CameraBase* camera);
};
