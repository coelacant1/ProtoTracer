/**
 * @file    APDS-9930.cpp
 * @brief   Library for the SparkFun APDS-9930 breakout board
 * @author  Shawn Hymel (SparkFun Electronics)
 *
 * @copyright	This code is public domain but you buy me a beer if you use
 * this and we meet someday (Beerware license).
 *
 * This library interfaces the Avago APDS-9930 to Arduino over I2C. The library
 * relies on the Arduino Wire (I2C) library. to use the library, instantiate an
 * APDS9930 object, call init(), and call the appropriate functions.
 *
 * APDS-9930 current draw tests (default parameters):
 *   Off:                   1mA
 *   Waiting for gesture:   14mA
 *   Gesture in progress:   35mA
 */
 
 #include <Arduino.h>
 #include <Wire.h>
 
 #include "APDS9930.h"
 
/**
 * @brief Constructor - Instantiates APDS9930 object
 */
APDS9930::APDS9930()
{

}
 
/**
 * @brief Destructor
 */
APDS9930::~APDS9930()
{

}

/**
 * @brief Configures I2C communications and initializes registers to defaults
 *
 * @return True if initialized successfully. False otherwise.
 */
bool APDS9930::init()
{
    uint8_t id;

    /* Initialize I2C */
    Wire.begin();
     
    /* Read ID register and check against known values for APDS-9930 */
    if( !wireReadDataByte(APDS9930_ID, id) ) {
        Serial.println(F("ID read"));
        return false;
    }
    if( !(id == APDS9930_ID_1 || id == APDS9930_ID_2) ) {
        Serial.println(F("ID check"));
        Serial.println(String("ID is ") + String(id, HEX));
        //return false;
    }
     
    /* Set ENABLE register to 0 (disable all features) */
    if( !setMode(ALL, OFF) ) {
        Serial.println(F("Regs off"));
        return false;
    }
    
    /* Set default values for ambient light and proximity registers */
    if( !wireWriteDataByte(APDS9930_ATIME, DEFAULT_ATIME) ) {
        return false;
    }
    if( !wireWriteDataByte(APDS9930_WTIME, DEFAULT_WTIME) ) {
        return false;
    }
    if( !wireWriteDataByte(APDS9930_PPULSE, DEFAULT_PPULSE) ) {
        return false;
    }
    if( !wireWriteDataByte(APDS9930_POFFSET, DEFAULT_POFFSET) ) {
        return false;
    }
    if( !wireWriteDataByte(APDS9930_CONFIG, DEFAULT_CONFIG) ) {
        return false;
    }
    if( !setLEDDrive(DEFAULT_PDRIVE) ) {
        return false;
    }
    if( !setProximityGain(DEFAULT_PGAIN) ) {
        return false;
    }
    if( !setAmbientLightGain(DEFAULT_AGAIN) ) {
        return false;
    }
    if( !setProximityDiode(DEFAULT_PDIODE) ) {
        return false;
    }
    if( !setProximityIntLowThreshold(DEFAULT_PILT) ) {
        return false;
    }
    if( !setProximityIntHighThreshold(DEFAULT_PIHT) ) {
        return false;
    }
    if( !setLightIntLowThreshold(DEFAULT_AILT) ) {
        return false;
    }
    if( !setLightIntHighThreshold(DEFAULT_AIHT) ) {
        return false;
    }
    if( !wireWriteDataByte(APDS9930_PERS, DEFAULT_PERS) ) {
        return false;
    }

    return true;
}

/*******************************************************************************
 * Public methods for controlling the APDS-9930
 ******************************************************************************/

/**
 * @brief Reads and returns the contents of the ENABLE register
 *
 * @return Contents of the ENABLE register. 0xFF if error.
 */
uint8_t APDS9930::getMode()
{
    uint8_t enable_value;
    
    /* Read current ENABLE register */
    if( !wireReadDataByte(APDS9930_ENABLE, enable_value) ) {
        return ERROR;
    }
    
    return enable_value;
}

/**
 * @brief Enables or disables a feature in the APDS-9930
 *
 * @param[in] mode which feature to enable
 * @param[in] enable ON (1) or OFF (0)
 * @return True if operation success. False otherwise.
 */
