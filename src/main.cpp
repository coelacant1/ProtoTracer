#include <Arduino.h>
#include "Render\Camera.h"
#include "Math\Rotation.h"

//MATRIX SPECIFIC FOR CUSTOM PANELS
#include "Flash\CameraObjs.h"
//END MATRIX SPECIFIC FOR CUSTOM PANELS

#include "Animation\KeyFrameTrack.h"
#include "Flash\MiscObjs.h"
#include "Materials\SimpleMaterial.h"
#include "Materials\GradientMaterial.h"
#include "Math\SimplexNoise.h"
#include "Morph\KaiborgV1.h"

//TEENSY SPECIFIC FOR WRITING TO LEDS
#include <OctoWS2811.h>

const int ledsPerStrip = 346;
DMAMEM int displayMemory[ledsPerStrip * 6];
int drawingMemory[ledsPerStrip * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);
//END TEENSY SPECIFIC FOR WRITING TO LEDS

KaiborgV1 kbFace;
KeyFrameTrack kbPOGTrack = KeyFrameTrack(kbFace.GetMorphWeightReference(KaiborgV1::POG), 0.0f, 1.0f, 10, KeyFrameTrack::Step);
KeyFrameTrack kbAngryEyesTrack = KeyFrameTrack(kbFace.GetMorphWeightReference(KaiborgV1::AngryEyes), 0.0f, 1.0f, 10, KeyFrameTrack::Linear);
KeyFrameTrack kbMouthFrownTrack = KeyFrameTrack(kbFace.GetMorphWeightReference(KaiborgV1::MouthFrown), 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);

Light lights[6];
Object3D* objects[2];
Object3D backgroundObj = Object3D(triangleString, 4, 2);
Scene* scene;
Camera camRght = Camera(Vector3D(0, 0, 0), Vector3D(0, 0, -500), 571, &tertiaryPixelString, false, false, false);
Camera camLeft = Camera(Vector3D(0, 0, 0), Vector3D(0, 0, -500), 571, &tertiaryPixelString, false, false, true);

RGBColor spectrum[4] = {RGBColor(0, 0, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
SimpleMaterial sMat = SimpleMaterial(RGBColor(0, 0, 0));
GradientMaterial gMat = GradientMaterial(6, spectrum, 150.0f, true);
GradientMaterial gNoiseMat = GradientMaterial(4, spectrum, 2.0f, false);
SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);

void updateLEDs(){
    //TEENSY SPECIFIC FOR WRITING TO LEDS/COPYING TO MEMORY
    for (int i = 0; i < 571; i++) {
        if (i < 346){
            leds.setPixel(i + ledsPerStrip * 2, camLeft.GetPixels()[i + 225].Color.R, camLeft.GetPixels()[i + 225].Color.G, camLeft.GetPixels()[i + 225].Color.B);//Pin 7
            leds.setPixel(i + ledsPerStrip * 7, camRght.GetPixels()[i].Color.R, camRght.GetPixels()[i].Color.G, camRght.GetPixels()[i].Color.B);//Pin 8
        }
        else{
            leds.setPixel(i + ledsPerStrip * 3 - 346, camLeft.GetPixels()[i - 346].Color.R, camLeft.GetPixels()[i - 346].Color.G, camLeft.GetPixels()[i - 346].Color.B);//Pin 8
            leds.setPixel(i + ledsPerStrip * 6 - 346, camRght.GetPixels()[i].Color.R, camRght.GetPixels()[i].Color.G, camRght.GetPixels()[i].Color.B);//Pin 8
        }
    }

    leds.show();
}

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
    objects[0] = kbFace.GetObject();
    objects[1] = &backgroundObj;

    Serial.println("Setting materials: ");
    objects[0]->SetMaterial(&sNoise);
    objects[1]->SetMaterial(&sNoise);

    Serial.println("Setting keyframes: ");
    kbPOGTrack.AddKeyFrame(0.0f, 0.0f);
    kbPOGTrack.AddKeyFrame(1.0f, 1.0f);
    kbPOGTrack.AddKeyFrame(2.0f, 0.0f);

    kbAngryEyesTrack.AddKeyFrame(0.0f, 0.0f);
    kbAngryEyesTrack.AddKeyFrame(0.5f, 1.0f);
    kbAngryEyesTrack.AddKeyFrame(1.0f, 0.0f);
    kbAngryEyesTrack.AddKeyFrame(1.5f, 1.0f);
    kbAngryEyesTrack.AddKeyFrame(2.0f, 0.0f);

    kbMouthFrownTrack.AddKeyFrame(0.0f, 1.0f);
    kbMouthFrownTrack.AddKeyFrame(0.2f, 0.0f);
    kbMouthFrownTrack.AddKeyFrame(0.4f, 1.0f);
    kbMouthFrownTrack.AddKeyFrame(0.6f, 0.0f);
    kbMouthFrownTrack.AddKeyFrame(0.8f, 1.0f);
    kbMouthFrownTrack.AddKeyFrame(1.0f, 0.0f);
    kbMouthFrownTrack.AddKeyFrame(2.0f, 0.0f);

    scene = new Scene(objects, lights, 2, 6);
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
        float sShift = linSweep * 0.0075f + 0.01f;

        //Change material parameters
        sMat.HueShift(ratio * 360 * 4);
        gMat.SetGradientPeriod(150.0f + x * 150.0f);
        gMat.SetPositionOffset(Vector2D(x * 2.0f, 100.0f + y * 2.0f));
        gNoiseMat.HueShift(ratio * 360 * 2);
        sNoise.SetScale(Vector3D(sShift, sShift, sShift));
        sNoise.SetZPosition(x * 6.0f);

        //Example of Face with slight movement, scaling, and rotation
        kbPOGTrack.Update();
        kbAngryEyesTrack.Update();
        kbMouthFrownTrack.Update();

        kbFace.Update();

        //Objects visibility can be enabled and disabled at any point before rasterizing to change its visibility
        objects[0]->Enable();//
        objects[1]->Disable();//Background

        //Resets the object back to the original state before any translates/modifications, must be ran once per loop in most cases
        objects[1]->ResetVertices();

        //Objects can be moved to a coordinate or translated by a vector
        objects[0]->MoveRelative(Vector3D(35.0f, 25.0f, 10.0f));

        //Objects can be rotated with by any rotation object (quaternion is preferred) and about any coordinate or center
        objects[0]->Rotate(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, 1), Vector3D(0, 100, 0));

        //Objects can be scaled by origin, center, and at a point
        float s = 1.0f + sin(i * 3.14159f / 180.0f * 3.0f) * 0.03f;
        objects[0]->Scale(Vector3D(s, s, s), Vector3D(70, 40, 50));
        lights[4].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
        lights[5].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));

        long prev = micros();//Used to calculate the render time in seconds

        camRght.Rasterize(scene, 1.0f, 40);
        camLeft.Rasterize(scene, 1.0f, 40);

        float dif = ((float)(micros() - prev)) / 1000000.0f;
        Serial.print(dif, 5);
        Serial.println(" seconds.");

        updateLEDs();
    }
}
