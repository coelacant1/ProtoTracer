/**
 * @file Controller.h
 * @brief Declares the Controller base class for managing lighting controllers.
 *
 * This file defines the Controller class, which serves as a base class for
 * managing brightness and display operations for various lighting controllers.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h> ///< Include for Arduino compatibility.
#include "../Utils/Math/Mathematics.h" ///< Include for mathematical utilities.
#include "../Camera/CameraManager/CameraManager.h" ///< Include for camera management.

/**
 * @class Controller
 * @brief Base class for managing brightness and display operations of lighting controllers.
 *
 * The Controller class provides an abstract interface and shared functionality
 * for managing lighting systems, including brightness adjustment and display updates.
 */
class Controller {
private:
    const uint32_t softStart = 5000000; ///< Duration for soft start in microseconds.
    uint32_t previousTime; ///< Tracks the last update time.

protected:
    CameraManager* cameras; ///< Pointer to the CameraManager for managing camera data.
    uint8_t brightness; ///< Current brightness level.
    uint8_t accentBrightness; ///< Current accent brightness level.
    uint8_t maxBrightness; ///< Maximum allowed brightness level.
    uint8_t maxAccentBrightness; ///< Maximum allowed accent brightness level.
    bool isOn = false; ///< Indicates if the controller is active.
    bool startTime = false; ///< Indicates if the start time has been recorded.

    /**
     * @brief Constructs a Controller with specified parameters.
     *
     * @param cameras Pointer to the CameraManager.
     * @param maxBrightness Maximum brightness for the controller.
     * @param maxAccentBrightness Maximum accent brightness for the controller.
     */
    Controller(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness);

    /**
     * @brief Updates the brightness based on internal logic.
     */
    void UpdateBrightness();

public:
    /**
     * @brief Initializes the controller.
     */
    virtual void Initialize() = 0;

    /**
     * @brief Updates and displays content on the lighting system.
     */
    virtual void Display() = 0;

    /**
     * @brief Retrieves the current brightness level.
     *
     * @return The current brightness as an 8-bit value.
     */
    uint8_t GetBrightness();

    /**
     * @brief Retrieves the current accent brightness level.
     *
     * @return The current accent brightness as an 8-bit value.
     */
    uint8_t GetAccentBrightness();

    /**
     * @brief Sets the maximum brightness for the controller.
     *
     * @param maxBrightness The maximum brightness value (0-255).
     */
    virtual void SetBrightness(uint8_t maxBrightness) = 0;

    /**
     * @brief Sets the maximum accent brightness for the controller.
     *
     * @param maxAccentBrightness The maximum accent brightness value (0-255). This is the secondary display if available.
     */
    virtual void SetAccentBrightness(uint8_t maxAccentBrightness) = 0;
};