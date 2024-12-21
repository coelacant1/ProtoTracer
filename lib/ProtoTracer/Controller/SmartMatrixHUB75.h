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
#elif
  #include "MatrixHardware_Teensy4_ShieldV5_RBG.h"        // SmartLED Shield for Teensy 4 (V5) and panel with swapped green and blue channels (RBG color order)
#endif

#include <SmartMatrix.h>

//HUB75
#define ENABLE_HUB75_REFRESH    1
#define COLOR_DEPTH 24                  // Choose the color depth used for storing pixels in the layers: 24 or 48 (24 is good for most sketches - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24)
const uint16_t kMatrixWidth = 64;       // Set to the width of your display, must be a multiple of 8
const uint16_t kMatrixHeight = 64;      // Set to the height of your display
const uint8_t kRefreshDepth = 36;       // Tradeoff of color quality vs refresh rate, max brightness, and RAM usage.  36 is typically good, drop down to 24 if you need to.  On Teensy, multiples of 3, up to 48: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48.  On ESP32: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save RAM, more to keep from dropping frames and automatically lowering refresh rate.  (This isn't used on ESP32, leave as default)
const uint8_t kPanelType = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;   // Choose the configuration that matches your panels.  See more details in MatrixCommonHub75.h and the docs: https://github.com/pixelmatix/SmartMatrix/wiki
const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_NONE);        // see docs for options: https://github.com/pixelmatix/SmartMatrix/wiki
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

//APA102
#define ENABLE_APA102_REFRESH   1
const uint16_t kApaMatrixWidth = 176;          // adjust this to your APA matrix/strip
const uint16_t kApaMatrixHeight = 1;         // set kApaMatrixHeight to 1 for a strip
const uint8_t kApaRefreshDepth = 36;        // not used for APA matrices as of now
const uint8_t kApaDmaBufferRows = 1;        // not used for APA matrices as of now
const uint8_t kApaPanelType = 0;            // not used for APA matrices as of now
const uint32_t kApaMatrixOptions = (SM_APA102_OPTIONS_COLOR_ORDER_BGR);      // The default color order is BGR, change here to match your LEDs
const uint8_t kApaBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

#endif
