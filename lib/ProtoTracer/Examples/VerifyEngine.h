#pragma once

#include "Templates\Project.h"
#include "..\Assets\Models\OBJ\Background.h"
#include "..\Assets\Models\OBJ\DeltaDisplayBackground.h"

#include "..\Camera\CameraManager\Implementations\HUB75DeltaCameras.h"
#include "..\Controller\SmartMatrixHUB75.h"

#include "..\Scene\Materials\Animated\RainbowSpiral.h"

class VerifyEngine : public Project{
protected:
    uint8_t GetAccentBrightness() override {
        return 50;
    }

    uint8_t GetBrightness() override {
        return 50;
    }

private:
    const uint8_t maxBrightness = 50;
    const uint8_t maxAccentBrightness = 50;

    HUB75DeltaCameraManager cameras;
    SmartMatrixHUB75 controller = SmartMatrixHUB75(&cameras, maxBrightness, maxAccentBrightness);

    Background background;
    DeltaDisplayBackground deltaDisplayBackground;
    
    RainbowSpiral material;

public:
    VerifyEngine() : Project(&cameras, &controller, 2) {
        scene.AddObject(background.GetObject());
        scene.AddObject(deltaDisplayBackground.GetObject());

        background.GetObject()->SetMaterial(&material);
        deltaDisplayBackground.GetObject()->SetMaterial(&material);
    }

    void Initialize() override {
        controller.Initialize();
    }

    void Update(float ratio) override {
        material.Update(ratio);
    }
    
    void FadeIn(float stepRatio) override {}
    
    void FadeOut(float stepRatio) override {}
    
};
