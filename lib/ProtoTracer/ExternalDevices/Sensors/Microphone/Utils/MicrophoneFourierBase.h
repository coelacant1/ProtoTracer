/**
 * @file MicrophoneFourierBase.h
 * @brief Provides a base class for FFT-based microphone signal processing.
 *
 * This file defines the MicrophoneFourierBase class, offering foundational functionality
 * for performing Fast Fourier Transform (FFT) on microphone input signals. It includes
 * methods for retrieving FFT results and managing microphone signal data.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h> ///< Include for Arduino compatibility.
#include "../../../../Utils/Filter/DerivativeFilter.h" ///< Include for derivative filtering.
#include "../../../../Utils/Filter/FFTFilter.h" ///< Include for FFT-based filtering.
#include "../../../../Utils/Time/TimeStep.h" ///< Include for time management.
#include "../../../../Utils/Signals/FFT.h" ///< Include for FFT processing.

/**
 * @class MicrophoneFourierBase
 * @brief Base class for FFT-based microphone signal processing.
 *
 * The MicrophoneFourierBase class provides foundational support for microphone signal processing,
 * including FFT transformations, signal normalization, and filtering. Derived classes can extend
 * its functionality for specific applications.
 */
class MicrophoneFourierBase {
protected:
    static const uint16_t FFTSize = 256; ///< Size of the FFT (number of samples).
    static const uint16_t OutputBins = 128; ///< Number of output bins from FFT processing.
    static uint16_t sampleRate; ///< Sampling rate in Hz.
    static uint8_t pin; ///< Pin number for microphone input.
    static float minDB; ///< Minimum decibel value for normalization.
    static float maxDB; ///< Maximum decibel value for normalization.
    static float threshold; ///< Threshold value for processing.
    static float currentValue; ///< Current magnitude of the microphone signal.
    static bool isInitialized; ///< Flag indicating if the system is initialized.

    static DerivativeFilter peakFilterRate; ///< Filter for peak rate detection.

    static float inputSamp[FFTSize * 2]; ///< Raw input samples for FFT.
    static float inputStorage[FFTSize]; ///< Storage for processed input samples.
    static float outputMagn[FFTSize]; ///< Magnitude output from FFT.
    static float outputData[OutputBins]; ///< Processed FFT data for output bins.
    static float outputDataFilt[OutputBins]; ///< Filtered FFT data for output bins.
    static FFTFilter fftFilters[OutputBins]; ///< Array of FFT filters for post-processing.

    static FFT<FFTSize> fft; ///< FFT processor instance.

public:
    /**
     * @brief Calculates the average magnitude of the specified FFT bins.
     *
     * @param binL The lower bound of the bin range (inclusive).
     * @param binH The upper bound of the bin range (inclusive).
     * @return The average magnitude within the specified range.
     */
    static float AverageMagnitude(uint16_t binL, uint16_t binH);

    /**
     * @brief Checks if the microphone system is initialized.
     *
     * @return True if initialized, false otherwise.
     */
    static bool IsInitialized();

    /**
     * @brief Retrieves the current sampling rate.
     *
     * @return The sampling rate in Hz.
     */
    static float GetSampleRate();

    /**
     * @brief Retrieves the raw input samples.
     *
     * @return Pointer to the array of raw input samples.
     */
    static float* GetSamples();

    /**
     * @brief Retrieves the FFT output data.
     *
     * @return Pointer to the array of FFT output data.
     */
    static float* GetFourier();

    /**
     * @brief Retrieves the filtered FFT output data.
     *
     * @return Pointer to the array of filtered FFT output data.
     */
    static float* GetFourierFiltered();

    /**
     * @brief Retrieves the current signal magnitude.
     *
     * @return The current magnitude value.
     */
    static float GetCurrentMagnitude();
};
