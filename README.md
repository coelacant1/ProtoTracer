# ProtoTracer: Protogen Ray-Tracing and Animation Engine
This project is a 3D ray-tracing and animation engine for pixel matrices, designed to be used for drawing live animations on Protogen style characters from 3D object files (.OBJ).

## Demonstration:
As a quick way to showcase the capabilities of this software, here is a recording of a demo uploaded to YouTube:
[![Protogen Ray-Tracing Engine](https://img.youtube.com/vi/s7G18tx6_nI/0.jpg)](https://www.youtube.com/watch?v=s7G18tx6_nI)

# Usage:
To use the ProtoTracing Engine you must first follow a few requirements:
## Have your pixel list ready:
A pixel list is a list of the XY coordinates (in millimeters, used for all dimensions) of the pixels on a camera. The easiest way to generate a pixel list is to export a Pick and Place file from a PCB design tool. The formatting utilizes a CSV file, each line is a pixel containing the object name, X coordinate, and Y coordinate. Here is an example:
```csv
U1,18,4
U2,25,4
U3,32,4
```
This list will be used to create your camera object for rendering the scene, with your list ready, you can pass the string to be parsed into the camera object to intialize it:
```C++
//Utilizing relative XYZ Euler Angles for camera orientation:
Camera camFrontTop = Camera(Vector3D(-45, 0, 180), Vector3D(90, -220, -500), 306, &pixelString, true, false);

//Utilizing a quaternion object as an input:
Camera camFrontTop = Camera(Rotation(EulerAngles(Vector3D(-45, 0, 180), EulerConstants::EulerOrderXYZR)).GetQuaternion(), Vector3D(90, -220, -500), 306, &pixelString, true, false);
```
Okay, so this may look busy so let's break it down. You must first set the orientation of your camera object which will be drawing the pixel data, this can be done as an Vector3D object representing the Euler Angles in an XYZ inertial frame of reference, as a quaternion object, rotation matrix, axis angle, or direction angle. The position also needs to be set which is the second parameter given as a Vector3D object in millimeters. The string reference to the Pixel list is then passed into the object as well as if you would like to invert the X-axis values or Y-axis values.

## Have your 3D object (.OBJ) files ready:
Object files can be manually created but **must be a triangulated mesh**. Triangles that share vertices should be properly linked within the object file to save on memory space as the memory is shared between triangles. Here is an example of a single right-triangle:
```obj
v -50.000000 -50.000000 0.000000
v -50.000000 50.000000 0.000000
v 50.000000 -50.000000 0.000000
f 3 2 1
```
This .OBJ file will be used to create an Object3D instance.
```C++
Object3D* objects[2];

Object3D dvdObj = Object3D(dvd, 100, 100);
Object3D dvdObj2 = Object3D(dvd, 100, 100);

objects[0] = &dvdObj;
objects[1] = &dvdObj2;
```
The Object3D file is initialized very similar to the camera object, you pass the reference to the String object containing the list of vertices and triangles as well as the maximum number of triangles and maximum number of vertices in the object. Once converted this object can be scaled, moved, rotated, enabled/disabled, and reset.
```C++
//Example of DVD 3d object scaling, moving, and rotating
//Objects visibility can be enabled and disabled at any point before rasterizing to change its visibility
objects[0]->Enable();

//Resets the object back to the original state before any translates/modifications, must be ran once per loop in most cases
objects[0]->ResetVertices();
    
//Objects can be scaled by origin, center, and at a point
objects[0]->Scale(Vector3D(1.3f + sin(i * 3.14159f / 180.0f * 3.0f) * 0.3f, 1.3f + sin(i * 3.14159f / 180.0f * 3.0f) * 0.3f, 1.0f), Vector3D(0, 0, 0));
    
//Objects can be moved to a coordinate or translated by a vector
objects[0]->Move(Vector3D(-100 + sin(i * 3.14159f / 180.0f * 3.0f) * 100.0f, 60 + cos(i * 3.14159f / 180.0f * 1.5f) * 100.0f, 0.0f));
    
//Objects can be rotated with by any rotation object (quaternion is preferred) and about any coordinate or center
objects[0]->Rotate(Vector3D(7 + sinf(i * 3.14159f / 180.0f * 4.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f), Vector3D(0, 100, 0));
```
## Create your light objects:
To create a light object you must specify the lights position, intensity, falloff distance, and falloff curvature:
```C++
Light lights[6];

//Set lights position, color intensity, falloff distance, and falloff curvature
lights[0].Set(Vector3D(1000, 0, 0), Vector3D(255, 0, 0), 1000.0f, 0.5f, 0.5f);

//Lights can be moved to any vector coordinate
lights[0].MoveTo(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f, 0, -cosf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f));
```
Lights can be manipulated similar to an object at any point after creation.

## Creating and linking your scene:
To create a scene, you need to pass the reference to your objects and lights as well as the amount of objects and lights into the constructor:
```C++
  Scene* scene = new Scene(objects, lights, 1, 6);
```

## Rendering the scene:
Now that you have everything to render the objects, you must call the rasterize function within the Camera object. This function warps the triangles in the scene to the cameras perspective allowing the triangles to be forced to a 2D perspective to optimize the intersection verification of each triangle, then calculates the light at each point of the triangle based on the original 3D triangles normal. To rasterize, you must set your pass your scene, set a scaling factor, and set the maximum brightness output at each pixel:
```C++
camFrontTop.Rasterize(scene, 1.0f, 20);
```

## Writing to your LED matrix:
You must implement the firmware for writing to your specific LED matrices. The included example utilizes the [OctoWS2811](https://github.com/PaulStoffregen/OctoWS2811) by Paul Stoffregen for writing to 4 WS2812B LED panels using a Teensy 4.0 or 4.1 microcontroller. To use your own LED code you will need to remove the lines containing the Teensy specific LED code and replace it with your own.

In this example codebase utilizing the OctoWS2811 library, all that must be done to set the LED outputs is as follows:
```C++
//Set the library specific parameters
const int ledsPerStrip = 306;//Set LEDs per board
DMAMEM int displayMemory[ledsPerStrip * 6];//Set up the display memory
int drawingMemory[ledsPerStrip * 6];//Set up the drawing memory
const int config = WS2811_GRB | WS2811_800kHz;//Set the config for color and LED type
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);//Initialize the library constructor

//Read each pixel from the ray-tracing engine and write it to the output LED DMA memory
for (int i = 0; i < 306; i++) {
  leds.setPixel(i,       (byte)camFrontTop.GetPixels()[i].RGB.X, (byte)camFrontTop.GetPixels()[i].RGB.Y, (byte)camFrontTop.GetPixels()[i].RGB.Z);
  leds.setPixel(i + 306,   (byte)camRearTop.GetPixels()[i].RGB.X, (byte)camRearTop.GetPixels()[i].RGB.Y, (byte)camRearTop.GetPixels()[i].RGB.Z);
  leds.setPixel(i + 306 * 2, (byte)camFrontBottom.GetPixels()[i].RGB.X, (byte)camFrontBottom.GetPixels()[i].RGB.Y, (byte)camFrontBottom.GetPixels()[i].RGB.Z);
  leds.setPixel(i + 306 * 3, (byte)camRearBottom.GetPixels()[i].RGB.X, (byte)camRearBottom.GetPixels()[i].RGB.Y, (byte)camRearBottom.GetPixels()[i].RGB.Z);
}

//Update the LED outputs
leds.show();
```
This method is not as efficient as it could be implemented as it could be writing directly to the DMA memory, however, this method allows for easier cross compatibility between platforms.

## Creating animations:
With your set up complete, now animations can be made. With all individual object, light, and camera manipulations described above, they simply need to be implemented within your main loop to change over time. This customization is entirely up to you, but as an example, here is an animation of a DVD logo bouncing around the screen in a figure 8 pattern:
```C++
for (int i = 0; i < 360; i++) {
    //Example of DVD 3D object scaling, moving, and rotating
    //Objects visibility can be enabled and disabled at any point before rasterizing to change its visibility
    objects[0]->Enable();

    //Resets the object back to the original state before any translates/modifications, must be ran once per loop in most cases
    objects[0]->ResetVertices();

    //Objects can be scaled by origin, center, and at a point
    objects[0]->Scale(Vector3D(1.3f + sin(i * 3.14159f / 180.0f * 3.0f) * 0.3f, 1.3f + sin(i * 3.14159f / 180.0f * 3.0f) * 0.3f, 1.0f), Vector3D(0, 0, 0));
    
    //Objects can be moved to a coordinate or translated by a vector
    objects[0]->Move(Vector3D(-100 + sin(i * 3.14159f / 180.0f * 3.0f) * 100.0f, 60 + cos(i * 3.14159f / 180.0f * 1.5f) * 100.0f, 0.0f));
    
    //Objects can be rotated with by any rotation object (quaternion is preferred) and about any coordinate or center
    objects[0]->Rotate(Vector3D(7 + sinf(i * 3.14159f / 180.0f * 4.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f), Vector3D(0, 100, 0));
  }
```
Here is a video example of the DVD logo rendering across multiple LED matrices:
[![ProtoTracer: DVD Logo Test](https://img.youtube.com/vi/yagZnh2IhjQ/0.jpg)](https://www.youtube.com/watch?v=yagZnh2IhjQ)

If you have any questions on usage or implementation, please ask in the discussion or ask me on my Twitter at [Coela Can't!](https://twitter.com/Coelacant1).

# Contributing:
Pull requests are very welcome. Any issues found should be reported first to open a discussion. Any recommendations can be added in the discussions tab and if you have any questions contact [Coela Can't! on Twitter](https://twitter.com/Coelacant1).

# License Agreement:
For this project, [AGPL-3.0](https://choosealicense.com/licenses/agpl-3.0/) is used for licensing as a means to make sure any contributions or usage of the software can benefit the community. If you use and modify this software for a product, you must make the modified code readily available as per the license agreement.
