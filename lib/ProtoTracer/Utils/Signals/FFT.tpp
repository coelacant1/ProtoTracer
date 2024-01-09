#pragma once

template<int fftSize>
constexpr int FFT<fftSize>::CalculateBits(int size, int count) {
    return (size <= 1) ? count : CalculateBits(size / 2, count + 1);
}

template<int fftSize>
void FFT<fftSize>::BitReverseOrder(float* data) {
    for (int i = 0; i < fftSize; ++i) {
        int j = ReverseBits(i);
        if (i < j) {//Swap the i and j elements
            Swap(&data[2 * i], &data[2 * j]);//Swap real part
            Swap(&data[2 * i + 1], &data[2 * j + 1]);//Swap imaginary part
        }
    }
}

template<int fftSize>
int FFT<fftSize>::ReverseBits(int num) {
    int reversed = 0;
    for (int i = 0; i < bitCount; i++) {
        if (num & (1 << i)) {
            reversed |= 1 << ((bitCount - 1) - i);
        }
    }
    return reversed;
}

template<int fftSize>
void FFT<fftSize>::Swap(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

template<int fftSize>
void FFT<fftSize>::Radix2FFT(float* data){
    BitReverseOrder(data);//Bit reversal reordering

    for (int s = 1; s <= log2(fftSize); ++s) {// FFT computation
        int m = 1 << s; //2 power s
        int m2 = m >> 1; //m2 = m/2 - bit shift
        float wReal = 1.0;
        float wImag = 0.0;
        float wmReal = cosf(Mathematics::MPI / m2);
        float wmImag = -sinf(Mathematics::MPI / m2);

        for (int j = 0; j < m2; ++j) {
            for (int k = j; k < fftSize; k += m) {
                int t = k + m2;
                float tr = wReal * data[2 * t] - wImag * data[2 * t + 1];
                float ti = wReal * data[2 * t + 1] + wImag * data[2 * t];

                data[2 * t] = data[2 * k] - tr;
                data[2 * t + 1] = data[2 * k + 1] - ti;
                data[2 * k] += tr;
                data[2 * k + 1] += ti;
            }

            float tmpReal = wReal;

            wReal = wReal * wmReal - wImag * wmImag;
            wImag = tmpReal * wmImag + wImag * wmReal;
        }
    }
}

template<int fftSize>
void FFT<fftSize>::ComplexMagnitude(float* complexData, float* magnitude){
    for (int i = 0; i < fftSize; ++i) {
        float real = complexData[2 * i];//Real part
        float imag = complexData[2 * i + 1];//Imaginary part

        magnitude[i] = sqrt(real * real + imag * imag);
    }
}
