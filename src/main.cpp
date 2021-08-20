//#include "Animation\ProtoDRMorphAnimation.h"
//#include "Animation\KaiborgV1Animation.h"
//#include "Animation\CoelaCubeAnimation.h"
//#include "Animation\SpyroAnimation.h"
#include "Animation\RocksAnimation.h"
//#include "Animation\PikachuAnimation.h"
//#include "Animation\BeeAnimation.h"
//#include "Animation\CreeperAnimation.h"
//#include "Controllers\KaiborgV1Controller.h"
//#include "Controllers\KaiborgV1D1Controller.h"
#include "Controllers\ProtoDRController.h"

const uint8_t maxBrightness = 20;
//Controller controller = ProtoDRController(maxBrightness, ProtoDRController::LEFT);
//Controller controller = ProtoDRController(maxBrightness, ProtoDRController::RIGHT);
Controller* controller = new ProtoDRController(maxBrightness, ProtoDRController::RIGHT);
//ProtoDRMorphAnimation protoDRMorph;
Animation* animation = new RocksAnimation();

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");

    controller->Initialize();
}

void loop() {
    for (float i = 0.0f; i < 1.0f; i += 1.0f / 720.0f) {
        animation->Update(i);

        controller->Render(animation->GetScene());

        controller->Display();

        Serial.print("Rendered in ");
        Serial.print(controller->GetRenderTime(), 4);
        Serial.println("s");
    }
}
