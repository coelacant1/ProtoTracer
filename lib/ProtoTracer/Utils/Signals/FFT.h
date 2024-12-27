/**
 * @file FFT.h
 * @brief Provides an implementation of the Radix-2 FFT algorithm and related utilities.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../Utils/Math/Mathematics.h"

/**
 * @class FFT
 * @brief A templated class for performing Fast Fourier Transform (FFT) operations.
 * @tparam fftSize The size of the FFT, must be a power of 2.
 */
template<int fftSize>
class FFT {
private:
    /**
     * @brief Precomputed twiddle coefficients for the FFT.
     */
    static const constexpr float twiddleCoefficients[fftSize * 2] = [] {
        float temp[fftSize * 2];

        for (int i = 0; i < fftSize * 2; ++i) {
            temp[i] = FFT<fftSize>::calculateCoefficient(i);
        }

        return temp;
    }();

    /**
     * @brief Calculates the number of bits required for bit reversal based on FFT size.
     * @param size The FFT size.
     * @param count Recursive parameter to count the bits.
     * @return The number of bits required.
     */
    static constexpr int CalculateBits(int size, int count = 0);

    /**
     * @brief The number of bits needed for bit reversal for this FFT size.
     */
    static const constexpr int bitCount = CalculateBits(fftSize);

    /**
     * @brief Reorders the data array in bit-reversed order.
     * @param data The data array to reorder.
     */
    static void BitReverseOrder(float* data);

    /**
     * @brief Reverses the bits of an integer.
     * @param num The number whose bits are to be reversed.
     * @return The bit-reversed integer.
     */
    static int ReverseBits(int num);

    /**
     * @brief Swaps two floating-point values.
     * @param a Pointer to the first value.
     * @param b Pointer to the second value.
     */
    static void Swap(float* a, float* b);

public:
    /**
     * @brief Performs a Radix-2 FFT on the provided data.
     * @param data The input array containing interleaved real and imaginary components.
     */
    static void Radix2FFT(float* data);

    /**
     * @brief Computes the magnitude of complex numbers from interleaved real and imaginary components.
     * @param complexData The input array containing interleaved real and imaginary components.
     * @param magnitude The output array for storing computed magnitudes.
     */
    static void ComplexMagnitude(float* complexData, float* magnitude);
};

#include "FFT.tpp"
