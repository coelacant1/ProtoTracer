/**
 * @file SmartMatrixHUB75.h
 * @brief Configuration file for SmartMatrix library with HUB75 panels and APA102 support.
 *
 * This file provides hardware-specific configurations and settings for SmartMatrix
 * library usage with HUB75 LED panels and APA102 LED strips.
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
#include <MatrixHardware_Teensy4_ShieldV5.h>        // SmartLED Shield for Teensy 4 (V5)
//#include <MatrixHardware_Teensy3_ShieldV1toV3.h>    // SmartMatrix Shield for Teensy 3 V1-V3
//#include <MatrixHardware_Teensy4_ShieldV4Adapter.h> // Teensy 4 Adapter attached to SmartLED Shield for Teensy 3 (V4)
//#include <MatrixHardware_ESP32_V0.h>                // This file contains multiple ESP32 hardware configurations, edit the file to define GPIOPINOUT (or add #define GPIOPINOUT with a hardcoded number before this #include)
//#include "MatrixHardware_Custom.h"                  // Copy an existing MatrixHardware file to your Sketch directory, rename, customize, and you can include it like this
#include <SmartMatrix.h>

/**
 * @def COLOR_DEPTH
 * @brief Specifies the color depth used for storing pixels in the layers.
 *
 * Use 24 for most sketches. If the sketch uses type `rgb24` directly, set COLOR_DEPTH to 24.
 */
#define COLOR_DEPTH 24                  

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
 *
 * The default color order is BGR. Adjust as needed to match your LEDs.
 */
const uint32_t kApaMatrixOptions = (SM_APA102_OPTIONS_COLOR_ORDER_BGR);

/**
 * @var kApaBackgroundLayerOptions
 * @brief Background layer options for APA matrices.
 */
const uint8_t kApaBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

#endif
