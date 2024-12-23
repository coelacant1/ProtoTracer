/**
 * @file APDS9960.h
 * @brief A class for interfacing with the Adafruit APDS9960 sensor.
 *
 * This file defines the APDS9960 class, which provides functionality for detecting proximity,
 * brightness, and determining if the sensor is "booped" (close proximity detection).
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h> ///< Include for Arduino compatibility.
#include <Wire.h> ///< Include for I2C communication.
#include <Adafruit_APDS9960.h> ///< Include for Adafruit APDS9960 sensor library.
#include "../../Utils/Filter/MinFilter.h" ///< Include for minimum filtering.
#include "../../Utils/Time/TimeStep.h" ///< Include for timing utilities.

/**
 * @class APDS9960
 * @brief A class for managing the Adafruit APDS9960 sensor.
 *
 * The APDS9960 class provides methods for initializing the sensor, detecting proximity and brightness,
 * and determining if the sensor is close enough to trigger a "boop" detection.
 */
class APDS9960 {
private:
    static Adafruit_APDS9960 apds; ///< Instance of the Adafruit APDS9960 sensor.
    static uint16_t proximity; ///< Current proximity value.
    static uint16_t threshold; ///< Threshold value for proximity detection.
    static MinFilter<10> minF; ///< Minimum filter for smoothing proximity values.
    static TimeStep timeStep; ///< Time utility for managing timing intervals.
    static float minimum; ///< Minimum detected value.
    static bool didBegin; ///< Flag indicating if the sensor has been initialized.
    static bool isBright; ///< Flag indicating if brightness detection is enabled.
    static bool isProx; ///< Flag indicating if proximity detection is enabled.

public:
    /**
     * @brief Initializes the APDS9960 sensor.
     *
     * @param threshold The threshold for proximity detection.
     * @return True if initialization is successful, false otherwise.
     */
    static bool Initialize(uint8_t threshold);

    /**
     * @brief Checks if the sensor is "booped" (close proximity detected).
     *
     * @return True if the sensor is booped, false otherwise.
     */
    static bool isBooped();

    /**
     * @brief Resets the I2C bus in case of communication issues.
     */
    static void ResetI2CBus();

    /**
     * @brief Retrieves the current proximity value.
     *
     * @return The current proximity value as an 8-bit integer.
     */
    static uint8_t GetValue();

    /**
     * @brief Retrieves the current brightness value.
     *
     * @return The current brightness value as a 16-bit integer.
     */
    static uint16_t GetBrightness();
};
