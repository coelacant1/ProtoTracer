/**
 * @file APA102Controller.h
 * @brief Declares the APA102Controller class for managing APA102 LED strips.
 *
 * This file defines the APA102Controller class, which extends the Controller base class.
 * It provides functionality for controlling and displaying content on APA102 LED strips.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <stdint.h> // Include for fixed-width integer types.
#include "Controller.h" // Include for base controller functionality.
#include "SmartMatrixAPA102.h" // Include for APA102-specific matrix utilities.
#include "../Camera/CameraManager/CameraManager.h" // Include for camera management.
#include "../Camera/Pixels/PixelGroup.h" // Include for pixel group management.

/**
 * @class APA102Controller
 * @brief Manages APA102 LED strips with camera integration.
 *
 * The APA102Controller class extends the Controller base class to provide specific
 * functionality for initializing, controlling, and displaying content on APA102 LED strips.
 */
class APA102Controller : public Controller {
public:
    /**
     * @brief Constructs an APA102Controller with specified parameters.
     *
     * @param cameras Pointer to the CameraManager for managing camera data.
     * @param maxBrightness Maximum brightness for the LED strips.
     * @param maxAccentBrightness Maximum brightness for accent lighting.
     */
    APA102Controller(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness);

    /**
     * @brief Initializes the APA102Controller and sets up the LED strip.
     */
    void Initialize() override;

    /**
     * @brief Updates and displays the content on the LED strip.
     */
    void Display() override;

    /**
     * @brief Sets the maximum brightness of the LED strip.
     *
     * @param maxBrightness The maximum brightness value (0-255).
     */
    void SetBrightness(uint8_t maxBrightness) override;

    /**
     * @brief Sets the maximum accent brightness of the LED strip.
     *
     * @param maxAccentBrightness The maximum accent brightness value (0-255).
     */
    void SetAccentBrightness(uint8_t maxAccentBrightness) override;
};
