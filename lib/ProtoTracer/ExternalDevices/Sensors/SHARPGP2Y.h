/**
 * @file SHARPGP2Y.h
 * @brief A class for interfacing with the SHARP GP2Y distance sensor.
 *
 * This file defines the SHARPGP2Y class, which provides methods for initializing and retrieving
 * distance measurements from the SHARP GP2Y sensor using a running average filter for smoothing.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h> // Include for Arduino compatibility.
#include "../../Utils/Filter/RunningAverageFilter.h" // Include for running average filtering.

/**
 * @class SHARPGP2Y
 * @brief A class for managing the SHARP GP2Y distance sensor.
 *
 * The SHARPGP2Y class provides methods for reading distance measurements from the sensor and
 * applying filtering for noise reduction.
 */
class SHARPGP2Y {
private:
    RunningAverageFilter<25> rAF = RunningAverageFilter<25>(0.1f); ///< Running average filter for smoothing sensor readings.
    float distance = 0.0f; ///< Current distance measurement.
    uint8_t pin; ///< Analog pin connected to the sensor.

    /**
     * @brief Converts a raw sensor reading to a distance value.
     *
     * @param reading The raw analog reading from the sensor.
     * @return The calculated distance in appropriate units (e.g., cm).
     */
    float ReadingToDistance(uint8_t reading);

public:
    /**
     * @brief Constructs a SHARPGP2Y instance with the specified pin.
     *
     * @param pin The analog pin connected to the SHARP GP2Y sensor.
     */
    SHARPGP2Y(uint8_t pin);

    /**
     * @brief Retrieves the current distance measurement.
     *
     * @return The current distance as a float.
     */
    float GetDistance();

    /**
     * @brief Updates the distance measurement by reading the sensor.
     *
     * @return The updated distance as a float.
     */
    float Update();
};