#pragma once

#ifndef _MINI_TFT_WING_H
#define _MINI_TFT_WING_H

#include "Adafruit_seesaw.h"

#define TFTWING_ADDR 0x5E

#define TFTWING_BACKLIGHT_ON 0       // inverted output!
#define TFTWING_BACKLIGHT_OFF 0xFFFF // inverted output!

extern uint32_t TFTWING_BUTTON_UP, TFTWING_BUTTON_DOWN, TFTWING_BUTTON_LEFT,
    TFTWING_BUTTON_RIGHT, TFTWING_BUTTON_A, TFTWING_BUTTON_B,
    TFTWING_BUTTON_SELECT;

/**************************************************************************/
/*!
    @brief  Class that stores state and functions for interacting with mini tft
   wing variant of seesaw helper IC
*/
/**************************************************************************/
class Adafruit_miniTFTWing : public Adafruit_seesaw {
public:
  Adafruit_miniTFTWing(){};
  ~Adafruit_miniTFTWing(){};

  bool begin(uint8_t addr = TFTWING_ADDR, TwoWire *Wi = NULL);

  void setBacklight(uint16_t value);
  void setBacklightFreq(uint16_t freq);
  void tftReset(bool rst = true);
  uint32_t readButtons();
};

#endif
