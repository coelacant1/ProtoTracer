/**
 * @file PhysicsSimulator.h
 * @brief Defines the PhysicsSimulator class for managing physics simulations within a scene.
 *
 * The PhysicsSimulator class integrates boundary motion, object dynamics, and lighting
 * to provide a cohesive simulation environment. It manages a scene with objects, boundary
 * conditions, and physical interactions.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../Renderer/Lights/Light.h"
#include "Utils/BoundaryMotionSimulator.h"
#include "../Scene/Objects/Object3D.h"
#include "../Utils/Math/Quaternion.h"
#include "../Scene/Scene.h"

/**
 * @class PhysicsSimulator
 * @brief Manages physics simulations for objects within a scene.
 */
class PhysicsSimulator {
private:
    BoundaryCube bC; ///< Boundary cube to contain and interact with objects.
    BoundaryMotionSimulator* bMS; ///< Simulator handling boundary object interactions.
    Scene* scene; ///< Scene containing objects and their dynamics.
    Light lights[6]; ///< Array of lights illuminating the scene.
    Object3D* objects[12]; ///< Array of objects in the simulation.
    
    long previousTime; ///< Time of the previous simulation update.
    bool startedSim; ///< Indicates if the simulation has started.

public:
    /**
     * @brief Default constructor initializes the PhysicsSimulator.
     */
    PhysicsSimulator();

    /**
     * @brief Retrieves the scene managed by the simulator.
     * @return Pointer to the Scene object.
     */
    Scene* GetScene();

    /**
     * @brief Updates the simulation with new acceleration and rotation values.
     * @param acceleration The acceleration vector applied to objects.
     * @param rotation The rotation quaternion applied to objects.
     */
    void Update(Vector3D acceleration, Quaternion rotation);
};
