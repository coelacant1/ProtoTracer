#pragma once

#include <TimeLib.h>

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "../Objects/Background.h"
#include "../Render/Scene.h"
#include "../Signals/FunctionGenerator.h"

#include "../Materials/Animated/RainbowNoise.h"
#include "../Materials/Animated/RainbowNoise2.h"
#include "../Materials/Animated/RainbowSpiral.h"
#include "../Materials/CombineMaterial.h"
#include "../Materials/Clock.h"

#include "../Materials/MaterialMask.h"
#include "../Shapes/Circle.h"
#include "../Shapes/Rectangle.h"

#include "../Sensors/APDS9960.h"
#include "../Filter/RunningAverageFilter.h"

time_t getTeensy3Time(){
    return Teensy3Clock.get();
}

class ClockAnimation : public Animation<1> {
private:
    Background background;

    RunningAverageFilter<25> rAF = RunningAverageFilter<25>();
    APDS9960 apds;
    Clock clock = Clock(false);
    float brightness = 255.0f;
    
    //Materials
    RainbowNoise rainbowNoise;
    RainbowNoise2 rainbowNoise2;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial orangeMaterial = SimpleMaterial(RGBColor(255, 165, 0));
    SimpleMaterial whiteMaterial = SimpleMaterial(RGBColor(255, 255, 255));
    SimpleMaterial greenMaterial = SimpleMaterial(RGBColor(0, 255, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    SimpleMaterial yellowMaterial = SimpleMaterial(RGBColor(255, 255, 0));
    SimpleMaterial purpleMaterial = SimpleMaterial(RGBColor(255, 0, 255));
    SimpleMaterial pinkMaterial = SimpleMaterial(RGBColor(227, 11, 92));
    SimpleMaterial blackMaterial = SimpleMaterial(RGBColor(0, 0, 0));

    Rectangle sadRect = Rectangle(Vector2D(48.0f, 48.0f), Vector2D(140.0f, 100.0f), 0.0f);
    
    MaterialMask sadMaterial = MaterialMask(&blackMaterial, &rainbowNoise, &sadRect);
    
    CombineMaterial<4> material;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -20.0f, 20.0f, 16.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 1.0f, 1.1f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -1.0f, 1.0f, 4.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -1.0f, 1.0f, 4.7f);
    FunctionGenerator fGenMatRot = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 1.63f);
    FunctionGenerator fGenMatHue = FunctionGenerator(FunctionGenerator::Triangle, 0.0f, 360.0f, 17.3f);

    
    FunctionGenerator fGenMatFade = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 15.63f);

    void LinkEasyEase(){
        
    }

    void ChangeInterpolationMethods(){
        
    }

    void SetMaterialLayers(){\
        material.AddMaterial(Material::Base, &clock, 1.0f);
        material.AddMaterial(Material::Replace, &rainbowNoise2, 0.0f);
    }

public:
    ClockAnimation() {
        setSyncProvider(getTeensy3Time);
        
        scene.AddObject(background.GetObject());

        LinkEasyEase();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        clock.SetMaterial(&rainbowNoise);

        background.GetObject()->SetMaterial(&material);
    }

    void Initialize() override {
        apds.Initialize(100);
    }

    uint8_t GetAccentBrightness(){
        return 0;
    };

    uint8_t GetBrightness(){
        Serial.println(brightness);

        return uint8_t(brightness);
    };

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return background.GetObject();
    }

    void Update(float ratio) override {
        //float xOffset = fGenMatXMove.Update();
        //float yOffset = fGenMatYMove.Update();
        //float scale = fGenScale.Update();
        //float rotate = fGenMatRot.Update();
        float fade = fGenMatFade.Update();

        uint16_t apdsBright = apds.GetBrightness();

        brightness = rAF.Filter(Mathematics::Map(Mathematics::Constrain(apdsBright, uint16_t(0), uint16_t(25)), uint16_t(0), uint16_t(25), uint16_t(1), uint16_t(255)));

        clock.SetDate(day(), month(), year() - 2000, weekday());
        clock.SetTime(hour(), minute(), second());

        clock.Update();
        clock.SetPosition(Vector2D(-69.75f, 18.75f));
        clock.SetSize(Vector2D(240.0f, 160.0f));
        clock.SetRotation(0);

        material.SetOpacity(1, fade);

        rainbowNoise.Update(ratio);
        rainbowNoise2.Update(ratio);
        rainbowSpiral.Update(ratio);

    }
};
