/*!
 * @file Adafruit_MMC56x3.cpp
 *
 * @mainpage Adafruit MMC56x3 Breakouts
 *
 * @section intro_sec Introduction
 *
 * This is a library for the MMC5603/MMC5613 Magnentometer/compass
 *
 * Designed specifically to work with the Adafruit MMC5603/MMC5613
 * Breakouts
 *
 * These sensors use I2C to communicate, 2 pins are required to interface.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing products
 * from Adafruit!
 *
 * @section author Author
 *
 * Written by ladyada for Adafruit Industries.
 *
 * @section license License
 *
 * BSD license, all text above must be included in any redistribution
 *
 */

#include "Arduino.h"
#include <Wire.h>

#include <limits.h>

#include "Adafruit_MMC56x3.h"

/***************************************************************************
 MAGNETOMETER
 ***************************************************************************/

/***************************************************************************
 CONSTRUCTOR
 ***************************************************************************/

/**************************************************************************/
/*!
    @brief  Instantiates a new Adafruit_MMC5603 class
    @param sensorID an option ID to differentiate the sensor from others
*/
/**************************************************************************/
Adafruit_MMC5603::Adafruit_MMC5603(int32_t sensorID) {
  _sensorID = sensorID;

  // Clear the raw mag data
  x = 0;
  y = 0;
  z = 0;
}

/***************************************************************************
 PUBLIC FUNCTIONS
 ***************************************************************************/
/*!
 *    @brief  Sets up the hardware and initializes I2C
 *    @param  i2c_address
 *            The I2C address to be used.
 *    @param  wire
 *            The Wire object to be used for I2C connections.
 *    @return True if initialization was successful, otherwise false.
 */
bool Adafruit_MMC5603::begin(uint8_t i2c_address, TwoWire *wire) {
  if (!i2c_dev) {
    i2c_dev = new Adafruit_I2CDevice(i2c_address, wire);
  }

  if (!i2c_dev->begin()) {
    return false;
  }

  // Check connection
  Adafruit_BusIO_Register chip_id =
      Adafruit_BusIO_Register(i2c_dev, MMC56X3_PRODUCT_ID);

  // make sure we're talking to the right chip
  if (chip_id.read() != MMC56X3_CHIP_ID) {
    // No MMC56X3 detected ... return false
    return false;
  }

  delete (_ctrl0_reg);
  _ctrl0_reg = new Adafruit_BusIO_Register(i2c_dev, MMC56X3_CTRL0_REG);
  delete (_ctrl1_reg);
  _ctrl1_reg = new Adafruit_BusIO_Register(i2c_dev, MMC56X3_CTRL1_REG);
  delete (_ctrl2_reg);
  _ctrl2_reg = new Adafruit_BusIO_Register(i2c_dev, MMC56X3_CTRL2_REG);
  delete (_status_reg);
  _status_reg = new Adafruit_BusIO_Register(i2c_dev, MMC56X3_STATUS_REG);

  reset();

  return true;
}
/*!
 *    @brief  Resets the sensor to an initial state
 */
void Adafruit_MMC5603::reset(void) {
  _ctrl1_reg->write(0x80); // write only, set topmost bit
  delay(20);
  _odr_cache = 0;
  _ctrl2_cache = 0;
  magnetSetReset();
  setContinuousMode(false);
}

/*!
 *    @brief  Pulse large currents through the sense coils to clear any offset
 */
void Adafruit_MMC5603::magnetSetReset(void) {
  _ctrl0_reg->write(0x08); // turn on set bit
  delay(1);
  _ctrl0_reg->write(0x10); // turn on reset bit
  delay(1);
}

/**************************************************************************/
/*!
    @brief  Sets whether we are in continuous read mode (t) or one-shot (f)
    @param mode True for continuous, False for one-shot
*/
/**************************************************************************/
void Adafruit_MMC5603::setContinuousMode(bool mode) {
  if (mode) {
    _ctrl0_reg->write(0x80); // turn on cmm_freq_en bit
    _ctrl2_cache |= 0x10;    // turn on cmm_en bit
  } else {
    _ctrl2_cache &= ~0x10; // turn off cmm_en bit
  }
  _ctrl2_reg->write(_ctrl2_cache);
}

/**************************************************************************/
/*!
    @brief Determine whether we are in continuous read mode (t) or one-shot (f)
    @returns True for continuous, False for one-shot
*/
/**************************************************************************/
bool Adafruit_MMC5603::isContinuousMode(void) { return _ctrl2_cache & 0x10; }

