#include <Arduino.h>
#include <OctoWS2811.h>

#include "Controller.h"
#include "Render/Camera.h"
#include "Flash/PixelGroups/KaiborgV1Pixels.h"
#include "Flash/PixelGroups/XenraxStrip.h"
#include "Flash/PixelGroups/XenraxSquare.h"
#include "Flash/PixelGroups/XenraxRing.h"

const int ledsPerStrip = 346;
DMAMEM int displayMemory[346 * 6];
int drawingMemory[346 * 6];
const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

class KaiborgV1D1Controller : public Controller {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);

    //X: left/right, Y: up/down, Z: forward/back
    Transform camRghtTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));
    Transform camLeftTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));
    Transform camFinTransform = Transform(Vector3D(0.0f, 0.0f, 1.0f), Vector3D(180.0f, 0, -500.0f), Vector3D(1, 1, 1));//Rotation/position/scale
    Transform camSquTransform = Transform(Vector3D(0.0f, 0.0f, 1.0f), Vector3D(180.0f, 0, -500.0f), Vector3D(1, 1, 1));//Use Z axis to rotate panels
    Transform camRinTransform = Transform(Vector3D(0.0f, 0.0f, 1.0f), Vector3D(180.0f, 0, -500.0f), Vector3D(1, 1, 1));//USE XY to move panels

    PixelGroup<571> camRghtPixels = PixelGroup<571>(KaiborgV1Pixels, IPixelGroup::ZEROTOMAX);
    PixelGroup<571> camLeftPixels = PixelGroup<571>(KaiborgV1Pixels, IPixelGroup::MAXTOZERO);
    PixelGroup<27> camFinPixels = PixelGroup<27>(XenraxStrip, IPixelGroup::ZEROTOMAX);
    PixelGroup<36> camSquPixels = PixelGroup<36>(XenraxSquare, IPixelGroup::ZEROTOMAX);
    PixelGroup<36> camRinPixels = PixelGroup<36>(XenraxRing, IPixelGroup::ZEROTOMAX);

    Camera<571> camRght = Camera<571>(&camRghtTransform, &cameraLayout, &camRghtPixels);
    Camera<571> camLeft = Camera<571>(&camLeftTransform, &cameraLayout, &camLeftPixels);
    Camera<27> camFin = Camera<27>(&camFinTransform, &cameraLayout, &camFinPixels);
    Camera<36> camSqu = Camera<36>(&camSquTransform, &cameraLayout, &camSquPixels);
    Camera<36> camRin = Camera<36>(&camRinTransform, &cameraLayout, &camRinPixels);

    CameraBase* cameras[5] = { &camRght, &camLeft, &camFin, &camSqu, &camRin };

public:
    KaiborgV1D1Controller(uint8_t maxBrightness) : Controller(cameras, 5, maxBrightness, maxBrightness){}

    void Initialize() override{
        leds.begin();
        leds.show();
    }

    void Display() override {
        int offset;

        for (int i = 0; i < 571; i++){
            *camLeftPixels.GetColor(i) = camLeftPixels.GetColor(i)->Scale(brightness);
            *camRghtPixels.GetColor(i) = camRghtPixels.GetColor(i)->Scale(brightness);

            if(i < 27) *camFinPixels.GetColor(i) = camFinPixels.GetColor(i)->Scale(accentBrightness);

            if(i < 36){
                *camSquPixels.GetColor(i) = camSquPixels.GetColor(i)->Scale(accentBrightness);
                *camRinPixels.GetColor(i) = camRinPixels.GetColor(i)->Scale(accentBrightness);
            }
        }

        for (int i = 0; i < 571; i++) {
            if (i < 346){
                offset = i + 225;

                leds.setPixel(i + 346 * 4, camLeftPixels.GetColor(offset)->R, camLeftPixels.GetColor(offset)->G, camLeftPixels.GetColor(offset)->B);//Pin 7
                leds.setPixel(i + 346 * 5, camRghtPixels.GetColor(i)->R, camRghtPixels.GetColor(i)->G, camRghtPixels.GetColor(i)->B);//Pin 8
            }
            else{
                offset = i - 346;

                leds.setPixel(i + 346 * 6 - 346, camLeftPixels.GetColor(offset)->R, camLeftPixels.GetColor(offset)->G, camLeftPixels.GetColor(offset)->B);//Pin 8
                leds.setPixel(i + 346 * 7 - 346, camRghtPixels.GetColor(i)->R, camRghtPixels.GetColor(i)->G, camRghtPixels.GetColor(i)->B);//Pin 8
            }

            if (i < 27){
                leds.setPixel(i + 346 * 2, camFinPixels.GetColor(i)->R, camFinPixels.GetColor(i)->G, camFinPixels.GetColor(i)->B);
                leds.setPixel(i + 346 * 3, camFinPixels.GetColor(i)->R, camFinPixels.GetColor(i)->G, camFinPixels.GetColor(i)->B);
            }

            if(i < 36){
                leds.setPixel(i + 346 * 2 + 27, camSquPixels.GetColor(i)->R, camSquPixels.GetColor(i)->G, camSquPixels.GetColor(i)->B);
                leds.setPixel(i + 346 * 3 + 27, camSquPixels.GetColor(i)->R, camSquPixels.GetColor(i)->G, camSquPixels.GetColor(i)->B);
                leds.setPixel(i + 346 * 2 + 27 + 36, camRinPixels.GetColor(i)->R, camRinPixels.GetColor(i)->G, camRinPixels.GetColor(i)->B);
                leds.setPixel(i + 346 * 3 + 27 + 36, camRinPixels.GetColor(i)->R, camRinPixels.GetColor(i)->G, camRinPixels.GetColor(i)->B);
            }
        }
        
        leds.show();
    }

    void SetPixels(uint8_t strip, uint16_t led, RGBColor rgb){
        leds.setPixel(346 * strip + led, rgb.R, rgb.G, rgb.B);//Pin 8
    }
};
