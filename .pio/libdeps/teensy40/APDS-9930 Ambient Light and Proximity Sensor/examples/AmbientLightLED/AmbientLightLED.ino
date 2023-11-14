/****************************************************************
AmbientLightLED.ino

Tests the ambient light sensing abilities of the 
APDS-9930. Configures APDS-9930 over I2C and polls the sensor for
ambient light levels, which are displayed over the 
serial console.

Hardware Connections:

IMPORTANT: The APDS-9930 can only accept 3.3V!
 
 Arduino Pin  APDS-9930 Board  Function
 
 3.3V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock

 10 (pwm)     LED anode

Distributed as-is; no warranty is given.
****************************************************************/

#define PWM_LED_PIN       10
#define DUMP_REGS

#include <Wire.h>
#include <APDS9930.h>

// Global Variables
APDS9930 apds = APDS9930();
float ambient_light = 0; // can also be an unsigned long
uint16_t ch0 = 0;
uint16_t ch1 = 1;
float max_light = 0;

void setup() {
  //analogReference(EXTERNAL);
  pinMode(PWM_LED_PIN, OUTPUT);
  
  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("APDS-9930 - Ambient light sensor"));
  Serial.println(F("--------------------------------"));
  
  // Initialize APDS-9930 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9930 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9930 init!"));
  }
  
  // Start running the APDS-9930 light sensor (no interrupts)
  if ( apds.enableLightSensor(false) ) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
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
  
  // Read the light levels (ambient, red, green, blue)
  if (  !apds.readAmbientLightLux(ambient_light) ||
        !apds.readCh0Light(ch0) || 
        !apds.readCh1Light(ch1) ) {
    Serial.println(F("Error reading light values"));
  } else {
    Serial.print(F("Ambient: "));
    Serial.print(ambient_light);
    Serial.print(F("  Ch0: "));
    Serial.print(ch0);
    Serial.print(F("  Ch1: "));
    Serial.println(ch1);

    if ( ambient_light > max_light ) {
      max_light = ambient_light;
    }
    ambient_light = map(ambient_light, 0, max_light, 0, 1023);
    analogWrite(PWM_LED_PIN, ambient_light);

  }
  
  // Wait 1 second before next reading
  delay(50);
}