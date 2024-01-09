#pragma once

#include "..\..\Utils\Math\Mathematics.h"

template<int fftSize>
class FFT {
private:
    static const constexpr float twiddleCoefficients[fftSize * 2] = [] {
        float temp[fftSize * 2];

        for (int i = 0; i < fftSize * 2; ++i) {
            temp[i] = FFT<fftSize>::calculateCoefficient(i);
        }

        return temp;
    }();


    static constexpr int CalculateBits(int size, int count = 0);
    
    static const constexpr int bitCount = CalculateBits(fftSize);

    static void BitReverseOrder(float* data);
    static int ReverseBits(int num);
    static void Swap(float* a, float* b);

public:
    static void Radix2FFT(float* data);
    static void ComplexMagnitude(float* complexData, float* magnitude);

};

#include "FFT.tpp"
