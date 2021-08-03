#include <Arduino.h>
#include "Render\Camera.h"
#include "Math\Rotation.h"

#include "Animation\KeyFrameTrack.h"
#include "Materials\SimpleMaterial.h"
#include "Materials\GradientMaterial.h"
#include "Materials\SimplexNoise.h"
#include "Morph\KaiborgV1.h"
#include "Flash\KaiborgV1Pixels.h"

//TEENSY SPECIFIC FOR WRITING TO LEDS
#include <OctoWS2811.h>

const int ledsPerStrip = 346;
DMAMEM int displayMemory[ledsPerStrip * 6];
int drawingMemory[ledsPerStrip * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);
//END TEENSY SPECIFIC FOR WRITING TO LEDS

const uint8_t MaxBrightness = 20;
Object3D* objects[1];
Scene* scene;

KaiborgV1 kbFace;
KeyFrameTrack kbPOGTrack = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Step);
KeyFrameTrack kbAngryEyesTrack = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Linear);
KeyFrameTrack kbMouthFrownTrack = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);

CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);

Transform camRghtTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));
Transform camLeftTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));

PixelGroup camRghtPixels = PixelGroup(KaiborgV1Pixels, 571, PixelGroup::ZEROTOMAX);
PixelGroup camLeftPixels = PixelGroup(KaiborgV1Pixels, 571, PixelGroup::MAXTOZERO);

Camera camRght = Camera(&camRghtTransform, &cameraLayout, &camRghtPixels);
Camera camLeft = Camera(&camLeftTransform, &cameraLayout, &camLeftPixels);

RGBColor spectrum[4] = {RGBColor(0, 0, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
SimpleMaterial sMat = SimpleMaterial(RGBColor(0, 0, 0));
GradientMaterial gMat = GradientMaterial(6, spectrum, 150.0f, true);
GradientMaterial gNoiseMat = GradientMaterial(4, spectrum, 2.0f, false);
SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);

void updateLEDs(){
    //TEENSY SPECIFIC FOR WRITING TO LEDS/COPYING TO MEMORY
    for (int i = 0; i < 571; i++){
        camLeftPixels.GetPixel(i)->Color = camLeftPixels.GetPixel(i)->Color.Scale(MaxBrightness);
        camRghtPixels.GetPixel(i)->Color = camRghtPixels.GetPixel(i)->Color.Scale(MaxBrightness);

    }

    for (int i = 0; i < 571; i++) {
        if (i < 346){
            leds.setPixel(i + ledsPerStrip * 2, camLeftPixels.GetPixel(i + 225)->Color.R, camLeftPixels.GetPixel(i + 225)->Color.G, camLeftPixels.GetPixel(i + 225)->Color.B);//Pin 7
            leds.setPixel(i + ledsPerStrip * 7, camRghtPixels.GetPixel(i)->Color.R, camRghtPixels.GetPixel(i)->Color.G, camRghtPixels.GetPixel(i)->Color.B);//Pin 8
        }
        else{
            leds.setPixel(i + ledsPerStrip * 3 - 346, camLeftPixels.GetPixel(i - 346)->Color.R, camLeftPixels.GetPixel(i - 346)->Color.G, camLeftPixels.GetPixel(i - 346)->Color.B);//Pin 8
            leds.setPixel(i + ledsPerStrip * 6 - 346, camRghtPixels.GetPixel(i)->Color.R, camRghtPixels.GetPixel(i)->Color.G, camRghtPixels.GetPixel(i)->Color.B);//Pin 8
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

    Serial.println("Linking objects: ");
    objects[0] = kbFace.GetObject();

    kbPOGTrack.AddParameter(kbFace.GetMorphWeightReference(KaiborgV1::POG));
    kbAngryEyesTrack.AddParameter(kbFace.GetMorphWeightReference(KaiborgV1::AngryEyes));
    kbMouthFrownTrack.AddParameter(kbFace.GetMorphWeightReference(KaiborgV1::MouthFrown));

    Serial.println("Setting materials: ");
    objects[0]->SetMaterial(&sNoise);

    Serial.println("Setting keyframes: ");
    kbPOGTrack.AddKeyFrame(0.0f, 0.0f);
    kbPOGTrack.AddKeyFrame(1.0f, 0.1f);
    kbPOGTrack.AddKeyFrame(2.0f, 0.0f);

    kbAngryEyesTrack.AddKeyFrame(0.0f, 0.0f);
    kbAngryEyesTrack.AddKeyFrame(0.5f, 0.25f);
    kbAngryEyesTrack.AddKeyFrame(1.0f, 0.0f);
    kbAngryEyesTrack.AddKeyFrame(1.5f, 0.25f);
    kbAngryEyesTrack.AddKeyFrame(2.0f, 0.0f);

    /*
    kbMouthFrownTrack.AddKeyFrame(0.0f, 1.0f);
    kbMouthFrownTrack.AddKeyFrame(0.2f, 0.0f);
    kbMouthFrownTrack.AddKeyFrame(0.4f, 1.0f);
    kbMouthFrownTrack.AddKeyFrame(0.6f, 0.0f);
    kbMouthFrownTrack.AddKeyFrame(0.8f, 1.0f);
    kbMouthFrownTrack.AddKeyFrame(1.0f, 0.0f);
    kbMouthFrownTrack.AddKeyFrame(2.0f, 0.0f);
    */
    scene = new Scene(objects, 1);
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

        //Objects can be moved to a coordinate or translated by a vector
        objects[0]->GetTransform()->SetPosition(Vector3D(35.0f, 20.0f, 10.0f));

        //Objects can be rotated with by any rotation object (quaternion is preferred) and about any coordinate or center
        objects[0]->GetTransform()->SetRotation(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 1.0f) * 1.0f, 1));

        //Objects can be scaled by origin, center, and at a point
        float s = 1.0f + sin(i * 3.14159f / 180.0f * 3.0f) * 0.03f;
        objects[0]->GetTransform()->SetScale(Vector3D(s, s, s));

        objects[0]->UpdateTransform();

        long prev = micros();//Used to calculate the render time in seconds

        camRght.Rasterize(scene);
        camLeft.Rasterize(scene);

        float dif = ((float)(micros() - prev)) / 1000000.0f;
        Serial.print(dif, 5);
        Serial.println(" seconds.");

        updateLEDs();
    }
}
