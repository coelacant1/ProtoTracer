/*
 * SmartMatrix Library - APA102 Refresh Code for Teensy 3.x Platform
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

#include "SmartMatrix.h"
#include <SPI.h>
#include "DMAChannel.h"

#define INLINE __attribute__( ( always_inline ) ) inline

#if defined(KINETISL)
    #define ROW_CALCULATION_ISR_PRIORITY   192   // Cortex-M0 Acceptable values: 0,64,128,192
#elif defined(KINETISK)
    #define ROW_CALCULATION_ISR_PRIORITY   240 // M4 acceptable values: 0,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240
#endif

//#define USE_INTERVALTIMER_NOT_FTM

// hardware-specific definitions
// prescale of 7 is F_BUS/128
#define APA_LATCH_TIMER_PRESCALE  0x07
#define APA_NS_TO_TICKS(X)      (uint32_t)(APA_TIMER_FREQUENCY * ((X) / 1000000000.0))

#if defined(KINETISL)
    #define APA_TIMER_FREQUENCY     (F_BUS/1)
    #error KINETISL APA102 support isnt tested
#elif defined(KINETISK)
    #define APA_TIMER_FREQUENCY     (F_BUS/128)
#endif

#define APA_TICKS_PER_FRAME   (APA_TIMER_FREQUENCY/refreshRate)
#define REFRESH_RATE_IN_US      (1000000/refreshRate)

// TODO: calculate a reasonable value based on timer overflow
#define APA_MIN_REFRESH_RATE 1

extern DMAChannel dmaClockOutDataApa;
extern IntervalTimer myTimer;

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
void apaRowShiftCompleteISR(void);
template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
void apaRowCalculationISR(void);

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
CircularBuffer_SM SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::dmaBuffer;

// dmaBufferNumRows = the size of the buffer that DMA pulls from to refresh the display
// must be minimum 2 rows so one can be updated while the other is refreshed
// increase beyond two to give more time for the update routine to complete
// (increase this number if non-DMA interrupts are causing display problems)
template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
uint8_t SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::dmaBufferNumRows;

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
uint8_t SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::refreshRate = 60;

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
uint32_t SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::spiClockSpeed = 5000000;

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
uint16_t SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::rowBitStructBytesToShift;

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
typename SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::frameDataStruct * SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::matrixUpdateFrame;

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::SmartMatrixAPA102Refresh(uint8_t bufferrows, frameDataStruct * frameDataBuffer) {
    dmaBufferNumRows = bufferrows;

    matrixUpdateFrame = frameDataBuffer;
}

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
bool SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::isRowBufferFree(void) {
    if(cbIsFull(&dmaBuffer))
        return false;
    else
        return true;
}

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
typename SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::frameDataStruct * SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::getNextRowBufferPtr(void) {
    return &(matrixUpdateFrame[cbGetNextWrite(&dmaBuffer)]);
}

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
void SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::writeRowBuffer(uint8_t currentRow) {
    cbWrite(&dmaBuffer);
}

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
void SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::recoverFromDmaUnderrun(void) {

}

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
typename SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::matrix_underrun_callback SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::matrixUnderrunCallback;

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
typename SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::matrix_calc_callback SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::matrixCalcCallback;

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
void SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::setMatrixCalculationsCallback(matrix_calc_callback f) {
    matrixCalcCallback = f;
}

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
void SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::setMatrixUnderrunCallback(matrix_underrun_callback f) {
    matrixUnderrunCallback = f;
}


#define MSB_BLOCK_TICKS_ADJUSTMENT_INCREMENT    10

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
void SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::calculateTimerLUT(void) {

}

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
void SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::setRefreshRate(uint8_t newRefreshRate) {
    if(newRefreshRate > APA_MIN_REFRESH_RATE)
        refreshRate = newRefreshRate;
    else
        refreshRate = APA_MIN_REFRESH_RATE;

#ifdef USE_INTERVALTIMER_NOT_FTM
   myTimer.update(REFRESH_RATE_IN_US);
#endif
}

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
void SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::setSpiClockSpeed(uint32_t newClockSpeed) {
    spiClockSpeed = newClockSpeed;

    // TODO: update clock speed after begin() called?
}

template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
void SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::begin(void) {
    cbInit(&dmaBuffer, dmaBufferNumRows);

    // setup debug output
#ifdef DEBUG_PINS_ENABLED
    pinMode(DEBUG_PIN_1, OUTPUT);
    digitalWriteFast(DEBUG_PIN_1, HIGH); // oscilloscope trigger
    digitalWriteFast(DEBUG_PIN_1, LOW);
    pinMode(DEBUG_PIN_2, OUTPUT);
    digitalWriteFast(DEBUG_PIN_2, HIGH); // oscilloscope trigger
    digitalWriteFast(DEBUG_PIN_2, LOW);
    pinMode(DEBUG_PIN_3, OUTPUT);
    digitalWriteFast(DEBUG_PIN_3, HIGH); // oscilloscope trigger
    digitalWriteFast(DEBUG_PIN_3, LOW);
#endif

    // completely fill buffer with data before enabling DMA
    matrixCalcCallback(true);

    // setup SPI and DMA to feed it
    SPI.begin();
    SPI.setMOSI(SMARTLED_APA_DAT_PIN);
    dmaClockOutDataApa.begin(false);
    dmaClockOutDataApa.disable();
    dmaClockOutDataApa.destination((volatile uint8_t&)SPI0_PUSHR);
    dmaClockOutDataApa.disableOnCompletion();
    dmaClockOutDataApa.triggerAtHardwareEvent(DMAMUX_SOURCE_SPI0_TX);
    dmaClockOutDataApa.attachInterrupt(apaRowCalculationISR<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>);
    dmaClockOutDataApa.interruptAtCompletion();
    NVIC_SET_PRIORITY(IRQ_DMA_CH0 + dmaClockOutDataApa.channel, ROW_CALCULATION_ISR_PRIORITY);

#ifndef USE_INTERVALTIMER_NOT_FTM
    // setup FTM2
    FTM2_SC = 0;
    FTM2_CNT = 0;
    FTM2_MOD = APA_TICKS_PER_FRAME;

#if 0
    // for debug: latch pulse width wide enough to be seen on logic analyzer
    FTM2_C0V = 100;

// out of date, set for FTM1_C0V
#define ENABLE_LATCH_PWM_OUTPUT() {                                     \
        CORE_PIN3_CONFIG |= PORT_PCR_MUX(3) | PORT_PCR_DSE | PORT_PCR_SRE;  \
    }

    // setup PWM outputs
    ENABLE_LATCH_PWM_OUTPUT();
#endif

    // enable timer from system clock, with appropriate prescale, TOF interrupt
    FTM2_SC = FTM_SC_CLKS(1) | FTM_SC_PS(APA_LATCH_TIMER_PRESCALE) | FTM_SC_TOIE;

    attachInterruptVector(IRQ_FTM2, apaRowShiftCompleteISR<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>);

    NVIC_ENABLE_IRQ(IRQ_FTM2);
#else
    myTimer.begin(apaRowShiftCompleteISR<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>, REFRESH_RATE_IN_US);  // blinkLED to run 60 Hz
#endif
}

// low priority ISR triggered by software interrupt on a DMA channel that doesn't need interrupts otherwise
template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
void apaRowCalculationISR(void) {
#ifdef DEBUG_PINS_ENABLED
    digitalWriteFast(DEBUG_PIN_2, HIGH); // oscilloscope trigger
#endif

    dmaClockOutDataApa.clearInterrupt();

    // done with previous row, mark it as read
    cbRead(&SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::dmaBuffer);

    SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::matrixCalcCallback(false);

#ifdef DEBUG_PINS_ENABLED
    digitalWriteFast(DEBUG_PIN_2, LOW);
#endif
}

// DMA transfer done (meaning data was shifted and timer value for MSB on current row just got loaded)
// set DMA up for loading the next row, triggered from the next timer latch
template <int refreshDepth, int matrixWidth, int matrixHeight, unsigned char panelType, uint32_t optionFlags>
void apaRowShiftCompleteISR(void) {
#ifdef DEBUG_PINS_ENABLED
    digitalWriteFast(DEBUG_PIN_1, HIGH); // oscilloscope trigger
#endif
    int currentRow = cbGetNextRead(&SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::dmaBuffer);

    // TODO: if underrun
        // set flag so other ISR can enable DMA again when data is ready
        //SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::dmaBufferUnderrun = true;
    // else, start SPI
    SPI.endTransaction();

    // disable SPI interrupts
    SPI0_RSER = 0;
    // clear flags
    SPI0_SR = SPI_SR_TCF | SPI_SR_EOQF | SPI_SR_TFUF | SPI_SR_TFFF | SPI_SR_RFOF | SPI_SR_RFDF;
    dmaClockOutDataApa.sourceBuffer(SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::matrixUpdateFrame[currentRow].data,
        ((matrixWidth * matrixHeight)*4) + (4+4));
    // Enable Transmit Fill DMA Requests
    SPI0_RSER = SPI_RSER_TFFF_RE | SPI_RSER_TFFF_DIRS;
    SPI.beginTransaction(SPISettings(SmartMatrixAPA102Refresh<refreshDepth, matrixWidth, matrixHeight, panelType, optionFlags>::spiClockSpeed, MSBFIRST, SPI_MODE0));
    dmaClockOutDataApa.enable();

#ifndef USE_INTERVALTIMER_NOT_FTM
    // clear timer overflow bit before leaving ISR
    FTM2_SC &= ~FTM_SC_TOF;
#endif

#ifdef DEBUG_PINS_ENABLED
    digitalWriteFast(DEBUG_PIN_1, LOW); // oscilloscope trigger
#endif
}
