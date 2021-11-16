#include <Arduino.h>
#include <SPI.h>
#define FASTLED_ALL_PINS_HARDWARE_SPI true
#include <FastLED.h>

#include "Controller.h"
#include "Flash/PixelGroups/MyloPixels.h"
#include "Render/Camera.h"

#define DATA_PIN 19
#define NUM_LEDS 256

class MyloController : public Controller {
  private:
   CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);
   Transform camRghtTransform = Transform(Vector3D(), Vector3D(50, 0, 0), Vector3D(1, 1, 1));

   PixelGroup* temp;
   PixelGroup* buf1;
   PixelGroup* buf2;

   Camera* camRght;
   Camera* cameras[1] = {camRght};

   CRGB leds[NUM_LEDS];

  public:
   MyloController() : Controller(cameras, 1) {
      this->buf1 = new PixelGroup(MyloPixels, NUM_LEDS, PixelGroup::ZEROTOMAX);
      this->temp = this->buf1;
      this->buf2 = new PixelGroup(MyloPixels, NUM_LEDS, PixelGroup::ZEROTOMAX);
      this->camRght = new Camera(&camRghtTransform, &cameraLayout, this->buf1);
   }

   void Initialize(uint8_t maxBrightness, boolean dither) override {
      FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      FastLED.setBrightness(maxBrightness);
      FastLED.setCorrection(TypicalSMD5050);
      if (!dither) FastLED.setDither(0);
      FastLED.clear();
      FastLED.show();
   }

   void Display() override {
      Pixel* currentPixel;
      for (int ii = 0; ii < NUM_LEDS; ii++) {
         currentPixel = buf2->GetPixel(ii);
         leds[ii].r = dim8_raw(currentPixel->Color.R);
         leds[ii].g = dim8_raw(currentPixel->Color.G);
         leds[ii].b = dim8_raw(currentPixel->Color.B);
      }
      FastLED.show();
   }

   void SwapBuffers() {
      this->temp = this->buf1;
      this->buf1 = this->buf2;
      this->buf2 = this->temp;
      camRght->SwapPixels(buf1);
   }
};
