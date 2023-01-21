#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Objects\Background.h"
#include "..\Render\Scene.h"
#include "..\Signals\FunctionGenerator.h"

#include "..\Materials\Animated\RainbowNoise2.h"
#include "..\Materials\Animated\RainbowSpiral.h"

#include "..\Materials\MaterialAnimator.h"

#include "..\Materials\Clock.h"

class ESP32Clock : public Animation<1> {
private:
    Background background;
    EasyEaseAnimator<25> eEA = EasyEaseAnimator<25>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);

    Clock clock = Clock(false);
    
    //Materials
    RainbowNoise rainbowNoise;
    RainbowSpiral rainbowSpiral;
    
    MaterialAnimator<10> materialAnimator;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 1.0f, 1.2f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 1.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 1.7f);
    FunctionGenerator fGenMatRot = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 1.63f);
    FunctionGenerator fGenMatHue = FunctionGenerator(FunctionGenerator::Triangle, 0.0f, 360.0f, 17.3f);


    void LinkEasyEase(){
        //eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Anger), NukudeFace::Anger, 15, 0.0f, 1.0f);
    }

    void ChangeInterpolationMethods(){
        //eEA.SetInterpolationMethod(NukudeFace::HideBlush, EasyEaseInterpolation::Cosine);
    }

    void SetMaterialLayers(){
        materialAnimator.SetBaseMaterial(Material::Add, &rainbowNoise);
        materialAnimator.AddMaterial(Material::Lighten, &clock, 40, 0.35f, 1.0f);
    }

    void SetMaterialColor(){
        materialAnimator.AddMaterialFrame(clock, 0.9f);
    }

public:
    ESP32Clock() {
        scene.AddObject(background.GetObject());

        LinkEasyEase();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        background.GetObject()->SetMaterial(&clock);
    }

    uint8_t GetAccentBrightness(){
        return 0;
    };

    uint8_t GetBrightness(){
        return 255;
    };

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return background.GetObject();
    }

    void Update(float ratio) override {
        float xOffset = fGenMatXMove.Update();
        float yOffset = fGenMatYMove.Update();
        float scale = fGenScale.Update();
        float rotate = fGenMatRot.Update();

        clock.Update();
        clock.SetPosition(Vector2D(xOffset - 96.0f, yOffset - 48.0f));
        clock.SetSize(Vector2D(180.0f * scale, 90.0f * scale));
        clock.SetRotation(-90.0f + rotate);

        SetMaterialColor();

        eEA.Update();

        rainbowNoise.Update(ratio);
        //rainbowSpiral.Update(ratio);
        materialAnimator.Update();
    }
};