/**
 * @file SmartMatrixHUB75.h
 * @brief Configuration file for SmartMatrix library with HUB75 panels and APA102 support.
 *
 * This file provides hardware-specific configurations and settings for SmartMatrix
 * library usage with HUB75 LED panels and APA102 LED strips, including support for RBG panels.
 * 
 * SmartMatrix Library - Hardware-Specific Header File (for SmartMatrix Shield for Teensy 4 V5)
 *
 * @date 22/12/2024
 * @author Copyright (c) 2020 Louis Beaudoin (Pixelmatix)
 */

#pragma once

#ifndef SMARTMATRIXHUB75
#define SMARTMATRIXHUB75

//#include <MatrixHardware_Teensy3_ShieldV4.h>        // SmartLED Shield for Teensy 3 (V4)
//#include <MatrixHardware_Teensy3_ShieldV1toV3.h>    // SmartMatrix Shield for Teensy 3 V1-V3
//#include <MatrixHardware_Teensy4_ShieldV4Adapter.h> // Teensy 4 Adapter attached to SmartLED Shield for Teensy 3 (V4)
//#include <MatrixHardware_ESP32_V0.h>                // This file contains multiple ESP32 hardware configurations, edit the file to define GPIOPINOUT (or add #define GPIOPINOUT with a hardcoded number before this #include)
//#include "MatrixHardware_Custom.h"                  // Copy an existing MatrixHardware file to your Sketch directory, rename, customize, and you can include it like this
#ifndef HUB75_RBG
  #include <MatrixHardware_Teensy4_ShieldV5.h>        // SmartLED Shield for Teensy 4 (V5)
#else
  #include "MatrixHardware_Teensy4_ShieldV5_RBG.h"  // SmartLED Shield for Teensy 4 (V5) and panel with swapped green and blue channels (RBG color order)
#endif

#include <SmartMatrix.h>

/**
 * @def ENABLE_HUB75_REFRESH
 * @brief Enables HUB75 refresh support.
 */
#define ENABLE_HUB75_REFRESH    1

/**
 * @def COLOR_DEPTH
 * @brief Specifies the color depth used for storing pixels in the layers.
 *
 * Use 24 for most sketches. If the sketch uses type `rgb24` directly, set COLOR_DEPTH to 24.
 */
#define COLOR_DEPTH 24

/**
 * @var kMatrixWidth
 * @brief Width of the HUB75 matrix.
 */
const uint16_t kMatrixWidth = 64;

/**
 * @var kMatrixHeight
 * @brief Height of the HUB75 matrix.
 */
const uint16_t kMatrixHeight = 64;

/**
 * @var kRefreshDepth
 * @brief Specifies the tradeoff between color quality and refresh rate for HUB75 matrices.
 */
const uint8_t kRefreshDepth = 36;

/**
 * @var kDmaBufferRows
 * @brief Number of DMA buffer rows for HUB75 matrices.
 */
const uint8_t kDmaBufferRows = 4;

/**
 * @var kPanelType
 * @brief Specifies the panel type for HUB75 matrices.
 */
const uint8_t kPanelType = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;

/**
 * @var kMatrixOptions
 * @brief Options for HUB75 matrices.
 */
const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_NONE);

/**
 * @var kBackgroundLayerOptions
 * @brief Background layer options for HUB75 matrices.
 */
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

/**
 * @def ENABLE_APA102_REFRESH
 * @brief Enables APA102 refresh support.
 */
#define ENABLE_APA102_REFRESH   1

/**
 * @var kApaMatrixWidth
 * @brief Width of the APA matrix or strip.
 */
const uint16_t kApaMatrixWidth = 176;

/**
 * @var kApaMatrixHeight
 * @brief Height of the APA matrix. Set to 1 for strips.
 */
const uint16_t kApaMatrixHeight = 1;

/**
 * @var kApaRefreshDepth
 * @brief Not currently used for APA matrices.
 */
const uint8_t kApaRefreshDepth = 36;

/**
 * @var kApaDmaBufferRows
 * @brief Not currently used for APA matrices.
 */
const uint8_t kApaDmaBufferRows = 1;

/**
 * @var kApaPanelType
 * @brief Not currently used for APA matrices.
 */
const uint8_t kApaPanelType = 0;

/**
 * @var kApaMatrixOptions
 * @brief Options for APA matrices, including color order.
 */
const uint32_t kApaMatrixOptions = (SM_APA102_OPTIONS_COLOR_ORDER_BGR);

/**
 * @var kApaBackgroundLayerOptions
 * @brief Background layer options for APA matrices.
 */
const uint8_t kApaBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

#endif
