#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;

#define BUTTON_X         6
#define BUTTON_Y         2
#define BUTTON_A         5
#define BUTTON_B         1
#define BUTTON_SELECT    0
#define BUTTON_START    16
uint32_t button_mask = (1UL << BUTTON_X) | (1UL << BUTTON_Y) | (1UL << BUTTON_START) |
                       (1UL << BUTTON_A) | (1UL << BUTTON_B) | (1UL << BUTTON_SELECT);

//#define IRQ_PIN   5


void setup() {
  Serial.begin(115200);

  while(!Serial) {
    delay(10);
  }

  Serial.println("Gamepad QT example!");
  
  if(!ss.begin(0x50)){
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  }
  Serial.println("seesaw started");
  uint32_t version = ((ss.getVersion() >> 16) & 0xFFFF);
  if (version != 5743) {
    Serial.print("Wrong firmware loaded? ");
    Serial.println(version);
    while(1) delay(10);
  }
  Serial.println("Found Product 5743");
  
  ss.pinModeBulk(button_mask, INPUT_PULLUP);
  ss.setGPIOInterrupts(button_mask, 1);

#if defined(IRQ_PIN)
  pinMode(IRQ_PIN, INPUT);
#endif
}


int last_x = 0, last_y = 0;

void loop() {
  delay(10); // delay in loop to slow serial output
  
  // Reverse x/y values to match joystick orientation
  int x = 1023 - ss.analogRead(14);
  int y = 1023 - ss.analogRead(15);
  
  if ( (abs(x - last_x) > 3)  ||  (abs(y - last_y) > 3)) {
    Serial.print("x: "); Serial.print(x); Serial.print(", "); Serial.print("y: "); Serial.println(y);
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

    if (! (buttons & (1UL << BUTTON_A))) {
      Serial.println("Button A pressed");
    }
    if (! (buttons & (1UL << BUTTON_B))) {
      Serial.println("Button B pressed");
    }
    if (! (buttons & (1UL << BUTTON_Y))) {
      Serial.println("Button Y pressed");
    }
    if (! (buttons & (1UL << BUTTON_X))) {
      Serial.println("Button X pressed");
    }
    if (! (buttons & (1UL << BUTTON_SELECT))) {
      Serial.println("Button SELECT pressed");
    }
    if (! (buttons & (1UL << BUTTON_START))) {
      Serial.println("Button START pressed");
    }
}
