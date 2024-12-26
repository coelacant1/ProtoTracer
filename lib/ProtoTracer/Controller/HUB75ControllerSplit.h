/**
 * @file HUB75ControllerSplit.h
 * @brief Declares the HUB75ControllerSplit class for managing HUB75 LED matrices and secondary LED displays.
 *
 * This file defines the HUB75ControllerSplit class, which extends the Controller base class.
 * It provides functionality for controlling and displaying content on HUB75 LED matrices
 * and managing secondary LED strips or displays for accent lighting.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <stdint.h> // Include for fixed-width integer types.
#include "Controller.h" // Include for base controller functionality.
#include "SmartMatrixHUB75.h" // Include for HUB75-specific matrix utilities.
#include "../Camera/CameraManager/CameraManager.h" // Include for camera management.
#include "../Camera/Pixels/PixelGroup.h" // Include for pixel group management.

/**
 * @class HUB75ControllerSplit
 * @brief Manages HUB75 LED matrices and secondary LED displays or strips.
 *
 * The HUB75ControllerSplit class extends the Controller base class to provide specific
 * functionality for initializing, controlling, and displaying content on HUB75 LED matrices
 * and managing secondary accent displays or LED strips.
 */
class HUB75ControllerSplit : public Controller {
public:
    /**
     * @brief Constructs a HUB75ControllerSplit with specified parameters.
     *
     * @param cameras Pointer to the CameraManager for managing camera data.
     * @param maxBrightness Maximum brightness for the main HUB75 LED matrix.
     * @param maxAccentBrightness Maximum brightness for the secondary LED strip or display.
     */
    HUB75ControllerSplit(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness);

    /**
     * @brief Initializes the HUB75ControllerSplit and sets up the displays.
     */
    void Initialize() override;

    /**
     * @brief Updates and displays the content on the main and secondary displays.
     */
    void Display() override;

    /**
     * @brief Sets the maximum brightness of the main HUB75 LED matrix.
     *
     * @param maxBrightness The maximum brightness value (0-255).
     */
    void SetBrightness(uint8_t maxBrightness);

    /**
     * @brief Sets the maximum brightness of the secondary LED strip or display.
     *
     * @param maxAccentBrightness The maximum brightness value (0-255).
     */
    void SetAccentBrightness(uint8_t maxAccentBrightness);
};
