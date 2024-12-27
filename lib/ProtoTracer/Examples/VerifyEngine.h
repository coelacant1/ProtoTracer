/**
 * @file VerifyEngine.h
 * @brief Implementation of a test project to verify the engine functionality.
 *
 * This file defines the VerifyEngine class, which is used to validate the behavior
 * of the rendering engine, camera management, and controller in a test environment.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "Templates/Project.h" // Base project template.
#include "../Assets/Models/OBJ/Background.h" // Background model.
#include "../Assets/Models/OBJ/DeltaDisplayBackground.h" // Delta display background model.

#include "../Camera/CameraManager/Implementations/HUB75DeltaCameras.h" // Camera manager for HUB75 Delta displays.
#include "../Controller/HUB75Controller.h" // Controller for HUB75 displays.

#include "../Scene/Materials/Animated/RainbowSpiral.h" // Animated material for rendering.

/**
 * @class VerifyEngine
 * @brief A project class to validate the rendering engine functionality.
 *
 * The VerifyEngine class is a test project that integrates a background model,
 * a Delta display background model, and an animated material for verifying the
 * engine's rendering and update capabilities.
 */
class VerifyEngine : public Project {
private:
    HUB75DeltaCameraManager cameras; ///< Camera manager for HUB75 Delta displays.
    HUB75Controller controller = HUB75Controller(&cameras, 50, 50); ///< Controller for managing HUB75 displays.

    Background background; ///< Background object for the scene.
    DeltaDisplayBackground deltaDisplayBackground; ///< Delta display background object for the scene.

    RainbowSpiral material; ///< Animated material applied to objects.

public:
    /**
     * @brief Constructs the VerifyEngine project.
     *
     * Initializes the camera manager, controller, scene objects, and applies the animated material.
     */
    VerifyEngine() : Project(&cameras, &controller, 2) {
        scene.AddObject(background.GetObject());
        scene.AddObject(deltaDisplayBackground.GetObject());

        background.GetObject()->SetMaterial(&material);
        deltaDisplayBackground.GetObject()->SetMaterial(&material);
    }

    /**
     * @brief Initializes the controller for the project.
     */
    void Initialize() override {
        controller.Initialize();
    }

    /**
     * @brief Updates the project state.
     *
     * @param ratio The time ratio for updates.
     */
    void Update(float ratio) override {
        material.Update(ratio);
    }
};
