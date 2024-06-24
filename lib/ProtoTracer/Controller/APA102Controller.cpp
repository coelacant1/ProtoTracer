#include "APA102Controller.h"

//Macro calls from SmartMatrix library included in SmartMatrixAPA102
SMARTMATRIX_APA_ALLOCATE_BUFFERS(apamatrix, kApaMatrixWidth, kApaMatrixHeight, kApaRefreshDepth, kApaDmaBufferRows, kApaPanelType, kApaMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(apaBackgroundLayer, kApaMatrixWidth, kApaMatrixHeight, COLOR_DEPTH, kApaBackgroundLayerOptions);

APA102Controller::APA102Controller(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness) : Controller(cameras, maxBrightness, maxAccentBrightness){}

void APA102Controller::Initialize(){
    //APA102
    apamatrix.addLayer(&apaBackgroundLayer);
    apamatrix.begin();
    apamatrix.setRefreshRate(240);
}

void APA102Controller::Display(){
    UpdateBrightness();

    apamatrix.setBrightness(brightness);

    IPixelGroup* camSidePixelsL = cameras->GetCameras()[0]->GetPixelGroup();
    IPixelGroup* camSidePixelsR = cameras->GetCameras()[1]->GetPixelGroup();

    for (uint16_t x = 0; x < kApaMatrixWidth / 2; x++){
        rgb24 rgbColorL = rgb24((uint16_t)camSidePixelsL->GetColor(x)->R, (uint16_t)camSidePixelsL->GetColor(x)->G, (uint16_t)camSidePixelsL->GetColor(x)->B);
        rgb24 rgbColorR = rgb24((uint16_t)camSidePixelsR->GetColor(x)->R, (uint16_t)camSidePixelsR->GetColor(x)->G, (uint16_t)camSidePixelsR->GetColor(x)->B);
        
        apaBackgroundLayer.drawPixel(x, 0, rgbColorL);
        apaBackgroundLayer.drawPixel(x + 88, 0, rgbColorR);
    }
    
    apaBackgroundLayer.swapBuffers(false);
}

void APA102Controller::SetBrightness(uint8_t maxBrightness){
    this->maxBrightness = maxBrightness * 25 + 5;
    
    if(isOn){//past soft start
        this->brightness = maxBrightness * 25 + 5;
    }
}

void APA102Controller::SetAccentBrightness(uint8_t maxAccentBrightness){
    this->maxAccentBrightness = maxAccentBrightness * 12 + 5;
    
    if(isOn){//past soft start
        this->accentBrightness = maxAccentBrightness * 12 + 5;
    }
}