/**
 * @file MicrophoneSimple.h
 * @brief A simple microphone processing class for analog input.
 *
 * This file defines the MicrophoneSimple class, which provides basic functionality
 * for reading and processing microphone signals, including filtering for noise reduction.
 * 
 * For the SPW2430 microphone
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h> ///< Include for Arduino compatibility.
#include "../../../Utils/Math/Mathematics.h" ///< Include for mathematical utilities.
#include "../../../Utils/Filter/RunningAverageFilter.h" ///< Include for running average filtering.
#include "../../../Utils/Filter/MinFilter.h" ///< Include for minimum filtering.

/**
 * @class MicrophoneSimple
 * @brief A simple class for processing microphone signals.
 *
 * The MicrophoneSimple class handles analog input from a microphone,
 * applies smoothing filters, and provides processed signal values.
 */
class MicrophoneSimple {
private:
    uint8_t pin; ///< Pin number for the microphone input.
    RunningAverageFilter<40> mv = RunningAverageFilter<40>(0.075f); ///< Moving average filter for smoothing input.
    MinFilter<100> minF = MinFilter<100>(); ///< Minimum filter for peak detection.
    RunningAverageFilter<10> output = RunningAverageFilter<10>(0.1f); ///< Filter for smoothing the output.
    float previousReading = 0.0f; ///< Previous reading from the microphone.
    long previousMillis = 0; ///< Time of the previous reading.
    long startMillis = 0; ///< Start time for processing.

public:
    /**
     * @brief Constructs a MicrophoneSimple instance with a specified pin.
     *
     * @param pin The pin number for the microphone input.
     */
    MicrophoneSimple(uint8_t pin);

    /**
     * @brief Updates the microphone reading and processes the signal.
     *
     * @return The processed microphone value.
     */
    float Update();
};
