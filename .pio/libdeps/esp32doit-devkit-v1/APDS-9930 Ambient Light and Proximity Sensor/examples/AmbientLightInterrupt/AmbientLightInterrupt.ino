/****************************************************************
AmbientLightInterrupt.ino
APDS-9930 RGB and Gesture Sensor
Shawn Hymel @ SparkFun Electronics
October 24, 2014
https://github.com/sparkfun/APDS-9930_RGB_and_Gesture_Sensor

Tests the ambient light interrupt abilities of the APDS-9930.
Configures the APDS-9930 over I2C and waits for an external
interrupt based on high or low light conditions. Try covering
the sensor with your hand or bringing the sensor close to a
bright light source. You might need to adjust the LIGHT_INT_HIGH
and LIGHT_INT_LOW values to get the interrupt to work correctly.

Hardware Connections:

IMPORTANT: The APDS-9930 can only accept 3.3V!
 
 Arduino Pin  APDS-9930 Board  Function
 
 3.3V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock
 2            INT              Interrupt
 13           -                LED

Resources:
Include Wire.h and APDS9930.h

Development environment specifics:
Written in Arduino 1.0.5
Tested with SparkFun Arduino Pro Mini 3.3V

This code is beerware; if you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, please
buy us a round!

Distributed as-is; no warranty is given.
****************************************************************/

#define DUMP_REGS

#include <Wire.h>
#include <APDS9930.h>

// Pins
#define APDS9930_INT    2  // Needs to be an interrupt pin
#define LED_PIN         13 // LED for showing interrupt

// Constants
#define LIGHT_INT_HIGH  1000 // High light level for interrupt
#define LIGHT_INT_LOW   10   // Low light level for interrupt

// Global variables
APDS9930 apds = APDS9930();
float ambient_light = 0;
uint16_t ch0 = 0;
uint16_t ch1 = 1;
volatile bool isr_flag = false;
uint16_t threshold = 0;

void setup() {
  
  // Set LED as output
  pinMode(LED_PIN, OUTPUT);
  pinMode(APDS9930_INT, INPUT);
  
  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("----------------------------"));
  Serial.println(F("APDS-9930 - Light Interrupts"));
  Serial.println(F("----------------------------"));
  
  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);
  
  // Initialize APDS-9930 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9930 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9930 init!"));
  }
  
  // Set high and low interrupt thresholds
  if ( !apds.setLightIntLowThreshold(LIGHT_INT_LOW) ) {
    Serial.println(F("Error writing low threshold"));
  }
  if ( !apds.setLightIntHighThreshold(LIGHT_INT_HIGH) ) {
    Serial.println(F("Error writing high threshold"));
  }
  
  // Start running the APDS-9930 light sensor (no interrupts)
  if ( apds.enableLightSensor(false) ) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  }
  
  // Read high and low interrupt thresholds
  if ( !apds.getLightIntLowThreshold(threshold) ) {
    Serial.println(F("Error reading low threshold"));
  } else {
    Serial.print(F("Low Threshold: "));
    Serial.println(threshold);
  }
  if ( !apds.getLightIntHighThreshold(threshold) ) {
    Serial.println(F("Error reading high threshold"));
  } else {
    Serial.print(F("High Threshold: "));
    Serial.println(threshold);
  }
  
  // Enable interrupts
  if ( !apds.setAmbientLightIntEnable(1) ) {
    Serial.println(F("Error enabling interrupts"));
  }

#ifdef DUMP_REGS
  /* Register dump */
  uint8_t reg;
  uint8_t val;

  for(reg = 0x00; reg <= 0x19; reg++) {
    if( (reg != 0x10) && \
        (reg != 0x11) )
    {
      apds.wireReadDataByte(reg, val);
      Serial.print(reg, HEX);
      Serial.print(": 0x");
      Serial.println(val, HEX);
    }
  }
  apds.wireReadDataByte(0x1E, val);
  Serial.print(0x1E, HEX);
  Serial.print(": 0x");
  Serial.println(val, HEX);
#endif

  // Wait for initialization and calibration to finish
  delay(500);
}

void loop() {
  
  // If interrupt occurs, print out the light levels
  if ( isr_flag ) {
    
    // Read the light levels (ambient, red, green, blue) and print
    if ( !apds.readAmbientLightLux(ambient_light) ||
         !apds.readCh0Light(ch0) || 
         !apds.readCh1Light(ch1) ) {
      Serial.println("Error reading light values");
    } else {
      Serial.print("Interrupt! Ambient: ");
      Serial.print(ambient_light);
      Serial.print(F("  Ch0: "));
      Serial.print(ch0);
      Serial.print(F("  Ch1: "));
      Serial.println(ch1);
    }
    
    // Turn on LED for a half a second
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    
    // Reset flag and clear APDS-9930 interrupt (IMPORTANT!)
    isr_flag = false;
    if ( !apds.clearAmbientLightInt() ) {
      Serial.println("Error clearing interrupt");
    }
    
  }
}

void interruptRoutine() {
  isr_flag = true;
}