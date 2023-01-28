#include <Arduino.h>
//#include <MatrixHardware_Teensy3_ShieldV4.h>        // SmartLED Shield for Teensy 3 (V4)
#include <MatrixHardware_Teensy4_ShieldV5.h>        // SmartLED Shield for Teensy 4 (V5)
//#include <MatrixHardware_Teensy3_ShieldV1toV3.h>    // SmartMatrix Shield for Teensy 3 V1-V3
//#include <MatrixHardware_Teensy4_ShieldV4Adapter.h> // Teensy 4 Adapter attached to SmartLED Shield for Teensy 3 (V4)
//#include <MatrixHardware_ESP32_V0.h>                // This file contains multiple ESP32 hardware configurations, edit the file to define GPIOPINOUT (or add #define GPIOPINOUT with a hardcoded number before this #include)
//#include "MatrixHardware_Custom.h"                  // Copy an existing MatrixHardware file to your Sketch directory, rename, customize, and you can include it like this
#include <SmartMatrix.h>
#include <FastLED.h>

#include "Controller.h"
#include "Render/Camera.h"
//#include "Flash/PixelGroups/P3HUB75.h"
#include "Flash/PixelGroups/LinearPixels.h"

//HUB75 SETUP ~~~~~~~~~~
#define RESOLUTION_X 128 //Pixel count of your HUB75 panel
#define RESOLUTION_Y 64
#define P_VALUE 2 //Use whatever P{VALUE} your panels are, Example: P2, P3, P4
#define ENABLE_HUB75_REFRESH    1
#define COLOR_DEPTH 24                  // Choose the color depth used for storing pixels in the layers: 24 or 48 (24 is good for most sketches - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24)
#define VERTICAL_STRETCH 0.8 //float 0.0 - 2.0 give best effects, usually around 0.8 for P2
#define HORIZONTAL_STRETCH 0.5 //float 0.0 - 2.0 give best effects, usually around 0.5  for P2
#define PIXELGROUP_TYPE 1 //0 = Base CoelaCan't formatting (better for memory), 1 = Slightly better FPS performance but more memory
const uint8_t kPanelType = SM_PANELTYPE_HUB75_64ROW_MOD32SCAN;   // Choose the configuration that matches your panels.  See more details in MatrixCommonHub75.h and the docs: https://github.com/pixelmatix/SmartMatrix/wiki
//~~~~~~~~~~~~

const uint16_t kMatrixWidth = RESOLUTION_X;       // Set to the width of your display, must be a multiple of 8
const uint16_t kMatrixHeight = RESOLUTION_Y*2;      // Set to the height of your display
const uint8_t kRefreshDepth = 36;       // Tradeoff of color quality vs refresh rate, max brightness, and RAM usage.  36 is typically good, drop down to 24 if you need to.  On Teensy, multiples of 3, up to 48: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48.  On ESP32: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save RAM, more to keep from dropping frames and automatically lowering refresh rate.  (This isn't used on ESP32, leave as default)
const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_NONE);        // see docs for options: https://github.com/pixelmatix/SmartMatrix/wiki
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

//APA102
#define ENABLE_APA102_REFRESH   1
const uint16_t kApaMatrixWidth = 100;          // adjust this to your APA matrix/strip
const uint16_t kApaMatrixHeight = 1;         // set kApaMatrixHeight to 1 for a strip
const uint8_t kApaRefreshDepth = 36;        // not used for APA matrices as of now
const uint8_t kApaDmaBufferRows = 1;        // not used for APA matrices as of now
const uint8_t kApaPanelType = 0;            // not used for APA matrices as of now
const uint32_t kApaMatrixOptions = (SM_APA102_OPTIONS_COLOR_ORDER_BGR);      // The default color order is BGR, change here to match your LEDs
const uint8_t kApaBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

SMARTMATRIX_APA_ALLOCATE_BUFFERS(apamatrix, kApaMatrixWidth, kApaMatrixHeight, kApaRefreshDepth, kApaDmaBufferRows, kApaPanelType, kApaMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(apaBackgroundLayer, kApaMatrixWidth, kApaMatrixHeight, COLOR_DEPTH, kApaBackgroundLayerOptions);


class SmartMatrixHUB75 : public Controller {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);

    Transform camTransform = Transform(Vector3D(), Vector3D(0, 0, 0), Vector3D(HORIZONTAL_STRETCH, VERTICAL_STRETCH, 1));
    Transform camSideTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));

    PixelGroup camPixels = createPanel();
    //Vector2D* panel = createPanel();
    //PixelGroup camPixels = PixelGroup(panel, RESOLUTION_X*RESOLUTION_Y);
    
    //PixelGroup camPixels = PixelGroup(P3HUB75, 2048);
    PixelGroup camSidePixels = PixelGroup(LinearPixels, 100);

    Camera camMain = Camera(&camTransform, &cameraLayout, &camPixels);
    Camera camSidePanels = Camera(&camSideTransform, &cameraLayout, &camSidePixels);

    Camera* cameras[2] = { &camMain, &camSidePanels };

public:
    SmartMatrixHUB75(uint8_t maxBrightness, uint8_t maxAccentBrightness) : Controller(cameras, 2, maxBrightness, maxAccentBrightness){}

    PixelGroup createPanel(){

        if(PIXELGROUP_TYPE == 0){
            return PixelGroup(Vector2D(RESOLUTION_X*P_VALUE,RESOLUTION_Y*P_VALUE), Vector2D(RESOLUTION_X,RESOLUTION_Y), RESOLUTION_Y*2, RESOLUTION_X*RESOLUTION_Y);
        } else {
            static Vector2D panelConfig[RESOLUTION_X*RESOLUTION_Y] = {};
            int count = 0;
            for (int y = 0; y < RESOLUTION_Y; y++) {
                for (int x = 0; x < RESOLUTION_X; x++){
                    panelConfig[count]=Vector2D((float)x*P_VALUE,(float)y*P_VALUE);
                    count++;
                }
            }
            return PixelGroup(panelConfig, RESOLUTION_X*RESOLUTION_Y);
        }
        return camPixels;
    }

    void Initialize() override{
        //HUB75
        matrix.addLayer(&backgroundLayer);
        matrix.begin();
        
        matrix.setRefreshRate(120);

        backgroundLayer.swapBuffers();//for ESP32 - first is ignored
    }

    void Display() override {
        matrix.setBrightness(brightness);

        for (uint16_t y = 0; y < RESOLUTION_Y; y++) {
            for (uint16_t x = 0; x < RESOLUTION_X; x++){
                uint16_t pixelNum = y * RESOLUTION_X + x;

                rgb24 rgbColor = rgb24((uint16_t)camPixels.GetColor(pixelNum)->R, (uint16_t)camPixels.GetColor(pixelNum)->G, (uint16_t)camPixels.GetColor(pixelNum)->B);

                
                backgroundLayer.drawPixel(x, RESOLUTION_Y - y, rgbColor);
                backgroundLayer.drawPixel(RESOLUTION_X - 1 - x, kMatrixHeight-y-1, rgbColor);//mirroring is vertical, provided by assigning y values up to 2*RESOLUTION_Y
            }
        }
        
        backgroundLayer.swapBuffers();
    }
};
