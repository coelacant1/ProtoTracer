#pragma once

#include <Arduino.h>
//#include <Adafruit_SPIDevice.h>
#include <Adafruit_APDS9960.h>
#include "..\Filter\MinFilter.h"
#include "..\Signals\TimeStep.h"

class APDS9960{
private:
    static Adafruit_APDS9960 apds;
    static uint16_t proximity;
    static uint16_t threshold;
    static MinFilter<10> minF;
    static TimeStep timeStep;
    static float minimum;
    static bool didBegin;
    static bool isBright;
    static bool isProx;

public:
    static bool Initialize(uint8_t threshold) {//timeout in milliseconds and threshold is minimum for detection (0 is far away, 255 is touching)
        APDS9960::threshold = threshold;

        Wire.begin();

        Wire.setSCL(19);
        Wire.setSDA(18);

        didBegin = apds.begin();

        //apds.setLED(APDS9960_LEDDRIVE_12MA, APDS9960_LEDBOOST_100PCNT);
        //apds.setProxGain(APDS9960_PGAIN_1X);

        return didBegin;
    }

    static bool isBooped(){
        GetValue();
        
        if(timeStep.IsReady()){
            minimum = minF.Filter(proximity);
        }

        return proximity > minimum + threshold;
    }

    static uint8_t GetValue(){
        if (didBegin){
            if(!isProx){
                apds.enableProximity(true);
                isProx = true;
            }
            proximity = apds.readProximity();
        }

        return proximity;
    }
    
    static uint16_t GetBrightness(){

        uint16_t brightness;
        uint16_t r, g, b, c;

        if (didBegin){
            if(!isBright){
                apds.enableColor();
                isBright = true;
            }

            apds.getColorData(&r, &g, &b, &c);

            brightness = r + g + b + c;
        }

        return brightness;
    }
};

Adafruit_APDS9960 APDS9960::apds;
uint16_t APDS9960::proximity;
uint16_t APDS9960::threshold;

MinFilter<10> APDS9960::minF = MinFilter<10>(false);
TimeStep APDS9960::timeStep = TimeStep(5);
float APDS9960::minimum = 0.0f;
bool APDS9960::didBegin = false;
bool APDS9960::isBright = false;
bool APDS9960::isProx = false;
