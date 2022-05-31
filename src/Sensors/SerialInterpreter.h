#pragma once

#include "..\Materials\RGBColor.h"
#include "..\Math\Quaternion.h"
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
    static void Initialize() {
        Serial4.begin(9600);
        dataTransfer.begin(Serial4, true); //_debug = true
        baseRotationSet = false;
    }

    static RGBColor GetColor() {
        return RGBColor(e32Data.r, e32Data.g, e32Data.b);
    }

    static Quaternion GetOrientation() {
        const Quaternion q = Quaternion(e32Data.oW, -e32Data.oX, -e32Data.oY, -e32Data.oZ); // XZ flipped

        if (!baseRotationSet) {
            baseRotation = q;
            baseRotationSet = true;
        }

        return q * baseRotation.Conjugate();
    }

    static float GetRatio() {
        return e32Data.ratio;
    }

    static uint8_t GetMode() {
        return e32Data.mode;
    }

    static uint8_t GetMorph() {
        return e32Data.m;
    }

    static void Update() {
        if (dataTransfer.available()) {
            uint16_t receiveSize = 0;

            receiveSize = dataTransfer.rxObj(e32Data, receiveSize);
            // Serial.println(GetColor().ToString());
            // Serial.print("\t");
        }
    }
};

Quaternion SerialInterpreter::baseRotation;
bool SerialInterpreter::baseRotationSet;

SerialTransfer SerialInterpreter::dataTransfer;
SerialInterpreter::ESP32Data SerialInterpreter::e32Data;
