# **ProtoTracer: 3D Rendering and Animation Engine**
This project is a real-time 3D rendering and animation engine designed for use on the Teensy 4.0. It supports 64x32 HUB75 panels, as well as a custom panel design based on WS2812b LEDs.

Before startint this project, it is _highly_ recommended that you have experience with other microcontroller projects first. This is not a simple or easy project to complete, and support can only be provided for issues with the base project, not with your specific setup. If you are looking for a simple, easy solution, please consider:
- Hudu WF-1
  - 🗸 RGB, works with HUB75 panels
  - 🗸 Easy Wi-Fi configuration, quick setup with an app
  - ❌ Not interactive, only shows static images
- MAX7219-based Protogen Designs
  - 🗸 Very cheap, readily available on Amazon / alternatives
  - 🗸 Uses an Arduino Nano as a controller
  - 🗸 Interactive (depending on the controller firmware)
  - 🗸 Uses less power than HUB75-based designs
  - ❌ Single color, pixels can only be on or off.
  - ❌ Lots of soldering required to connect the panels together
  
# FREQUENTLY ASKED QUESTIONS
These are the most commonly asked questions about the project

## Will this project work on a Raspberry Pi?
- No, this project will not run on a Raspberry Pi.
## Will this project work on an ESP32?
- No, this project will not run on an ESP32.
## Will this project work on an Arduino Nano/Uno/Mega?
- No, this project will not run on an Arduino.

## Demonstration:
As a quick way to showcase the capabilities of this software, here is a demo showing a live rendering of a rotating and textured .OBJ file:

![SpyroExample](https://user-images.githubusercontent.com/77935580/130149757-41306da9-5296-42f5-86bc-87f785d9e56b.gif)

## Recommended platform requirements:
- Teensy 4.0 microcontroller
- 2x 64x32 HUB75 panels
- SmartMatrix V4 LED Shield or ProtoController V2 (coming soon)

This codebase has been tested a Teensy 4.0 (2000 triangle scene with a 4,096 pixel matrix).

# Usage:
The following links give a detailed description on how to import files, set up controllers, manipulate objects, and render to displays:
- [Creating a controller](https://github.com/coelacant1/ProtoTracer/wiki/Creating-a-custom-controller)
- [Using an existing controller](https://github.com/coelacant1/ProtoTracer/wiki/Using-an-Existing-Controller)
- [Creating an animation](https://github.com/coelacant1/ProtoTracer/wiki/Creating-an-Animation)
  - [Adding (.OBJ) objects with UV maps](https://github.com/coelacant1/ProtoTracer/wiki/Adding-.OBJ-Objects-with-UV-Maps)
  - [Adding (.FBX) objects with blend shapes](https://github.com/coelacant1/ProtoTracer/wiki/Adding-.FBX-objects-with-Blend-Shapes)
  - [Adding image materials](https://github.com/coelacant1/ProtoTracer/wiki/Adding-Image-Materials)
  - [Adding gif materials](https://github.com/coelacant1/ProtoTracer/wiki/Adding-GIF-Materials)
  - [Creating a shader material](https://github.com/coelacant1/ProtoTracer/wiki/Creating-a-Shader-Material)
  - [Modifying 3D objects](https://github.com/coelacant1/ProtoTracer/wiki/Modifying-3D-Objects)
  - [Keyframing animations](https://github.com/coelacant1/ProtoTracer/wiki/Keyframing-Animations)

# Questions?
Any recommendations on additional information to add can be requested in the discussions tab. If you have additional questions, feel free to ask in my [Discord server](https://discord.gg/YwaWnhJ). Please note that help can only be provided for the base project, and not for problems with your specific setup.

# Contributing:
Pull requests are very welcome. Any issues found should be reported first to open a discussion. Any recommendations can be requested in the discussions tab. For contributing, please follow the following steps:

- Fork the repository on GitHub.
- Commit your changes (git commit -m 'Add some YourFeature').
- Push to the branch (git push origin main).
- Submit a pull request through the GitHub website.

If you would like to help me keep this project going, any support on Patreon would be greatly appreciated: https://www.patreon.com/coelacant1

# License Agreement:
For this project, [AGPL-3.0](https://choosealicense.com/licenses/agpl-3.0/) is used for licensing as a means to make sure any contributions or usage of the software can benefit the community. If you use and modify this software for a product, you must make the modified code readily available as per the license agreement.
