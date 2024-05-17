#pragma once

#include <SerialTransfer.h>
#include "../../../Utils/Math/Vector2D.h"

class SerialSync {
private:
    static struct Data {
        float ratio;
        uint8_t mode;
        float mouthMove;

        uint8_t faceState;
        uint8_t bright;
        uint8_t accentBright;
        uint8_t microphone;
        uint8_t micLevel;
        uint8_t boopSensor;
        uint8_t spectrumMirror;
        uint8_t faceSize;
        uint8_t color;

        uint8_t currentMenu;
        bool dead;
        bool boop;
    } data;

    static SerialTransfer dataTransfer;

public:
    static void Initialize();
    static float GetRatio();
    static uint8_t GetMode();
    static float GetMouthMove();
    static void Read();
    static void SetRatio(float ratio);
    static void SetMode(uint8_t mode);
    static void SetMouthMove(float ratio);
    static void Send();
    static void SetFaceState(uint8_t faceState);
    static uint8_t GetFaceState();
    static void SetBrightness(uint8_t bright);
    static uint8_t GetBrightness();
    static void SetAccentBrightness(uint8_t accentBright);
    static uint8_t GetAccentBrightness();
    static void SetUseMicrophone(uint8_t microphone);
    static uint8_t UseMicrophone();
    static void SetMicLevel(uint8_t micLevel);
    static uint8_t GetMicLevel();
    static void SetUseBoopSensor(uint8_t boopSensor);
    static uint8_t UseBoopSensor();
    static void SetMirrorSpectrumAnalyzer(uint8_t spectrumMirror);
    static uint8_t MirrorSpectrumAnalyzer();
    static void SetFaceSize(uint8_t faceSize);
    static uint8_t GetFaceSize();
    static void SetFaceColor(uint8_t color);
    static uint8_t GetFaceColor();
    static void SetCurrentMenu(uint8_t currentMenu);
    static uint8_t GetCurrentMenu();
    static void SetDead(bool dead);
    static bool GetDead();
    static void SetBoop(bool boop);
    static bool GetBoop();
};
