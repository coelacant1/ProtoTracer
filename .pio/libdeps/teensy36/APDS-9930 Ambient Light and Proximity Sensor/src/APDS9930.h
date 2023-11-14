/**
 * @file    APDS-9930.h
 * @brief   Library for the SparkFun APDS-9930 breakout board
 * @author  Shawn Hymel (SparkFun Electronics)
 *
 * @copyright	This code is public domain but you buy me a beer if you use
 * this and we meet someday (Beerware license).
 *
 * This library interfaces the Avago APDS-9930 to Arduino over I2C. The library
 * relies on the Arduino Wire (I2C) library. to use the library, instantiate an
 * APDS9930 object, call init(), and call the appropriate functions.
 */
 
#ifndef APDS9930_H
#define APDS9930_H

#include <Arduino.h>

/* Debug */
#define DEBUG                   0

/* APDS-9930 I2C address */
#define APDS9930_I2C_ADDR       0x39

/* Command register modes */
#define REPEATED_BYTE           0x80
#define AUTO_INCREMENT          0xA0
#define SPECIAL_FN              0xE0

/* Error code for returned values */
#define ERROR                   0xFF

/* Acceptable device IDs */
#define APDS9930_ID_1           0x12
#define APDS9930_ID_2           0x39

/* Misc parameters */
#define FIFO_PAUSE_TIME         30      // Wait period (ms) between FIFO reads

/* APDS-9930 register addresses */
#define APDS9930_ENABLE         0x00
#define APDS9930_ATIME          0x01
#define APDS9930_PTIME          0x02
#define APDS9930_WTIME          0x03
#define APDS9930_AILTL          0x04
#define APDS9930_AILTH          0x05
#define APDS9930_AIHTL          0x06
#define APDS9930_AIHTH          0x07
#define APDS9930_PILTL          0x08
#define APDS9930_PILTH          0x09
#define APDS9930_PIHTL          0x0A
#define APDS9930_PIHTH          0x0B
#define APDS9930_PERS           0x0C
#define APDS9930_CONFIG         0x0D
#define APDS9930_PPULSE         0x0E
#define APDS9930_CONTROL        0x0F
#define APDS9930_ID             0x12
#define APDS9930_STATUS         0x13
#define APDS9930_Ch0DATAL       0x14
#define APDS9930_Ch0DATAH       0x15
#define APDS9930_Ch1DATAL       0x16
#define APDS9930_Ch1DATAH       0x17
#define APDS9930_PDATAL         0x18
#define APDS9930_PDATAH         0x19
#define APDS9930_POFFSET        0x1E


/* Bit fields */
#define APDS9930_PON            0b00000001
#define APDS9930_AEN            0b00000010
#define APDS9930_PEN            0b00000100
#define APDS9930_WEN            0b00001000
#define APSD9930_AIEN           0b00010000
#define APDS9930_PIEN           0b00100000
#define APDS9930_SAI            0b01000000

/* On/Off definitions */
#define OFF                     0
#define ON                      1

/* Acceptable parameters for setMode */
#define POWER                   0
#define AMBIENT_LIGHT           1
#define PROXIMITY               2
#define WAIT                    3
#define AMBIENT_LIGHT_INT       4
#define PROXIMITY_INT           5
#define SLEEP_AFTER_INT         6
#define ALL                     7

/* LED Drive values */
#define LED_DRIVE_100MA         0
#define LED_DRIVE_50MA          1
#define LED_DRIVE_25MA          2
#define LED_DRIVE_12_5MA        3

/* Proximity Gain (PGAIN) values */
#define PGAIN_1X                0
#define PGAIN_2X                1
#define PGAIN_4X                2
#define PGAIN_8X                3

/* ALS Gain (AGAIN) values */
#define AGAIN_1X                0
#define AGAIN_8X                1
#define AGAIN_16X               2
#define AGAIN_120X              3

/* Interrupt clear values */
#define CLEAR_PROX_INT          0xE5
#define CLEAR_ALS_INT           0xE6
#define CLEAR_ALL_INTS          0xE7

