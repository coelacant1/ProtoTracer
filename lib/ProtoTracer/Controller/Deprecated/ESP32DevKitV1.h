#include <Arduino.h>

#include "Controller.h"
#include "Render/Camera.h"

//HUB75
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>
#include <FastLED.h>

// Configure for your panel(s) as appropriate!
#define PANEL_RES_X 64 // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 32 // Number of pixels tall of each INDIVIDUAL panel module.

#define NUM_ROWS 2 // Number of rows of chained INDIVIDUAL PANELS
#define NUM_COLS 1 // Number of INDIVIDUAL PANELS per ROW
#define PANEL_CHAIN NUM_ROWS*NUM_COLS    // total number of panels chained one to another

// Change this to your needs, for details on VirtualPanel pls read the PDF!
#define SERPENT true


// placeholder for the matrix object
MatrixPanel_I2S_DMA *dma_display = nullptr;

// placeholder for the virtual display object
VirtualMatrixPanel  *virtualDisp = nullptr;

class ESP32DevKitV1 : public Controller {
private:
    Transform camTransform1 = Transform(Vector3D(), Vector3D(0, 0.0f, 0), Vector3D(1, 1, 1));
    Transform camTransform2 = Transform(Vector3D(), Vector3D(0, 96.0f, 0), Vector3D(1, 1, 1));

    Vector2D size = Vector2D(192.0f, 96.0f);
    Vector2D position = Vector2D(0.0f, 0.0f);

    PixelGroup camPixels1 = PixelGroup(size, position, 64, 2048);
    PixelGroup camPixels2 = PixelGroup(size, position, 64, 2048);
    
    Camera camMain1 = Camera(&camTransform1, &camPixels1);
    Camera camMain2 = Camera(&camTransform2, &camPixels2);

    //Camera* cameras[1] = { &camMain1 };
    Camera* cameras[2] = { &camMain1, &camMain2 };

public:
    ESP32DevKitV1(uint8_t maxBrightness) : Controller(cameras, 2, maxBrightness, 0){}

    void Initialize() override{

        HUB75_I2S_CFG mxconfig(
                PANEL_RES_X,   // module width
                PANEL_RES_Y,   // module height
                PANEL_CHAIN    // chain length
        );

        // OK, now we can create our matrix object
        dma_display = new MatrixPanel_I2S_DMA(mxconfig);

        // let's adjust default brightness to about 75%
        dma_display->setBrightness8(128);    // range is 0-255, 0 - 0%, 255 - 100%

        // Allocate memory and start DMA display
        if(!dma_display->begin()){
            Serial.println("****** I2S memory allocation failed ***********");
        }

        // create VirtualDisplay object based on our newly created dma_display object
        virtualDisp = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, SERPENT);
        
        dma_display->clearScreen();
    }

    void Display() override {
        dma_display->setBrightness8(brightness);
        
        for (uint16_t y = 0; y < 32; y++) {
            for (uint16_t x = 0; x < 64; x++){
                uint16_t pixelNum = y * 64 + x;

                virtualDisp->drawPixelRGB888(x, y, (uint8_t)camPixels1.GetColor(pixelNum)->R, (uint8_t)camPixels1.GetColor(pixelNum)->G, (uint8_t)camPixels1.GetColor(pixelNum)->B);
            }
        }
        
        for (uint16_t y = 0; y < 32; y++) {
            for (uint16_t x = 0; x < 64; x++){
                uint16_t pixelNum = y * 64 + x;

                virtualDisp->drawPixelRGB888(x, y + 32, (uint8_t)camPixels2.GetColor(pixelNum)->R, (uint8_t)camPixels2.GetColor(pixelNum)->G, (uint8_t)camPixels2.GetColor(pixelNum)->B);
            }
        }
    }
};
