#pragma once

#include <Arduino.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <APDS9930.h>

class HardwareTest{
private:
    static void PrintAddress(uint8_t address, const String& text){
        Serial.print(address, HEX);
        Serial.print('\t');
        Serial.println(text);
    }

    static void PrintAddressValue(uint8_t address, const String& text, int value){
        Serial.print(address, HEX);
        Serial.print('\t');
        Serial.print(text);
        Serial.print('\t');
        Serial.println(value);
    }

    static bool TestI2CConnection(uint8_t address, String name, bool flip){
        Wire.setClock(400000);//for longer range transmissions

        if(flip){
            Wire.setSDA(19);
            Wire.setSCL(18);
        }
        else{
            Wire.setSDA(18);
            Wire.setSCL(19);
        }

        Wire.begin();
        
        Wire.beginTransmission(address);

        uint8_t error = Wire.endTransmission();
        
        switch (error) {
            case 0:
                PrintAddress(address, " " + name + " Found!");
                return true;
                break;
            case 1:
                PrintAddress(address, " " + name + ":\tData too long to fit in transmit buffer.");
                break;
            case 2:
                PrintAddress(address, " " + name + ":\tReceived NACK on transmit of address.");
                break;
            case 3:
                PrintAddress(address, " " + name + ":\tReceived NACK on transmit of data.");
                break;
            case 4:
                PrintAddress(address, " " + name + ":\tOther error.");
                break;
            default:
                PrintAddress(address, " " + name + " not found. Unknown error.");
                break;
        }
        
        Wire.end();

        return false;
    }

    static void TestAPDS9960(uint8_t address, bool flip){
        Wire.setClock(400000);//for longer range transmissions
        
        if(flip){
            Wire.setSDA(19);
            Wire.setSCL(18);
        }
        else{
            Wire.setSDA(18);
            Wire.setSCL(19);
        }

        Wire.begin();

		Wire.beginTransmission(address);

        Adafruit_APDS9960 apds;

        bool didBegin = apds.begin(10U, APDS9960_AGAIN_4X, address);
        apds.enableProximity(true);

        delay(500);

        PrintAddressValue(address, " APDS Did Begin: ", didBegin);

        if(didBegin){
            PrintAddressValue(address, " APDS Proximity: ", apds.readProximity());
        }
		
        Wire.end();
    }

    static void TestAPDS9930(uint8_t address, bool flip){
        Wire.setClock(400000);//for longer range transmissions
        
        if(flip){
            Wire.setSDA(19);
            Wire.setSCL(18);
        }
        else{
            Wire.setSDA(18);
            Wire.setSCL(19);
        }

        Wire.begin();

		Wire.beginTransmission(address);
        
        APDS9930 apds = APDS9930();

        bool didBegin = apds.init();
        
        //if(!apds.setProximityGain(PGAIN_8X)) Serial.println(F("Something went wrong trying to set PGAIN"));
        
        // Start running the APDS-9930 proximity sensor (no interrupts)
        if(apds.enableProximitySensor(false)) Serial.println(F("Proximity sensor is now running"));

        delay(500);

        PrintAddressValue(address, " APDS Did Begin: ", didBegin);

        uint16_t data = 100;
        for (int i = 0; i < 10; i++){
            bool didRead = apds.readProximity(data);

            if(didBegin && didRead){
                PrintAddressValue(address, " APDS Proximity: ", data);
            }

            delay(150);
        }
        
		
        Wire.end();
    }

    static void TestSSD1306(uint8_t address, bool flip){
        Wire.setClock(100000);//for longer range transmissions
        
        if(flip){
            Wire.setSDA(19);
            Wire.setSCL(18);
        }
        else{
            Wire.setSDA(18);
            Wire.setSCL(19);
        }

        Wire.begin();

		Wire.beginTransmission(address);

	    Adafruit_SSD1306 display;

		display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

        // Clear the buffer and display
        display.clearDisplay();
        display.invertDisplay(true);
        display.display();
        
        // Draw some shapes and text
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println(F("Hello, SSD1306!"));

        display.drawRect(10, 10, 20, 20, SSD1306_WHITE);
        display.fillCircle(60, 30, 15, SSD1306_WHITE);

        display.display(); // Display the buffer content
		
        Wire.end();
    }

public:
    static void TestMicrophone(){

    }

    static void TestButton(){

    }

    static void TestUART(){

    }

    static void TestHUD(){
        bool test1 = TestI2CConnection(0x3C, "SSD1306", false);

        if (test1) TestSSD1306(0x3C, false);
    }

    static void TestBoopSensor(){
        bool test1 = TestI2CConnection(0x39, "APDS9960", false);

        if (test1) TestAPDS9960(0x39, false);
        //if (test1) TestAPDS9930(0x39, false);

    }

    static void ScanDevices() {//timeout in milliseconds and threshold is minimum for detection (0 is far away, 255 is touching)
        Wire.setClock(100000);//for longer range transmissions
        Wire.begin();
        
        Wire.setSDA(18);
        Wire.setSCL(19);

        uint8_t numDevices = 0;

        for (uint8_t i = 0; i < 127; i++){
            Wire.beginTransmission(i);

            uint8_t error = Wire.endTransmission();

            if(error == 0){// SSD1306 Found
                Serial.print("Device on address: ");
                Serial.println(i, HEX);
                numDevices++;
            }
        }

        Serial.print("Number of Devices Found: ");
        Serial.println(numDevices);
		
        Wire.end();
    }


    static void ResetI2CBus() {
        Wire.end();  // Disable the I2C hardware
        delay(10);   // Wait a bit
        Wire.begin();  // Re-enable the I2C hardware
    }

};
