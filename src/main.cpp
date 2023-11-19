//#define HARDWARETEST

//#define PRINTINFO

#include "Examples\Protogen\ProtogenHUB75Project.h"

ProtogenHUB75 project;

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
    
    project.Initialize();
    delay(100);
}

void loop() {
    float ratio = (float)(millis() % 5000) / 5000.0f;

    project.Update(ratio);

    #ifdef PRINTINFO
    Serial.print("Animated in ");
    Serial.print(animation.GetAnimationTime(), 4);

    Serial.print("s, Rendered in ");
    Serial.print(controller.GetRenderTime(), 4);

    
    Serial.print("s, Free memory ");
    Serial.print(FreeMem(),3);

    Serial.println("Kb");
    #endif
}