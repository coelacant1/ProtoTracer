/**
 * @file Scene.h
 * @brief Defines the `Scene` class for managing objects and effects in a 3D environment.
 *
 * The `Scene` class serves as a container for 3D objects and optional screen-space effects.
 * It provides methods to manage objects and apply visual effects to the entire scene.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Screenspace/Effect.h"
#include "Objects/Object3D.h"

/**
 * @class Scene
 * @brief Manages a collection of 3D objects and applies optional screen-space effects.
 *
 * The `Scene` class allows for the addition, removal, and management of 3D objects.
 * It also supports applying screen-space effects to modify the appearance of the entire scene.
 */
class Scene {
private:
    
    const int maxObjects; ///< Maximum number of objects allowed in the scene.
    Object3D** objects; ///< Array of pointers to the `Object3D` instances in the scene.
    unsigned int numObjects = 0; ///< Current number of objects in the scene.
    Effect* effect; ///< Pointer to the screen-space `Effect` applied to the scene.
    bool doesUseEffect = false; ///< Flag indicating whether the effect is enabled.

    /**
     * @brief Removes an object from the scene by its index.
     *
     * This method adjusts the internal array to maintain order.
     *
     * @param element Index of the object to remove.
     */
    void RemoveElement(unsigned int element);

public:
    /**
     * @brief Constructs a `Scene` instance.
     * 
     * @param maxObjects Maximum number of objects the scene can hold.
     */
    Scene(unsigned int maxObjects);

    /**
     * @brief Destructor for `Scene`, freeing allocated resources.
     */
    ~Scene();

    /**
     * @brief Checks if an effect is enabled for the scene.
     * 
     * @return `true` if an effect is enabled, otherwise `false`.
     */
    bool UseEffect();

    /**
     * @brief Enables the screen-space effect for the scene.
     */
    void EnableEffect();

    /**
     * @brief Disables the screen-space effect for the scene.
     */
    void DisableEffect();

    /**
     * @brief Retrieves the current screen-space effect.
     * 
     * @return Pointer to the current `Effect`, or `nullptr` if no effect is set.
     */
    Effect* GetEffect();

    /**
     * @brief Sets the screen-space effect for the scene.
     * 
     * @param effect Pointer to the `Effect` to apply.
     */
    void SetEffect(Effect* effect);

    /**
     * @brief Adds a 3D object to the scene.
     * 
     * @param object Pointer to the `Object3D` to add.
     */
    void AddObject(Object3D* object);

    /**
     * @brief Removes a 3D object from the scene by its index.
     * 
     * @param i Index of the object to remove.
     */
    void RemoveObject(unsigned int i);

    /**
     * @brief Removes a specific 3D object from the scene.
     * 
     * @param object Pointer to the `Object3D` to remove.
     */
    void RemoveObject(Object3D* object);

    /**
     * @brief Retrieves all objects in the scene.
     * 
     * @return Pointer to the array of `Object3D` pointers.
     */
    Object3D** GetObjects();

    /**
     * @brief Retrieves the current number of objects in the scene.
     * 
     * @return Number of objects in the scene.
     */
    uint8_t GetObjectCount();
};
