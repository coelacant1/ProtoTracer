/**
 * @file TimeStep.h
 * @brief Utility class for timing operations based on a set frequency.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h>

/**
 * @class TimeStep
 * @brief Provides a mechanism to trigger actions at a specified frequency.
 */
class TimeStep {
private:
    unsigned long previousMillis; ///< Stores the last recorded time in milliseconds.
    uint16_t updateInterval;      ///< Interval in milliseconds between updates.

public:
    /**
     * @brief Constructor to initialize TimeStep with a frequency.
     * @param frequency The frequency in Hz.
     */
    TimeStep(float frequency);

    /**
     * @brief Sets the frequency for the TimeStep.
     * @param frequency The new frequency in Hz.
     */
    void SetFrequency(float frequency);

    /**
     * @brief Checks if the specified time interval has elapsed.
     * @return True if the interval has elapsed, otherwise false.
     */
    bool IsReady();
};
