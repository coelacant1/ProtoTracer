#pragma once

#include "..\Math\Quaternion.h"
#include <SerialTransfer.h>

class SerialInterpreter{
private:
    static struct ESP32Data {
        float oW;
        float oX;
        float oY;
        float oZ;
        uint16_t r;
        uint16_t g;
        uint16_t b;
        uint16_t c;
    } e32Data;

    static SerialTransfer dataTransfer;

public:
    static void Initialize(){
        Serial4.begin(115200);
        dataTransfer.begin(Serial4);
    }

    static RGBColor GetColor(){
        return RGBColor(e32Data.r, e32Data.g, e32Data.b);
    }

    static Quaternion GetOrientation(){
        return Quaternion(e32Data.oW, e32Data.oX, e32Data.oY, e32Data.oZ);
    }

    static void Update(){
        if(dataTransfer.available()){
            uint16_t receiveSize = 0;

            receiveSize = dataTransfer.rxObj(e32Data, receiveSize);
            //Serial.println(GetColor().ToString());
            //Serial.print("\t");
        }
    }

};

SerialTransfer SerialInterpreter::dataTransfer;
SerialInterpreter::ESP32Data SerialInterpreter::e32Data;