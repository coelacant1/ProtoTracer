#pragma once

#include "Templates/Project.h"
#include "../Assets/Models/OBJ/Background.h"
#include "../Assets/Models/OBJ/DeltaDisplayBackground.h"

#include "../Camera/CameraManager/Implementations/HUB75DeltaCameras.h"
#include "../Controller/HUB75Controller.h"

#include "../Scene/Materials/Animated/RainbowSpiral.h"

class VerifyEngine : public Project{
    HUB75DeltaCameraManager cameras;
    HUB75Controller controller = HUB75Controller(&cameras, 50, 50);

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
    
};
