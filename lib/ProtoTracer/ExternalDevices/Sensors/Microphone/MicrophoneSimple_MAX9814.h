/**
 * @file MicrophoneSimple_MAX9814.h
 * @brief A simple microphone processing class for analog input.
 *
 * This file defines the MicrophoneSimple class, which provides basic functionality
 * for reading and processing microphone signals, including gain adjustment,
 * clipping, and filtering.
 *
 * For the MAX9814 microphone.
 * 
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h> // Include for Arduino compatibility.
#include "../../../Utils/Math/Mathematics.h" // Include for mathematical utilities.
#include "../../../Utils/Filter/RunningAverageFilter.h" // Include for running average filtering.
#include "../../../Utils/Filter/MinFilter.h" // Include for minimum filtering.

/**
 * @class MicrophoneSimple
 * @brief A simple class for processing microphone signals.
 *
 * The MicrophoneSimple class handles analog input from a microphone,
 * applies gain and clipping, and uses filters to smooth the output.
 */
class MicrophoneSimple {
private:
    uint8_t pin; ///< Pin number for the microphone input.
    RunningAverageFilter<5> mv = RunningAverageFilter<5>(0.2f); ///< Moving average filter for smoothing input.
    MinFilter<100> minF = MinFilter<100>(); ///< Minimum filter for peak detection.
    RunningAverageFilter<5> output = RunningAverageFilter<5>(0.2f); ///< Filter for smoothing the output.
    float previousReading = 0.0f; ///< Previous reading from the microphone.
    float gain = 1.0f; ///< Gain applied to the microphone signal.
    float clipping = 1.0f; ///< Clipping level for the microphone signal.
    long previousMillis = 0; ///< Time of the previous reading.
    long startMillis = 0; ///< Start time for processing.
    float currentValue = 0.0f; ///< Current processed microphone value.

public:
    /**
     * @brief Constructs a default MicrophoneSimple instance.
     */
    MicrophoneSimple();

    /**
     * @brief Constructs a MicrophoneSimple instance with specified parameters.
     *
     * @param pin The pin number for the microphone input.
     * @param gain The gain to apply to the microphone signal (default is 1.0).
     * @param clipping The clipping level for the microphone signal (default is 1.0).
     */
    MicrophoneSimple(uint8_t pin, float gain = 1.0f, float clipping = 1.0f);

    /**
     * @brief Retrieves the current processed microphone value.
     *
     * @return The current value of the microphone signal.
     */
    float GetCurrentValue();

    /**
     * @brief Updates the microphone reading and processes the signal.
     *
     * @return The processed microphone value.
     */
    float Update();

    /**
     * @brief Updates the microphone reading with an externally provided value.
     *
     * @param read The external reading to process.
     * @return The processed microphone value.
     */
    float Update(float read);
};
