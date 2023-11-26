#include "APDS9960.h"

Adafruit_APDS9960 APDS9960::apds;
uint16_t APDS9960::proximity;
uint16_t APDS9960::threshold;

MinFilter<10> APDS9960::minF = MinFilter<10>(false);
TimeStep APDS9960::timeStep = TimeStep(5);
float APDS9960::minimum = 0.0f;
bool APDS9960::didBegin = false;
bool APDS9960::isBright = false;
bool APDS9960::isProx = false;

bool APDS9960::Initialize(uint8_t threshold) {
    APDS9960::threshold = threshold;

    Wire.setClock(100000); // for longer-range transmissions
    Wire.begin();

#ifdef WS35
    Wire.setSDA(19);
    Wire.setSCL(18);
#else
    Wire.setSDA(18);
    Wire.setSCL(19);
#endif

    Wire.beginTransmission(0x39);
    uint8_t error = Wire.endTransmission();

    if (error == 0) { // SSD1306 Found
        didBegin = apds.begin();

        // apds.setLED(APDS9960_LEDDRIVE_12MA, APDS9960_LEDBOOST_100PCNT);
        // apds.setProxGain(APDS9960_PGAIN_1X);
    } else {
        didBegin = false;
    }

    return didBegin;
}

bool APDS9960::isBooped() {
    GetValue();

    if (timeStep.IsReady()) {
        minimum = minF.Filter(proximity);
    }

    return proximity > minimum + threshold;
}

void APDS9960::ResetI2CBus() {
    Wire.end(); // Disable the I2C hardware
    delay(10);  // Wait a bit
    Wire.begin(); // Re-enable the I2C hardware
}

uint8_t APDS9960::GetValue() {
    unsigned long cmdTime = millis();

    if (didBegin) {
        if (!isProx) {
            apds.enableProximity(true);
            isProx = true;
        }
        proximity = apds.readProximity();
    }

    if (millis() - cmdTime > 100) {
        // Timeout occurred
        ResetI2CBus();
    }

    return proximity;
}

uint16_t APDS9960::GetBrightness() {
    uint16_t brightness;
    uint16_t r, g, b, c;

    if (didBegin) {
        if (!isBright) {
            apds.enableColor();
            isBright = true;
        }

        apds.getColorData(&r, &g, &b, &c);

        brightness = r + g + b + c;
    }
    else{
        brightness = 0;
    }

    return brightness;
}
