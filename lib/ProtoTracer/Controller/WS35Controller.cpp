#include "WS35Controller.h"

WS35Controller::WS35Controller(CameraManager* cameras, uint8_t maxBrightness) : Controller(cameras, maxBrightness, 0){}

void WS35Controller::Initialize(){
    leds.begin();
    leds.show();
}

void WS35Controller::Display(){
    UpdateBrightness();

    int offset;

    IPixelGroup* camRghtPixels = cameras->GetCameras()[0]->GetPixelGroup();
    IPixelGroup* camLeftPixels = cameras->GetCameras()[1]->GetPixelGroup();

    for (int i = 0; i < 571; i++){
        *camLeftPixels->GetColor(i) = camLeftPixels->GetColor(i)->Scale(brightness);
        *camRghtPixels->GetColor(i) = camRghtPixels->GetColor(i)->Scale(brightness);
    }

    for (int i = 0; i < 571; i++) {
        if (i < 346){
            offset = i + 225;

            leds.setPixel(i + 346 * 4, camLeftPixels->GetColor(offset)->R, camLeftPixels->GetColor(offset)->G, camLeftPixels->GetColor(offset)->B);//Pin 7
            leds.setPixel(i + 346 * 5, camRghtPixels->GetColor(i)->R, camRghtPixels->GetColor(i)->G, camRghtPixels->GetColor(i)->B);//Pin 8
        }
        else{
            offset = i - 346;

            leds.setPixel(i + 346 * 6 - 346, camLeftPixels->GetColor(offset)->R, camLeftPixels->GetColor(offset)->G, camLeftPixels->GetColor(offset)->B);//Pin 8
            leds.setPixel(i + 346 * 7 - 346, camRghtPixels->GetColor(i)->R, camRghtPixels->GetColor(i)->G, camRghtPixels->GetColor(i)->B);//Pin 8
        }
    }
    
    leds.show();
}

void WS35Controller::SetPixels(uint8_t strip, uint16_t led, RGBColor rgb){
    leds.setPixel(346 * strip + led, rgb.R, rgb.G, rgb.B);//Pin 8
}

void WS35Controller::SetBrightness(uint8_t maxBrightness){
    this->maxBrightness = maxBrightness * 25 + 5;
    
    if(isOn){//past soft start
        this->brightness = maxBrightness * 25 + 5;
    }
}

void WS35Controller::SetAccentBrightness(uint8_t maxAccentBrightness){
    this->maxAccentBrightness = maxAccentBrightness * 25 + 5;
    
    if(isOn){//past soft start
        this->accentBrightness = maxAccentBrightness * 25 + 5;
    }
}