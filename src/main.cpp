#include "Animation\ProtoDRMorphAnimation.h"
#include "Animation\KaiborgV1Animation.h"
#include "Animation\CubeAnimation.h"
#include "Controllers\KaiborgV1Controller.h"
//#include "Controllers\ProtoDRController.h"


const uint8_t maxBrightness = 20;
//Controller controller = ProtoDRController(maxBrightness, ProtoDRController::LEFT);
//Controller controller = ProtoDRController(maxBrightness, ProtoDRController::RIGHT);
Controller* controller = new KaiborgV1Controller(maxBrightness);
ProtoDRMorphAnimation protoDRMorph;
CubeAnimation cube;
KaiborgV1Animation kaiborg;

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
    
    leds.begin();

    controller->Initialize();
}

void loop() {
    for (float i = 0.0f; i < 1.0f; i += 1.0f / 720.0f) {
        kaiborg.Update(i);

        controller->Render(kaiborg.GetScene());

        controller->Display();

        Serial.print("Rendered in ");
        Serial.print(controller->GetRenderTime(), 4);
        Serial.println("s");
    }
}
