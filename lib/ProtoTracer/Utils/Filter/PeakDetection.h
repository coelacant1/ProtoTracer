/**
 * @file PeakDetection.h
 * @brief Implements peak detection for time-series data using a sliding window approach.
 *
 * The `PeakDetection` class identifies peaks in a data stream by maintaining a moving
 * average and standard deviation and comparing incoming values against a dynamic threshold.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../Math/Mathematics.h"

/**
 * @class PeakDetection
 * @brief Detects peaks in time-series data using statistical methods.
 *
 * This class identifies peaks by calculating a moving average and standard deviation
 * of the data and comparing each value against a dynamically adjusted threshold.
 *
 * @tparam sampleSize The size of the data window used for peak detection.
 */
template <size_t sampleSize>
class PeakDetection {
private:
    uint8_t lag; ///< Number of data points to use for moving average and standard deviation.
    float threshold; ///< Threshold for peak detection, expressed as a multiple of the standard deviation.
    float influence; ///< Influence of detected peaks on subsequent calculations.
    float filData[sampleSize]; ///< Filtered data array for influence adjustment.
    float avg[sampleSize]; ///< Moving average of the data.
    float std[sampleSize]; ///< Moving standard deviation of the data.

    /**
     * @brief Calculates the mean and standard deviation for a range of data.
     *
     * @param start The starting index of the range.
     * @param length The number of elements in the range.
     * @param data Pointer to the data array.
     * @param avgRet Output parameter for the calculated mean.
     * @param stdRet Output parameter for the calculated standard deviation.
     */
    void GetStdDev(uint8_t start, uint8_t length, float* data, float& avgRet, float& stdRet);

public:
    /**
     * @brief Constructs a `PeakDetection` object with the specified parameters.
     *
     * @param lag The number of data points for the moving average and standard deviation (default: 12).
     * @param threshold The threshold for detecting peaks, expressed as a multiple of the standard deviation (default: 0.75).
     * @param influence The influence of detected peaks on subsequent calculations (default: 0.5).
     */
    PeakDetection(uint8_t lag = 12, float threshold = 0.75f, float influence = 0.5f);

    /**
     * @brief Processes the data and identifies peaks.
     *
     * @param data Pointer to the input data array.
     * @param peaks Output array of boolean values indicating whether each point is a peak.
     */
    void Calculate(float* data, bool* peaks);
};

#include "PeakDetection.tpp" // Includes the implementation of the template class.
