/*
 * This is a demo for a Feather ESP32-S2 TFT connected to a Quad
 * Rotary Encoder board
 * https://www.adafruit.com/product/5300
 * https://www.adafruit.com/product/5752
 * 
 */
#include "Adafruit_seesaw.h"
#include <seesaw_neopixel.h>
#include <Adafruit_ST7789.h> 
#include <Fonts/FreeSans12pt7b.h>
// we hvae loooots of PSRAM so lets use a GFX canvas for flicker-free graphics!
GFXcanvas16 canvas(240, 135);
Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


#define SS_NEO_PIN       18
#define SS_ENC0_SWITCH   12
#define SS_ENC1_SWITCH   14
#define SS_ENC2_SWITCH   17
#define SS_ENC3_SWITCH   9

#define SEESAW_ADDR      0x49

Adafruit_seesaw ss = Adafruit_seesaw(&Wire);
seesaw_NeoPixel pixels = seesaw_NeoPixel(4, SS_NEO_PIN, NEO_GRB + NEO_KHZ800);

int32_t enc_positions[4] = {0, 0, 0, 0};

void setup() {
  Serial.begin(115200);
  //while (!Serial) delay(10);

  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, LOW);
    
  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);
  
  Serial.println("Looking for seesaw!");
  
  if (! ss.begin(SEESAW_ADDR) || !pixels.begin(SEESAW_ADDR)) {
    Serial.println("Couldn't find seesaw on default address");
    while(1) delay(10);
  }
  Serial.println("seesaw started");
  uint32_t version = ((ss.getVersion() >> 16) & 0xFFFF);
  if (version  != 5752){
    Serial.print("Wrong firmware loaded? ");
    Serial.println(version);
    while(1) delay(10);
  }
  Serial.println("Found Product 5752");

  ss.pinMode(SS_ENC0_SWITCH, INPUT_PULLUP);
  ss.pinMode(SS_ENC1_SWITCH, INPUT_PULLUP);
  ss.pinMode(SS_ENC2_SWITCH, INPUT_PULLUP);
  ss.pinMode(SS_ENC3_SWITCH, INPUT_PULLUP);
  ss.setGPIOInterrupts(1UL << SS_ENC0_SWITCH | 1UL << SS_ENC1_SWITCH | 
                       1UL << SS_ENC2_SWITCH | 1UL << SS_ENC3_SWITCH, 1);

  
  // get starting positions
  for (int e=0; e<4; e++) {
    enc_positions[e] = ss.getEncoderPosition(e);
    ss.enableEncoderInterrupt(e);
  }
  
  Serial.println("Turning on interrupts");

  pixels.setBrightness(255);
  pixels.show(); // Initialize all pixels to 'off'

  display.init(135, 240);           // Init ST7789 240x135
  display.setRotation(3);
  display.fillScreen(ST77XX_BLUE);
  digitalWrite(TFT_BACKLITE, HIGH);

  canvas.setFont(&FreeSans12pt7b);
  canvas.setTextColor(ST77XX_WHITE);  
}

uint8_t switch_pins[] = {SS_ENC0_SWITCH, SS_ENC1_SWITCH, SS_ENC2_SWITCH, SS_ENC3_SWITCH};

void loop() {
  bool changed = false;
  canvas.fillScreen(ST77XX_BLACK);
  canvas.setCursor(0, 25);
  canvas.setTextColor(ST77XX_WHITE);
  //canvas.println("Quad Encoder QT Demo");

  for (int e=0; e<4; e++) {
    int32_t new_enc_position = ss.getEncoderPosition(e);
    // did we move around?
    if (enc_positions[e] != new_enc_position) {
      Serial.print("Rot. #");
      Serial.print(e);
      Serial.print(" -> ");
      Serial.println(new_enc_position);      // display new position
      enc_positions[e] = new_enc_position;      // and save for next round
      
      // change the neopixel color, mulitply the new positiion by 4 to speed it up
      pixels.setPixelColor(e, Wheel((new_enc_position*4) & 0xFF));
      pixels.show();
      changed = true;
    }
    canvas.setTextColor(ST77XX_WHITE);
    canvas.print("Rotary #");
    canvas.print(e);
    canvas.print(": ");
    canvas.print(enc_positions[e]);

    if (! ss.digitalRead(switch_pins[e])) {
       Serial.print("ENC");
       Serial.print("e");
       Serial.println("pressed!");
       canvas.setTextColor(ST77XX_RED);
       canvas.print(" DOWN");
       changed = true;
    }
    canvas.println();
  }

  if (changed) {
    display.drawRGBBitmap(0, 0, canvas.getBuffer(), 240, 135);
  }
}


uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return seesaw_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return seesaw_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return seesaw_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
