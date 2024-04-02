#include "Examples\UserConfiguration.h"

#ifdef TESTHARDWARE
#include "Examples\Protogen\ProtogenHardwareTest.h"
#endif

#include "Examples\Commissions\UnicornZhenjaAnimation.h"
//#include "Examples\Protogen\ProtogenHUB75Project.h"
//#include "Examples\Protogen\ProtogenWS35Project.h"
//#include "Examples\VerifyEngine.h"

UnicornZhenjaAnimation project;

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
    
    #ifndef TESTHARDWARE
    project.Initialize();
    delay(100);
    #else
    while(true){
        HardwareTest::ScanDevices();
        HardwareTest::TestNeoTrellis();
        HardwareTest::TestBoopSensor();
        HardwareTest::TestHUD();
    }
    #endif
}

void loop() {
    float ratio = (float)(millis() % 5000) / 5000.0f;

    project.Animate(ratio); 

    project.Render();

    project.Display();

    project.PrintStats();
}