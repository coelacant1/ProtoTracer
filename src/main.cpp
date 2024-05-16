#include "Examples\UserConfiguration.h"
#include "..\lib\ProtoTracer\ExternalDevices\InputDevices\ButtonHandler.h"

#ifdef TESTHARDWARE
#include "Examples\Protogen\ProtogenHardwareTest.h"
#endif

//#include "Examples\Commissions\UnicornZhenjaAnimation.h"
#include "Examples\Protogen\ProtogenHUB75Project.h"
//#include "Examples\VerifyEngine.h"

ProtogenHUB75Project project;

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
    pinMode(14, INPUT_PULLDOWN);
    
    project.Initialize();
    delay(100);
}

void loop(){

    
    // project.CustomColor(customMaterial);
    // project.SelectColor(9);

    // ButtonHandler::Initialize(14, 100, 100);
     
    project.SelectColor(5); // Set white color

    float ratio = (float)(millis() % 5000) / 5000.0f;

    project.Animate(ratio); 

    project.Render();

    project.Display();

    project.PrintStats();
}