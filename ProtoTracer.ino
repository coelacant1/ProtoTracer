#include "Camera.h"
#include "Rotation.h"

//MATRIX SPECIFIC FOR CUSTOM PANELS
#include "TemporaryObjCamera.h"
//END MATRIX SPECIFIC FOR CUSTOM PANELS

//TEENSY SPECIFIC FOR WRITING TO LEDS
#include <OctoWS2811.h>

const int ledsPerStrip = 306;
DMAMEM int displayMemory[ledsPerStrip * 6];
int drawingMemory[ledsPerStrip * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);
//END TEENSY SPECIFIC FOR WRITING TO LEDS

Light lights[6];
Object3D* objects[1];
Object3D dvdObj = Object3D(dvd, 100, 100);
Scene* scene;
Camera camFrontTop = Camera(Vector3D(-45, 0, 180), Vector3D(90, -220, -500), 306, &pixelString, true, false);
Camera camRearTop = Camera(Rotation(EulerAngles(Vector3D(45, 0, 0), EulerConstants::EulerOrderXYZR)).GetQuaternion(), Vector3D(90, 90, -500), 306, &pixelString, false, false);
Camera camFrontBottom = Camera(Rotation(EulerAngles(Vector3D(0, 0, 0), EulerConstants::EulerOrderXYZR)).GetQuaternion(), Vector3D(-5, 0, -500), 306, &pixelString, true, false);
Camera camRearBottom = Camera(Rotation(EulerAngles(Vector3D(0, 0, 180), EulerConstants::EulerOrderXYZR)).GetQuaternion(), Vector3D(-20, -131, -500), 306, &pixelString, false, false);

void setup() {
  leds.begin();
  leds.show();

  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting...");

  lights[0].Set(Vector3D(1000, 0, 0), Vector3D(255, 0, 0), 1000.0f, 0.5f, 0.5f);//Set lights position, color intensity, falloff distance, and falloff curvature
  lights[1].Set(Vector3D(0, 1000, 0), Vector3D(0, 255, 0), 1000.0f, 0.5f, 0.5f);
  lights[2].Set(Vector3D(0, 0, 1000), Vector3D(0, 0, 255), 1000.0f, 0.5f, 0.5f);
  lights[3].Set(Vector3D(-1000, 0, 0), Vector3D(120, 0, 120), 1000.0f, 0.5f, 0.5f);
  lights[4].Set(Vector3D(0, -1000, 0), Vector3D(120, 120, 0), 1000.0f, 0.5f, 0.5f);
  lights[5].Set(Vector3D(0, 0, -1000), Vector3D(0, 120, 120), 1000.0f, 0.5f, 0.5f);

  Serial.println("Linking objects: ");
  objects[0] = &dvdObj;

  scene = new Scene(objects, lights, 1, 6);
  Serial.println("Objects linked, scene created: ");
  delay(50);
}

void loop() {
  for (int i = 0; i < 720; i++) {
    Serial.print("Rendering frame ");
    Serial.print(i);
    Serial.print(" of 720 at ");

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

    lights[0].MoveTo(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f, 0, -cosf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f));//Lights can be moved to any vector coordinate
    lights[1].MoveTo(Vector3D(sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
    lights[2].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f, cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));
    lights[3].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f, 0, cosf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f));
    lights[4].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
    lights[5].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));

    long prev = micros();//Used to calculate the render time in seconds

    camFrontTop.Rasterize(scene, 1.0f, 20);
    camRearTop.Rasterize(scene, 1.0f, 20);
    camFrontBottom.Rasterize(scene, 1.0f, 20);
    camRearBottom.Rasterize(scene, 1.0f, 20);

    float dif = ((float)(micros() - prev)) / 1000000.0f;
    prev = micros();
    
    //TEENSY SPECIFIC FOR WRITING TO LEDS/COPYING TO MEMORY
    for (int i = 0; i < 306; i++) {
      leds.setPixel(i,       (byte)camFrontTop.GetPixels()[i].RGB.X, (byte)camFrontTop.GetPixels()[i].RGB.Y, (byte)camFrontTop.GetPixels()[i].RGB.Z);
      leds.setPixel(i + 306,   (byte)camRearTop.GetPixels()[i].RGB.X, (byte)camRearTop.GetPixels()[i].RGB.Y, (byte)camRearTop.GetPixels()[i].RGB.Z);
      leds.setPixel(i + 306 * 2, (byte)camFrontBottom.GetPixels()[i].RGB.X, (byte)camFrontBottom.GetPixels()[i].RGB.Y, (byte)camFrontBottom.GetPixels()[i].RGB.Z);
      leds.setPixel(i + 306 * 3, (byte)camRearBottom.GetPixels()[i].RGB.X, (byte)camRearBottom.GetPixels()[i].RGB.Y, (byte)camRearBottom.GetPixels()[i].RGB.Z);
    }

    leds.show();
    //END TEENSY SPECIFIC FOR WRITING TO LEDS/COPYING TO MEMORY

    Serial.print(dif, 5);
    Serial.print(" ");
    Serial.print(((float)(micros() - prev)) / 1000000.0f, 5);
    Serial.println(" seconds.");
  }

}
