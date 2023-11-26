#define PRINTINFO

#include "Examples\Protogen\ProtogenHUB75Project.h"
//#include "Examples\Protogen\ProtogenWS35Project.h"
//#include "Examples\VerifyEngine.h"

ProtogenHUB75Project project;

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
    
    project.Initialize();
    delay(100);
    
    Serial.println("Hardware initialized...");
    Serial.println("Beginning Render...");
    delay(100);
}

void loop() {
    float ratio = (float)(millis() % 5000) / 5000.0f;

    project.Animate(ratio);

    project.Render();

    project.Display();

    #ifdef PRINTINFO
    Serial.print("FPS: ");
    Serial.print(project.GetFrameRate(), 0);
    Serial.print(", Animated in ");
    Serial.print(project.GetAnimationTime(), 4);

    Serial.print("s, Rendered in ");
    Serial.print(project.GetRenderTime(), 4);

    Serial.print("s, Displayed in ");
    Serial.print(project.GetDisplayTime(), 4);
    Serial.println("s");
    #endif
}