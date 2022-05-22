/*
 * SmartMatrix Library - APA102 Refresh Class
 *
 * Copyright (c) 2020 Louis Beaudoin (Pixelmatix)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef SmartMatrixAPA102Refresh_h
#define SmartMatrixAPA102Refresh_h

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
class SmartMatrixAPA102Refresh {
public:
    struct frameDataStruct {
        uint8_t data[((matrixWidth*matrixHeight) * 4) + (4+4)];
    };

    typedef void (*matrix_underrun_callback)(void);
    typedef void (*matrix_calc_callback)(bool initial);

    // init
    SmartMatrixAPA102Refresh(uint8_t bufferrows, frameDataStruct * frameDataBuffer);
    static void begin(void);

    static void setBrightness(uint8_t newBrightness);

    // refresh API
    static frameDataStruct * getNextRowBufferPtr(void);
    static void writeRowBuffer(uint8_t currentRow);
    static void recoverFromDmaUnderrun(void);
    static bool isRowBufferFree(void);
    static void setRefreshRate(uint8_t newRefreshRate);
    static void setSpiClockSpeed(uint32_t newClockSpeed);
    static void setMatrixCalculationsCallback(matrix_calc_callback f);
    static void setMatrixUnderrunCallback(matrix_underrun_callback f);

private:
    // enable ISR access to private member variables
    template <int refreshDepth1, int matrixWidth1, int matrixHeight1, unsigned char panelType1, uint32_t optionFlags1>
    friend void apaRowCalculationISR(void);
    template <int refreshDepth1, int matrixWidth1, int matrixHeight1, unsigned char panelType1, uint32_t optionFlags1>
    friend void apaRowShiftCompleteISR(void);

    // configuration helper functions
    static void calculateTimerLUT(void);

    static uint16_t rowBitStructBytesToShift;
    static uint8_t refreshRate;
    static uint32_t spiClockSpeed;
    static uint8_t dmaBufferNumRows;
    static frameDataStruct * matrixUpdateFrame;

    static matrix_calc_callback matrixCalcCallback;
    static matrix_underrun_callback matrixUnderrunCallback;

    static CircularBuffer_SM dmaBuffer;
};

#endif
