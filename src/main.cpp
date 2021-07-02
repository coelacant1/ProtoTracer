#include <Arduino.h>
#include "Render\Camera.h"
#include "Math\Rotation.h"

//MATRIX SPECIFIC FOR CUSTOM PANELS
#include "Flash\CameraObjs.h"
//END MATRIX SPECIFIC FOR CUSTOM PANELS

#include "Flash\KaiborgFaceObjs.h"
#include "Flash\MiscObjs.h"

#include "Materials\SimpleMaterial.h"
#include "Materials\GradientMaterial.h"
#include "Math\SimplexNoise.h"


//TEENSY SPECIFIC FOR WRITING TO LEDS
#include <OctoWS2811.h>

const int ledsPerStrip = 571;
DMAMEM int displayMemory[ledsPerStrip * 6];
int drawingMemory[ledsPerStrip * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);
//END TEENSY SPECIFIC FOR WRITING TO LEDS

Light lights[6];
Object3D* objects[9];
Object3D noseObj1 = Object3D(noseString, 10, 10);
Object3D eyeObj1 = Object3D(eyeString, 10, 10);
Object3D eyeBrowObj1 = Object3D(eyeBrowString, 10, 10);
Object3D mouthObj1 = Object3D(mouthString, 10, 10);
Object3D noseObj2 = Object3D(noseString, 10, 10);
Object3D eyeObj2 = Object3D(eyeString, 10, 10);
Object3D eyeBrowObj2 = Object3D(eyeBrowString, 10, 10);
Object3D mouthObj2 = Object3D(mouthString, 10, 10);
Object3D backgroundObj = Object3D(triangleString, 4, 2);
Scene* scene;
Camera camRght = Camera(Vector3D(0, 0, 0), Vector3D(0, 0, -500), 571, &tertiaryPixelString, false, false, false);
Camera camLeft = Camera(Vector3D(0, 0, 0), Vector3D(0, 0, -500), 571, &tertiaryPixelString, false, false, true);

RGBColor spectrum[3] = {RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};

SimpleMaterial sMat = SimpleMaterial(RGBColor(128, 0, 0));
GradientMaterial gMat = GradientMaterial(6, spectrum, 150.0f, true);
GradientMaterial gNoiseMat = GradientMaterial(3, spectrum, 2.0f, false);
SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);

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
  objects[0] = &noseObj1;
  objects[1] = &eyeObj1;
  objects[2] = &eyeBrowObj1;
  objects[3] = &mouthObj1;
  objects[4] = &noseObj2;
  objects[5] = &eyeObj2;
  objects[6] = &eyeBrowObj2;
  objects[7] = &mouthObj2;
  objects[8] = &backgroundObj;

  Serial.println("Setting materials: ");
  objects[0]->SetMaterial(&sNoise);
  objects[1]->SetMaterial(&sNoise);
  objects[2]->SetMaterial(&sNoise);
  objects[3]->SetMaterial(&sNoise);
  objects[4]->SetMaterial(&gMat);
  objects[5]->SetMaterial(&gMat);
  objects[6]->SetMaterial(&gMat);
  objects[7]->SetMaterial(&gMat);
  objects[8]->SetMaterial(&sNoise);

  scene = new Scene(objects, lights, 9, 6);
  Serial.println("Objects linked, scene created: ");
  delay(50);
}

