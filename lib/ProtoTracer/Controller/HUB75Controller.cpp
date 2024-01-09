#include "HUB75Controller.h"

//Macro calls from SmartMatrix library included in SmartMatrixHUB75
SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

SMARTMATRIX_APA_ALLOCATE_BUFFERS(apamatrix, kApaMatrixWidth, kApaMatrixHeight, kApaRefreshDepth, kApaDmaBufferRows, kApaPanelType, kApaMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(apaBackgroundLayer, kApaMatrixWidth, kApaMatrixHeight, COLOR_DEPTH, kApaBackgroundLayerOptions);

HUB75Controller::HUB75Controller(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness) : Controller(cameras, maxBrightness, maxAccentBrightness){}

void HUB75Controller::Initialize(){
    //HUB75
    matrix.addLayer(&backgroundLayer);
    matrix.begin();
    matrix.setRefreshRate(240);

    backgroundLayer.swapBuffers();//for ESP32 - first is ignored

    //APA102
    apamatrix.addLayer(&apaBackgroundLayer);
    apamatrix.begin();
    apamatrix.setRefreshRate(240);
}

void HUB75Controller::Display(){
    UpdateBrightness();

    matrix.setBrightness(brightness);
    apamatrix.setBrightness(accentBrightness);

    IPixelGroup* camPixels = cameras->GetCameras()[0]->GetPixelGroup();
    IPixelGroup* camSidePixelsL = cameras->GetCameras()[1]->GetPixelGroup();
    IPixelGroup* camSidePixelsR = cameras->GetCameras()[2]->GetPixelGroup();

    for (uint16_t y = 0; y < 32; y++) {
        for (uint16_t x = 0; x < 64; x++){
            uint16_t pixelNum = y * 64 + x;

            rgb24 rgbColor = rgb24((uint16_t)camPixels->GetColor(pixelNum)->R, (uint16_t)camPixels->GetColor(pixelNum)->G, (uint16_t)camPixels->GetColor(pixelNum)->B);

            backgroundLayer.drawPixel(x, (31 - y), rgbColor);
            backgroundLayer.drawPixel(63 - x, (31 - y) + 32, rgbColor);
        }
    }

    backgroundLayer.swapBuffers(false);

    for (uint16_t x = 0; x < kApaMatrixWidth; x++){
        rgb24 rgbColorL = rgb24((uint16_t)camSidePixelsL->GetColor(x)->R, (uint16_t)camSidePixelsL->GetColor(x)->G, (uint16_t)camSidePixelsL->GetColor(x)->B);
        rgb24 rgbColorR = rgb24((uint16_t)camSidePixelsR->GetColor(x)->R, (uint16_t)camSidePixelsR->GetColor(x)->G, (uint16_t)camSidePixelsR->GetColor(x)->B);
        
        apaBackgroundLayer.drawPixel(x + 88, 0, rgbColorL);
        apaBackgroundLayer.drawPixel(x, 0, rgbColorR);
    }
    
    apaBackgroundLayer.swapBuffers(false);
}

void HUB75Controller::SetBrightness(uint8_t maxBrightness){
    this->maxBrightness = maxBrightness * 25 + 5;
    
    if(isOn){//past soft start
        this->brightness = maxBrightness * 25 + 5;
    }
}

void HUB75Controller::SetAccentBrightness(uint8_t maxAccentBrightness){
    this->maxAccentBrightness = maxAccentBrightness * 12 + 5;
    
    if(isOn){//past soft start
        this->accentBrightness = maxAccentBrightness * 12 + 5;
    }
}