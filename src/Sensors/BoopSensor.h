#include <Arduino.h>
//#include <Adafruit_SPIDevice.h>
#include <Adafruit_APDS9960.h>

class BoopSensor {
private:
    static Adafruit_APDS9960 apds;
    static uint8_t proximity;
    static uint8_t threshold;

public:
    static bool Initialize(const uint8_t threshold) { // timeout in milliseconds and threshold is minimum for detection (0 is far away, 255 is touching)
        BoopSensor::threshold = threshold;

        Wire.begin();

        Wire.setSCL(19);
        Wire.setSDA(18);

        bool didBegin = apds.begin();

        apds.enableProximity(true);

        // apds.setLED(APDS9960_LEDDRIVE_12MA, APDS9960_LEDBOOST_100PCNT);
        // apds.setProxGain(APDS9960_PGAIN_1X);

        return didBegin;
    }

    static bool isBooped() {
        GetValue();

        return proximity > threshold;
    }

    static uint8_t GetValue() {
        proximity = apds.readProximity();

        return proximity;
    }
};

Adafruit_APDS9960 BoopSensor::apds;
uint8_t BoopSensor::proximity;
uint8_t BoopSensor::threshold;
