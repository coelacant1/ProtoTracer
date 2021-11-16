<<<<<<< HEAD
#include "Animation\CoelaBonkAnimation.h"
#include "Controllers\MyloController.h"
#include "soc/rtc_wdt.h"
#define MAX_BRIGHT 31
#define DITHER true

Animation* bonk = new CoelaBonkAnimation();
MyloController* controller = new MyloController();

TaskHandle_t Task1;
TaskHandle_t Task2;

boolean frameReady = false;
boolean frameAck = false;

void renderThread(void* pvParameters);
void displayThread(void* pvParameters);
=======
#include "Animation\ProtoDRMorphAnimation.h"
//#include "Animation\KaiborgV1Animation.h"
//include "Animation\ProtoV3Animation.h"
//#include "Animation\FullScreenAnimation.h"
//#include "Animation\CoelaBonkAnimation.h"
//#include "Animation\SpyroAnimation.h"
//#include "Animation\SpyroRotateAnimation.h"
//#include "Animation\PikachuAnimation.h"
//#include "Animation\BeeAnimation.h"
//#include "Animation\CreeperAnimation.h"
//#include "Animation\DeltaruneAnimation.h"
//#include "Controllers\KaiborgV1Controller.h"
//#include "Controllers\KaiborgV1D1Controller.h"
#include "Controllers\ProtoDRController.h"

const uint8_t maxBrightness = 10;
//Controller controller = ProtoDRController(maxBrightness, ProtoDRController::LEFT);
Controller* controller = new ProtoDRController(maxBrightness, ProtoDRController::RIGHT);
//Controller* controller = new KaiborgV1D1Controller(maxBrightness);
//ProtoDRMorphAnimation protoDRMorph;
Animation* animation = new ProtoDRMorphAnimation();
>>>>>>> ESP32

void setup() {
   Serial.begin(115200);
   Serial.println("\nStarting...");
   controller->Initialize(MAX_BRIGHT, DITHER);

   xTaskCreatePinnedToCore(displayThread, "DisplayThread", 10000, NULL, 1, &Task2, 0);
   delay(10);
   xTaskCreatePinnedToCore(renderThread, "RenderThread", 10000, NULL, 1, &Task1, 1);
}

void renderThread(void* pvParameters) {
   while (true) {
      for (float i = 0.0f; i < 1.0f; i += 1.0f / 720.0f) {
         bonk->Update(i);

         controller->Render(bonk->GetScene());
         frameReady = true;

         while (true) {
            if (frameAck)
               break;
            else {
               delay(1);
            }
         }
         frameReady = false;
         frameAck = false;
      }
   }
}

void displayThread(void* pvParameters) {
   while (true) {
      if (frameReady) {
         controller->SwapBuffers();
         frameAck = true;
         frameReady = false;
         controller->Display();
      } else {
         delay(1);
         FastLED.show();
      }
   }
}

void loop() {}