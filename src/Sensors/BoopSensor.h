#include <Arduino.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_APDS9960.h>


class BoopSensor{
private:
    static Adafruit_APDS9960 apds;
    static uint32_t previousMillis;
    static uint16_t timeout;
    static uint8_t proximity;
    static uint8_t threshold;

public:
    static bool Initialize(uint16_t timeout, uint8_t threshold) {//timeout in milliseconds and threshold is minimum for detection (0 is far away, 255 is touching)
        BoopSensor::timeout = timeout;
        BoopSensor::threshold = threshold;

        bool didBegin = apds.begin();
        
        apds.enableProximity(true);

        return didBegin;
    }

    static bool isBooped(){
        bool isBooped = false;

        proximity = GetValue();

        if (proximity > threshold && millis() - previousMillis < timeout){
            isBooped = true;
        }
        else{
            previousMillis = millis();
        }

        return isBooped;
    }

    static uint8_t GetValue(){
        proximity = apds.readProximity();

        return proximity;
    }
};

Adafruit_APDS9960 BoopSensor::apds;
uint32_t BoopSensor::previousMillis;
uint16_t BoopSensor::timeout;
uint8_t BoopSensor::proximity;
uint8_t BoopSensor::threshold;
