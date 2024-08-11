/*!
 * @file Adafruit_SH1106.h
 *
 * Modified by Coela, original is SSD1306 library
 * 
 * 
 * This is part of for Adafruit's SH1106 library for monochrome
 * OLED displays: http://www.adafruit.com/category/63_98
 *
 * These displays use I2C or SPI to communicate. I2C requires 2 pins
 * (SCL+SDA) and optionally a RESET pin. SPI requires 4 pins (MOSI, SCK,
 * select, data/command) and optionally a reset pin. Hardware SPI or
 * 'bitbang' software SPI are both supported.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries, with
 * contributions from the open source community.
 *
 * BSD license, all text above, and the splash screen header file,
 * must be included in any redistribution.
 *
 */

#ifndef _Adafruit_SH1106_H_
#define _Adafruit_SH1106_H_

// ONE of the following three lines must be #defined:
#define SH1106_128_64 ///< DEPRECTAED: old way to specify 128x64 screen
//#define SH1106_128_32 ///< DEPRECATED: old way to specify 128x32 screen
//#define SH1106_96_16  ///< DEPRECATED: old way to specify 96x16 screen
// This establishes the screen dimensions in old Adafruit_SH1106 sketches
// (NEW CODE SHOULD IGNORE THIS, USE THE CONSTRUCTORS THAT ACCEPT WIDTH
// AND HEIGHT ARGUMENTS).

// Uncomment to disable Adafruit splash logo
//#define SH1106_NO_SPLASH

#if defined(ARDUINO_STM32_FEATHER)
typedef class HardwareSPI SPIClass;
#endif

#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>

#if defined(__AVR__)
typedef volatile uint8_t PortReg;
typedef uint8_t PortMask;
#define HAVE_PORTREG
#elif defined(__SAM3X8E__)
typedef volatile RwReg PortReg;
typedef uint32_t PortMask;
#define HAVE_PORTREG
#elif (defined(__arm__) || defined(ARDUINO_FEATHER52)) &&                      \
    !defined(ARDUINO_ARCH_MBED) && !defined(ARDUINO_ARCH_RP2040)
typedef volatile uint32_t PortReg;
typedef uint32_t PortMask;
#define HAVE_PORTREG
#endif

/// The following "raw" color names are kept for backwards client compatability
/// They can be disabled by predefining this macro before including the Adafruit
/// header client code will then need to be modified to use the scoped enum
/// values directly
#ifndef NO_ADAFRUIT_SH1106_COLOR_COMPATIBILITY
#define BLACK SH1106_BLACK     ///< Draw 'off' pixels
#define WHITE SH1106_WHITE     ///< Draw 'on' pixels
#define INVERSE SH1106_INVERSE ///< Invert pixels
#endif
/// fit into the SH1106_ naming scheme
#define SH1106_BLACK 0   ///< Draw 'off' pixels
#define SH1106_WHITE 1   ///< Draw 'on' pixels
#define SH1106_INVERSE 2 ///< Invert pixels

#define SH1106_MEMORYMODE 0x20          ///< See datasheet
#define SH1106_COLUMNADDR 0x21          ///< See datasheet
#define SH1106_PAGEADDR 0x22            ///< See datasheet
#define SH1106_SETCONTRAST 0x81         ///< See datasheet
#define SH1106_CHARGEPUMP 0x8D          ///< See datasheet
#define SH1106_SEGREMAP 0xA0            ///< See datasheet
#define SH1106_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SH1106_DISPLAYALLON 0xA5        ///< Not currently used
#define SH1106_NORMALDISPLAY 0xA6       ///< See datasheet
#define SH1106_INVERTDISPLAY 0xA7       ///< See datasheet
#define SH1106_SETMULTIPLEX 0xA8        ///< See datasheet
#define SH1106_DISPLAYOFF 0xAE          ///< See datasheet
#define SH1106_DISPLAYON 0xAF           ///< See datasheet
#define SH1106_COMSCANINC 0xC0          ///< Not currently used
#define SH1106_COMSCANDEC 0xC8          ///< See datasheet
#define SH1106_SETDISPLAYOFFSET 0xD3    ///< See datasheet
#define SH1106_SETDISPLAYCLOCKDIV 0xD5  ///< See datasheet
#define SH1106_SETPRECHARGE 0xD9        ///< See datasheet
#define SH1106_SETCOMPINS 0xDA          ///< See datasheet
#define SH1106_SETVCOMDETECT 0xDB       ///< See datasheet

#define SH1106_SETLOWCOLUMN 0x00  ///< Not currently used
#define SH1106_SETHIGHCOLUMN 0x10 ///< Not currently used
#define SH1106_SETSTARTLINE 0x40  ///< See datasheet

#define SH1106_EXTERNALVCC 0x01  ///< External display voltage source
#define SH1106_SWITCHCAPVCC 0x02 ///< Gen. display voltage from 3.3V

#define SH1106_RIGHT_HORIZONTAL_SCROLL 0x26              ///< Init rt scroll
#define SH1106_LEFT_HORIZONTAL_SCROLL 0x27               ///< Init left scroll
#define SH1106_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29 ///< Init diag scroll
#define SH1106_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A  ///< Init diag scroll
#define SH1106_DEACTIVATE_SCROLL 0x2E                    ///< Stop scroll
#define SH1106_ACTIVATE_SCROLL 0x2F                      ///< Start scroll
#define SH1106_SET_VERTICAL_SCROLL_AREA 0xA3             ///< Set scroll range

