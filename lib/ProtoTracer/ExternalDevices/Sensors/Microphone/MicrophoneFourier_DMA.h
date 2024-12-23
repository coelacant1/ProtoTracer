/**
 * @file MicrophoneFourier.h
 * @brief Declares the MicrophoneFourier class for performing FFT on microphone input.
 *
 * This file defines the MicrophoneFourier class, which extends MicrophoneFourierBase to provide
 * functionality for real-time Fast Fourier Transform (FFT) analysis of microphone signals using DMA.
 *
 * @date 22/12/2024
 * @author Bitstream
 */

#pragma once

#include <Arduino.h> ///< Include for Arduino compatibility.
#include <ADC.h> ///< Include for analog-to-digital conversion support.
#include <DMAChannel.h> ///< Include for DMA channel handling.
#include <AnalogBufferDMA.h> ///< Include for DMA-based analog buffer management.
#include "Utils/MicrophoneFourierBase.h" ///< Base class for microphone FFT operations.

/**
 * @class MicrophoneFourier
 * @brief Provides real-time FFT analysis of microphone signals.
 *
 * The MicrophoneFourier class leverages DMA and FFT techniques to analyze microphone input signals
 * in real time. It supports configurable sampling rates, gain control, and signal processing.
 */
class MicrophoneFourier : public MicrophoneFourierBase {
private:
    static const int16_t Hanning256[]; ///< Hanning window coefficients for FFT.

    static bool microphoneGain_50db; ///< Flag to enable or disable 50dB microphone gain.
    static uint8_t gain_pin; ///< Pin number for gain control (if applicable).

    /**
     * @brief Applies a Hanning window to raw FFT data.
     *
     * @param buffer Pointer to the raw FFT data buffer.
     * @param window Pointer to the windowing coefficients.
     */
    static void window_raw_fft_data(void* buffer, const void* window);

    /**
     * @brief Callback function for DMA sampling.
     *
     * @param dma_buffer_instance Instance of the DMA buffer used for sampling.
     * @param adc_num ADC number associated with the sample.
     */
    static void SamplerCallback(AnalogBufferDMA* dma_buffer_instance, int8_t adc_num);

public:
    /**
     * @brief Initializes the microphone and FFT system with basic parameters.
     *
     * @param pin Pin number connected to the microphone output.
     * @param sampleRate Sampling rate in Hz.
     * @param minDB Minimum dB level for normalization.
     * @param maxDB Maximum dB level for normalization.
     */
    static void Initialize(uint8_t pin, uint32_t sampleRate, float minDB, float maxDB);

    /**
     * @brief Initializes the microphone and FFT system with advanced parameters.
     *
     * @param pin Pin number connected to the microphone output.
     * @param gain_pin Pin number for gain control.
     * @param sampleRate Sampling rate in Hz.
     * @param minDB Minimum dB level for normalization.
     * @param maxDB Maximum dB level for normalization.
     * @param microphoneGain_50db Flag to enable or disable 50dB microphone gain.
     */
    static void Initialize(uint8_t pin, uint8_t gain_pin, uint32_t sampleRate, float minDB, float maxDB, bool microphoneGain_50db);

    /**
     * @brief Sets the sampling rate for the microphone.
     *
     * @param sampleRate Sampling rate in Hz.
     */
    static void setSamplingRate(uint32_t sampleRate);

    /**
     * @brief Sets the microphone gain.
     *
     * @param is50db True to enable 50dB gain, false to disable.
     */
    static void setMicGain(bool is50db);

    /**
     * @brief Updates the DMA system to process new samples.
     */
    static void UpdateDMA();
};
