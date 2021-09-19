#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#include "Controller.h"
#include "Flash/PixelGroups/MandoPixels.h"
#include "Render/Camera.h"

#define NUM_ROWS 32
#define NUM_COLS 64
#define NUM_PANELS 2

#define NUM_LEDS NUM_ROWS * NUM_COLS

class MandoController : public Controller {
  private:
   CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);
   Transform camTransform = Transform(Vector3D(), Vector3D(-100, -100, 0), Vector3D(1.5, 1.5, 1));

   PixelGroup camPixels = PixelGroup(MandoPixels, NUM_LEDS, PixelGroup::ZEROTOMAX);
   MatrixPanel_I2S_DMA *dma_display = nullptr;

   Camera* camRght;
   Camera* cameras[1] = {camRght};

   uint8_t maxBrightness;

  public:
   MandoController(uint8_t brightLimit) : Controller(cameras, 1) {
      camRght = new Camera(&camTransform, &cameraLayout, &camPixels);
      maxBrightness = brightLimit;
   }

   void Initialize() override {
      HUB75_I2S_CFG mxconfig(
         NUM_COLS,   // module width
         NUM_ROWS,   // module height
         NUM_PANELS    // Chain length
      );
      mxconfig.double_buff = true; // Turn on double buffer
      mxconfig.clkphase = false;

      dma_display = new MatrixPanel_I2S_DMA(mxconfig);
      dma_display->begin();
      dma_display->setBrightness8(maxBrightness); //0-255
      dma_display->clearScreen();
   }

   void Display() override {
      dma_display->flipDMABuffer();
      dma_display->clearScreen();

      for (int16_t xx = 0; xx < NUM_COLS; xx++) {
         for (int16_t yy = 0; yy < NUM_ROWS; yy++) {
            Pixel* curPix = camPixels.GetPixel(xx + (yy * 64));
            dma_display->drawPixelRGB888(xx, yy, curPix->Color.R, curPix->Color.G, curPix->Color.B);
            dma_display->drawPixelRGB888(127 - xx, yy, curPix->Color.R, curPix->Color.G, curPix->Color.B);
         }
      }
   }
};
