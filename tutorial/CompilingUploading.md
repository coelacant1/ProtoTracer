# Compiling and Uploading {#CompilingUploading}

## Compiling and Uploading ProtoTracer

This guide will walk you through the process of compiling and uploading the code for the Protogen animation engine using PlatformIO. PlatformIO is a versatile toolchain for embedded development, fully integrated into Visual Studio Code.

## Prerequisites

1. **Install Visual Studio Code**:
   Download and install Visual Studio Code from [https://code.visualstudio.com/](https://code.visualstudio.com/).

2. **Install PlatformIO**:
   Open Visual Studio Code and install the PlatformIO IDE extension from the Extensions Marketplace.

3. **Clone the Repository**:
   Clone the project repository to your local machine.

### Supported Environments

The project supports multiple Teensy 4.0 and Teensy 4.1 configurations:

- **Teensy 4.0**:
  - `teensy40hub75`
  - `teensy40ws35`
  - `teensy40beta`
  - `teensy40verifyrender`
  - `teensy40verifyhardware`

- **Teensy 4.1**:
  - `teensy41hub75`
  - `teensy41ws35`
  - `teensy41beta`
  - `teensy41verifyrender`
  - `teensy41verifyhardware`

## Compile and Upload Instructions

1. **Open the Project in PlatformIO**:
   - Launch Visual Studio Code.
   - Use the PlatformIO Home tab or navigate to `File > Open Workspace` and open the workspace file in the root directory of the project.

2. **Select the Environment**:
   - In the `platformio.ini` file, each environment corresponds to a specific Teensy and Protogen configuration.
   - To select an environment, click on the Platform IO logo on the left of the VS Code window or run the following command in the terminal:

     ```bash
     pio run -e <environment_name>
     ```

     Replace `<environment_name>` with one of the available environments (e.g., `teensy40hub75`).

3. **Modify `UserConfiguration.h` (if necessary)**:
   - Located in the `Examples` directory, this file allows you to customize various settings, such as enabling or disabling features.


4. **Build the Project**:
   - Click the PlatformIO Build button in the left of the VS Code window.
   - Alternatively, use the terminal command:

     ```bash
     pio run
     ```

5. **Upload the Code**:
   - Ensure your Teensy board is connected via USB.
   - Click the PlatformIO Upload button in the left of the VS Code window.
   - Alternatively, use the terminal command:

     ```bash
     pio run -t upload -e <environment_name>
     ```

6. **Monitor Serial Output** (Optional):
   - To open the serial monitor, click on the Serial Monitor button in PlatformIO or use the terminal command:

     ```bash
     pio device monitor
     ```

## Library Dependencies

The following libraries are automatically managed by PlatformIO and specified in the `lib_deps` section of `platformio.ini`:

- ProtoTracer
- SPI
- Wire
- EEPROM
- Adafruit Unified Sensor
- OctoWS2811
- Adafruit BNO055
- SerialTransfer
- Adafruit APDS9960 Library
- SmartMatrix
- Adafruit BusIO
- Teensy_ADC
- Adafruit SSD1306
- Adafruit seesaw Library
- Adafruit MMC56x3

## Troubleshooting

- **Missing Dependencies**:
  If a library is not found, PlatformIO will attempt to download it automatically. Ensure you are connected to the internet during the first build.

- **Upload Errors**:
  Verify that the correct Teensy board is selected and that it is properly connected to your system.

- **Serial Monitor Issues**:
  Ensure the correct COM port is selected in the PlatformIO settings.

## Additional Notes

- By default, the output directory is structured under `.pio/`.
- To add custom functionality, modify the configuration in `platformio.ini` and the project files as needed.

For further assistance, refer to the [PlatformIO Documentation](https://docs.platformio.org/) or the Teensy [PJRC Documentation](https://www.pjrc.com/teensy/).
