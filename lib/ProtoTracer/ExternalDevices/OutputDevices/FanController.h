/**
 * @file FanController.h
 * @brief Declares the FanController class for managing PWM-based fan speed control.
 *
 * This file defines the FanController class, which provides methods for initializing
 * and controlling a fan using PWM signals, as well as setting speed as a ratio.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h> // Include for Arduino compatibility.
#include "../../Utils/Math/Mathematics.h" // Include for mathematical utilities.

/**
 * @class FanController
 * @brief Manages PWM-based fan speed control.
 *
 * The FanController class provides functionality for initializing a fan, setting its
 * speed using PWM signals, and retrieving the current PWM value.
 */
class FanController {
private:
    uint8_t pin; ///< The pin number connected to the fan's PWM input.
    uint8_t pwm; ///< The current PWM value (0-255).

public:
    /**
     * @brief Constructs a FanController with the specified pin.
     *
     * @param pin The pin number connected to the fan's PWM input.
     */
    FanController(uint8_t pin);

    /**
     * @brief Initializes the fan controller by setting up the pin for PWM output.
     */
    void Initialize();

    /**
     * @brief Sets the PWM value to control the fan speed.
     *
     * @param pwm The PWM value (0-255) to set.
     */
    void SetPWM(uint8_t pwm);

    /**
     * @brief Sets the fan speed as a ratio of its maximum speed.
     *
     * @param ratio A float value between 0.0 and 1.0 representing the speed ratio.
     */
    void SetSpeed(float ratio);

    /**
     * @brief Retrieves the current PWM value.
     *
     * @return The current PWM value (0-255).
     */
    uint8_t GetPWM();
};
