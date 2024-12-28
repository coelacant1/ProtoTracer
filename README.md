# ProtoTracer: 3D Rendering and Animation Engine

ProtoTracer is a real-time 3D rendering and animation engine designed for microcontrollers. While it has broad applicability, this is a project made for free and it will be down to you to customize support for other hardware other than the examples provided. Support for other microcontrollers may be possible through custom implementations, but users should be prepared to develop their own adaptations if working with platforms other than the Teensy 4/4.1.

ProtoTracer supports:
- **64x32 HUB75 panels**
- **Custom panel designs based on WS2812B LEDs - WS35 Boards**

## Important Note
This project is complex and requires prior experience with microcontroller projects. If you're new to microcontrollers or seeking an easier solution, consider alternatives like:
- **Huidu WF-1**
  - 🗸 RGB, works with HUB75 panels
  - 🗸 Easy Wi-Fi configuration, quick setup with an app
  - ❌ Limited to static images, GIFs, and slideshows
  - ❌ No interactivity with sensors or buttons
- **MAX7219-based Protogen Designs**
  - 🗸 Affordable and widely available
  - 🗸 Compatible with Arduino Nano or similar controllers
  - 🗸 Interactive depending on firmware
  - 🗸 Low power consumption compared to HUB75 designs
  - ❌ Single-color, on/off pixels only
  - ❌ Requires significant soldering

---

# Frequently Asked Questions

## Can this project work on other microcontrollers?
- **Yes, but only the Teensy 4.0 and 4.1 are officially supported.** Users can develop custom implementations for other microcontrollers, but this requires in-depth technical expertise.

## Will this project work on a Raspberry Pi?
- **No**, ProtoTracer is not designed to run on a Raspberry Pi, but could be ported.

## Will this project work on an ESP32?
- **No**, ProtoTracer is not compatible with the ESP32, but could be ported.

## Will this project work on an Arduino Nano/Uno/Mega?
- **No**, ProtoTracer cannot practically run on these platforms due to hardware limitations.

---

# Demonstration

Here’s an example showcasing ProtoTracer's capabilities, demonstrating live rendering of a textured and rotating `.OBJ` file:

![SpyroExample](https://user-images.githubusercontent.com/77935580/130149757-41306da9-5296-42f5-86bc-87f785d9e56b.gif)

---

# Recommended Platform Requirements

- **Microcontroller:** Teensy 4.0 or Teensy 4.1
- **Panels:** Two 64x32 HUB75 panels or WS35 LED boards
- **Shield:** SmartMatrix V4 LED Shield, OctoWS2811 board, or ProtoController V2 (coming soon)

ProtoTracer has been tested on a Teensy 4.0 using a 2,000-triangle scene with a 4,096-pixel matrix.

---

# Usage

To get started with ProtoTracer, refer to the [ProtoTracer Documentation](https://coelacant1.github.io/ProtoTracer). It provides detailed instructions on:
- Importing files
- Setting up controllers
- Manipulating objects
- Rendering to displays

---

# Customization

While ProtoTracer is designed for the Teensy 4 series, advanced users can create custom controllers for other microcontrollers. This requires a deep understanding of the codebase and the target microcontroller's capabilities. Refer to the [documentation](https://coelacant1.github.io/ProtoTracer) for guidance.

---

# Questions and Support

For additional information or recommendations, use the **Discussions** tab on GitHub. For specific questions, join the project's [Discord server](https://discord.gg/YwaWnhJ). Please note:
- There is no dedicated support, this project is provided for free.
- Assistance is not guaranteed for problems specific to your custom setup, assume you are on your own.

---

# Contributing

Contributions are welcome! To contribute:
1. Fork the repository on GitHub.
2. Commit your changes with a descriptive message (git commit -m 'Add YourFeature').
3. Push the branch (git push origin main).
4. Submit a pull request on GitHub.

---

# Sponsoring
If you would like to help me keep this project going, any support on Patreon would be greatly appreciated: https://www.patreon.com/coelacant1

---

# License Agreement

ProtoTracer is licensed under the [AGPL-3.0](https://choosealicense.com/licenses/agpl-3.0/). This ensures modifications and contributions benefit the community. If you use or modify this software for a product, you must make the modified code publicly available as per the license.

