#include "Animation\CoelaBonkAnimation.h"
#include "Controllers\MandoController.h"

#include "soc/rtc_wdt.h"

const uint8_t maxBrightness = 10;
MandoController* controller = new MandoController(maxBrightness);

Animation* bonk = new CoelaBonkAnimation();

TaskHandle_t Task1;
TaskHandle_t Task2;

boolean frameReady = false;
boolean frameAck = false;

void renderThread(void* pvParameters);
void displayThread(void* pvParameters);

void setup() {
   Serial.begin(115200);
   Serial.println("\nStarting...");

   delay(3000);
   controller->Initialize();
   delay(500);

   xTaskCreatePinnedToCore(displayThread, "DisplayThread", 10000, NULL, 1, &Task2, 1);
   xTaskCreatePinnedToCore(renderThread, "RenderThread", 10000, NULL, 1, &Task1, 0);
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
            else
               delay(1);
         }
         frameReady = false;
         frameAck = false;
      }
   }
}

void displayThread(void* pvParameters) {
   while (true) {
      if (frameReady) {
         frameAck = true;
         frameReady = false;
         controller->Display();
      } else {
         delay(1);
      }
   }
}

void loop() {}