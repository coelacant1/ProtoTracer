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
    Transform camLeftFrntTransform = Transform(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0, -500.0f), Vector3D(1, 1, 1));
    Transform camRghtRearTransform = Transform(Vector3D(0.0f, 0.0f, 159.0f), Vector3D(387.0f, 190.0f, -500.0f), Vector3D(1, 1, 1));
    Transform camLeftRearTransform = Transform(Vector3D(0.0f, 0.0f, 159.0f), Vector3D(387.0f, 190.0f, -500.0f), Vector3D(1, 1, 1));
    Transform camRghtChinTransform = Transform(Vector3D(0.0f, 0.0f, -45.0f), Vector3D(0.0f, 0.0f, -500.0f), Vector3D(1, 1, 1));
    Transform camLeftChinTransform = Transform(Vector3D(0.0f, 0.0f, -45.0f), Vector3D(0.0f, 0.0f, -500.0f), Vector3D(1, 1, 1));

    PixelGroup<571> camRghtFrntPixels = PixelGroup<571>(KaiborgV1Pixels, PixelGroup<571>::ZEROTOMAX);
    PixelGroup<571> camLeftFrntPixels = PixelGroup<571>(KaiborgV1Pixels, PixelGroup<571>::MAXTOZERO);
    PixelGroup<571> camRghtRearPixels = PixelGroup<571>(KaiborgV1Pixels, PixelGroup<571>::ZEROTOMAX);
    PixelGroup<571> camLeftRearPixels = PixelGroup<571>(KaiborgV1Pixels, PixelGroup<571>::MAXTOZERO);
    PixelGroup<89> camRghtChinPixels = PixelGroup<89>(ProtoDRMini);
    PixelGroup<89> camLeftChinPixels = PixelGroup<89>(ProtoDRMini);

    Camera<571> camRghtFrnt = Camera<571>(&camRghtFrntTransform, &cameraLayout, &camRghtFrntPixels);
    Camera<571> camLeftFrnt = Camera<571>(&camLeftFrntTransform, &cameraLayout, &camLeftFrntPixels);
    Camera<571> camRghtRear = Camera<571>(&camRghtRearTransform, &cameraLayout, &camRghtRearPixels);
    Camera<571> camLeftRear = Camera<571>(&camLeftRearTransform, &cameraLayout, &camLeftRearPixels);
    Camera<89> camRghtChin = Camera<89>(&camRghtChinTransform, &cameraLayout, &camRghtChinPixels);
    Camera<89> camLeftChin = Camera<89>(&camLeftChinTransform, &cameraLayout, &camLeftChinPixels);

    CameraBase* cameras[6] = { &camRghtFrnt, &camLeftFrnt, &camRghtRear, &camLeftRear, &camRghtChin, &camLeftChin };
    uint8_t maxBrightness;

public:
    BetaProtoController(uint8_t maxBrightness) : Controller(cameras, 6, maxBrightness, 0){
        this->maxBrightness = maxBrightness;
    }

    void Initialize() override{
        leds.begin();
        leds.show();
    }

    void Display() override {
        for (int i = 0; i < 571; i++){
            *camLeftFrntPixels.GetColor(i) = camLeftFrntPixels.GetColor(i)->Scale(brightness);
            *camRghtFrntPixels.GetColor(i) = camRghtFrntPixels.GetColor(i)->Scale(brightness);

            *camLeftRearPixels.GetColor(i) = camLeftRearPixels.GetColor(i)->Scale(brightness);
            *camRghtRearPixels.GetColor(i) = camRghtRearPixels.GetColor(i)->Scale(brightness);
            
            if(i < 89){
                *camRghtChinPixels.GetColor(i) = camRghtChinPixels.GetColor(i)->Scale(brightness * 2);
                *camLeftChinPixels.GetColor(i) = camLeftChinPixels.GetColor(i)->Scale(brightness * 2);
            }
        }

        for (int i = 0; i < 571; i++) {
            if (i < 346){
                //Rear Panels
                leds.setPixel(i + 346 * 1, camLeftRearPixels.GetColor(i + 225)->R, camLeftRearPixels.GetColor(i + 225)->G, camLeftRearPixels.GetColor(i + 225)->B);//Pin 7
                leds.setPixel(i + 346 * 3, camRghtRearPixels.GetColor(i)->R, camRghtRearPixels.GetColor(i)->G, camRghtRearPixels.GetColor(i)->B);//Pin 8

                //Front Panels
                leds.setPixel(i + 346 * 5, camLeftFrntPixels.GetColor(i + 225)->R, camLeftFrntPixels.GetColor(i + 225)->G, camLeftFrntPixels.GetColor(i + 225)->B);//Pin 7
                leds.setPixel(i + 346 * 4, camRghtFrntPixels.GetColor(i)->R, camRghtFrntPixels.GetColor(i)->G, camRghtFrntPixels.GetColor(i)->B);//Pin 8
            }
            else{
                //Rear Panels
                leds.setPixel(i + 346 * 0 - 346, camLeftRearPixels.GetColor(i - 346)->R, camLeftRearPixels.GetColor(i - 346)->G, camLeftRearPixels.GetColor(i - 346)->B);//Pin 8
                leds.setPixel(i + 346 * 2 - 346, camRghtRearPixels.GetColor(i)->R, camRghtRearPixels.GetColor(i)->G, camRghtRearPixels.GetColor(i)->B);//Pin 8

                //Front Panels
                leds.setPixel(i + 346 * 7 - 346, camLeftFrntPixels.GetColor(i - 346)->R, camLeftFrntPixels.GetColor(i - 346)->G, camLeftFrntPixels.GetColor(i - 346)->B);//Pin 8
                leds.setPixel(i + 346 * 6 - 346, camRghtFrntPixels.GetColor(i)->R, camRghtFrntPixels.GetColor(i)->G, camRghtFrntPixels.GetColor(i)->B);//Pin 8
            }
        }
        
        for(int i = 0; i < 89; i++){
            //Front Panels
            leds.setPixel(i + 346 * 7 + 225, camLeftChinPixels.GetColor(i)->R, camLeftChinPixels.GetColor(i)->G, camLeftChinPixels.GetColor(i)->B);//Pin 8
            leds.setPixel(i + 346 * 6 + 225, camRghtChinPixels.GetColor(i)->R, camRghtChinPixels.GetColor(i)->G, camRghtChinPixels.GetColor(i)->B);//Pin 8
        }

        leds.show();
    }
};
