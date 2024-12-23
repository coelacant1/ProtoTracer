/**
 * @file BoundarySphere.h
 * @brief Defines the BoundarySphere class for simulating spherical boundary objects.
 *
 * The BoundarySphere class provides functionality to represent a 3D sphere's position, velocity,
 * and radius, along with methods to handle motion, detect intersections, and resolve collisions.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../Utils/Math/Rotation.h"
#include "../../Utils/Math/Vector3D.h"
#include "../../Scene/Objects/Object3D.h"

/**
 * @class BoundarySphere
 * @brief Represents a spherical boundary object for motion and collision simulations.
 */
class BoundarySphere {
private:
    Object3D* object; ///< Pointer to the 3D object associated with the sphere.
    Vector3D centerPosition; ///< Center position of the sphere.
    Quaternion previousRotation; ///< Previous rotation of the sphere.
    float radius = 1.0f; ///< Radius of the sphere.

public:
    Vector3D velocity = Vector3D(0, 0, 0); ///< Velocity vector of the sphere.
    Vector3D position = Vector3D(0, 0, 0); ///< Current position of the sphere.

    /**
     * @brief Constructs a BoundarySphere with a given object and radius.
     * @param object Pointer to the Object3D associated with the sphere.
     * @param radius Radius of the sphere.
     */
    BoundarySphere(Object3D* object, float radius);

    /**
     * @brief Constructs a BoundarySphere with a given object, position, and radius.
     * @param object Pointer to the Object3D associated with the sphere.
     * @param position Initial position of the sphere.
     * @param radius Radius of the sphere.
     */
    BoundarySphere(Object3D* object, Vector3D position, float radius);

    /**
     * @brief Gets the radius of the sphere.
     * @return Radius of the sphere.
     */
    float GetRadius();

    /**
     * @brief Gets the associated Object3D of the sphere.
     * @return Pointer to the Object3D.
     */
    Object3D* GetObject3D();

    /**
     * @brief Updates the sphere's position and velocity based on acceleration and rotation.
     * @param dT Time step in seconds.
     * @param acceleration Acceleration vector applied to the sphere.
     * @param rotation Rotation quaternion applied to the sphere.
     */
    void Update(float dT, Vector3D acceleration, Quaternion rotation);

    /**
     * @brief Checks if the sphere intersects with another BoundarySphere.
     * @param bO Pointer to the other BoundarySphere.
     * @return True if the spheres intersect, false otherwise.
     */
    bool IsIntersecting(BoundarySphere* bO);

    /**
     * @brief Resolves collision between this sphere and another BoundarySphere.
     * @param elasticity Elasticity coefficient for the collision.
     * @param bO Pointer to the other BoundarySphere.
     */
    void Collide(float elasticity, BoundarySphere* bO);
};
