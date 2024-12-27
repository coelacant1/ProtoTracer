/**
 * @file FunctionGenerator.h
 * @brief Provides a generator for common mathematical wave functions.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h>
#include "../Math/Mathematics.h"

/**
 * @class FunctionGenerator
 * @brief A class to generate various waveform functions with customizable parameters.
 */
class FunctionGenerator {
public:
    /**
     * @enum Function
     * @brief Enumerates the supported wave functions.
     */
    enum Function {
        Triangle,   ///< Triangle waveform.
        Square,     ///< Square waveform.
        Sine,       ///< Sine waveform.
        Sawtooth,   ///< Sawtooth waveform.
        Gravity     ///< Gravity-like function.
    };

private:
    Function function; ///< Current waveform function.
    float minimum = 0.0f; ///< Minimum value of the waveform.
    float maximum = 0.0f; ///< Maximum value of the waveform.
    float period = 0.0f;  ///< Period of the waveform.

    /**
     * @brief Generates a triangle wave value.
     * @param ratio The input ratio (0 to 1).
     * @return The output wave value.
     */
    float TriangleWave(float ratio);

    /**
     * @brief Generates a square wave value.
     * @param ratio The input ratio (0 to 1).
     * @return The output wave value.
     */
    float SquareWave(float ratio);

    /**
     * @brief Generates a sine wave value.
     * @param ratio The input ratio (0 to 1).
     * @return The output wave value.
     */
    float SineWave(float ratio);

    /**
     * @brief Generates a sawtooth wave value.
     * @param ratio The input ratio (0 to 1).
     * @return The output wave value.
     */
    float SawtoothWave(float ratio);

    /**
     * @brief Generates a gravity-like function value.
     * @param ratio The input ratio (0 to 1).
     * @return The output wave value.
     */
    float GravityFunction(float ratio);

public:
    /**
     * @brief Constructor to initialize the FunctionGenerator with parameters.
     * @param function The waveform function to use.
     * @param minimum The minimum value of the waveform.
     * @param maximum The maximum value of the waveform.
     * @param period The period of the waveform.
     */
    FunctionGenerator(Function function, float minimum, float maximum, float period);

    /**
     * @brief Sets the period of the waveform.
     * @param period The new period.
     */
    void SetPeriod(float period);

    /**
     * @brief Sets the waveform function.
     * @param function The new waveform function.
     */
    void SetFunction(Function function);

    /**
     * @brief Updates and calculates the next value of the waveform.
     * @return The calculated wave value.
     */
    float Update();
};