// Deprecated size stuff for backwards compatibility with old sketches
#if defined SH1106_128_64
#define SH1106_LCDWIDTH 128 ///< DEPRECATED: width w/SH1106_128_64 defined
#define SH1106_LCDHEIGHT 64 ///< DEPRECATED: height w/SH1106_128_64 defined
#endif
#if defined SH1106_128_32
#define SH1106_LCDWIDTH 128 ///< DEPRECATED: width w/SH1106_128_32 defined
#define SH1106_LCDHEIGHT 32 ///< DEPRECATED: height w/SH1106_128_32 defined
#endif
#if defined SH1106_96_16
#define SH1106_LCDWIDTH 96  ///< DEPRECATED: width w/SH1106_96_16 defined
#define SH1106_LCDHEIGHT 16 ///< DEPRECATED: height w/SH1106_96_16 defined
#endif

/*!
    @brief  Class that stores state and functions for interacting with
            SH1106 OLED displays.
*/
class Adafruit_SH1106 : public Adafruit_GFX {
public:
  // NEW CONSTRUCTORS -- recommended for new projects
  Adafruit_SH1106(uint8_t w, uint8_t h, TwoWire *twi = &Wire,
                   int8_t rst_pin = -1, uint32_t clkDuring = 400000UL,
                   uint32_t clkAfter = 100000UL);
  Adafruit_SH1106(uint8_t w, uint8_t h, int8_t mosi_pin, int8_t sclk_pin,
                   int8_t dc_pin, int8_t rst_pin, int8_t cs_pin);
  Adafruit_SH1106(uint8_t w, uint8_t h, SPIClass *spi, int8_t dc_pin,
                   int8_t rst_pin, int8_t cs_pin, uint32_t bitrate = 8000000UL);

  // DEPRECATED CONSTRUCTORS - for back compatibility, avoid in new projects
  Adafruit_SH1106(int8_t mosi_pin, int8_t sclk_pin, int8_t dc_pin,
                   int8_t rst_pin, int8_t cs_pin);
  Adafruit_SH1106(int8_t dc_pin, int8_t rst_pin, int8_t cs_pin);
  Adafruit_SH1106(int8_t rst_pin = -1);

  ~Adafruit_SH1106(void);

  bool begin(uint8_t switchvcc = SH1106_SWITCHCAPVCC, uint8_t i2caddr = 0,
             bool reset = true, bool periphBegin = true);
  void display(void);
  void clearDisplay(void);
  void invertDisplay(bool i);
  void dim(bool dim);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void startscrollright(uint8_t start, uint8_t stop);
  void startscrollleft(uint8_t start, uint8_t stop);
  void startscrolldiagright(uint8_t start, uint8_t stop);
  void startscrolldiagleft(uint8_t start, uint8_t stop);
  void stopscroll(void);
  void sh1106_command(uint8_t c);
  bool getPixel(int16_t x, int16_t y);
  uint8_t *getBuffer(void);

protected:
  inline void SPIwrite(uint8_t d) __attribute__((always_inline));
  void drawFastHLineInternal(int16_t x, int16_t y, int16_t w, uint16_t color);
  void drawFastVLineInternal(int16_t x, int16_t y, int16_t h, uint16_t color);
  void sh1106_command1(uint8_t c);
  void sh1106_commandList(const uint8_t *c, uint8_t n);

  SPIClass *spi;   ///< Initialized during construction when using SPI. See
                   ///< SPI.cpp, SPI.h
  TwoWire *wire;   ///< Initialized during construction when using I2C. See
                   ///< Wire.cpp, Wire.h
  uint8_t *buffer; ///< Buffer data used for display buffer. Allocated when
                   ///< begin method is called.
  int8_t i2caddr;  ///< I2C address initialized when begin method is called.
  int8_t vccstate; ///< VCC selection, set by begin method.
  int8_t page_end; ///< not used
  int8_t mosiPin;  ///< (Master Out Slave In) set when using SPI set during
                   ///< construction.
  int8_t clkPin;   ///< (Clock Pin) set when using SPI set during construction.
  int8_t dcPin;    ///< (Data Pin) set when using SPI set during construction.
  int8_t
      csPin; ///< (Chip Select Pin) set when using SPI set during construction.
  int8_t rstPin; ///< Display reset pin assignment. Set during construction.

#ifdef HAVE_PORTREG
  PortReg *mosiPort, *clkPort, *dcPort, *csPort;
  PortMask mosiPinMask, clkPinMask, dcPinMask, csPinMask;
#endif
#if ARDUINO >= 157
  uint32_t wireClk;    ///< Wire speed for SH1106 transfers
  uint32_t restoreClk; ///< Wire speed following SH1106 transfers
#endif
  uint8_t contrast; ///< normal contrast setting for this device
#if defined(SPI_HAS_TRANSACTION)
protected:
  // Allow sub-class to change
  SPISettings spiSettings;
#endif
};

#endif // _Adafruit_SH1106_H_