APDS9930 Ambient Light and Proximity sensor
===========================================

This is a fork of the [library from Sparkfun for the APDS-9960 sensor](https://github.com/sparkfun/APDS-9960_RGB_and_Gesture_Sensor). It has been adapted to read values from this other model.

[**Quick-start guide available here**](https://web.archive.org/web/20151224052223/http://davideddu.org/blog/posts/apds-9930-arduino-quickstart/)

[**Purchase an Avago APDS-9930 Breakout Board here**](http://www.dx.com/p/384037?Utm_rid=14976370&Utm_source=affiliate)


# DO NOT EMAIL ME IF YOU HAVE AN ISSUE
It will be deleted without reading. If you have an issue, [create an issue](https://github.com/Depau/APDS9930/issues) here on GitHub.

# Unmaintained
I'm not going to maintain this library any more. I will merge pull requests, though. Contributions are welcome. Just don't expect anything from me.

![Avago APDS-9930 Breakout Board](http://img.dxcdn.com/productimages/sku_384037_1.jpg)

**Note:** even though it says APDS-9960, it's an APDS-9930. That's how I ended up getting one of those. I wanted the RGB sensor. I found this crap in my mailbox. But I decided to write a library for it anyways ;)

Getting Started
---------------

* Download the Git repository as a ZIP ("Download ZIP" button)
* Unzip
* Copy the entire library directory (APDS-9930) to
\<Arduino installation directory\>/libraries
* Open the Arduino program
* Select File -> Examples -> APDS9930 -> GestureTest
* Plug in your Arduino and APDS-9930 with the following connections

*-OR-*

* Use the library manager

| Arduino Pin | APDS-9930 Board | Function |
|---|---|---| 
| 3.3V | VCC | Power |
| GND | GND | Ground |
| A4 | SDA | I²C Data |
| A5 | SCL | I²C Clock |
| 2 | INT | Interrupt |

*P.S.: you already know you can't use this purple little thing with your 5V Arduino without a level shifter, right? :) In case you don't have a level shifter, you can detach the microcontroller from an Arduino Uno, reconnect the oscillator pins, the RX and TX pins, the reset and the LED/SCK pins back to the board with some jumper wires. You can then power the microcontroller from a 3.3V source (the 3V3 output on the board should work) and connect the sensor directly to the MCU. Look up "Arduino on Breadboard".*

* Go to Tools -> Board and select your Arduino board
* Go to Tools -> Serial Port and select the COM port of your Arduino board
* Click "Upload"
* Go to Tools -> Serial Monitor
* Ensure the baud rate is set at 9600 baud
* Swipe your hand over the sensor in various directions!

Repository Contents
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/extras** - Additional documentation for the user. These files are ignored by the IDE. 
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE. 
* **library.properties** - General library properties for the Arduino package manager. 

Documentation
--------------

* **[Quickstart Guide](https://web.archive.org/web/20151224052223/http://davideddu.org/blog/posts/apds-9930-arduino-quickstart/)** - Basic hookup guide for the sensor.
* **[Product Repository](https://github.com/Davideddu/APDS9930)** - Main repository (including hardware files) for the APDS9930 ambient light and proximity sensor.
* **[Installing an Arduino Library Guide](https://learn.sparkfun.com/tutorials/installing-an-arduino-library)** - Basic information on how to install an Arduino library.


Version History
---------------
* master - Adapted for use with APDS-9930
* [V_1.4.0](https://github.com/sparkfun/APDS-9960_RGB_and_Gesture_Sensor_Arduino_Library/tree/V_1.4.0) - Updated to new library structure
* V_1.3.0 - Implemented disableProximitySensor(). Thanks to jmg5150 for catching that!
* V_1.2.0 - Added pinMode line to GestureTest demo to fix interrupt bug with some Arduinos
* V_1.1.0 - Updated GestureTest demo to not freeze with fast swipes
* V_1.0.0: Initial release
* Ambient and RGB light sensing implemented
* Ambient light interrupts working
* Proximity sensing implemented
* Proximity interrupts working

License Information
-------------------

This product is _**open source**_! 

Please use, reuse, and modify these files as you see fit. Please maintain attribution to SparkFun Electronics and release anything derivative under the same license.

Distributed as-is; no warranty is given.

- Your friends at SparkFun. And Davide Depau :*
