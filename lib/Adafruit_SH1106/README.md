# Adafruit_SH1106 (Fork of Adafruit_SSD1306) [![Build Status](https://github.com/coelacant1/Adafruit_SH1106/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/coelacant1/Adafruit_SH1106/actions)

This is a library that provides support for the SH1106 display drivers that is drop in compatible with Adafruits Monochrome OLEDs based SSD1306 driver: http://www.adafruit.com/category/63_98

These displays use I2C or SPI to communicate, 2 to 5 pins are required to interface.

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries, with contributions from the open source community. Scrolling code contributed by Michael Gregg. Dynamic buffer allocation based on work by Andrew Canaday. Modified support for SH1106 by Coelacant1.
BSD license, check license.txt for more information. All text above must be included in any redistribution

Preferred installation method is to use the Arduino IDE Library Manager. To download the source from Github instead, click "Clone or download" above, then "Download ZIP." After uncompressing, rename the resulting folder Adafruit_SH1106. Check that the Adafruit_SH1106 folder contains Adafruit_SH1106.cpp and Adafruit_SH1106.h.

You will also have to install the **Adafruit GFX library** which provides graphics primitves such as lines, circles, text, etc. This also can be found in the Arduino Library Manager, or you can get the source from https://github.com/adafruit/Adafruit-GFX-Library

## Changes
Fork 2024:
   * This fork provides support to use the existing design/structure of the SSD1306 library for the SH1106 to allow this library to be drag and drop.

Pull Request:
   (November 2021) 
   * Added define `SSD1306_NO_SPLASH` to opt-out of including splash images in `PROGMEM` and drawing to display during `begin`.

Pull Request:
   (September 2019) 
   * new #defines for SSD1306_BLACK, SSD1306_WHITE and SSD1306_INVERSE that match existing #define naming scheme and won't conflict with common color names
   * old #defines for BLACK, WHITE and INVERSE kept for backwards compat (opt-out with #define NO_ADAFRUIT_SSD1306_COLOR_COMPATIBILITY)

Version 1.2 (November 2018) introduces some significant changes:

  * Display dimensions are now specified in the constructor...you no longer need to edit the .h file for different screens (though old sketches can continue to work that way).
  * SPI transactions are used and SPI bitrate can be specified (both require Arduino 1.6 or later).
  * SPI and Wire (I2C) interfaces other than the defaults are supported.

<!-- START COMPATIBILITY TABLE -->

## Compatibility

Functionality | Tested Works | Doesn't Work | Not Tested
--------------|:-------------|:-------------|:----------
I2C           |       X      |              |           
SPI           |              |              |     X     
Scrolling     |              |              |     X

MCU         |Tested Works|Doesn't Work|Not Tested|Notes
------------|:----------:|:----------:|:--------:|-----
Atmega328   |            |            |     X    |
Atmega32u4  |            |            |     X    |
Atmega2560  |            |            |     X    |
ESP8266     |            |            |     X    | Change OLED_RESET to different pin if using default I2C pins D4/D5.
ESP32       |            |            |     X    |
ATSAM3X8E   |            |            |     X    |
ATSAMD21    |            |            |     X    |
Intel Curie |            |            |     X    |
WICED       |            |            |     X    | No hardware SPI - bitbang only
ATtiny85    |            |            |     X    |
Particle    |            |            |     X    |
Teensy 4.0  |      X     |            |          |

  * ATmega328 : Arduino UNO, Adafruit Pro Trinket, Adafruit Metro 328, Adafruit Metro Mini
  * ATmega32u4 : Arduino Leonardo, Arduino Micro, Arduino Yun, Teensy 2.0, Adafruit Flora, Bluefruit Micro
  * ATmega2560 : Arduino Mega
  * ESP8266 : Adafruit Huzzah
  * ATSAM3X8E : Arduino Due
  * ATSAMD21 : Arduino Zero, M0 Pro, Adafruit Metro Express, Feather M0
  * ATtiny85 : Adafruit Gemma, Arduino Gemma, Adafruit Trinket
  * Particle: Particle Argon

<!-- END COMPATIBILITY TABLE -->