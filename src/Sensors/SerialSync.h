#pragma once

#include <SerialTransfer.h>

class SerialSync{
private:
    static struct ESP32Data {
        float ratio;
        uint8_t mode;
        float mouthMove;
    } e32Data;

    static SerialTransfer dataTransfer;

public:
    static void Initialize(){
        Serial6.begin(115200);
        dataTransfer.begin(Serial6, false);//_debug = true
    }

    static float GetRatio(){
        return e32Data.ratio;
    }

    static uint8_t GetMode(){
        return e32Data.mode;
    }

    static float GetMouthMove(){
        return e32Data.mouthMove;
    }

    static void Read(){
        if(dataTransfer.available()){
            uint16_t receiveSize = 0;

            receiveSize = dataTransfer.rxObj(e32Data, receiveSize);
        }
    }

    static void SetRatio(float ratio){
        e32Data.ratio = ratio;
    }

    static void SetMode(uint8_t mode){
        e32Data.mode = mode;
    }
    
    static void SetMouthMove(float ratio){
        e32Data.mouthMove = ratio;
    }
    
    static void Send(){
        uint16_t sendSize = 0;

        sendSize = dataTransfer.txObj(e32Data, sendSize);
        dataTransfer.sendData(sendSize);
    }

};

SerialTransfer SerialSync::dataTransfer;
SerialSync::ESP32Data SerialSync::e32Data;
