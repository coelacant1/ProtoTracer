/*!
 * @file Adafruit_MMC56x3.h
 *
 * This is a library for the MMC5603 magnentometer/compass
 *
 * Designed specifically to work with the Adafruit MMC5603 / MMC5613
 * Breakouts
 *
 * These sensors use I2C to communicate, 2 pins are required to interface.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing products
 * from Adafruit!
 *
 * Written by ladyada for Adafruit Industries.
 * BSD license, all text above must be included in any redistribution
 */

#ifndef MMC56X3_MAG_H
#define MMC56X3_MAG_H

#include <Adafruit_BusIO_Register.h>

#include <Adafruit_I2CDevice.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
#define MMC56X3_DEFAULT_ADDRESS 0x30 //!< Default address
#define MMC56X3_CHIP_ID 0x10         //!< Chip ID from WHO_AM_I register

/*=========================================================================*/

/*!
 * @brief MMC56X3 I2C register address bits
 */
typedef enum {
  MMC56X3_PRODUCT_ID = 0x39,
  MMC56X3_CTRL0_REG = 0x1B,
  MMC56X3_CTRL1_REG = 0x1C,
  MMC56X3_CTRL2_REG = 0x1D,
  MMC56X3_STATUS_REG = 0x18,
  MMC56X3_OUT_TEMP = 0x09,
  MMC56X3_OUT_X_L = 0x00,
  MMC5603_ODR_REG = 0x1A,

} mmc56x3_register_t;
/*=========================================================================*/

/**************************************************************************/
/*!
    @brief  Unified sensor driver for the magnetometer
*/
/**************************************************************************/
class Adafruit_MMC5603 : public Adafruit_Sensor {
public:
  Adafruit_MMC5603(int32_t sensorID = -1);

  bool begin(uint8_t i2c_addr = MMC56X3_DEFAULT_ADDRESS, TwoWire *wire = &Wire);

  bool getEvent(sensors_event_t *);
  void getSensor(sensor_t *);

  void reset(void);
  void magnetSetReset(void);

  void setContinuousMode(bool mode);
  bool isContinuousMode(void);

  float readTemperature(void);

  uint16_t getDataRate();
  void setDataRate(uint16_t rate);

private:
  Adafruit_BusIO_Register *_ctrl0_reg = NULL, *_ctrl1_reg = NULL,
                          *_ctrl2_reg = NULL, *_status_reg = NULL;

  uint16_t _odr_cache = 0;
  uint8_t _ctrl2_cache = 0;

  int32_t x; ///< x-axis raw data
  int32_t y; ///< y-axis raw data
  int32_t z; ///< z-axis raw data

  int32_t _sensorID;

  Adafruit_I2CDevice *i2c_dev = NULL;
};

#endif
