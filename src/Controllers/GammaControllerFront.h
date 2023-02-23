#include <Arduino.h>
#include <OctoWS2811.h>

#include "Controller.h"
#include "Render/Camera.h"
#include "Flash/PixelGroups/KaiborgV1Pixels.h"

const int ledsPerStrip = 346;
DMAMEM int displayMemory[346 * 6];
int drawingMemory[346 * 6];
const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

class GammaControllerFront : public Controller {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);

    Transform camTopTransform = Transform(Vector3D(0.0f, 0.0f, -139.06f), Vector3D(46.445f, 130.121f, -500.0f), Vector3D(1, 1, 1));
    Transform camBotTransform = Transform(Vector3D(0.0f, 180.0f, 0.0f), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));

    PixelGroup<571> camTopPixels = PixelGroup<571>(KaiborgV1Pixels, IPixelGroup::ZEROTOMAX);
    PixelGroup<571> camBotPixels = PixelGroup<571>(KaiborgV1Pixels, IPixelGroup::MAXTOZERO);

    Camera<571> camTop = Camera<571>(&camTopTransform, &cameraLayout, &camTopPixels);
    Camera<571> camBot = Camera<571>(&camBotTransform, &cameraLayout, &camBotPixels);

    CameraBase* cameras[2] = { &camTop, &camBot };

public:
    GammaControllerFront(uint8_t maxBrightness) : Controller(cameras, 2, maxBrightness, 0){}

    void Initialize() override{
        leds.begin();
        leds.show();
    }

    void Display() override {
        int offset;

        for (int i = 0; i < 571; i++){
            *camBotPixels.GetColor(i) = camBotPixels.GetColor(i)->Scale(brightness);
            *camTopPixels.GetColor(i) = camTopPixels.GetColor(i)->Scale(brightness);
        }

        //0: BLT, RIGHT
        //1: FLT, RIGHT
        //2: BRT, LEFT
        //3: FRT, LEFT
        //4: BRB, RIGHT
        //5: FRB, RIGHT
        //6: BLB, LEFT
        //7: FLB, LEFT

        for (int i = 0; i < 571; i++) {
            if (i < 346){
                offset = i + 225;
                leds.setPixel(i + 346 * 0, camTopPixels.GetColor(i)->R, camTopPixels.GetColor(i)->G, camTopPixels.GetColor(i)->B);//Top Right
                leds.setPixel(570 - i + 346 * 4, camBotPixels.GetColor(i)->R, camBotPixels.GetColor(i)->G, camBotPixels.GetColor(i)->B);//Bottom Right

                leds.setPixel(i + 346 * 2, camTopPixels.GetColor(570 - offset)->R, camTopPixels.GetColor(570 - offset)->G, camTopPixels.GetColor(570 - offset)->B);//Top Left
                leds.setPixel(i + 346 * 6, camBotPixels.GetColor(offset)->R, camBotPixels.GetColor(offset)->G, camBotPixels.GetColor(offset)->B);//Bottom Left
            }
            else{
                offset = i - 346;
                leds.setPixel(i + 346 * 1 - 346, camTopPixels.GetColor(i)->R, camTopPixels.GetColor(i)->G, camTopPixels.GetColor(i)->B);//Top Right
                leds.setPixel(570 - i + 346 * 5 - 346, camBotPixels.GetColor(i)->R, camBotPixels.GetColor(i)->G, camBotPixels.GetColor(i)->B);//Bottom Right

                leds.setPixel(i + 346 * 3 - 346, camTopPixels.GetColor(570 - offset)->R, camTopPixels.GetColor(570 - offset)->G, camTopPixels.GetColor(570 - offset)->B);//Top Left
                leds.setPixel(i + 346 * 7 - 346, camBotPixels.GetColor(offset)->R, camBotPixels.GetColor(offset)->G, camBotPixels.GetColor(offset)->B);//Bottom Left
            }
        }
        
        leds.show();
    }

    void SetPixels(uint8_t strip, uint16_t led, RGBColor rgb){
        leds.setPixel(346 * strip + led, rgb.R, rgb.G, rgb.B);//Pin 8
    }
};
