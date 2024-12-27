\page GettingStarted Getting Started with ProtoTracer

# Basic Setup and Usage

Welcome to the ProtoTracer: Animation Engine! This guide will help you set up your hardware, build the code, and get started with creating and deploying animations.

---

## Overview

This project is a 3D ray-tracing and animation engine designed to run on Teensy 4.0 and Teensy 4.1 boards but can be modified to run on most hardware. It supports a variety of hardware configurations for Protogen-style characters and pixel matrices.

---

## Hardware Requirements

To use this project, you'll need the following hardware:

1. **Microcontroller**: Teensy 4.0 or Teensy 4.1.
2. **Display Matrix**:
   - HUB75 LED Matrix
   - WS2812/WS2811 LED strips or panels
3. **Additional Sensors** (optional, based on features used):
   - Adafruit BNO055 (IMU Sensor)
   - Adafruit APDS9960 (Gesture Sensor)
   - SSD1306 (OLED Display)
4. **Connections**:
   - Power supply sufficient for the number of LEDs you plan to use.
   - USB cable for programming and power delivery.

---

## Software Setup

1. **Install Visual Studio Code**:
   - Download from [https://code.visualstudio.com/](https://code.visualstudio.com/).
   
2. **Install PlatformIO**:
   - In Visual Studio Code, go to the Extensions Marketplace and search for "PlatformIO IDE".
   - Install the PlatformIO IDE extension.

3. **Clone the Repository**:
   - Clone the project repository to your local machine.

4. **Install Required Libraries**:
   - PlatformIO will automatically install the required libraries listed in `platformio.ini`. No manual intervention is needed.

---

## Building and Uploading

Full guide on compiling and uploading ProtoTracer: \subpage CompilingUploading

1. **Open the Project**:
   - Launch Visual Studio Code and open the project folder.

2. **Build the Code**:
   - Click the PlatformIO Build button or use the terminal command:
     ```bash
     pio run -e <environment_name>
     ```

3. **Upload the Code**:
   - Connect your Teensy board via USB.
   - Click the PlatformIO Upload button or use the terminal command:
     ```bash
     pio run -t upload -e <environment_name>
     ```

4. **Serial Monitor**:
   - Use the serial monitor to view debugging information. Open it via PlatformIO or with:
     ```bash
     pio device monitor
     ```


---

## Hardware Setup

1. **Connect Your LEDs**:
   - For HUB75: Connect the panel to the appropriate pins on the Teensy as per the documentation.
   - For WS2812/WS2811: Connect the data line to the designated pins.

2. **Power Supply**:
   - Ensure your LEDs have a sufficient and stable power supply.
   - Use a capacitor across the power supply to protect the LEDs and microcontroller.

3. **Sensor Connections**:
   - Refer to the Adafruit documentation for wiring details on the BNO055, APDS9960, or other sensors.

---

## Running the Code

After uploading the code:

1. **Connect Power**:
   - Provide power to your LED matrix or strips.

2. **Observe Output**:
   - Animations should start immediately on the display.
   - Use the serial monitor to debug or view real-time stats if configured.

---

## Troubleshooting

- **Build Errors**:
  - Ensure PlatformIO is installed and up-to-date.
  - Verify the correct environment is selected in `platformio.ini`.

- **No Output**:
  - Check LED connections and power supply.
  - Ensure the correct LED type is selected in `UserConfiguration.h`.

- **Sensor Issues**:
  - Verify I2C connections for sensors.
  - Check the serial monitor for error messages.

---

For additional support, refer to the official documentation or open an issue in the repository.
