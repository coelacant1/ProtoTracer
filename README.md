# **ProtoTracer: 3D Rendering and Animation Engine**
This project is a live 3D rendering and animation engine designed for use on microcontrollers.

## Demonstration:
As a quick way to showcase the capabilities of this software, here is a demo showing a live rendering of a rotating and textured .OBJ file:

![SpyroExample](https://user-images.githubusercontent.com/77935580/130149757-41306da9-5296-42f5-86bc-87f785d9e56b.gif)

## Recommended platform requirements:
* 32-bit FPU
* 200MHz+ processor
* At least 80KB dynamic memory

This codebase has been tested on an Arduino Mega (smaller .OBJ file with a 89 pixel matrix) and on a Teensy 4.0 (2000 triangle scene with a 2,804 pixel matrix).

# Usage:
The following links give a detailed description on how to import files, set up controllers, manipulate objects, and render to displays:
- [Hardware Requirements and Use Cases](Hardware-Requirements-and-Use-Cases)
- [Creating a controller](Creating-a-custom-controller)
  - [Creating and importing the pixel map](Creating-and-Importing-the-Pixel-Map)
  - [Rendering the camera](Rendering-the-Camera)
  - [Writing to the display](Writing-to-the-Display)
- [Using an existing controller](Using-an-Existing-Controller)
  - [Kaiborg V1 controller](Kaiborg-V1-controller)
  - [Kaiborg V1.1 controller](Kaiborg-V1.1-Controller)
  - [ProtoDR controller](ProtoDR-Controller)
- [Creating an animation](Creating-an-Animation)
  - [Adding (.OBJ) objects with UV maps](Adding-.OBJ-Objects-with-UV-Maps)
  - [Adding (.FBX) objects with blend shapes](Adding-.FBX-objects-with-Blend-Shapes)
  - [Adding image materials](Adding-Image-Materials)
  - [Adding gif materials](Adding-GIF-Materials)
  - [Creating a shader material](Creating-a-Shader-Material)
  - [Modifying 3D objects](Modifying-3D-Objects)
  - [Keyframing animations](Keyframing-Animations)

# Questions?
Any recommendations on additional information to add can be requested in the discussions tab. If you have additional questions, you can @ me in my [Discord server](https://discord.gg/YwaWnhJ) or on direct message me on [Twitter](https://twitter.com/Coelacant1).

# Contributing:
Pull requests are very welcome. Any issues found should be reported first to open a discussion. Any recommendations can be requested in the discussions tab.

# License Agreement:
For this project, [AGPL-3.0](https://choosealicense.com/licenses/agpl-3.0/) is used for licensing as a means to make sure any contributions or usage of the software can benefit the community. If you use and modify this software for a product, you must make the modified code readily available as per the license agreement.
