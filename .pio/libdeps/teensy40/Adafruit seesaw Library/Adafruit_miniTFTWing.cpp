#include "Adafruit_miniTFTWing.h"

// These are the default SAMD09 version pins! (for back compatibility)
uint8_t TFTWING_RESET_PIN = 8;

uint8_t TFTWING_BUTTON_UP_PIN = 2;
uint32_t TFTWING_BUTTON_UP = (1UL << TFTWING_BUTTON_UP_PIN);

uint8_t TFTWING_BUTTON_DOWN_PIN = 4;
uint32_t TFTWING_BUTTON_DOWN = (1UL << TFTWING_BUTTON_DOWN_PIN);

uint8_t TFTWING_BUTTON_LEFT_PIN = 3;
uint32_t TFTWING_BUTTON_LEFT = (1UL << TFTWING_BUTTON_LEFT_PIN);

uint8_t TFTWING_BUTTON_RIGHT_PIN = 7;
uint32_t TFTWING_BUTTON_RIGHT = (1UL << TFTWING_BUTTON_RIGHT_PIN);

uint8_t TFTWING_BUTTON_SELECT_PIN = 11;
uint32_t TFTWING_BUTTON_SELECT = (1UL << TFTWING_BUTTON_SELECT_PIN);

uint8_t TFTWING_BUTTON_A_PIN = 10;
uint32_t TFTWING_BUTTON_A = (1UL << TFTWING_BUTTON_A_PIN);

uint8_t TFTWING_BUTTON_B_PIN = 9;
uint32_t TFTWING_BUTTON_B = (1UL << TFTWING_BUTTON_B_PIN);

uint32_t TFTWING_BUTTON_ALL =
    (TFTWING_BUTTON_UP | TFTWING_BUTTON_DOWN | TFTWING_BUTTON_LEFT |
     TFTWING_BUTTON_RIGHT | TFTWING_BUTTON_SELECT | TFTWING_BUTTON_A |
     TFTWING_BUTTON_B);

/**************************************************************************/
/*!
    @brief  set up the miniTFTWing
    @param  addr optional address the seesaw chip can be found on
    @param  Wi optional alternative I2C port to use, e.g. &Wire1 etc. Defaults
   to &Wire
    @returns true on success, false on error
*/
/**************************************************************************/
bool Adafruit_miniTFTWing::begin(uint8_t addr, TwoWire *Wi) {
  if (Wi != NULL) {
    Adafruit_seesaw::_i2cbus = Wi;
  }

  if (!Adafruit_seesaw::begin(addr, -1)) {
    return false;
  }

  if ((getVersion() >> 16) == 3322) {
    // check if we have a product ID burned in, if so its the ATtiny816 version!
    TFTWING_BUTTON_UP_PIN = 16;
    TFTWING_BUTTON_UP = (1UL << TFTWING_BUTTON_UP_PIN);

    TFTWING_BUTTON_DOWN_PIN = 13;
    TFTWING_BUTTON_DOWN = (1UL << TFTWING_BUTTON_DOWN_PIN);

    TFTWING_BUTTON_LEFT_PIN = 12;
    TFTWING_BUTTON_LEFT = (1UL << TFTWING_BUTTON_LEFT_PIN);

    TFTWING_BUTTON_RIGHT_PIN = 14;
    TFTWING_BUTTON_RIGHT = (1UL << TFTWING_BUTTON_RIGHT_PIN);

    TFTWING_BUTTON_SELECT_PIN = 15;
    TFTWING_BUTTON_SELECT = (1UL << TFTWING_BUTTON_SELECT_PIN);

    TFTWING_BUTTON_A_PIN = 11;
    TFTWING_BUTTON_A = (1UL << TFTWING_BUTTON_A_PIN);

    TFTWING_BUTTON_B_PIN = 10;
    TFTWING_BUTTON_B = (1UL << TFTWING_BUTTON_B_PIN);

    TFTWING_BUTTON_ALL =
        (TFTWING_BUTTON_UP | TFTWING_BUTTON_DOWN | TFTWING_BUTTON_LEFT |
         TFTWING_BUTTON_RIGHT | TFTWING_BUTTON_SELECT | TFTWING_BUTTON_A |
         TFTWING_BUTTON_B);

    TFTWING_RESET_PIN = 6;
  }
  this->pinMode(TFTWING_RESET_PIN, OUTPUT);
  this->pinModeBulk(TFTWING_BUTTON_ALL, INPUT_PULLUP);
  return true;
}

/**************************************************************************/
/*!
    @brief  set the value of the backlight
    @param  value the backlight value to set NOTE: 0xFFFF is all the way on
   0x0000 is off.
*/
/**************************************************************************/
void Adafruit_miniTFTWing::setBacklight(uint16_t value) {

  if ((getVersion() >> 16) == 3322) {
    // this->analogWrite(7, value);
    this->pinMode(7, OUTPUT);
    if (value == TFTWING_BACKLIGHT_ON) {
      this->digitalWrite(7, LOW);
    } else {
      this->digitalWrite(7, HIGH);
    }
  } else {
    uint8_t cmd[] = {0x00, (uint8_t)(value >> 8), (uint8_t)value};
    this->write(SEESAW_TIMER_BASE, SEESAW_TIMER_PWM, cmd, 3);
  }
}

/**************************************************************************/
/*!
    @brief  set the PWM frequency for the backlight
    @param  freq the frequency to set the backlight to
*/
/**************************************************************************/
void Adafruit_miniTFTWing::setBacklightFreq(uint16_t freq) {
  if ((getVersion() >> 16) == 3322) {
  } else {
    uint8_t cmd[] = {0x0, (uint8_t)(freq >> 8), (uint8_t)freq};
    this->write(SEESAW_TIMER_BASE, SEESAW_TIMER_FREQ, cmd, 3);
  }
}

/**************************************************************************/
/*!
    @brief  reset the TFT screen by setting the value of the reset pin
    @param  rst the value to set the reset pin to
*/
/**************************************************************************/
void Adafruit_miniTFTWing::tftReset(bool rst) {
  this->digitalWrite(TFTWING_RESET_PIN, rst);
}

/**************************************************************************/
/*!
    @brief  read all buttons on the wing and return as a 32 bit integer
    @returns the value of the buttons
*/
/**************************************************************************/
uint32_t Adafruit_miniTFTWing::readButtons() {
  return this->digitalReadBulk(TFTWING_BUTTON_ALL);
}
