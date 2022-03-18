#include <Arduino.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_APDS9960.h>


class BoopSensor{
private:
    static Adafruit_APDS9960 apds;
    static uint8_t proximity;
    static uint8_t threshold;

public:
    static bool Initialize(uint8_t threshold) {//timeout in milliseconds and threshold is minimum for detection (0 is far away, 255 is touching)
        BoopSensor::threshold = threshold;

        bool didBegin = apds.begin();
        
        apds.enableProximity(true);

        return didBegin;
    }

    static bool isBooped(){
        proximity = GetValue();

        return proximity > threshold;
    }

    static uint8_t GetValue(){
        proximity = apds.readProximity();

        return proximity;
    }
};

Adafruit_APDS9960 BoopSensor::apds;
uint8_t BoopSensor::proximity;
uint8_t BoopSensor::threshold;
