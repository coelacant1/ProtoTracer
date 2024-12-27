/**
 * @file BouncePhysics.h
 * @brief Defines the BouncePhysics class for simulating basic bouncing physics with velocity and gravity.
 *
 * The BouncePhysics class provides functionality to simulate a simple bouncing motion
 * influenced by gravity and velocity damping. It also includes filtering for smoother velocity calculations.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../Utils/Math/Mathematics.h"
#include "../../Utils/Filter/RunningAverageFilter.h"

/**
 * @class BouncePhysics
 * @brief Simulates bouncing physics with gravity and velocity damping.
 */
class BouncePhysics {
private:
    RunningAverageFilter<10> velocityFilter; ///< Filter to smooth out velocity fluctuations.
    float currentVelocity; ///< Current velocity of the object.
    float currentPosition; ///< Current position of the object.
    float velocityRatio; ///< Ratio to control velocity damping.
    float gravity; ///< Gravity constant affecting the motion.
    unsigned long previousMillis; ///< Stores the last timestamp for time-based calculations.
    float previousVelocity; ///< Tracks the velocity from the previous update.

public:
    /**
     * @brief Constructs a BouncePhysics object with the specified gravity and velocity ratio.
     * @param gravity Gravitational acceleration affecting the bounce.
     * @param velocityRatio Damping ratio for the velocity (default is 1.0).
     */
    BouncePhysics(float gravity, float velocityRatio = 1.0f);

    /**
     * @brief Calculates the new position and velocity based on the current velocity and time.
     * @param velocity Initial velocity to calculate the bounce.
     * @param currentMillis Current time in milliseconds.
     * @return Updated position after applying physics.
     */
    float Calculate(float velocity, unsigned long currentMillis);

    /**
     * @brief Calculates the new position and velocity based on the current velocity and time delta.
     * @param velocity Initial velocity to calculate the bounce.
     * @param dT Time delta in seconds.
     * @return Updated position after applying physics.
     */
    float Calculate(float velocity, float dT);
};
