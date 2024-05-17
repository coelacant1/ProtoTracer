#include "Examples/UserConfiguration.h"
#include "../lib/ProtoTracer/ExternalDevices/InputDevices/ButtonHandler.h"

#ifdef TESTHARDWARE
#include "Examples/Protogen/ProtogenHardwareTest.h"
#endif

//#include "Examples/Commissions/UnicornZhenjaAnimation.h"
#include "Examples/Protogen/ProtogenHUB75Project.h"
//#include "Examples/VerifyEngine.h"

ProtogenHUB75Project project;

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
    pinMode(14, INPUT_PULLDOWN);
    
    project.Initialize();
    delay(100);
}

unsigned long currentMillis = 0;
unsigned long prevMillis = 0;

void loop() {

    currentMillis = millis();

    if(currentMillis - prevMillis >= 2000) { // timer thingy that does something every 2 seconds
        prevMillis = currentMillis;

    }

    project.CustomFaceColor(RGBColor(0, 255, 150));

    float ratio = (float)(millis() % 5000) / 5000.0f;

    project.Animate(ratio); 

    project.Render();

    project.Display();

    project.PrintStats();
}