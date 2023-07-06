#include <Arduino.h>
#include <OctoWS2811.h>

#include "Controller.h"
#include "Render/Camera.h"
#include "Flash/PixelGroups/KaiborgV1Pixels.h"
#include "Flash/PixelGroups/ProtoDRMini.h"

const int ledsPerStrip = 346;
DMAMEM int displayMemory[346 * 6];
int drawingMemory[346 * 6];
const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

class BetaProtoController : public Controller {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);

    Transform camRghtFrntTransform = Transform(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0, -500.0f), Vector3D(1, 1, 1));
    Transform camRghtRearTransform = Transform(Vector3D(0.0f, 0.0f, 159.0f), Vector3D(387.0f, 190.0f, -500.0f), Vector3D(1, 1, 1));

    PixelGroup<571> camRghtFrntPixels = PixelGroup<571>(KaiborgV1Pixels, PixelGroup<571>::ZEROTOMAX);
    PixelGroup<571> camRghtRearPixels = PixelGroup<571>(KaiborgV1Pixels, PixelGroup<571>::ZEROTOMAX);

    Camera<571> camRghtFrnt = Camera<571>(&camRghtFrntTransform, &cameraLayout, &camRghtFrntPixels);
    Camera<571> camRghtRear = Camera<571>(&camRghtRearTransform, &cameraLayout, &camRghtRearPixels);

    CameraBase* cameras[2] = { &camRghtFrnt, &camRghtRear };
    uint8_t maxBrightness;
    uint8_t maxAccentBrightness;

public:
    BetaProtoController(uint8_t maxBrightness, uint8_t maxAccentBrightness) : Controller(cameras, 2, maxBrightness, maxAccentBrightness){
        this->maxBrightness = maxBrightness;
        this->maxAccentBrightness = maxAccentBrightness;
    }

    void Initialize() override{
        leds.begin();
        leds.show();
    }

    void Display() override {
        int offset, inverseOffset;

        for (int i = 0; i < 571; i++){
            *camRghtFrntPixels.GetColor(i) = camRghtFrntPixels.GetColor(i)->Scale(brightness);

            *camRghtRearPixels.GetColor(i) = camRghtRearPixels.GetColor(i)->Scale(accentBrightness);
        }

        for (int i = 0; i < 571; i++) {
            if (i < 346){
                offset = i + 225;
                inverseOffset = 570 - offset;

                //Rear Panels
                leds.setPixel(i + 346 * 0, camRghtRearPixels.GetColor(inverseOffset)->R, camRghtRearPixels.GetColor(inverseOffset)->G, camRghtRearPixels.GetColor(inverseOffset)->B);//LEFT
                leds.setPixel(i + 346 * 1, camRghtRearPixels.GetColor(i)->R, camRghtRearPixels.GetColor(i)->G, camRghtRearPixels.GetColor(i)->B);//Pin 8

                //Front Panels
                leds.setPixel(i + 346 * 4, camRghtFrntPixels.GetColor(inverseOffset)->R, camRghtFrntPixels.GetColor(inverseOffset)->G, camRghtFrntPixels.GetColor(inverseOffset)->B);//Pin 7
                leds.setPixel(i + 346 * 5, camRghtFrntPixels.GetColor(i)->R, camRghtFrntPixels.GetColor(i)->G, camRghtFrntPixels.GetColor(i)->B);//Pin 8
            }
            else{
                offset = i - 346;
                inverseOffset = 570 - offset;

                //Rear Panels
                leds.setPixel(i + 346 * 2 - 346, camRghtRearPixels.GetColor(inverseOffset)->R, camRghtRearPixels.GetColor(inverseOffset)->G, camRghtRearPixels.GetColor(inverseOffset)->B);//Pin 8
                leds.setPixel(i + 346 * 3 - 346, camRghtRearPixels.GetColor(i)->R, camRghtRearPixels.GetColor(i)->G, camRghtRearPixels.GetColor(i)->B);//Pin 8

                //Front Panels
                leds.setPixel(i + 346 * 6 - 346, camRghtFrntPixels.GetColor(inverseOffset)->R, camRghtFrntPixels.GetColor(inverseOffset)->G, camRghtFrntPixels.GetColor(inverseOffset)->B);//Pin 8
                leds.setPixel(i + 346 * 7 - 346, camRghtFrntPixels.GetColor(i)->R, camRghtFrntPixels.GetColor(i)->G, camRghtFrntPixels.GetColor(i)->B);//Pin 8
            }
        }

        leds.show();
    }
};
