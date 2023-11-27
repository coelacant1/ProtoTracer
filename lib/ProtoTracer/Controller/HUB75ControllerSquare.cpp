#include "HUB75ControllerSquare.h"

//Macro calls from SmartMatrix library included in SmartMatrixHUB75
SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

SMARTMATRIX_APA_ALLOCATE_BUFFERS(apamatrix, kApaMatrixWidth, kApaMatrixHeight, kApaRefreshDepth, kApaDmaBufferRows, kApaPanelType, kApaMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(apaBackgroundLayer, kApaMatrixWidth, kApaMatrixHeight, COLOR_DEPTH, kApaBackgroundLayerOptions);

HUB75ControllerSquare::HUB75ControllerSquare(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness) : Controller(cameras, maxBrightness, maxAccentBrightness){}

void HUB75ControllerSquare::Initialize(){
    matrix.addLayer(&backgroundLayer);
    matrix.begin();
    matrix.setRefreshRate(240);

    backgroundLayer.swapBuffers();//for ESP32 - first is ignored
}

void HUB75ControllerSquare::Display(){
    UpdateBrightness();

    matrix.setBrightness(brightness);

    IPixelGroup* camPixelsRight = cameras->GetCameras()[0]->GetPixelGroup();
    IPixelGroup* camPixelsLeft = cameras->GetCameras()[1]->GetPixelGroup();

    for (uint16_t y = 0; y < 32; y++) {
        for (uint16_t x = 0; x < 64; x++){
            uint16_t pixelNum = y * 64 + x;

            rgb24 rgbColorLeft = rgb24((uint16_t)camPixelsLeft->GetColor(pixelNum)->R, (uint16_t)camPixelsLeft->GetColor(pixelNum)->G, (uint16_t)camPixelsLeft->GetColor(pixelNum)->B);
            rgb24 rgbColorRight = rgb24((uint16_t)camPixelsRight->GetColor(pixelNum)->R, (uint16_t)camPixelsRight->GetColor(pixelNum)->G, (uint16_t)camPixelsRight->GetColor(pixelNum)->B);

            backgroundLayer.drawPixel(63 - x, (31 - y), rgbColorLeft);
            backgroundLayer.drawPixel(x, (y) + 32, rgbColorRight);
        }
    }

    backgroundLayer.swapBuffers(false);
}

void HUB75ControllerSquare::SetBrightness(uint8_t maxBrightness){
    this->maxBrightness = maxBrightness * 25 + 5;
    
    if(isOn){//past soft start
        this->brightness = maxBrightness * 25 + 5;
    }
}

void HUB75ControllerSquare::SetAccentBrightness(uint8_t maxAccentBrightness){
    this->maxAccentBrightness = maxAccentBrightness * 12 + 5;
    
    if(isOn){//past soft start
        this->accentBrightness = maxAccentBrightness * 12 + 5;
    }
}