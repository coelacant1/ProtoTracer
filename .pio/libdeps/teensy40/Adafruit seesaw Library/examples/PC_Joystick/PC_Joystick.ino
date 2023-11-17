#include "Adafruit_seesaw.h"

// creates seesaw on I2C0 port
Adafruit_seesaw ss = Adafruit_seesaw(&Wire);
// uncomment this for using I2C1, such as STEMMA port on QT Py RP2040
// Adafruit_seesaw ss = Adafruit_seesaw(&Wire1);

#define BUTTON_1         3
#define BUTTON_2         13
#define BUTTON_3         2
#define BUTTON_4         14
uint32_t button_mask = (1UL << BUTTON_1) | (1UL << BUTTON_2) |
                       (1UL << BUTTON_3) | (1UL << BUTTON_4);
#define JOY1_X            1
#define JOY1_Y           15
#define JOY2_X            0
#define JOY2_Y           16

//#define IRQ_PIN   5

void setup() {
  Serial.begin(115200);

  while(!Serial) {
    delay(10);
  }

  Serial.println("PC Joystick QT example!");
  ss.begin(0x49);
  Serial.println("seesaw started");
  uint32_t version = ((ss.getVersion() >> 16) & 0xFFFF);
  if (version != 5753) {
    Serial.print("Wrong firmware loaded? ");
    Serial.println(version);
    while(1) delay(10);
  }
  Serial.println("Found Product 5753");
  
  ss.pinModeBulk(button_mask, INPUT_PULLUP);
  ss.setGPIOInterrupts(button_mask, 1);

#if defined(IRQ_PIN)
  pinMode(IRQ_PIN, INPUT);
#endif
}

float last_x = 0, last_y = 0;

void loop() {
  delay(10); // delay in loop to slow serial output

  float x = 0, y = 0;
  // These joysticks are really jittery so lets take 4 samples of each axis
  for (int s=0; s<4; s++) {
    x += ss.analogRead(JOY1_X);
    y += ss.analogRead(JOY1_Y);
  }
  x /= 4.0; // Take the average of the 4 samples
  y /= 4.0; 
  // PC joysticks aren't "true" voltage divider, because we have a fixed 10K
  // we dont know the 'normalized' value so we're just going to give you
  // the result in 'Kohms' for easier printing
  x = (1024.0/(float)x - 1);
  y = (1024.0/(float)y - 1);

  if ( (fabs(x - last_x) > 0.1)  ||  (fabs(y - last_y) > 0.1)) {
    Serial.print(x); Serial.print(", "); Serial.println(y);
    last_x = x;
    last_y = y;
  }

#if defined(IRQ_PIN)
  if(!digitalRead(IRQ_PIN)) {
    return;
  }
#endif

  uint32_t buttons = ss.digitalReadBulk(button_mask);
  //Serial.println(buttons, BIN);

  if (! (buttons & (1UL << BUTTON_1))) {
    Serial.println("Button 1 pressed");
  }
  if (! (buttons & (1UL << BUTTON_2))) {
    Serial.println("Button 2 pressed");
  }
  if (! (buttons & (1UL << BUTTON_3))) {
    Serial.println("Button 3 pressed");
  }
  if (! (buttons & (1UL << BUTTON_4))) {
    Serial.println("Button 4 pressed");
  }
}