bool APDS9930::setMode(uint8_t mode, uint8_t enable)
{
    uint8_t reg_val;

    /* Read current ENABLE register */
    reg_val = getMode();
    if( reg_val == ERROR ) {
        return false;
    }
    
    /* Change bit(s) in ENABLE register */
    enable = enable & 0x01;
    if( mode >= 0 && mode <= 6 ) {
        if (enable) {
            reg_val |= (1 << mode);
        } else {
            reg_val &= ~(1 << mode);
        }
    } else if( mode == ALL ) {
        if (enable) {
            reg_val = 0x7F;
        } else {
            reg_val = 0x00;
        }
    }
        
    /* Write value back to ENABLE register */
    if( !wireWriteDataByte(APDS9930_ENABLE, reg_val) ) {
        return false;
    }
        
    return true;
}

/**
 * @brief Starts the light (Ambient/IR) sensor on the APDS-9930
 *
 * @param[in] interrupts true to enable hardware interrupt on high or low light
 * @return True if sensor enabled correctly. False on error.
 */
bool APDS9930::enableLightSensor(bool interrupts)
{
    
    /* Set default gain, interrupts, enable power, and enable sensor */
    if( !setAmbientLightGain(DEFAULT_AGAIN) ) {
        return false;
    }
    if( interrupts ) {
        if( !setAmbientLightIntEnable(1) ) {
            return false;
        }
    } else {
        if( !setAmbientLightIntEnable(0) ) {
            return false;
        }
    }
    if( !enablePower() ){
        return false;
    }
    if( !setMode(AMBIENT_LIGHT, 1) ) {
        return false;
    }
    
    return true;

}

/**
 * @brief Ends the light sensor on the APDS-9930
 *
 * @return True if sensor disabled correctly. False on error.
 */
