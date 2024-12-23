/**
 * @file FFTVoiceDetection.h
 * @brief Declares the FFTVoiceDetection template class for real-time viseme detection based on FFT data.
 *
 * This file defines the FFTVoiceDetection class, which extends the Viseme class to provide functionality
 * for detecting mouth shapes (visemes) based on formant frequencies extracted from FFT analysis of voice signals.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../../../../Utils/Filter/RunningAverageFilter.h" ///< Include for smoothing peaks.
#include "../../../../Utils/Filter/PeakDetection.h" ///< Include for peak detection in FFT data.
#include "../../../../Renderer/Utils/IndexGroup.h" ///< Include for utility structures.
#include "../../../../Renderer/Utils/Triangle2D.h" ///< Include for 2D triangle utilities.
#include "../../../../Utils/Math/Vector2D.h" ///< Include for 2D vector utilities.

/**
 * @class Viseme
 * @brief Defines the available mouth shapes (visemes).
 */
class Viseme {
public:
    /**
     * @enum MouthShape
     * @brief Enumerates the possible mouth shapes for viseme detection.
     */
    enum MouthShape {
        EE, ///< Mouth shape corresponding to the "EE" sound.
        AE, ///< Mouth shape corresponding to the "AE" sound.
        UH, ///< Mouth shape corresponding to the "UH" sound.
        AR, ///< Mouth shape corresponding to the "AR" sound.
        ER, ///< Mouth shape corresponding to the "ER" sound.
        AH, ///< Mouth shape corresponding to the "AH" sound.
        OO, ///< Mouth shape corresponding to the "OO" sound.
        SS  ///< Mouth shape corresponding to the "SS" sound (optional).
    };
};

/**
 * @class FFTVoiceDetection
 * @brief Detects visemes based on FFT voice analysis.
 *
 * The FFTVoiceDetection class uses formant frequencies (F1 and F2) derived from FFT peaks
 * to detect and assign probabilities to various mouth shapes (visemes). It employs peak detection,
 * smoothing filters, and threshold-based calculations to determine the most probable viseme.
 *
 * @tparam peakCount The number of peaks to analyze in the FFT data.
 */
template <size_t peakCount>
class FFTVoiceDetection : public Viseme {
private:
    static const uint8_t visemeCount = 7; ///< Number of supported visemes.

    // Formant frequency coordinates for each viseme.
    Vector2D visEE = Vector2D(350.0f, 3200.0f); ///< Coordinates for "EE".
    Vector2D visAE = Vector2D(500.0f, 2700.0f); ///< Coordinates for "AE".
    Vector2D visUH = Vector2D(1100.0f, 2700.0f); ///< Coordinates for "UH".
    Vector2D visAR = Vector2D(850.0f, 850.0f); ///< Coordinates for "AR".
    Vector2D visER = Vector2D(1000.0f, 1000.0f); ///< Coordinates for "ER".
    Vector2D visAH = Vector2D(900.0f, 2400.0f); ///< Coordinates for "AH".
    Vector2D visOO = Vector2D(600.0f, 600.0f); ///< Coordinates for "OO".

    Vector2D* coordinates[visemeCount] = { &visEE, &visAE, &visUH, &visAR, &visER, &visAH, &visOO }; ///< Array of viseme coordinates.

    // Viseme probabilities.
    float visRatioEE = 0.0f; ///< Probability for "EE".
    float visRatioAE = 0.0f; ///< Probability for "AE".
    float visRatioUH = 0.0f; ///< Probability for "UH".
    float visRatioAR = 0.0f; ///< Probability for "AR".
    float visRatioER = 0.0f; ///< Probability for "ER".
    float visRatioAH = 0.0f; ///< Probability for "AH".
    float visRatioOO = 0.0f; ///< Probability for "OO".

    float* visRatios[visemeCount] = { &visRatioEE, &visRatioAE, &visRatioUH, &visRatioAR, &visRatioER, &visRatioAH, &visRatioOO }; ///< Array of viseme probabilities.

    PeakDetection<peakCount> peakDetection = PeakDetection<peakCount>(8, 2.0f, 0.5f); ///< Peak detection instance.
    RunningAverageFilter<10> peakSmoothing = RunningAverageFilter<10>(0.1f); ///< Smoothing filter for peak data.

    bool peaksBinary[peakCount]; ///< Binary array indicating peak presence.
    float peakDensity[peakCount]; ///< Array of peak densities.

    float f1; ///< Formant frequency F1.
    float f2; ///< Formant frequency F2.

    float threshold = 400.0f; ///< Threshold for formant calculations.

    /**
     * @brief Calculates formant frequencies (F1 and F2) from FFT peaks.
     *
     * @param peaks Array of FFT peak values.
     * @param bandwidth Bandwidth of the FFT data.
     */
    void CalculateFormants(float* peaks, uint8_t bandwidth);

    /**
     * @brief Calculates the viseme group probabilities based on formants.
     */
    void CalculateVisemeGroup();

public:
    /**
     * @brief Constructs a new FFTVoiceDetection instance.
     */
    FFTVoiceDetection() {}

    /**
     * @brief Sets the threshold for formant calculations.
     *
     * @param threshold The new threshold value.
     */
    void SetThreshold(float threshold);

    /**
     * @brief Retrieves the probability of a specific viseme.
     *
     * @param viseme The viseme to query.
     * @return The probability of the specified viseme (0.0 - 1.0).
     */
    float GetViseme(MouthShape viseme);

    /**
     * @brief Prints the probabilities of all visemes to the serial console.
     */
    void PrintVisemes();

    /**
     * @brief Resets all viseme probabilities to zero.
     */
    void ResetVisemes();

    /**
     * @brief Updates the viseme probabilities based on new FFT data.
     *
     * @param peaks Array of FFT peak values.
     * @param maxFrequency Maximum frequency represented in the FFT data.
     */
    void Update(float* peaks, float maxFrequency);
};

#include "FFTVoiceDetection.tpp" ///< Include the template implementation.