void loop() {
  for (int i = 0; i < 720; i++) {
    Serial.print("Rendering frame ");
    Serial.print(i);
    Serial.print(" of 720 at ");

    float ratio = ((float)i) / 720.0f;

    float x = sinf(ratio * 3.14159f / 180.0f * 360.0f) * 50.0f;
    float y = cosf(ratio * 3.14159f / 180.0f * 360.0f) * 50.0f;
    
    float linSweep = ratio > 0.5f ? 1.0f - ratio : ratio;
    float zShift = linSweep * 500.0f;
    float sShift = linSweep * 0.0075f + 0.01f;

    sMat.HueShift(ratio * 360 * 4);
    //gMat.HueShift(ratio * 360 * 4);
    //gMat.SetRotationAngle(ratio * 360 * 2);
    gMat.SetGradientPeriod(150.0f + x * 150.0f);
    gMat.SetPositionOffset(Vector2D(x * 2.0f, 100.0f + y * 2.0f));
    //gMat.SetPositionOffset(Vector2D(0.0f, 100.0f));
    
    gNoiseMat.HueShift(ratio * 360 * 2);

    sNoise.SetScale(Vector3D(sShift, sShift, sShift));
    sNoise.SetZPosition(x * 6.0f);

    //Example of Face with slight movement, scaling, and rotation
    //Objects visibility can be enabled and disabled at any point before rasterizing to change its visibility
    objects[0]->Enable();//
    objects[1]->Enable();//
    objects[2]->Disable();
    objects[3]->Enable();//
    objects[4]->Disable();
    objects[5]->Disable();
    objects[6]->Disable();
    objects[7]->Disable();
    objects[8]->Disable();//Background

    //Resets the object back to the original state before any translates/modifications, must be ran once per loop in most cases
    objects[0]->ResetVertices();
    objects[1]->ResetVertices();
    objects[2]->ResetVertices();
    objects[3]->ResetVertices();
    objects[4]->ResetVertices();
    objects[5]->ResetVertices();
    objects[6]->ResetVertices();
    objects[7]->ResetVertices();

    //Objects can be moved to a coordinate or translated by a vector
    objects[0]->MoveRelative(Vector3D(35.0f, 25.0f, 10.0f));
    objects[1]->MoveRelative(Vector3D(25.0f, 25.0f, 30.0f));
    objects[2]->MoveRelative(Vector3D(35.0f, 25.0f, 10.0f));
    objects[3]->MoveRelative(Vector3D(35.0f, 25.0f, 10.0f));
    objects[4]->MoveRelative(Vector3D(0, 0, -10.0f));
    objects[5]->MoveRelative(Vector3D(0, 0, -10.0f));
    objects[6]->MoveRelative(Vector3D(0, 0, -10.0f));
    objects[7]->MoveRelative(Vector3D(0, 0, -10.0f));
    
    //Objects can be rotated with by any rotation object (quaternion is preferred) and about any coordinate or center
    objects[0]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, 1), Vector3D(0, 100, 0));
    objects[1]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, 1), Vector3D(0, 100, 0));
    objects[2]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, 1), Vector3D(0, 100, 0));
    objects[3]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, 1), Vector3D(0, 100, 0));
    objects[4]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, -1), Vector3D(0, 100, 0));
    objects[5]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, -1), Vector3D(0, 100, 0));
    objects[6]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, -1), Vector3D(0, 100, 0));
    objects[7]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, -1), Vector3D(0, 100, 0));

    //Objects can be scaled by origin, center, and at a point
    float s = 1.0f + sin(i * 3.14159f / 180.0f * 3.0f) * 0.03f;
    objects[0]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    objects[1]->Scale(Vector3D(s+0.2f, s+0.2f, s+0.2f), Vector3D(70, 40, 50));
    objects[2]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    objects[3]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    objects[4]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    objects[5]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    objects[6]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
    lights[4].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
    lights[5].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));

    long prev = micros();//Used to calculate the render time in seconds

    camRght.Rasterize(scene, 1.0f, 20);
    camLeft.Rasterize(scene, 1.0f, 20);

    float dif = ((float)(micros() - prev)) / 1000000.0f;
    prev = micros();
    
    //TEENSY SPECIFIC FOR WRITING TO LEDS/COPYING TO MEMORY
    for (int i = 0; i < ledsPerStrip; i++) {
      leds.setPixel(i,                camRght.GetPixels()[i].Color.R, camRght.GetPixels()[i].Color.G, camRght.GetPixels()[i].Color.B);
      leds.setPixel(i + ledsPerStrip, camLeft.GetPixels()[i].Color.R, camLeft.GetPixels()[i].Color.G, camLeft.GetPixels()[i].Color.B);
    }

    leds.show();
    //END TEENSY SPECIFIC FOR WRITING TO LEDS/COPYING TO MEMORY

    Serial.print(dif, 5);
    Serial.print(" wrote in ");
    Serial.print(((float)(micros() - prev)) / 1000000.0f, 5);
    Serial.println(" seconds.");
  }

}
