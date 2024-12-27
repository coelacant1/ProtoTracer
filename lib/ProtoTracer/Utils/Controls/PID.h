/**
 * @file PID.h
 * @brief Defines the `PID` class for implementing a proportional-integral-derivative controller.
 *
 * The `PID` class provides functionality to calculate control outputs based on
 * proportional, integral, and derivative components of error.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

/**
 * @class PID
 * @brief Implements a proportional-integral-derivative (PID) controller.
 *
 * This class calculates control outputs based on the error between a setpoint
 * and a process variable, using configurable proportional, integral, and derivative gains.
 */
class PID {
private:
    float integral; ///< Integral term accumulator.
    float error; ///< Current error value.
    float previousError; ///< Previous error value for derivative calculation.
    float output; ///< Calculated output value.
    float kp; ///< Proportional gain.
    float ki; ///< Integral gain.
    float kd; ///< Derivative gain.
    float previousSeconds; ///< Time of the previous calculation in seconds.

public:
    /**
     * @brief Default constructor for `PID`, initializes gains to zero.
     */
    PID();

    /**
     * @brief Constructs a `PID` controller with specified gains.
     *
     * @param kp Proportional gain.
     * @param ki Integral gain.
     * @param kd Derivative gain.
     */
    PID(float kp, float ki, float kd);

    /**
     * @brief Destructor for `PID`.
     */
    ~PID();

    /**
     * @brief Calculates the control output based on the setpoint and process variable.
     *
     * This method uses the elapsed time in milliseconds since the last call to calculate the derivative term.
     *
     * @param setpoint Desired target value.
     * @param processVariable Current value of the process variable.
     * @param currentMillis Current time in milliseconds.
     * @return Calculated control output.
     */
    float Calculate(float setpoint, float processVariable, unsigned long currentMillis);

    /**
     * @brief Calculates the control output based on the setpoint and process variable.
     *
     * This method requires the caller to provide the time delta in seconds since the last calculation.
     *
     * @param setpoint Desired target value.
     * @param processVariable Current value of the process variable.
     * @param dT Time delta in seconds since the last calculation.
     * @return Calculated control output.
     */
    float Calculate(float setpoint, float processVariable, float dT);
};
