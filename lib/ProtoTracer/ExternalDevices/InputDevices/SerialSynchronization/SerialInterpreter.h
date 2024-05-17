#pragma once

#include "../../../Utils/Math/Quaternion.h"
#include "../../../Utils/RGBColor.h"
#include <SerialTransfer.h>

class SerialInterpreter {
private:
    static Quaternion baseRotation;
    static bool baseRotationSet;

    static struct ESP32Data {
        float oW;
        float oX;
        float oY;
        float oZ;
        uint16_t r;
        uint16_t g;
        uint16_t b;
        uint16_t c;
        uint8_t m;
        uint8_t d;
        float ratio;
        uint8_t mode;
    } e32Data;

    static SerialTransfer dataTransfer;

public:
    static void Initialize();
    static RGBColor GetColor();
    static Quaternion GetOrientation();
    static float GetRatio();
    static uint8_t GetMode();
    static uint8_t GetMorph();
    static void Update();
};
