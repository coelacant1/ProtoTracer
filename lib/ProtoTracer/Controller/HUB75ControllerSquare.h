/**
 * @file HUB75ControllerSquare.h
 * @brief Declares the HUB75ControllerSquare class for managing a square display using two vertical HUB75 panels.
 *
 * This file defines the HUB75ControllerSquare class, which extends the Controller base class.
 * It provides functionality for combining two vertical HUB75 panels into a single square display
 * and managing brightness and content display.
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
 * @class HUB75ControllerSquare
 * @brief Manages a square display composed of two vertical HUB75 panels.
 *
 * The HUB75ControllerSquare class extends the Controller base class to provide specific
 * functionality for initializing, controlling, and displaying content on a square display
 * created by combining two vertical HUB75 panels.
 */
class HUB75ControllerSquare : public Controller {
public:
    /**
     * @brief Constructs a HUB75ControllerSquare with specified parameters.
     *
     * @param cameras Pointer to the CameraManager for managing camera data.
     * @param maxBrightness Maximum brightness for the square display.
     * @param maxAccentBrightness Maximum brightness for any secondary accent lighting.
     */
    HUB75ControllerSquare(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness);

    /**
     * @brief Initializes the HUB75ControllerSquare and sets up the square display.
     */
    void Initialize() override;

    /**
     * @brief Updates and displays the content on the square display.
     */
    void Display() override;

    /**
     * @brief Sets the maximum brightness of the square display.
     *
     * @param maxBrightness The maximum brightness value (0-255).
     */
    void SetBrightness(uint8_t maxBrightness) override;

    /**
     * @brief Sets the maximum brightness for any secondary accent lighting.
     *
     * @param maxAccentBrightness The maximum brightness value (0-255).
     */
    void SetAccentBrightness(uint8_t maxAccentBrightness) override;
};