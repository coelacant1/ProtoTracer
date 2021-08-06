#include "Animation\ProtoDRMorphAnimation.h"
#include "Animation\KaiborgV1Animation.h"
#include "Animation\CubeAnimation.h"
#include "Controllers\KaiborgV1Controller.h"
//#include "Controllers\ProtoDRController.h"

const uint8_t maxBrightness = 20;
//ProtoDRController protoDRController = ProtoDRController(maxBrightness, ProtoDRController::LEFT);
//ProtoDRController protoDRController = ProtoDRController(maxBrightness, ProtoDRController::RIGHT);
KaiborgV1Controller kaiborgController = KaiborgV1Controller(maxBrightness);
ProtoDRMorphAnimation protoDRMorph;
CubeAnimation cube;
KaiborgV1Animation kaiborg;

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
    
    leds.begin();

    kaiborgController.Initialize();
}

void loop() {
    for (float i = 0.0f; i < 1.0f; i += 1.0f / 720.0f) {
        //protoDRMorph.Update(i);
        //cube.Update(i);
        kaiborg.Update(i);

        //protoDRController.Render(protoDRMorph.GetScene());
        //protoDRController.Render(cube.GetScene());
        kaiborgController.Render(kaiborg.GetScene());

        kaiborgController.Display();

        Serial.print("Rendered in ");
        Serial.print(kaiborgController.GetRenderTime(), 4);
        Serial.println("s");
    }
}
