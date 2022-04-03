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

class SmartMatrixHUB75 : public Controller {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);

    Transform camTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));

    PixelGroup camPixels = PixelGroup(P3HUB75, 2048);

    Camera cam = Camera(&camTransform, &cameraLayout, &camPixels);

    Camera* cameras[1] = { &cam };
    uint8_t maxBrightness;

public:
    SmartMatrixHUB75(uint8_t maxBrightness) : Controller(cameras, 1){
        this->maxBrightness = maxBrightness;
    }

    void Initialize() override{
        matrix.addLayer(&backgroundLayer);
        matrix.begin();
        
        matrix.setBrightness(255);
        matrix.setRefreshRate(240);

        backgroundLayer.swapBuffers();//for ESP32 - first is ignored
    }

    void Display() override {
        for (int i = 0; i < 2048; i++){
            if (camPixels.GetPixel(i)->Color.R == 0 && camPixels.GetPixel(i)->Color.G == 0 && camPixels.GetPixel(i)->Color.B == 0){
                camPixels.GetPixel(i)->Color = camPixels.GetPixel(i)->Color.Scale(maxBrightness).Add(16);
            }
        }

        for (uint16_t y = 0; y < 32; y++) {
            for (uint16_t x = 0; x < 64; x++){
                uint16_t pixelNum = y * 64 + x;

                rgb24 rgbColor = rgb24((uint16_t)camPixels.GetPixel(pixelNum)->Color.R, (uint16_t)camPixels.GetPixel(pixelNum)->Color.G, (uint16_t)camPixels.GetPixel(pixelNum)->Color.B);

                backgroundLayer.drawPixel(x, y, rgbColor);
                backgroundLayer.drawPixel(63 - x, y + 32, rgbColor);
            }
        }

        backgroundLayer.swapBuffers();
    }
};
