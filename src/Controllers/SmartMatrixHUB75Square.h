#include <Arduino.h>
//#include <MatrixHardware_Teensy3_ShieldV4.h>        // SmartLED Shield for Teensy 3 (V4)
#include <MatrixHardware_Teensy4_ShieldV5.h>        // SmartLED Shield for Teensy 4 (V5)
//#include <MatrixHardware_Teensy3_ShieldV1toV3.h>    // SmartMatrix Shield for Teensy 3 V1-V3
//#include <MatrixHardware_Teensy4_ShieldV4Adapter.h> // Teensy 4 Adapter attached to SmartLED Shield for Teensy 3 (V4)
//#include <MatrixHardware_ESP32_V0.h>                // This file contains multiple ESP32 hardware configurations, edit the file to define GPIOPINOUT (or add #define GPIOPINOUT with a hardcoded number before this #include)
//#include "MatrixHardware_Custom.h"                  // Copy an existing MatrixHardware file to your Sketch directory, rename, customize, and you can include it like this
#include <SmartMatrix.h>

#include "Controller.h"
#include "Render/Camera.h"
#include "Flash/PixelGroups/P3HUB75.h"


#define COLOR_DEPTH 24                  // Choose the color depth used for storing pixels in the layers: 24 or 48 (24 is good for most sketches - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24)
const uint16_t kMatrixWidth = 64;       // Set to the width of your display, must be a multiple of 8
const uint16_t kMatrixHeight = 64;      // Set to the height of your display
const uint8_t kRefreshDepth = 12;       // Tradeoff of color quality vs refresh rate, max brightness, and RAM usage.  36 is typically good, drop down to 24 if you need to.  On Teensy, multiples of 3, up to 48: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48.  On ESP32: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save RAM, more to keep from dropping frames and automatically lowering refresh rate.  (This isn't used on ESP32, leave as default)
const uint8_t kPanelType = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;   // Choose the configuration that matches your panels.  See more details in MatrixCommonHub75.h and the docs: https://github.com/pixelmatix/SmartMatrix/wiki
const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_NONE);        // see docs for options: https://github.com/pixelmatix/SmartMatrix/wiki
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

class SmartMatrixHUB75Split : public Controller {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);

    Transform camTransform1 = Transform(Vector3D(), Vector3D(0, 96.0f, -500.0f), Vector3D(1, 1, 1));
    Transform camTransform2 = Transform(Vector3D(), Vector3D(0, 0.0f, -500.0f), Vector3D(1, 1, 1));

    PixelGroup<2048> camPixelsLeft = PixelGroup<2048>(P3HUB75);
    PixelGroup<2048> camPixelsRight = PixelGroup<2048>(P3HUB75);

    Camera<2048> camLeft = Camera<2048>(&camTransform1, &cameraLayout, &camPixelsLeft);
    Camera<2048> camRight = Camera<2048>(&camTransform2, &cameraLayout, &camPixelsRight);

    CameraBase* cameras[2] = { &camLeft, &camRight };

public:
    SmartMatrixHUB75Split(uint8_t maxBrightness, uint8_t maxAccentBrightness) : Controller(cameras, 2, maxBrightness, maxAccentBrightness){}

    void Initialize() override{
        matrix.addLayer(&backgroundLayer);
        matrix.begin();
        
        matrix.setRefreshRate(240);

        backgroundLayer.swapBuffers();//for ESP32 - first is ignored
    }

    void Display() override {
        matrix.setBrightness(brightness);

        for (uint16_t y = 0; y < 32; y++) {
            for (uint16_t x = 0; x < 64; x++){
                uint16_t pixelNum = y * 64 + x;

                rgb24 rgbColorLeft = rgb24((uint16_t)camPixelsLeft.GetColor(pixelNum)->R, (uint16_t)camPixelsLeft.GetColor(pixelNum)->G, (uint16_t)camPixelsLeft.GetColor(pixelNum)->B);
                rgb24 rgbColorRight = rgb24((uint16_t)camPixelsRight.GetColor(pixelNum)->R, (uint16_t)camPixelsRight.GetColor(pixelNum)->G, (uint16_t)camPixelsRight.GetColor(pixelNum)->B);

                backgroundLayer.drawPixel(63 - x, (31 - y), rgbColorLeft);
                backgroundLayer.drawPixel(x, (y) + 32, rgbColorRight);
            }
        }

        backgroundLayer.swapBuffers();
    }
};
