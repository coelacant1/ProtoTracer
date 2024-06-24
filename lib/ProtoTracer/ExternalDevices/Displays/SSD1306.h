#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/Picopixel.h>

#include "..\InputDevices\Menu\Menu.h"
#include "..\..\Utils\Math\Mathematics.h"
#include "..\..\Scene\Screenspace\Effect.h"
#include "..\..\Utils\Time\TimeStep.h"

class HeadsUpDisplay : public Effect {
private:
    static const uint16_t SCREEN_WIDTH = 128;
    static const uint16_t SCREEN_HEIGHT = 64;
    static const int8_t OLED_RESET = -1;
    static const uint8_t faceXMinPosition = 66;
    static const uint8_t faceXMaxPosition = 124;
    static const uint8_t faceYMinPosition = 35;
    static const uint8_t faceYMaxPosition = 60;
    static const uint32_t splashTime = 2500;
    static const int bufferSize = 2048; // 64 * 32

    const __FlashStringHelper* percentArray[10] = {F("10%"), F("20%"), F("30%"), F("40%"), F("50%"), F("60%"), F("70%"), F("80%"), F("90%"), F("100%")};
	const __FlashStringHelper* effectArray[10] = {F("NONE"), F("PHASEY"), F("PHASEX"), F("PHASER"), F("GLITCHX"), F("MAGNET"), F("FISHEYE"), F("BLURH"), F("BLURV"), F("BLURR")};
	const __FlashStringHelper* colorArray[10] = {F("GRDIENT"), F("YELLOW"), F("ORANGE"), F("WHITE"), F("GREEN"), F("PURPLE"), F("RED"), F("BLUE"), F("RAINBOW"), F("NOISE")};
	const __FlashStringHelper* onOffArray[2] = {F("OFFLINE"), F("ONLINE")};
	const __FlashStringHelper* hueArray[10] = {F("0 DEG"), F("36 DEG"), F("72 DEG"), F("108 DEG"), F("144 DEG"), F("180 DEG"), F("216 DEG"), F("252 DEG"), F("288 DEG"), F("324 DEG")};
	const __FlashStringHelper* faceArray[10] = {F("DEFAULT"), F("ANGRY"), F("DOUBT"), F("FROWN"), F("LOOKUP"), F("SAD"), F("AUDIO1"), F("AUDIO2"), F("AUDIO3")};
    const __FlashStringHelper** faceNames;
	bool useExternalFace = false;

    Effect* subEffect;
    TimeStep timeStep = TimeStep(5);
    bool didBegin = false;
	bool splashFinished = false;
    Vector2D faceMin;
    Vector2D faceMax;
    uint32_t startMillis;

    static Adafruit_SSD1306 display;
    static uint8_t faceBitmap[bufferSize];

    static const uint8_t CoelaSplash[];
    static const uint8_t PrototracerSplash[];
    static const uint8_t FaceTemplate[];

    void ResetDisplayBuffer();
    void EnableBitFaceRender(float xIn, float yIn);
    void UpdateFaceInformation();

public:
    HeadsUpDisplay(Vector2D faceMin, Vector2D faceMax);
    void SetFaceArray(const __FlashStringHelper** faceNames);
    void SetFaceMin(Vector2D faceMin);
    void SetFaceMax(Vector2D faceMax);
    void Initialize();
    void ResetI2CBus();
    void Update();
    void SetEffect(Effect* effect);
    void ApplyEffect(IPixelGroup* pixelGroup);
    void CheckInvertPrintText(int16_t x, int16_t y, uint8_t menu, const String &str);
};
