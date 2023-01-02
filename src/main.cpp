//#define ALPHARIGHT
//#define ALPHALEFT
//#define BETAWS35
//#define GAMMAFRONT
//#define GAMMABACK
#define HUB75
//#define HUB75Split
//#define WS35

//#define PRINTINFO

#include <Arduino.h>

uint8_t maxBrightness = 50;
uint8_t maxAccentBrightness = 100;

#ifdef ALPHARIGHT
#include "Controllers\ProtoDRController.h"
#include "Animation\ProtoDRMorphAnimation.h"
ProtoDRController controller = ProtoDRController(maxBrightness, ProtoDRController::RIGHT);
#elif defined(ALPHALEFT)
#include "Controllers\ProtoDRController.h"
#include "Animation\ProtoDRMorphAnimation.h"
ProtoDRController controller = ProtoDRController(maxBrightness, ProtoDRController::LEFT);
#elif defined(BETAWS35)
#include "Controllers\BetaProtoController.h"
#include "Animation\ProtoV3Animation.h"
BetaProtoController controller = BetaProtoController(maxBrightness);
#elif defined(GAMMAFRONT)
#include "Controllers\GammaControllerFront.h"
#include "Animation\GammaAnimation.h"
GammaControllerFront controller = GammaControllerFront(maxBrightness);
#elif defined(GAMMABACK)
#include "Controllers\GammaControllerBack.h"
#include "Animation\GammaAnimation.h"
GammaControllerBack controller = GammaControllerBack(maxBrightness);
#elif defined(HUB75)
#include "Controllers\SmartMatrixHUB75.h"
#include "Animation\ProtogenHUB75Animation.h"
SmartMatrixHUB75 controller = SmartMatrixHUB75(maxBrightness, maxAccentBrightness);
ProtogenHUB75Animation animation = ProtogenHUB75Animation();
#elif defined(HUB75Split)
#include "Controllers\SmartMatrixHUB75Split.h"
#include "Animation\ProtogenHUB75AnimationSplit.h"
SmartMatrixHUB75Split controller = SmartMatrixHUB75Split(maxBrightness, maxAccentBrightness);
ProtogenHUB75AnimationSplit animation = ProtogenHUB75AnimationSplit();
#elif defined(WS35)
#include "Controllers\KaiborgV1D1Controller.h"
#include "Animation\ProtogenKitFaceAnimation.h"
KaiborgV1D1Controller controller = KaiborgV1D1Controller(maxBrightness);
ProtogenKitFaceAnimation animation = ProtogenKitFaceAnimation();
#else
//Define your own here
//--------------- ANIMATIONS ---------------
//#include "Animation\Test\FullScreenAnimation.h"
//#include "Animation\VectorFieldAnimation.h"
//#include "Animation\CoelaBonkAnimation.h"
//#include "Animation\SpyroAnimation.h"
//#include "Animation\SpyroRotateAnimation.h"

//--------------- CONTROLLERS ---------------
//#include "Controllers\KaiborgV1Controller.h"
//#include "Controllers\KaiborgV1D1Controller.h"
//#include "Controllers\ProtoDRController.h"
//include "Controllers\SmartMatrixHUB75.h"
//#include "Controllers\SmartMatrixHUB75Split.h"
#endif

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

    animation.UpdateTime(ratio);

    #ifdef HUB75Split
    controller.SetAccentBrightness(Menu::GetAccentBrightness() * 25 + 5);
    controller.SetBrightness(Menu::GetBrightness() * 25 + 5);

    animation.SetCameraMirror(false);
    animation.UpdateTime(ratio);
    controller.RenderCamera(animation.GetScene(), 0);

    animation.SetCameraMirror(true);
    animation.UpdateTime(ratio);
    controller.RenderCamera(animation.GetScene(), 1);
    #elif defined(HUB75)
    controller.SetAccentBrightness(Menu::GetAccentBrightness() * 25 + 5);
    controller.SetBrightness(Menu::GetBrightness() * 25 + 5);

    controller.Render(animation.GetScene());
    #else
    controller.SetAccentBrightness(Menu::GetAccentBrightness() * 25 + 5);

    controller.SetBrightness(powf(Menu::GetBrightness() + 3, 2) / 3);
    #endif
    

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