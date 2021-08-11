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

    Transform camFronTopTransform = Transform(Vector3D(   35.25f, -2.25f, 216.5f), Vector3D(  68.25f, 210.75f, 31.0f), Vector3D(-1, 1, 1));
    Transform camRearTopTransform = Transform(Vector3D(   -36.5f, 14.0f, 45.0f), Vector3D(  15.5f,   117.5f,   -43.5f), Vector3D(-1, 1, 1));
    Transform camFronBotTransform = Transform(Vector3D(   20.25f,   7.0f,   1.0f), Vector3D(  0, 0, 0), Vector3D( 1, 1, 1));
    Transform camRearBotTransform = Transform(Vector3D(   -20.75f,   -16.5f,   177.5f), Vector3D(  17, 122, -42), Vector3D( 1, 1, 1));

    Transform camRearMidTransform;
    Transform camFronMidTransform;
    
    PixelGroup camFronTopPixels = PixelGroup(ProtoDRCamera, 306);
    PixelGroup camRearTopPixels = PixelGroup(ProtoDRCamera, 306);
    PixelGroup camFronBotPixels = PixelGroup(ProtoDRCamera, 306);
    PixelGroup camRearBotPixels = PixelGroup(ProtoDRCamera, 306);
    PixelGroup camRearMidPixels = PixelGroup(ProtoDRMini, 89);
    PixelGroup camFronMidPixels = PixelGroup(ProtoDRMini, 89);
    
    Camera camFronTop = Camera(&camFronTopTransform, &cameraLayout, &camFronTopPixels);
    Camera camRearTop = Camera(&camRearTopTransform, &cameraLayout, &camRearTopPixels);
    Camera camFronBot = Camera(&camFronBotTransform, &cameraLayout, &camFronBotPixels);
    Camera camRearBot = Camera(&camRearBotTransform, &cameraLayout, &camRearBotPixels);
    Camera camRearMid = Camera(&camRearMidTransform, &cameraLayout, &camRearMidPixels);
    Camera camFronMid = Camera(&camFronMidTransform, &cameraLayout, &camFronMidPixels);

    Camera* cameras[6] = { &camFronTop, &camRearTop, &camFronBot, &camRearBot, &camRearMid, &camFronMid };
    uint8_t maxBrightness = 0;

public:
    ProtoDRController(uint8_t maxBrightness, Side side) : Controller(cameras, 6){
        this->maxBrightness = maxBrightness;

        switch(side){
            case LEFT:
                camRearMidTransform = Transform(Vector3D(13.5f, -189.0f, 312.5f), Vector3D(-59.0f, 191.0f, 175.0f), Vector3D(1, 1, 1));
                camFronMidTransform = Transform(Vector3D(-13.5f, 171.0f, 132.5f), Vector3D(-126.0f, 117.5f, 191.0f), Vector3D(1, 1, 1));
                break;
            case RIGHT:
                camRearMidTransform = Transform(Vector3D(-7.5f, 15.5f, 44.5f), Vector3D(-195.0f, 184.0f, -113.0f), Vector3D(1, 1, 1));
                camFronMidTransform = Transform(Vector3D(7.5f, -15.5f, -135.5f), Vector3D(10.5f, 122.5f, -46.5f), Vector3D(1, 1, 1));
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
            camFronTopPixels.GetPixel(i)->Color = camFronTopPixels.GetPixel(i)->Color.Scale(maxBrightness);
            camRearTopPixels.GetPixel(i)->Color = camRearTopPixels.GetPixel(i)->Color.Scale(maxBrightness);
            camFronBotPixels.GetPixel(i)->Color = camFronBotPixels.GetPixel(i)->Color.Scale(maxBrightness);
            camRearBotPixels.GetPixel(i)->Color = camRearBotPixels.GetPixel(i)->Color.Scale(maxBrightness);

            leds.setPixel(i + 2142,  camFronTopPixels.GetPixel(i)->Color.R, camFronTopPixels.GetPixel(i)->Color.G, camFronTopPixels.GetPixel(i)->Color.B);//918
            leds.setPixel(i + 918,   camRearTopPixels.GetPixel(i)->Color.R, camRearTopPixels.GetPixel(i)->Color.G, camRearTopPixels.GetPixel(i)->Color.B);//306
            leds.setPixel(i + 306,   camFronBotPixels.GetPixel(i)->Color.R, camFronBotPixels.GetPixel(i)->Color.G, camFronBotPixels.GetPixel(i)->Color.B);//1530
            leds.setPixel(i + 1530,  camRearBotPixels.GetPixel(i)->Color.R, camRearBotPixels.GetPixel(i)->Color.G, camRearBotPixels.GetPixel(i)->Color.B);//2142
            
            if(i < 89){
                camRearMidPixels.GetPixel(i)->Color = camRearMidPixels.GetPixel(i)->Color.Scale(maxBrightness);
                camFronMidPixels.GetPixel(i)->Color = camFronMidPixels.GetPixel(i)->Color.Scale(maxBrightness);
                
                leds.setPixel(i + 1836, camRearMidPixels.GetPixel(i)->Color.R, camRearMidPixels.GetPixel(i)->Color.G, camRearMidPixels.GetPixel(i)->Color.B);//1224
                leds.setPixel(i + 612,  camFronMidPixels.GetPixel(i)->Color.R, camFronMidPixels.GetPixel(i)->Color.G, camFronMidPixels.GetPixel(i)->Color.B);//1836
            }
        }
        
        leds.show();
    }
};
