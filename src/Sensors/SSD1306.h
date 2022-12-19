#include <Wire.h>

class SSD1306 {
public:
  // Initialize the display
  void Begin() {
    // Initialize the I2C bus
    Wire.begin();

    // Initialize the display
    SendCommand(0xAE); // Display off
    SendCommand(0xA8); // Set multiplex ratio
    SendCommand(0x3F); // 1/64 duty
    SendCommand(0xD3); // Set display offset
    SendCommand(0x00); // No offset
    SendCommand(0x40); // Set display start line
    SendCommand(0x8D); // Enable charge pump
    SendCommand(0x14); // Enable charge pump
    SendCommand(0x20); // Set memory mode
    SendCommand(0x00); // Horizontal addressing mode
    SendCommand(0xA1); // Set segment remap
    SendCommand(0xC8); // Set COM output scan direction
    SendCommand(0xDA); // Set COM pins hardware configuration
    SendCommand(0x12);
    SendCommand(0x81); // Set contrast control
    SendCommand(0xCF); // Max contrast
    SendCommand(0xD9); // Set precharge period
    SendCommand(0xF1);
    SendCommand(0xDB); // Set VCOMH deselect level
    SendCommand(0x40);
    SendCommand(0xA4); // Set entire display on/off
    SendCommand(0xA6); // Set normal display
    SendCommand(0xAF); // Display on

    // Clear the display
    Clear();
  }

  // Clear the display
  void Clear() {
    for (int i = 0; i < 8; i++) {
      SendCommand(0xB0 + i); // Set page address
      SendCommand(0x00); // Set lower column address
      SendCommand(0x10); // Set higher column address
      for (int j = 0; j < 128; j++) {
        SendData(0x00);
      }
    }
  }

  // Set the display brightness
  void SetBrightness(uint8_t value) {
    SendCommand(0x81); // Set contrast control
    SendCommand(value);
  }

  // Print text to a specific line on the display
  void PrintLine(int line, String text) {
    int len = text.length();
    if (len > 16) {
      len = 16;
    }

    // Set the text position
    SendCommand(0xB0 + line); // Set page address
    SendCommand(0x00); // Set lower column address
    SendCommand(0x10); // Set higher column address

    // Print the text
    for (int i = 0; i < len; i++) {
      SendData(pgm_read_byte(&font5x8[text[i] - 0x20][i]));
    }
  }

private:
  // Send a command to the display
  void SendCommand(uint8_t value) {
    Wire.beginTransmission(0x3C); // I2C address of the display
    Wire.write(0x00); // Co = 0, D/C = 0
    Wire.write(value);
    Wire.endTransmission();
  }

  // Send data to the display
  void SendData(uint8_t value) {
    Wire.beginTransmission(0x3C); // I2C address of the display
    Wire.write(0x40); // Co = 0, D/C = 1
    Wire.write(value);
    Wire.endTransmission();
  }
};