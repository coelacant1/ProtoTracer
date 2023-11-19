#pragma once

#include <Arduino.h>
#include <OctoWS2811.h>
#include "Controller.h"
#include "Render/Camera.h"
#include "Flash/PixelGroups/ProtoDR.h"
#include "Flash/PixelGroups/ProtoDRMini.h"

const int ledsPerStrip = 306;
DMAMEM int displayMemory[306 * 6];
int drawingMemory[306 * 6];
const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

class ProtoDRController : public Controller {
public:
    enum Side{
        LEFT,
        RIGHT
    };

private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);

    Transform camFronTopTransform = Transform(Vector3D(   35.25f, -2.25f, 216.5f), Vector3D(  68.25f, 210.75f, 31.0f - 5000.0f), Vector3D(-1, 1, 1));
    Transform camRearTopTransform = Transform(Vector3D(   -36.5f, 14.0f, 45.0f), Vector3D(  15.5f,   117.5f,   -43.5f - 5000.0f), Vector3D(-1, 1, 1));
    Transform camFronBotTransform = Transform(Vector3D(   20.25f,   7.0f,   1.0f), Vector3D(  0, 0, 0 - 5000.0f), Vector3D( 1, 1, 1));
    Transform camRearBotTransform = Transform(Vector3D(   -20.75f,   -16.5f,   177.5f), Vector3D(  17, 122, -42 - 5000.0f), Vector3D( 1, 1, 1));

    Transform camRearMidTransform;
    Transform camFronMidTransform;
    
    PixelGroup<306> camFronTopPixels = PixelGroup<306>(ProtoDRCamera);
    PixelGroup<306> camRearTopPixels = PixelGroup<306>(ProtoDRCamera);
    PixelGroup<306> camFronBotPixels = PixelGroup<306>(ProtoDRCamera);
    PixelGroup<306> camRearBotPixels = PixelGroup<306>(ProtoDRCamera);
    PixelGroup<89> camRearMidPixels = PixelGroup<89>(ProtoDRMini);
    PixelGroup<89> camFronMidPixels = PixelGroup<89>(ProtoDRMini);
    
    Camera<306> camFronTop = Camera<306>(&camFronTopTransform, &cameraLayout, &camFronTopPixels);
    Camera<306> camRearTop = Camera<306>(&camRearTopTransform, &cameraLayout, &camRearTopPixels);
    Camera<306> camFronBot = Camera<306>(&camFronBotTransform, &cameraLayout, &camFronBotPixels);
    Camera<306> camRearBot = Camera<306>(&camRearBotTransform, &cameraLayout, &camRearBotPixels);
    Camera<89> camRearMid = Camera<89>(&camRearMidTransform, &cameraLayout, &camRearMidPixels);
    Camera<89> camFronMid = Camera<89>(&camFronMidTransform, &cameraLayout, &camFronMidPixels);

    CameraBase* cameras[6] = { &camFronTop, &camRearTop, &camFronBot, &camRearBot, &camRearMid, &camFronMid };

public:
    ProtoDRController(uint8_t maxBrightness, Side side) : Controller(cameras, 6, maxBrightness, 0){
        switch(side){
            case LEFT:
                camRearMidTransform = Transform(Vector3D(13.5f, -189.0f, 312.5f), Vector3D(-59.0f, 191.0f, 175.0f - 5000.0f), Vector3D(1, 1, 1));
                camFronMidTransform = Transform(Vector3D(-13.5f, 171.0f, 132.5f), Vector3D(-126.0f, 117.5f, 191.0f - 5000.0f), Vector3D(1, 1, 1));
                break;
            case RIGHT:
                camRearMidTransform = Transform(Vector3D(-7.5f, 15.5f, 44.5f), Vector3D(-195.0f, 184.0f, -113.0f - 5000.0f), Vector3D(1, 1, 1));
                camFronMidTransform = Transform(Vector3D(7.5f, -15.5f, -135.5f), Vector3D(10.5f, 122.5f, -46.5f - 5000.0f), Vector3D(1, 1, 1));
                break;
            default:
                break;
        }
    }

    void Initialize() override{
        leds.begin();
        leds.show();
    }

    void Display() override {
        for (int i = 0; i < 306; i++) {
            *camFronTopPixels.GetColor(i) = camFronTopPixels.GetColor(i)->Scale(brightness);
            *camRearTopPixels.GetColor(i) = camRearTopPixels.GetColor(i)->Scale(brightness);
            *camFronBotPixels.GetColor(i) = camFronBotPixels.GetColor(i)->Scale(brightness);
            *camRearBotPixels.GetColor(i) = camRearBotPixels.GetColor(i)->Scale(brightness);

            leds.setPixel(i + 2142,  camFronTopPixels.GetColor(i)->R, camFronTopPixels.GetColor(i)->G, camFronTopPixels.GetColor(i)->B);//918
            leds.setPixel(i + 918,   camRearTopPixels.GetColor(i)->R, camRearTopPixels.GetColor(i)->G, camRearTopPixels.GetColor(i)->B);//306
            leds.setPixel(i + 306,   camFronBotPixels.GetColor(i)->R, camFronBotPixels.GetColor(i)->G, camFronBotPixels.GetColor(i)->B);//1530
            leds.setPixel(i + 1530,  camRearBotPixels.GetColor(i)->R, camRearBotPixels.GetColor(i)->G, camRearBotPixels.GetColor(i)->B);//2142
            
            if(i < 89){
                *camRearMidPixels.GetColor(i) = camRearMidPixels.GetColor(i)->Scale(brightness);
                *camFronMidPixels.GetColor(i) = camFronMidPixels.GetColor(i)->Scale(brightness);
                
                leds.setPixel(i + 1836, camRearMidPixels.GetColor(i)->R, camRearMidPixels.GetColor(i)->G, camRearMidPixels.GetColor(i)->B);//1224
                leds.setPixel(i + 612,  camFronMidPixels.GetColor(i)->R, camFronMidPixels.GetColor(i)->G, camFronMidPixels.GetColor(i)->B);//1836
            }
        }
        
        leds.show();
    }
};
