#pragma once

#include <SerialTransfer.h>
#include "..\Math\Vector2D.h"

class SerialSync{
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
    static void Initialize(){
        Serial4.begin(115200);
        dataTransfer.begin(Serial4, false);//_debug = true
    }

    static float GetRatio(){
        return data.ratio;
    }

    static uint8_t GetMode(){
        return data.mode;
    }

    static float GetMouthMove(){
        return data.mouthMove;
    }

    static void Read(){
        if(dataTransfer.available()){
            uint16_t receiveSize = 0;

            receiveSize = dataTransfer.rxObj(data, receiveSize);
        }
    }

    static void SetRatio(float ratio){
        data.ratio = ratio;
    }

    static void SetMode(uint8_t mode){
        data.mode = mode;
    }
    
    static void SetMouthMove(float ratio){
        data.mouthMove = ratio;
    }

    static void Send(){
        uint16_t sendSize = 0;

        sendSize = dataTransfer.txObj(data, sendSize);
        dataTransfer.sendData(sendSize);
    }

    static void SetFaceState(uint8_t faceState){
        data.faceState = faceState;
    }

    static uint8_t GetFaceState(){
        return data.faceState;
    }

    static void SetBrightness(uint8_t bright){
        data.bright = bright;
    }

    static uint8_t GetBrightness(){
        return data.bright;
    }

    static void SetAccentBrightness(uint8_t accentBright){
        data.accentBright = accentBright;
    }

    static uint8_t GetAccentBrightness(){
        return data.accentBright;
    }

    static void SetUseMicrophone(uint8_t microphone){
        data.microphone = microphone;
    }

    static uint8_t UseMicrophone(){
        return data.microphone;
    }

    static void SetMicLevel(uint8_t micLevel){
        data.micLevel = micLevel;
    }

    static uint8_t GetMicLevel(){
        return data.micLevel;
    }

    static void SetUseBoopSensor(uint8_t boopSensor){
        data.boopSensor = boopSensor;
    }

    static uint8_t UseBoopSensor(){
        return data.boopSensor;
    }

    static void SetMirrorSpectrumAnalyzer(uint8_t spectrumMirror){
        data.spectrumMirror = spectrumMirror;
    }

    static uint8_t MirrorSpectrumAnalyzer(){
        return data.spectrumMirror;
    }

    static void SetFaceSize(uint8_t faceSize){
        data.faceSize = faceSize;
    }

    static uint8_t GetFaceSize(){
        return data.faceSize;
    }

    static void SetFaceColor(uint8_t color){
        data.color = color;
    }

    static uint8_t GetFaceColor(){
        return data.color;
    }

    static void SetCurrentMenu(uint8_t currentMenu){
        data.currentMenu = currentMenu;
    }

    static uint8_t GetCurrentMenu(){
        return data.currentMenu;
    }

    static void SetDead(bool dead){
        data.dead = dead;
    }

    static bool GetDead(){
        return data.dead;
    }

    static void SetBoop(bool boop){
        data.boop = boop;
    }

    static bool GetBoop(){
        return data.boop;
    }
};

SerialTransfer SerialSync::dataTransfer;
SerialSync::Data SerialSync::data;
