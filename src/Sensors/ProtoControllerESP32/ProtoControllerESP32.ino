#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SerialTransfer.h>
#include <Adafruit_APDS9960.h>
Adafruit_APDS9960 apds;

uint16_t BNO055_SAMPLERATE_DELAY_MS = 10;

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

static struct ESP32Data {
    float oW;
    float oX;
    float oY;
    float oZ;
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t c;
} e32Data;

SerialTransfer dataTransfer;

void setup(void){
  Wire.begin(23, 22);
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 12, 13);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  dataTransfer.begin(Serial1);

  /* Initialise the sensor */
  if (!bno.begin()){
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  //enable color sensign mode
  apds.enableColor(true);

  delay(1000);
}

void loop(void){
  imu::Quaternion quat = bno.getQuat();
  apds.getColorData(&e32Data.r, &e32Data.g, &e32Data.b, &e32Data.c);

  e32Data.oW = quat.w();
  e32Data.oX = quat.x();
  e32Data.oY = quat.y();
  e32Data.oZ = quat.z();
  
  Serial.print(F("Quaternion: "));
  Serial.print((float)quat.w());
  Serial.print(F(", "));
  Serial.print((float)quat.x());
  Serial.print(F(", "));
  Serial.print((float)quat.y());
  Serial.print(F(", "));
  Serial.print((float)quat.z());
  Serial.print(F(", "));
  Serial.print(e32Data.r);
  Serial.print(F(", "));
  Serial.print(e32Data.g);
  Serial.print(F(", "));
  Serial.print(e32Data.b);
  Serial.print(F(", "));
  Serial.print(e32Data.c);
  Serial.println(F(""));
 
  uint16_t sendSize = 0;

  sendSize = dataTransfer.txObj(e32Data, sendSize);
  
  dataTransfer.sendData(sendSize);

  delay(BNO055_SAMPLERATE_DELAY_MS);
}
