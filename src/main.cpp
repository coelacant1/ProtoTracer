#include "Examples\UserConfiguration.h"

#ifdef TESTHARDWARE
#include "Examples\Protogen\ProtogenHardwareTest.h"
#endif

//#include "Examples\Commissions\UnicornZhenjaAnimation.h"
#include "Examples\Protogen\ProtogenHUB75Project.h"
//#include "Examples\Protogen\ProtogenWS35Project.h"
//#include "Examples\VerifyEngine.h"

ProtogenHUB75Project project;

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
    
    project.Initialize();
    delay(100);
}

unsigned long currentMillis = 0;
unsigned long prevMillis = 0;
uint8_t color = 1;

void loop() {

    currentMillis = millis();

    if(currentMillis - prevMillis >= 2000) {
        prevMillis = currentMillis;
        
        if (color >= 10){
            color = 1;
        } else {
            color++;
        }
        Serial.println(color);
    }

    project.SelectColor(color);

    float ratio = (float)(millis() % 5000) / 5000.0f;

    project.Animate(ratio); 

    project.Render();

    project.Display();

    project.PrintStats();
}