/**************************************************************************/
/*!
    @brief Read the temperature from onboard sensor - must not be in continuous
   mode for this to function it seems
    @returns Floating point temp in C, or NaN if sensor is in continuous mode
*/
/**************************************************************************/
float Adafruit_MMC5603::readTemperature(void) {
  if (isContinuousMode())
    return NAN;

  _ctrl0_reg->write(0x02); // TM_T trigger

  Adafruit_BusIO_RegisterBits temp_read_done =
      Adafruit_BusIO_RegisterBits(_status_reg, 1, 7);

  while (!temp_read_done.read()) {
    delay(5);
  }

  Adafruit_BusIO_Register temp_data =
      Adafruit_BusIO_Register(i2c_dev, MMC56X3_OUT_TEMP);

  float temp = temp_data.read();
  temp *= 0.8; //  0.8*C / LSB
  temp -= 75;  //  0 value is -75

  return temp;
}

/**************************************************************************/
/*!
    @brief  Gets the most recent sensor event
    @param event The `sensors_event_t` to fill with event data
    @returns true, always
*/
/**************************************************************************/
bool Adafruit_MMC5603::getEvent(sensors_event_t *event) {

  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  /* Read new data */
  if (!isContinuousMode()) {
    _ctrl0_reg->write(0x01); // TM_M trigger

    Adafruit_BusIO_RegisterBits mag_read_done =
        Adafruit_BusIO_RegisterBits(_status_reg, 1, 6);
    while (!mag_read_done.read()) {
      delay(5);
    }
  }
  uint8_t buffer[9];
  buffer[0] = MMC56X3_OUT_X_L;

  // read 8 bytes!
  i2c_dev->write_then_read(buffer, 1, buffer, 9);

  x = (uint32_t)buffer[0] << 12 | (uint32_t)buffer[1] << 4 |
      (uint32_t)buffer[6] >> 4;
  y = (uint32_t)buffer[2] << 12 | (uint32_t)buffer[3] << 4 |
      (uint32_t)buffer[7] >> 4;
  z = (uint32_t)buffer[4] << 12 | (uint32_t)buffer[5] << 4 |
      (uint32_t)buffer[8] >> 4;
  // fix center offsets
  x -= (uint32_t)1 << 19;
  y -= (uint32_t)1 << 19;
  z -= (uint32_t)1 << 19;

  event->version = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type = SENSOR_TYPE_MAGNETIC_FIELD;
  event->timestamp = millis();
  event->magnetic.x = (float)x * 0.00625; // scale to uT by LSB in datasheet
  event->magnetic.y = (float)y * 0.00625;
  event->magnetic.z = (float)z * 0.00625;

  return true;
}

/**************************************************************************/
/*!
    @brief  Sets the magnetometer's update rate, from 0-255 or 1000
    @param rate The new frequency data rate to set, from 0-255 or 1000
*/
/**************************************************************************/
void Adafruit_MMC5603::setDataRate(uint16_t rate) {
  // only 0~255 and 1000 are valid, so just move any high rates to 1000
  if (rate > 255)
    rate = 1000;
  _odr_cache = rate;

  Adafruit_BusIO_Register odr_reg =
      Adafruit_BusIO_Register(i2c_dev, MMC5603_ODR_REG);

  if (rate == 1000) {
    odr_reg.write(255);
    _ctrl2_cache |= 0x80; // turn on hpower bit
    _ctrl2_reg->write(_ctrl2_cache);
  } else {
    odr_reg.write(rate);
    _ctrl2_cache &= ~0x80; // turn off hpower bit
    _ctrl2_reg->write(_ctrl2_cache);
  }
}

/**************************************************************************/
/*!
    @brief  Gets the magnetometer's update rate (cached from data rate set)
    @returns The current data rate from 0-255 or 1000
*/
/**************************************************************************/
uint16_t Adafruit_MMC5603::getDataRate(void) { return _ctrl2_cache; }

/**************************************************************************/
/*!
    @brief  Gets the sensor_t data
    @param  sensor The unified sensor_t object we will populate
*/
/**************************************************************************/
void Adafruit_MMC5603::getSensor(sensor_t *sensor) {
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy(sensor->name, "MMC5603", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name) - 1] = 0;
  sensor->version = 1;
  sensor->sensor_id = _sensorID;
  sensor->type = SENSOR_TYPE_MAGNETIC_FIELD;
  sensor->min_delay = 0;
  sensor->max_value = 3000;     // 30 gauss = 3000 uTesla
  sensor->min_value = -3000;    // -30 gauss = -3000 uTesla
  sensor->resolution = 0.00625; // 20 bit 0.00625 uT LSB
}
