//#define RIGHTFACE
//#define DEMOMODE
#define PRINTINFO


//--------------- ANIMATIONS ---------------
//#include "Animation\ProtoDRMorphAnimation.h"
//#include "Animation\ProtogenKitFaceAnimation.h"
//#include "Animation\ProtogenHUB75Animation.h"
//#include "Animation\ProtogenHUB75AnimationSplit.h"
#include "Animation\Commissions\WarzoneAnimationV2.h"
//#include "Animation\Commissions\InfraredAnimation.h"
//#include "Animation\KaiborgV1Animation.h"
//#include "Animation\ProtoV3Animation.h"
//#include "Animation\FullScreenAnimation.h"
//#include "Animation\VectorFieldAnimation.h"
//#include "Animation\CoelaBonkAnimation.h"
//#include "Animation\SpyroAnimation.h"
//#include "Animation\SpyroRotateAnimation.h"
//#include "Animation\Commissions\InfraredAnimation.h"

//--------------- CONTROLLERS ---------------
//#include "Controllers\KaiborgV1Controller.h"
//#include "Controllers\KaiborgV1D1Controller.h"
//#include "Controllers\ProtoDRController.h"
#include "Controllers\SmartMatrixHUB75.h"
//#include "Controllers\SmartMatrixHUB75Split.h"

uint8_t maxBrightness = 50;
uint8_t maxAccentBrightness = 100;
#ifdef RIGHTFACE
ProtoDRController controller = ProtoDRController(maxBrightness, ProtoDRController::RIGHT);
#else
//ProtoDRController controller = ProtoDRController(maxBrightness, ProtoDRController::LEFT);
#endif
SmartMatrixHUB75 controller = SmartMatrixHUB75(maxBrightness, maxAccentBrightness);
Warzone2Animation animation = Warzone2Animation();

float FreeMem(){
    uint32_t stackT;
    uint32_t heapT;

    // current position of the stack.
    stackT = (uint32_t) &stackT;

    void* heapPos = malloc(1);
    heapT = (uint32_t) heapPos;
    free(heapPos);

    float temp = stackT - heapT;

    return temp / 1000000.0f;
}

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");

    controller.Initialize();
}

void loop() {
    float ratio = (float)(millis() % 5000) / 5000.0f;

    controller.SetBrightness(Menu::GetBrightness());// / 8);
    controller.SetAccentBrightness(Menu::GetAccentBrightness());

    animation.UpdateTime(ratio);
    controller.Render(animation.GetScene());
    /*
    animation.SetCameraMirror(false);
    animation.UpdateTime(ratio);
    controller.RenderCamera(animation.GetScene(), 0);

    animation.SetCameraMirror(true);
    animation.UpdateTime(ratio);
    controller.RenderCamera(animation.GetScene(), 1);
    */

    controller.Display();

    #ifdef PRINTINFO
    Serial.print("Animated in ");
    Serial.print(animation.GetAnimationTime(), 4);

    Serial.print("s, Rendered in ");
    Serial.print(controller.GetRenderTime(), 4);

    
    Serial.print("s, Free memory ");
    Serial.print(FreeMem(),3);

    Serial.println("Kb");
    #endif
}