bool APDS9930::disableLightSensor()
{
    if( !setAmbientLightIntEnable(0) ) {
        return false;
    }
    if( !setMode(AMBIENT_LIGHT, 0) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Starts the proximity sensor on the APDS-9930
 *
 * @param[in] interrupts true to enable hardware external interrupt on proximity
 * @return True if sensor enabled correctly. False on error.
 */
bool APDS9930::enableProximitySensor(bool interrupts)
{
    /* Set default gain, LED, interrupts, enable power, and enable sensor */
    if( !setProximityGain(DEFAULT_PGAIN) ) {
        return false;
    }
    if( !setLEDDrive(DEFAULT_PDRIVE) ) {
        return false;
    }
    if( interrupts ) {
        if( !setProximityIntEnable(1) ) {
            return false;
        }
    } else {
        if( !setProximityIntEnable(0) ) {
            return false;
        }
    }
    if( !enablePower() ){
        return false;
    }
    if( !setMode(PROXIMITY, 1) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Ends the proximity sensor on the APDS-9930
 *
 * @return True if sensor disabled correctly. False on error.
 */
bool APDS9930::disableProximitySensor()
{
	if( !setProximityIntEnable(0) ) {
		return false;
	}
	if( !setMode(PROXIMITY, 0) ) {
		return false;
	}

	return true;
}

/**
 * Turn the APDS-9930 on
 *
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::enablePower()
{
    if( !setMode(POWER, 1) ) {
        return false;
    }
    
    return true;
}

/**
 * Turn the APDS-9930 off
 *
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::disablePower()
{
    if( !setMode(POWER, 0) ) {
        return false;
    }
    
    return true;
}

/*******************************************************************************
 * Ambient light sensor controls
 ******************************************************************************/

/**
 * @brief Reads the ambient (clear) light level as a 16-bit value
 *
 * @param[out] val value of the light sensor.
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::readAmbientLightLux(float &val)
{
    uint16_t Ch0;
    uint16_t Ch1;
    
    /* Read value from channel 0 */
    if( !readCh0Light(Ch0) ) {
        return false;
    }

    /* Read value from channel 1 */
    if( !readCh1Light(Ch1) ) {
        return false;
    }

    val = floatAmbientToLux(Ch0, Ch1);
    return true;
}

bool APDS9930::readAmbientLightLux(unsigned long &val)
{
    uint16_t Ch0;
    uint16_t Ch1;
    
    /* Read value from channel 0 */
    if( !readCh0Light(Ch0) ) {
        return false;
    }

    /* Read value from channel 1 */
    if( !readCh1Light(Ch1) ) {
        return false;
    }

    val = ulongAmbientToLux(Ch0, Ch1);
    return true;
}

float APDS9930::floatAmbientToLux(uint16_t Ch0, uint16_t Ch1)
{
	uint8_t x[4]={1,8,16,120};
    float ALSIT = 2.73 * (256 - DEFAULT_ATIME);
    float iac  = max(Ch0 - ALS_B * Ch1, ALS_C * Ch0 - ALS_D * Ch1);
    if (iac < 0) iac = 0;
	float lpc  = GA * DF / (ALSIT * x[getAmbientLightGain()]);
    return iac * lpc;
}

unsigned long APDS9930::ulongAmbientToLux(uint16_t Ch0, uint16_t Ch1)
{
	uint8_t x[4]={1,8,16,120};
    unsigned long ALSIT = 2.73 * (256 - DEFAULT_ATIME);
    unsigned long iac  = max(Ch0 - ALS_B * Ch1, ALS_C * Ch0 - ALS_D * Ch1);
	if (iac < 0) iac = 0;
    unsigned long lpc  = GA * DF / (ALSIT * x[getAmbientLightGain()]);
    return iac * lpc;
}

bool APDS9930::readCh0Light(uint16_t &val)
{
    uint8_t val_byte;
    val = 0;
    
    /* Read value from channel 0 */
    if( !wireReadDataByte(APDS9930_Ch0DATAL, val_byte) ) {
        return false;
    }
    val = val_byte;
    if( !wireReadDataByte(APDS9930_Ch0DATAH, val_byte) ) {
        return false;
    }
    val += ((uint16_t)val_byte << 8);
    return true;
}

bool APDS9930::readCh1Light(uint16_t &val)
{
    uint8_t val_byte;
    val = 0;
    
    /* Read value from channel 0 */
    if( !wireReadDataByte(APDS9930_Ch1DATAL, val_byte) ) {
        return false;
    }
    val = val_byte;
    if( !wireReadDataByte(APDS9930_Ch1DATAH, val_byte) ) {
        return false;
    }
    val += ((uint16_t)val_byte << 8);
    return true;
}

/*******************************************************************************
 * Proximity sensor controls
 ******************************************************************************/

/**
 * @brief Reads the proximity level as an 8-bit value
 *
 * @param[out] val value of the proximity sensor.
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::readProximity(uint16_t &val)
{
    val = 0;
    uint8_t val_byte;

    /* Read value from proximity data register */
    if( !wireReadDataByte(APDS9930_PDATAL, val_byte) ) {
        return false;
    }
    val = val_byte;
    if( !wireReadDataByte(APDS9930_PDATAH, val_byte) ) {
        return false;
    }
    val += ((uint16_t)val_byte << 8);
    
    return true;
}

/*******************************************************************************
 * Getters and setters for register values
 ******************************************************************************/

/**
 * @brief Returns the lower threshold for proximity detection
 *
 * @return lower threshold
 */
uint16_t APDS9930::getProximityIntLowThreshold()
{
    uint16_t val;
    uint8_t val_byte;
    
    /* Read value from PILT register */
    if( !wireReadDataByte(APDS9930_PILTL, val_byte) ) {
        val = 0;
    }
    val = val_byte;
    if( !wireReadDataByte(APDS9930_PILTH, val_byte) ) {
        val = 0;
    }
    val |= ((uint16_t)val_byte << 8);    
    
    return val;
}

/**
 * @brief Sets the lower threshold for proximity detection
 *
 * @param[in] threshold the lower proximity threshold
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setProximityIntLowThreshold(uint16_t threshold)
{
    uint8_t lo;
    uint8_t hi;
    hi = threshold >> 8;
    lo = threshold & 0x00FF;

    if( !wireWriteDataByte(APDS9930_PILTL, lo) ) {
        return false;
    }
    if( !wireWriteDataByte(APDS9930_PILTH, hi) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Returns the high threshold for proximity detection
 *
 * @return high threshold
 */
uint16_t APDS9930::getProximityIntHighThreshold()
{
    uint16_t val;
    uint8_t val_byte;
    
    /* Read value from PILT register */
    if( !wireReadDataByte(APDS9930_PIHTL, val_byte) ) {
        val = 0;
    }
    val = val_byte;
    if( !wireReadDataByte(APDS9930_PIHTH, val_byte) ) {
        val = 0;
    }
    val |= ((uint16_t)val_byte << 8);    
    
    return val;
}

/**
 * @brief Sets the high threshold for proximity detection
 *
 * @param[in] threshold the high proximity threshold
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setProximityIntHighThreshold(uint16_t threshold)
{
    uint8_t lo;
    uint8_t hi;
    hi = threshold >> 8;
    lo = threshold & 0x00FF;

    if( !wireWriteDataByte(APDS9930_PIHTL, lo) ) {
        return false;
    }
    if( !wireWriteDataByte(APDS9930_PIHTH, hi) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Returns LED drive strength for proximity and ALS
 *
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 * @return the value of the LED drive strength. 0xFF on failure.
 */
uint8_t APDS9930::getLEDDrive()
{
    uint8_t val;
    
    /* Read value from CONTROL register */
    if( !wireReadDataByte(APDS9930_CONTROL, val) ) {
        return ERROR;
    }
    
    /* Shift and mask out LED drive bits */
    val = (val >> 6) & 0b00000011;
    
    return val;
}

/**
 * @brief Sets the LED drive strength for proximity and ALS
 *
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 * @param[in] drive the value (0-3) for the LED drive strength
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setLEDDrive(uint8_t drive)
{
    uint8_t val;
    
    /* Read value from CONTROL register */
    if( !wireReadDataByte(APDS9930_CONTROL, val) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    drive &= 0b00000011;
    drive = drive << 6;
    val &= 0b00111111;
    val |= drive;
    
    /* Write register value back into CONTROL register */
    if( !wireWriteDataByte(APDS9930_CONTROL, val) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Returns receiver gain for proximity detection
 *
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *
 * @return the value of the proximity gain. 0xFF on failure.
 */
uint8_t APDS9930::getProximityGain()
{
    uint8_t val;
    
    /* Read value from CONTROL register */
    if( !wireReadDataByte(APDS9930_CONTROL, val) ) {
        return ERROR;
    }
    
    /* Shift and mask out PDRIVE bits */
    val = (val >> 2) & 0b00000011;
    
    return val;
}

/**
 * @brief Sets the receiver gain for proximity detection
 *
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *
 * @param[in] drive the value (0-3) for the gain
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setProximityGain(uint8_t drive)
{
    uint8_t val;
    
    /* Read value from CONTROL register */
    if( !wireReadDataByte(APDS9930_CONTROL, val) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    drive &= 0b00000011;
    drive = drive << 2;
    val &= 0b11110011;
    val |= drive;
    
    /* Write register value back into CONTROL register */
    if( !wireWriteDataByte(APDS9930_CONTROL, val) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Returns the proximity diode
 *
 * Value    Diode selection
 *   0       Reserved
 *   1       Reserved
 *   2       Use Ch1 diode
 *   3       Reserved
 *
 * @return the selected diode. 0xFF on failure.
 */
uint8_t APDS9930::getProximityDiode()
{
    uint8_t val;
    
    /* Read value from CONTROL register */
    if( !wireReadDataByte(APDS9930_CONTROL, val) ) {
        return ERROR;
    }
    
    /* Shift and mask out PDRIVE bits */
    val = (val >> 4) & 0b00000011;
    
    return val;
}

/**
 * @brief Selects the proximity diode
 *
 * Value    Diode selection
 *   0       Reserved
 *   1       Reserved
 *   2       Use Ch1 diode
 *   3       Reserved
 *
 * @param[in] drive the value (0-3) for the diode
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setProximityDiode(uint8_t drive)
{
    uint8_t val;
    
    /* Read value from CONTROL register */
    if( !wireReadDataByte(APDS9930_CONTROL, val) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    drive &= 0b00000011;
    drive = drive << 4;
    val &= 0b11001111;
    val |= drive;
    
    /* Write register value back into CONTROL register */
    if( !wireWriteDataByte(APDS9930_CONTROL, val) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Returns receiver gain for the ambient light sensor (ALS)
 *
 * Value    Gain
 *   0        1x
 *   1        4x
 *   2       16x
 *   3      120x
 *
 * @return the value of the ALS gain. 0xFF on failure.
 */
uint8_t APDS9930::getAmbientLightGain()
{
    uint8_t val;
    
    /* Read value from CONTROL register */
    if( !wireReadDataByte(APDS9930_CONTROL, val) ) {
        return ERROR;
    }
    
    /* Shift and mask out ADRIVE bits */
    val &= 0b00000011;
	
    return val;
}

/**
 * @brief Sets the receiver gain for the ambient light sensor (ALS)
 *
 * Value    Gain
 *   0        1x
 *   1        4x
 *   2       16x
 *   3       64x
 *
 * @param[in] drive the value (0-3) for the gain
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setAmbientLightGain(uint8_t drive)
{
    uint8_t val;
    
    /* Read value from CONTROL register */
    if( !wireReadDataByte(APDS9930_CONTROL, val) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    drive &= 0b00000011;
    val &= 0b11111100;
    val |= drive;
    
    /* Write register value back into CONTROL register */
    if( !wireWriteDataByte(APDS9930_CONTROL, val) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Gets the low threshold for ambient light interrupts
 *
 * @param[out] threshold current low threshold stored on the APDS-9930
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::getLightIntLowThreshold(uint16_t &threshold)
{
    uint8_t val_byte;
    threshold = 0;
    
    /* Read value from ambient light low threshold, low byte register */
    if( !wireReadDataByte(APDS9930_AILTL, val_byte) ) {
        return false;
    }
    threshold = val_byte;
    
    /* Read value from ambient light low threshold, high byte register */
    if( !wireReadDataByte(APDS9930_AILTH, val_byte) ) {
        return false;
    }
    threshold = threshold + ((uint16_t)val_byte << 8);
    
    return true;
}

/**
 * @brief Sets the low threshold for ambient light interrupts
 *
 * @param[in] threshold low threshold value for interrupt to trigger
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setLightIntLowThreshold(uint16_t threshold)
{
    uint8_t val_low;
    uint8_t val_high;
    
    /* Break 16-bit threshold into 2 8-bit values */
    val_low = threshold & 0x00FF;
    val_high = (threshold & 0xFF00) >> 8;
    
    /* Write low byte */
    if( !wireWriteDataByte(APDS9930_AILTL, val_low) ) {
        return false;
    }
    
    /* Write high byte */
    if( !wireWriteDataByte(APDS9930_AILTH, val_high) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Gets the high threshold for ambient light interrupts
 *
 * @param[out] threshold current low threshold stored on the APDS-9930
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::getLightIntHighThreshold(uint16_t &threshold)
{
    uint8_t val_byte;
    threshold = 0;
    
    /* Read value from ambient light high threshold, low byte register */
    if( !wireReadDataByte(APDS9930_AIHTL, val_byte) ) {
        return false;
    }
    threshold = val_byte;
    
    /* Read value from ambient light high threshold, high byte register */
    if( !wireReadDataByte(APDS9930_AIHTH, val_byte) ) {
        return false;
    }
    threshold = threshold + ((uint16_t)val_byte << 8);
    
    return true;
}

/**
 * @brief Sets the high threshold for ambient light interrupts
 *
 * @param[in] threshold high threshold value for interrupt to trigger
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setLightIntHighThreshold(uint16_t threshold)
{
    uint8_t val_low;
    uint8_t val_high;
    
    /* Break 16-bit threshold into 2 8-bit values */
    val_low = threshold & 0x00FF;
    val_high = (threshold & 0xFF00) >> 8;
    
    /* Write low byte */
    if( !wireWriteDataByte(APDS9930_AIHTL, val_low) ) {
        return false;
    }
    
    /* Write high byte */
    if( !wireWriteDataByte(APDS9930_AIHTH, val_high) ) {
        return false;
    }
    
    return true;
}


/**
 * @brief Gets if ambient light interrupts are enabled or not
 *
 * @return 1 if interrupts are enabled, 0 if not. 0xFF on error.
 */
uint8_t APDS9930::getAmbientLightIntEnable()
{
    uint8_t val;
    
    /* Read value from ENABLE register */
    if( !wireReadDataByte(APDS9930_ENABLE, val) ) {
        return ERROR;
    }
    
    /* Shift and mask out AIEN bit */
    val = (val >> 4) & 0b00000001;
    
    return val;
}

/**
 * @brief Turns ambient light interrupts on or off
 *
 * @param[in] enable 1 to enable interrupts, 0 to turn them off
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setAmbientLightIntEnable(uint8_t enable)
{
    uint8_t val;
    
    /* Read value from ENABLE register */
    if( !wireReadDataByte(APDS9930_ENABLE, val) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    enable &= 0b00000001;
    enable = enable << 4;
    val &= 0b11101111;
    val |= enable;
    
    /* Write register value back into ENABLE register */
    if( !wireWriteDataByte(APDS9930_ENABLE, val) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Gets if proximity interrupts are enabled or not
 *
 * @return 1 if interrupts are enabled, 0 if not. 0xFF on error.
 */
uint8_t APDS9930::getProximityIntEnable()
{
    uint8_t val;
    
    /* Read value from ENABLE register */
    if( !wireReadDataByte(APDS9930_ENABLE, val) ) {
        return ERROR;
    }
    
    /* Shift and mask out PIEN bit */
    val = (val >> 5) & 0b00000001;
    
    return val;
}

/**
 * @brief Turns proximity interrupts on or off
 *
 * @param[in] enable 1 to enable interrupts, 0 to turn them off
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setProximityIntEnable(uint8_t enable)
{
    uint8_t val;
    
    /* Read value from ENABLE register */
    if( !wireReadDataByte(APDS9930_ENABLE, val) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    enable &= 0b00000001;
    enable = enable << 5;
    val &= 0b11011111;
    val |= enable;
    
    /* Write register value back into ENABLE register */
    if( !wireWriteDataByte(APDS9930_ENABLE, val) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Clears the ambient light interrupt
 *
 * @return True if operation completed successfully. False otherwise.
 */
bool APDS9930::clearAmbientLightInt()
{
    if( !wireWriteByte(CLEAR_ALS_INT) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Clears the proximity interrupt
 *
 * @return True if operation completed successfully. False otherwise.
 */
bool APDS9930::clearProximityInt()
{
    if( !wireWriteByte(CLEAR_PROX_INT) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Clears all interrupts
 *
 * @return True if operation completed successfully. False otherwise.
 */
bool APDS9930::clearAllInts()
{
    if( !wireWriteByte(CLEAR_ALL_INTS) ) {
        return false;
    }
    
    return true;
}

/*******************************************************************************
 * Raw I2C Reads and Writes
 ******************************************************************************/

/**
 * @brief Writes a single byte to the I2C device (no register)
 *
 * @param[in] val the 1-byte value to write to the I2C device
 * @return True if successful write operation. False otherwise.
 */
bool APDS9930::wireWriteByte(uint8_t val)
{
    Wire.beginTransmission(APDS9930_I2C_ADDR);
    Wire.write(val);
    if( Wire.endTransmission() != 0 ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Writes a single byte to the I2C device and specified register
 *
 * @param[in] reg the register in the I2C device to write to
 * @param[in] val the 1-byte value to write to the I2C device
 * @return True if successful write operation. False otherwise.
 */
bool APDS9930::wireWriteDataByte(uint8_t reg, uint8_t val)
{
    Wire.beginTransmission(APDS9930_I2C_ADDR);
    Wire.write(reg | AUTO_INCREMENT);
    Wire.write(val);
    if( Wire.endTransmission() != 0 ) {
        return false;
    }

    return true;
}

/**
 * @brief Writes a block (array) of bytes to the I2C device and register
 *
 * @param[in] reg the register in the I2C device to write to
 * @param[in] val pointer to the beginning of the data byte array
 * @param[in] len the length (in bytes) of the data to write
 * @return True if successful write operation. False otherwise.
 */
bool APDS9930::wireWriteDataBlock(  uint8_t reg, 
                                        uint8_t *val, 
                                        unsigned int len)
{
    unsigned int i;

    Wire.beginTransmission(APDS9930_I2C_ADDR);
    Wire.write(reg | AUTO_INCREMENT);
    for(i = 0; i < len; i++) {
        Wire.beginTransmission(APDS9930_I2C_ADDR);
        Wire.write(val[i]);
    }
    if( Wire.endTransmission() != 0 ) {
        return false;
    }

    return true;
}

/**
 * @brief Reads a single byte from the I2C device and specified register
 *
 * @param[in] reg the register to read from
 * @param[out] the value returned from the register
 * @return True if successful read operation. False otherwise.
 */
bool APDS9930::wireReadDataByte(uint8_t reg, uint8_t &val)
{
    
    /* Indicate which register we want to read from */
    if (!wireWriteByte(reg | AUTO_INCREMENT)) {
        return false;
    }
    
    /* Read from register */
    Wire.requestFrom(APDS9930_I2C_ADDR, 1);
    while (Wire.available()) {
        val = Wire.read();
    }

    return true;
}


/**
 * @brief Reads a block (array) of bytes from the I2C device and register
 *
 * @param[in] reg the register to read from
 * @param[out] val pointer to the beginning of the data
 * @param[in] len number of bytes to read
 * @return Number of bytes read. -1 on read error.
 */
int APDS9930::wireReadDataBlock(   uint8_t reg, 
                                        uint8_t *val, 
                                        unsigned int len)
{
    unsigned char i = 0;
    
    /* Indicate which register we want to read from */
    if (!wireWriteByte(reg | AUTO_INCREMENT)) {
        return -1;
    }
    
    /* Read block data */
    Wire.requestFrom(APDS9930_I2C_ADDR, len);
    while (Wire.available()) {
        if (i >= len) {
            return -1;
        }
        val[i] = Wire.read();
        i++;
    }

    return i;
}