#include "DisplayTest.h"

void DisplayTest::FillWhite(CameraBase* camera) {
    for (unsigned int i = 0; i < camera->GetPixelGroup()->GetPixelCount(); i++) {
        RGBColor color = RGBColor(255, 255, 255);

        camera->GetPixelGroup()->GetColor(i)->R = color.R;
        camera->GetPixelGroup()->GetColor(i)->G = color.G;
        camera->GetPixelGroup()->GetColor(i)->B = color.B;
    }
}

void DisplayTest::FillAltWhiteBlack(CameraBase* camera) {
    bool alternate = false;
    
    for (unsigned int i = 0; i < camera->GetPixelGroup()->GetPixelCount(); i++) {
        RGBColor color;
        
        if (alternate){
            color = RGBColor(255, 255, 255);
            alternate != alternate;
        }
        else{
            color = RGBColor(0, 0, 0);
            alternate != alternate;
        }

        camera->GetPixelGroup()->GetColor(i)->R = color.R;
        camera->GetPixelGroup()->GetColor(i)->G = color.G;
        camera->GetPixelGroup()->GetColor(i)->B = color.B;
    }
}
