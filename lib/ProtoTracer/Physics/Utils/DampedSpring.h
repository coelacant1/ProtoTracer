/**
 * @file DampedSpring.h
 * @brief Defines the DampedSpring class for simulating damped spring motion.
 *
 * The DampedSpring class provides a simple physical simulation of a damped spring,
 * modeling its position and velocity over time based on a target position, spring
 * constant, and damping factor.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../Utils/Math/Mathematics.h"

/**
 * @class DampedSpring
 * @brief Simulates the motion of a damped spring.
 */
class DampedSpring {
private:
    float currentVelocity; ///< Current velocity of the spring.
    float currentPosition; ///< Current position of the spring.
    float springConstant; ///< Spring constant determining stiffness.
    float springForce; ///< Force exerted by the spring.
    float dampingForce; ///< Damping force resisting motion.
    float force; ///< Combined force acting on the spring.
    float damping; ///< Damping coefficient.
    unsigned long previousMillis; ///< Previous timestamp for time calculations.

public:
    /**
     * @brief Default constructor initializing a damped spring with default values.
     */
    DampedSpring();

    /**
     * @brief Constructs a DampedSpring with specified spring constant and damping.
     * @param springConstant Spring constant determining stiffness.
     * @param damping Damping coefficient.
     */
    DampedSpring(float springConstant, float damping);

    /**
     * @brief Gets the current position of the spring.
     * @return Current position as a float.
     */
    float GetCurrentPosition();

    /**
     * @brief Sets the spring constant and damping coefficient.
     * @param springConstant New spring constant.
     * @param damping New damping coefficient.
     */
    void SetConstants(float springConstant, float damping);

    /**
     * @brief Calculates the spring's position and velocity using a target position and timestamp.
     * @param target Target position for the spring.
     * @param currentMillis Current time in milliseconds.
     * @return Updated position as a float.
     */
    float Calculate(float target, unsigned long currentMillis);

    /**
     * @brief Calculates the spring's position and velocity using a target position and delta time.
     * @param target Target position for the spring.
     * @param dT Time step in seconds.
     * @return Updated position as a float.
     */
    float Calculate(float target, float dT);
};