/* Default values */
#define DEFAULT_ATIME           0xED
#define DEFAULT_WTIME           0xFF
#define DEFAULT_PTIME           0xFF
#define DEFAULT_PPULSE          0x08
#define DEFAULT_POFFSET         0       // 0 offset
#define DEFAULT_CONFIG          0
#define DEFAULT_PDRIVE          LED_DRIVE_100MA
#define DEFAULT_PDIODE          2
#define DEFAULT_PGAIN           PGAIN_8X
#define DEFAULT_AGAIN           AGAIN_1X
#define DEFAULT_PILT            0       // Low proximity threshold
#define DEFAULT_PIHT            50      // High proximity threshold
#define DEFAULT_AILT            0xFFFF  // Force interrupt for calibration
#define DEFAULT_AIHT            0
#define DEFAULT_PERS            0x22    // 2 consecutive prox or ALS for int.

/* ALS coefficients */
#define DF                      52
#define GA                      0.49
#define ALS_B                       1.862
#define ALS_C                       0.746
#define ALS_D                       1.291

/* State definitions */
enum {
  NOTAVAILABLE_STATE,
  NEAR_STATE,
  FAR_STATE,
  ALL_STATE
};

#ifdef _AVR_IO_H_
    // Do not use this alias as it's deprecated
    #define NA_STATE NOTAVAILABLE_STATE
#endif

/* APDS9930 Class */
class APDS9930 {
public:

    /* Initialization methods */
    APDS9930();
    ~APDS9930();
    bool init();
    uint8_t getMode();
    bool setMode(uint8_t mode, uint8_t enable);
    
    /* Turn the APDS-9930 on and off */
    bool enablePower();
    bool disablePower();
    
    /* Enable or disable specific sensors */
    bool enableLightSensor(bool interrupts = false);
    bool disableLightSensor();
    bool enableProximitySensor(bool interrupts = false);
    bool disableProximitySensor();

    /* LED drive strength control */
    uint8_t getLEDDrive();
    bool setLEDDrive(uint8_t drive);
    // uint8_t getGestureLEDDrive();
    // bool setGestureLEDDrive(uint8_t drive);
    
    /* Gain control */
    uint8_t getAmbientLightGain();
    bool setAmbientLightGain(uint8_t gain);
    uint8_t getProximityGain();
    bool setProximityGain(uint8_t gain);
    bool setProximityDiode(uint8_t drive);
    uint8_t getProximityDiode();

    
    /* Get and set light interrupt thresholds */
    bool getLightIntLowThreshold(uint16_t &threshold);
    bool setLightIntLowThreshold(uint16_t threshold);
    bool getLightIntHighThreshold(uint16_t &threshold);
    bool setLightIntHighThreshold(uint16_t threshold);
    
    /* Get and set interrupt enables */
    uint8_t getAmbientLightIntEnable();
    bool setAmbientLightIntEnable(uint8_t enable);
    uint8_t getProximityIntEnable();
    bool setProximityIntEnable(uint8_t enable);
    
    /* Clear interrupts */
    bool clearAmbientLightInt();
    bool clearProximityInt();
    bool clearAllInts();
    
    /* Proximity methods */
    bool readProximity(uint16_t &val);

    /* Ambient light methods */
    bool readAmbientLightLux(float &val);
    bool readAmbientLightLux(unsigned long &val);
    float floatAmbientToLux(uint16_t Ch0, uint16_t Ch1);
    unsigned long ulongAmbientToLux(uint16_t Ch0, uint16_t Ch1);
    bool readCh0Light(uint16_t &val);
    bool readCh1Light(uint16_t &val);
    
//private:

    /* Proximity Interrupt Threshold */
    uint16_t getProximityIntLowThreshold();
    bool setProximityIntLowThreshold(uint16_t threshold);
    uint16_t getProximityIntHighThreshold();
    bool setProximityIntHighThreshold(uint16_t threshold);
    
    /* Raw I2C Commands */
    bool wireWriteByte(uint8_t val);
    bool wireWriteDataByte(uint8_t reg, uint8_t val);
    bool wireWriteDataBlock(uint8_t reg, uint8_t *val, unsigned int len);
    bool wireReadDataByte(uint8_t reg, uint8_t &val);
    int wireReadDataBlock(uint8_t reg, uint8_t *val, unsigned int len);
};

#endif
