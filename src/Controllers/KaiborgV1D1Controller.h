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

class KaiborgV1D1Controller : public Controller {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);

    Transform camRghtTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));
    Transform camLeftTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));

    PixelGroup camRghtPixels = PixelGroup(KaiborgV1Pixels, 571, PixelGroup::ZEROTOMAX);
    PixelGroup camLeftPixels = PixelGroup(KaiborgV1Pixels, 571, PixelGroup::MAXTOZERO);

    Camera camRght = Camera(&camRghtTransform, &cameraLayout, &camRghtPixels);
    Camera camLeft = Camera(&camLeftTransform, &cameraLayout, &camLeftPixels);

    Camera* cameras[2] = { &camRght, &camLeft };

public:
    KaiborgV1D1Controller(uint8_t maxBrightness) : Controller(cameras, 2, maxBrightness){}

    void Initialize() override{
        leds.begin();
        leds.show();
    }

    void Display() override {
        int offset;

        for (int i = 0; i < 571; i++){
            camLeftPixels.GetPixel(i)->Color = camLeftPixels.GetPixel(i)->Color.Scale(brightness);
            camRghtPixels.GetPixel(i)->Color = camRghtPixels.GetPixel(i)->Color.Scale(brightness);
        }

        for (int i = 0; i < 571; i++) {
            if (i < 346){
                offset = i + 225;

                leds.setPixel(i + 346 * 4, camLeftPixels.GetPixel(offset)->Color.R, camLeftPixels.GetPixel(offset)->Color.G, camLeftPixels.GetPixel(offset)->Color.B);//Pin 7
                leds.setPixel(i + 346 * 5, camRghtPixels.GetPixel(i)->Color.R, camRghtPixels.GetPixel(i)->Color.G, camRghtPixels.GetPixel(i)->Color.B);//Pin 8
            }
            else{
                offset = i - 346;

                leds.setPixel(i + 346 * 6 - 346, camLeftPixels.GetPixel(offset)->Color.R, camLeftPixels.GetPixel(offset)->Color.G, camLeftPixels.GetPixel(offset)->Color.B);//Pin 8
                leds.setPixel(i + 346 * 7 - 346, camRghtPixels.GetPixel(i)->Color.R, camRghtPixels.GetPixel(i)->Color.G, camRghtPixels.GetPixel(i)->Color.B);//Pin 8
            }
        }

        leds.show();
    }

    void SetPixels(uint8_t strip, uint16_t led, RGBColor rgb){
        leds.setPixel(346 * strip + led, rgb.R, rgb.G, rgb.B);//Pin 8
    }
};
