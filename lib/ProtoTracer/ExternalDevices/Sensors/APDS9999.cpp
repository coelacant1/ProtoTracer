#include "APDS9999.h"

Adafruit_APDS9999 APDS9999::apds;
uint16_t APDS9999::proximity;
uint16_t APDS9999::threshold;

MinFilter<10> APDS9999::minF = MinFilter<10>(false);
TimeStep APDS9999::timeStep = TimeStep(5);
float APDS9999::minimum = 0.0f;
bool APDS9999::didBegin = false;
bool APDS9999::isBright = false;
bool APDS9999::isProx = false;

bool APDS9999::Initialize(uint8_t threshold)
{
    APDS9999::threshold = threshold;

    Wire.setClock(100000); // for longer-range transmissions
    Wire.begin();

#ifdef WS35
    Wire.setSDA(19);
    Wire.setSCL(18);
#else
    Wire.setSDA(18);
    Wire.setSCL(19);
#endif
    Wire.beginTransmission(0x52);
    uint8_t error = Wire.endTransmission();

    if (error == 0)
    { // APDS9999 Found
        didBegin = apds.begin();
    }
    else
    {
        didBegin = false;
    }

    return didBegin;
}

bool APDS9999::isBooped()
{
    GetValue();

    if (timeStep.IsReady())
    {
        minimum = minF.Filter(proximity);
    }

    return proximity > minimum + threshold;
}

void APDS9999::ResetI2CBus()
{
    Wire.end();   // Disable the I2C hardware
    delay(10);    // Wait a bit
    Wire.begin(); // Re-enable the I2C hardware
}

uint8_t APDS9999::GetValue()
{
    unsigned long cmdTime = millis();

    if (didBegin)
    {
        if (!isProx)
        {
            apds.enableProximitySensor(true);
            isProx = true;
        }
        uint16_t proxVal = 0;
        apds.readProximity(&proxVal);
        proximity = proxVal;
    }

    if (millis() - cmdTime > 100)
    {
        // Timeout occurred
        ResetI2CBus();
    }

    return proximity;
}

uint16_t APDS9999::GetBrightness()
{
    uint16_t brightness;

    if (didBegin)
    {
        if (!isBright)
        {
            apds.lightSensorEnabled();
            isBright = true;
        }

        brightness = apds.getLightGain();
    }
    else
    {
        brightness = 0;
    }

    return brightness;
}
