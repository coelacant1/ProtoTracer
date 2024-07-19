#include "WS35BetaController.h"

DMAMEM int dmaDisplayMemory[346 * 6];

WS35BetaController::WS35BetaController(CameraManager* cameras, uint8_t maxBrightness) : Controller(cameras, maxBrightness, 0), leds(OctoWS2811(ledsPerStrip, dmaDisplayMemory, drawingMemory, config)){
}

void WS35BetaController::Initialize(){
    leds.begin();
    leds.show();
}

void WS35BetaController::Display(){
    UpdateBrightness();

    IPixelGroup* camRghtFrntPixels = cameras->GetCameras()[0]->GetPixelGroup();
    IPixelGroup* camRghtRearPixels = cameras->GetCameras()[1]->GetPixelGroup();

    int offset, inverseOffset;

    for (int i = 0; i < 571; i++){
        *camRghtFrntPixels->GetColor(i) = camRghtFrntPixels->GetColor(i)->Scale(brightness);
        *camRghtRearPixels->GetColor(i) = camRghtRearPixels->GetColor(i)->Scale(brightness);
    }

    for (int i = 0; i < 571; i++) {
        if (i < 346){
            offset = i + 225;
            inverseOffset = 570 - offset;

            //Rear Panels
            leds.setPixel(i + 346 * 0, camRghtRearPixels->GetColor(inverseOffset)->R, camRghtRearPixels->GetColor(inverseOffset)->G, camRghtRearPixels->GetColor(inverseOffset)->B);//LEFT
            leds.setPixel(i + 346 * 1, camRghtRearPixels->GetColor(i)->R, camRghtRearPixels->GetColor(i)->G, camRghtRearPixels->GetColor(i)->B);//Pin 8

            //Front Panels
            leds.setPixel(i + 346 * 4, camRghtFrntPixels->GetColor(inverseOffset)->R, camRghtFrntPixels->GetColor(inverseOffset)->G, camRghtFrntPixels->GetColor(inverseOffset)->B);//Pin 7
            leds.setPixel(i + 346 * 5, camRghtFrntPixels->GetColor(i)->R, camRghtFrntPixels->GetColor(i)->G, camRghtFrntPixels->GetColor(i)->B);//Pin 8
        }
        else{
            offset = i - 346;
            inverseOffset = 570 - offset;

            //Rear Panels
            leds.setPixel(i + 346 * 2 - 346, camRghtRearPixels->GetColor(inverseOffset)->R, camRghtRearPixels->GetColor(inverseOffset)->G, camRghtRearPixels->GetColor(inverseOffset)->B);//Pin 8
            leds.setPixel(i + 346 * 3 - 346, camRghtRearPixels->GetColor(i)->R, camRghtRearPixels->GetColor(i)->G, camRghtRearPixels->GetColor(i)->B);//Pin 8

            //Front Panels
            leds.setPixel(i + 346 * 6 - 346, camRghtFrntPixels->GetColor(inverseOffset)->R, camRghtFrntPixels->GetColor(inverseOffset)->G, camRghtFrntPixels->GetColor(inverseOffset)->B);//Pin 8
            leds.setPixel(i + 346 * 7 - 346, camRghtFrntPixels->GetColor(i)->R, camRghtFrntPixels->GetColor(i)->G, camRghtFrntPixels->GetColor(i)->B);//Pin 8
        }
    }

    leds.show();
}

void WS35BetaController::SetPixels(uint8_t strip, uint16_t led, RGBColor rgb){
    leds.setPixel(346 * strip + led, rgb.R, rgb.G, rgb.B);//Pin 8
}

void WS35BetaController::SetBrightness(uint8_t maxBrightness){
    this->maxBrightness = maxBrightness * 25 + 5;
    
    if(isOn){//past soft start
        this->brightness = maxBrightness * 25 + 5;
    }
}

void WS35BetaController::SetAccentBrightness(uint8_t maxAccentBrightness){
    this->maxAccentBrightness = maxAccentBrightness * 25 + 5;
    
    if(isOn){//past soft start
        this->accentBrightness = maxAccentBrightness * 25 + 5;
    }
}