#define RIGHTFACE
#define DEMOMODE

//#include "Animation\ProtoDRMorphAnimation.h"
//#include "Animation\KaiborgV1Animation.h"
//include "Animation\ProtoV3Animation.h"
//#include "Animation\FullScreenAnimation.h"
#include "Animation\VectorFieldAnimation.h"
//#include "Animation\CoelaBonkAnimation.h"
//#include "Animation\FoxAnimation.h"
//#include "Animation\SpyroAnimation.h"
//#include "Animation\SpyroRotateAnimation.h"
//#include "Animation\PikachuAnimation.h"
//#include "Animation\BeeAnimation.h"
//#include "Animation\CreeperAnimation.h"
//#include "Animation\DeltaruneAnimation.h"
//#include "Controllers\KaiborgV1Controller.h"
//#include "Controllers\KaiborgV1D1Controller.h"
//#include "Animation\NukudeFaceAnimation.h"
#include "Controllers\ProtoDRController.h"


const uint8_t maxBrightness = 15;
#ifdef RIGHTFACE
Controller* controller = new ProtoDRController(maxBrightness, ProtoDRController::RIGHT);
#else
Controller* controller = new ProtoDRController(maxBrightness, ProtoDRController::LEFT);
#endif
//Controller* controller = new KaiborgV1D1Controller(maxBrightness);
Animation* animation = new VectorFieldAnimation();

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");

    controller->Initialize();
}

void loop() {
    float ratio = (float)(millis() % 5000) / 5000.0f;
    animation->Update(ratio);

    controller->Render(animation->GetScene());

    controller->Display();

    //Serial.print("Rendered in ");
    //Serial.print(controller->GetRenderTime(), 4);
    //Serial.println("s");
}
