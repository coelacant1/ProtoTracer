#include "Examples/UserConfiguration.h"

// Adding change to main to force action

// Define the project based on a preprocessor macro
#if defined(PROJECT_PROTOGEN_HUB75)
    #include "Examples/Protogen/ProtogenHUB75Project.h"
    ProtogenHUB75Project project;
#elif defined(PROJECT_PROTOGEN_WS35)
    #include "Examples/Protogen/ProtogenWS35Project.h"
    ProtogenWS35Project project;
#elif defined(PROJECT_PROTOGEN_BETA)
    #include "Examples/Protogen/BetaProject.h"
    BetaProject project;
#elif defined(PROJECT_VERIFY_ENGINE)
    #include "Examples/VerifyEngine.h"
    VerifyEngine project;
#elif defined(PROJECT_VERIFY_HARDWARE)
    #include "Examples/Protogen/ProtogenHardwareTest.h"
#else
    #error "No project defined! Please define one of PROJECT_PROTOGEN_HUB75, PROJECT_PROTOGEN_WS35, or PROJECT_VERIFY_ENGINE."
#endif

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
    
    #ifndef PROJECT_VERIFY_HARDWARE
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
    
    #ifndef PROJECT_VERIFY_HARDWARE
    float ratio = (float)(millis() % 5000) / 5000.0f;

    project.Animate(ratio); 
    project.Render();
    project.Display();
    project.PrintStats();
    #endif
}
