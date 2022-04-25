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

    Transform camRghtFrntTransform = Transform(Vector3D(0.0f, 27.0f, 0.0f), Vector3D(1.0f, 0, -500.0f+14.0f), Vector3D(1, 1, 1));
    Transform camLeftFrntTransform = Transform(Vector3D(0.0f, -27.0f, 0.0f), Vector3D(1.0f, 0, -500.0f-14.0f), Vector3D(1, 1, 1));
    Transform camRghtRearTransform = Transform(Vector3D(-5.631f, -1.508f, 164.057f), Vector3D(460.0f, 290.0f, -500.0f+111.0f), Vector3D(1, 1, 1));
    Transform camLeftRearTransform = Transform(Vector3D(5.631f, 1.508f, 164.057f), Vector3D(460.0f, 290.0f, -500.0f-111.0f), Vector3D(1, 1, 1));
    Transform camRghtChinTransform = Transform(Vector3D(52.014f, 9.825f, 28.423f), Vector3D(19.0f + 30.0f, 30.0f, -500.0f-19.0f), Vector3D(1, 1, 1));
    Transform camLeftChinTransform = Transform(Vector3D(-163.947f, -52.151f, 130.883f), Vector3D(145.0f + 30.0f, 30.0f, -500.0f+81.0f), Vector3D(1, 1, 1));

    PixelGroup camRghtFrntPixels = PixelGroup(KaiborgV1Pixels, 571, PixelGroup::ZEROTOMAX);
    PixelGroup camLeftFrntPixels = PixelGroup(KaiborgV1Pixels, 571, PixelGroup::MAXTOZERO);
    PixelGroup camRghtRearPixels = PixelGroup(KaiborgV1Pixels, 571, PixelGroup::ZEROTOMAX);
    PixelGroup camLeftRearPixels = PixelGroup(KaiborgV1Pixels, 571, PixelGroup::MAXTOZERO);
    PixelGroup camRghtChinPixels = PixelGroup(ProtoDRMini, 89);
    PixelGroup camLeftChinPixels = PixelGroup(ProtoDRMini, 89);

    Camera camRghtFrnt = Camera(&camRghtFrntTransform, &cameraLayout, &camRghtFrntPixels);
    Camera camLeftFrnt = Camera(&camLeftFrntTransform, &cameraLayout, &camLeftFrntPixels);
    Camera camRghtRear = Camera(&camRghtRearTransform, &cameraLayout, &camRghtRearPixels);
    Camera camLeftRear = Camera(&camLeftRearTransform, &cameraLayout, &camLeftRearPixels);
    Camera camRghtChin = Camera(&camRghtChinTransform, &cameraLayout, &camRghtChinPixels);
    Camera camLeftChin = Camera(&camLeftChinTransform, &cameraLayout, &camLeftChinPixels);

    Camera* cameras[6] = { &camRghtFrnt, &camLeftFrnt, &camRghtRear, &camLeftRear, &camRghtChin, &camLeftChin };

public:
    BetaProtoController(uint8_t maxBrightness) : Controller(cameras, 8, maxBrightness){}

    void Initialize() override{
        leds.begin();
        leds.show();
    }

    void Display() override {
        for (int i = 0; i < 571; i++){
            camLeftFrntPixels.GetPixel(i)->Color = camLeftFrntPixels.GetPixel(i)->Color.Scale(brightness);
            camRghtFrntPixels.GetPixel(i)->Color = camRghtFrntPixels.GetPixel(i)->Color.Scale(brightness);

            camLeftRearPixels.GetPixel(i)->Color = camLeftRearPixels.GetPixel(i)->Color.Scale(brightness);
            camRghtRearPixels.GetPixel(i)->Color = camRghtRearPixels.GetPixel(i)->Color.Scale(brightness);
            
            if(i < 89){
                camRghtChinPixels.GetPixel(i)->Color = camRghtChinPixels.GetPixel(i)->Color.Scale(brightness * 2);
                camLeftChinPixels.GetPixel(i)->Color = camLeftChinPixels.GetPixel(i)->Color.Scale(brightness * 2);
            }
        }

        for (int i = 0; i < 571; i++) {
            if (i < 346){
                //Rear Panels
                leds.setPixel(i + 346 * 7, camLeftRearPixels.GetPixel(i + 225)->Color.R, camLeftRearPixels.GetPixel(i + 225)->Color.G, camLeftRearPixels.GetPixel(i + 225)->Color.B);//Pin 7
                leds.setPixel(i + 346 * 6, camRghtRearPixels.GetPixel(i)->Color.R, camRghtRearPixels.GetPixel(i)->Color.G, camRghtRearPixels.GetPixel(i)->Color.B);//Pin 8

                //Front Panels
                leds.setPixel(i + 346 * 3, camLeftFrntPixels.GetPixel(i + 225)->Color.R, camLeftFrntPixels.GetPixel(i + 225)->Color.G, camLeftFrntPixels.GetPixel(i + 225)->Color.B);//Pin 7
                leds.setPixel(i + 346 * 2, camRghtFrntPixels.GetPixel(i)->Color.R, camRghtFrntPixels.GetPixel(i)->Color.G, camRghtFrntPixels.GetPixel(i)->Color.B);//Pin 8
            }
            else{
                //Rear Panels
                leds.setPixel(i + 346 * 5 - 346, camLeftRearPixels.GetPixel(i - 346)->Color.R, camLeftRearPixels.GetPixel(i - 346)->Color.G, camLeftRearPixels.GetPixel(i - 346)->Color.B);//Pin 8
                leds.setPixel(i + 346 * 4 - 346, camRghtRearPixels.GetPixel(i)->Color.R, camRghtRearPixels.GetPixel(i)->Color.G, camRghtRearPixels.GetPixel(i)->Color.B);//Pin 8

                //Front Panels
                leds.setPixel(i + 346 * 1 - 346, camLeftFrntPixels.GetPixel(i - 346)->Color.R, camLeftFrntPixels.GetPixel(i - 346)->Color.G, camLeftFrntPixels.GetPixel(i - 346)->Color.B);//Pin 8
                leds.setPixel(i + 346 * 0 - 346, camRghtFrntPixels.GetPixel(i)->Color.R, camRghtFrntPixels.GetPixel(i)->Color.G, camRghtFrntPixels.GetPixel(i)->Color.B);//Pin 8
            }
        }
        
        for(int i = 0; i < 89; i++){
            //Front Panels
            leds.setPixel(i + 346 * 1 + 225, camLeftChinPixels.GetPixel(i)->Color.R, camLeftChinPixels.GetPixel(i)->Color.G, camLeftChinPixels.GetPixel(i)->Color.B);//Pin 8
            leds.setPixel(i + 346 * 0 + 225, camRghtChinPixels.GetPixel(i)->Color.R, camRghtChinPixels.GetPixel(i)->Color.G, camRghtChinPixels.GetPixel(i)->Color.B);//Pin 8
        }

        leds.show();
    }
};
