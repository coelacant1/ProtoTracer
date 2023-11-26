#include "SerialInterpreter.h"

Quaternion SerialInterpreter::baseRotation;
bool SerialInterpreter::baseRotationSet;

SerialTransfer SerialInterpreter::dataTransfer;
SerialInterpreter::ESP32Data SerialInterpreter::e32Data;

void SerialInterpreter::Initialize() {
    Serial4.begin(9600);
    dataTransfer.begin(Serial4, true);  // _debug = true
    baseRotationSet = false;
}

RGBColor SerialInterpreter::GetColor() {
    return RGBColor(e32Data.r, e32Data.g, e32Data.b);
}

Quaternion SerialInterpreter::GetOrientation() {
    Quaternion q = Quaternion(e32Data.oW, -e32Data.oX, -e32Data.oY, -e32Data.oZ);  // XZ flipped

    if (!baseRotationSet) {
        baseRotation = q;
        baseRotationSet = true;
    }

    return q.Multiply(baseRotation.Conjugate());
}

float SerialInterpreter::GetRatio() {
    return e32Data.ratio;
}

uint8_t SerialInterpreter::GetMode() {
    return e32Data.mode;
}

uint8_t SerialInterpreter::GetMorph() {
    return e32Data.m;
}

void SerialInterpreter::Update() {
    if (dataTransfer.available()) {
        uint16_t receiveSize = 0;

        receiveSize = dataTransfer.rxObj(e32Data, receiveSize);
        // Serial.println(GetColor().ToString());
        // Serial.print("\t");
    }
}
