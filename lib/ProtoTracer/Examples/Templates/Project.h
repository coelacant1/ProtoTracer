/**
 * @file Project.h
 * @brief Declares the Project class for managing animations, rendering, and display operations.
 *
 * This file defines the Project class, which integrates camera management, scene rendering,
 * and display updates while maintaining performance statistics.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h> ///< Include for Arduino compatibility.
#include "../../Engine/Engine.h" ///< Include for rendering engine.
#include "../../Scene/Scene.h" ///< Include for scene management.
#include "../../Camera/CameraManager/CameraManager.h" ///< Include for camera management.
#include "../../Controller/Controller.h" ///< Include for controller operations.
#include "../../Utils/Filter/RunningAverageFilter.h" ///< Include for filtering utilities.
#include "Utils/Debug.h" ///< Include for debugging utilities.
#include "../UserConfiguration.h" ///< Include for user-specific configuration.

/**
 * @class Project
 * @brief Manages animations, rendering, and display operations.
 *
 * The Project class integrates various subsystems including camera management, scene rendering,
 * and display updates. It also tracks and reports performance metrics such as frame rate and
 * individual operation times.
 */
class Project {
protected:
    CameraManager* cameras; ///< Pointer to the CameraManager for managing cameras.
    Controller* controller; ///< Pointer to the Controller for controlling the display.
    Scene scene; ///< The Scene object representing the rendered environment.

    RunningAverageFilter<50> avgFPS = RunningAverageFilter<50>(0.05f); ///< Running average filter for frame rate calculation.

    long previousAnimationTime = 0; ///< Time of the previous animation frame in microseconds.
    long previousRenderTime = 0; ///< Time of the previous render frame in microseconds.
    long previousDisplayTime = 0; ///< Time of the previous display frame in microseconds.
    float fade = 0.0f; ///< Fade parameter for animations.
    float animationTime = 0.0f; ///< Time spent on animation in milliseconds.
    float renderTime = 0.0f; ///< Time spent on rendering in milliseconds.
    float displayTime = 0.0f; ///< Time spent on display in milliseconds.

    /**
     * @brief Updates the project state based on the given ratio.
     *
     * This method is intended to be overridden by derived classes to define
     * specific update logic for animations or state transitions.
     *
     * @param ratio A float representing the interpolation ratio for updates.
     */
    virtual void Update(float ratio) = 0;

    /**
     * @brief Starts the render timer for measuring render performance.
     */
    void RenderStartTimer();

    /**
     * @brief Stops the render timer and records the elapsed time.
     */
    void RenderEndTimer();

public:
    /**
     * @brief Constructs a Project with specified camera manager and controller.
     *
     * @param cameras Pointer to the CameraManager managing the cameras.
     * @param controller Pointer to the Controller managing the display.
     * @param numObjects Number of objects to initialize in the scene.
     */
    Project(CameraManager* cameras, Controller* controller, uint8_t numObjects);

    /**
     * @brief Retrieves the time spent on animations.
     *
     * @return The animation time in milliseconds.
     */
    float GetAnimationTime();

    /**
     * @brief Retrieves the time spent on rendering.
     *
     * @return The render time in milliseconds.
     */
    float GetRenderTime();

    /**
     * @brief Retrieves the time spent on display operations.
     *
     * @return The display time in milliseconds.
     */
    float GetDisplayTime();

    /**
     * @brief Retrieves the current frame rate.
     *
     * @return The frame rate in frames per second (FPS).
     */
    float GetFrameRate();

    /**
     * @brief Initializes the project.
     *
     * This method is intended to be overridden by derived classes to define
     * specific initialization logic for the project.
     */
    virtual void Initialize() = 0;

    /**
     * @brief Animates the project state based on the given ratio.
     *
     * @param ratio A float representing the interpolation ratio for animations.
     */
    void Animate(float ratio);

    /**
     * @brief Renders the scene.
     */
    void Render();

    /**
     * @brief Updates the display with the rendered content.
     */
    void Display();

    /**
     * @brief Prints performance statistics such as frame rate and operation times.
     */
    void PrintStats();
};
