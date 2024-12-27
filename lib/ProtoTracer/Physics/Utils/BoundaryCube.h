/**
 * @file BoundaryCube.h
 * @brief Defines the BoundaryCube class for representing and managing axis-aligned bounding cubes.
 *
 * The BoundaryCube class provides functionality for collision detection and physics calculations
 * for axis-aligned bounding cubes, including interactions with BoundarySphere objects.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../Utils/Math/Rotation.h"
#include "../../Utils/Math/Vector3D.h"
#include "../../Scene/Objects/Object3D.h"
#include "BoundarySphere.h"

/**
 * @class BoundaryCube
 * @brief Represents an axis-aligned bounding cube for collision detection and physics.
 */
class BoundaryCube {
private:
    Quaternion previousRotation; ///< Previous rotation of the object.
    Vector3D centerPosition; ///< Center position of the bounding cube.
    Vector3D maximum; ///< Maximum coordinates of the bounding cube.
    Vector3D minimum; ///< Minimum coordinates of the bounding cube.

public:
    Vector3D velocity = Vector3D(0, 0, 0); ///< Velocity of the cube.
    Vector3D position = Vector3D(0, 0, 0); ///< Current position of the cube.

    /**
     * @brief Constructs a BoundaryCube object based on the given 3D object.
     * @param object Pointer to an Object3D instance to initialize the boundary cube.
     */
    BoundaryCube(Object3D* object);

    /**
     * @brief Constructs a BoundaryCube object with a specified center and size.
     * @param centerPosition Center position of the cube.
     * @param objectSize Size of the cube.
     */
    BoundaryCube(Vector3D centerPosition, Vector3D objectSize);

    /**
     * @brief Retrieves the current position of the cube.
     * @return The current position as a Vector3D.
     */
    Vector3D GetPosition();

    /**
     * @brief Retrieves the size of the cube.
     * @return The size as a Vector3D.
     */
    Vector3D GetSize();

    /**
     * @brief Retrieves the maximum coordinates of the cube.
     * @return The maximum coordinates as a Vector3D.
     */
    Vector3D GetMaximum();

    /**
     * @brief Retrieves the minimum coordinates of the cube.
     * @return The minimum coordinates as a Vector3D.
     */
    Vector3D GetMinimum();

    /**
     * @brief Updates the cube's state based on time, acceleration, and rotation.
     * @param dT Time step in seconds.
     * @param acceleration Acceleration vector applied to the cube.
     * @param rotation Rotation quaternion applied to the cube.
     */
    void Update(float dT, Vector3D acceleration, Quaternion rotation);

    /**
     * @brief Checks for intersection with another BoundaryCube.
     * @param bO Pointer to the other BoundaryCube.
     * @return The intersection vector if intersecting, otherwise zero vector.
     */
    Vector3D IsIntersecting(BoundaryCube* bO);

    /**
     * @brief Checks for intersection with a BoundarySphere.
     * @param bO Pointer to the BoundarySphere.
     * @return The intersection vector if intersecting, otherwise zero vector.
     */
    Vector3D IsIntersecting(BoundarySphere* bO);

    /**
     * @brief Handles collision with a BoundarySphere.
     * @param elasticity Elasticity coefficient for the collision.
     * @param bO Pointer to the BoundarySphere.
     */
    void CollideSphere(float elasticity, BoundarySphere* bO);
};
