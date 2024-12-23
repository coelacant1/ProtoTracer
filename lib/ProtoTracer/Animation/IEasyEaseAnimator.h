/**
 * @file IEasyEaseAnimator.h
 * @brief Declares the IEasyEaseAnimator interface for defining animation behaviors.
 *
 * This file defines the IEasyEaseAnimator interface, which provides the foundational
 * methods for managing animations with various interpolation methods and parameter updates.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

#include "KeyFrame.h" ///< Include for keyframe management.
#include "../Utils/Math/Mathematics.h" ///< Include for mathematical utilities.
#include "../Physics/Utils/DampedSpring.h" ///< Include for damped spring physics.
#include "../Utils/Filter/RampFilter.h" ///< Include for ramp filtering utilities.

/**
 * @class IEasyEaseAnimator
 * @brief Interface for defining animation behaviors with easing and interpolation.
 *
 * The IEasyEaseAnimator interface provides methods for managing animated parameters,
 * supporting interpolation methods, damped spring constants, and parameter transitions.
 */
class IEasyEaseAnimator {
public:
    /**
     * @enum InterpolationMethod
     * @brief Enumeration of interpolation methods for animations.
     *
     * Provides various interpolation techniques for smooth and dynamic transitions.
     */
    enum InterpolationMethod {
        Cosine,    ///< Smooth cosine interpolation.
        Bounce,    ///< Bouncy effect during interpolation.
        Linear,    ///< Straight linear interpolation.
        Overshoot  ///< Interpolation with overshooting behavior.
    };

    /**
     * @brief Sets the spring and damping constants for a parameter.
     *
     * @param dictionaryValue The parameter's dictionary identifier.
     * @param springConstant The spring constant to set.
     * @param damping The damping constant to set.
     */
    virtual void SetConstants(uint16_t dictionaryValue, float springConstant, float damping) = 0;

    /**
     * @brief Retrieves the current value of a parameter.
     *
     * @param dictionaryValue The parameter's dictionary identifier.
     * @return The current value of the parameter.
     */
    virtual float GetValue(uint16_t dictionaryValue) = 0;

    /**
     * @brief Retrieves the target value of a parameter.
     *
     * @param dictionaryValue The parameter's dictionary identifier.
     * @return The target value of the parameter.
     */
    virtual float GetTarget(uint16_t dictionaryValue) = 0;

    /**
     * @brief Adds a new parameter to the animator.
     *
     * @param parameter A pointer to the parameter to animate.
     * @param dictionaryValue The parameter's dictionary identifier.
     * @param frames The number of frames for the transition.
     * @param basis The initial basis value.
     * @param goal The target goal value.
     */
    virtual void AddParameter(float* parameter, uint16_t dictionaryValue, uint16_t frames, float basis, float goal) = 0;

    /**
     * @brief Adds a single frame value to a parameter.
     *
     * @param dictionaryValue The parameter's dictionary identifier.
     * @param value The frame value to add.
     */
    virtual void AddParameterFrame(uint16_t dictionaryValue, float value) = 0;

    /**
     * @brief Sets the interpolation method for a parameter.
     *
     * @param dictionaryValue The parameter's dictionary identifier.
     * @param interpMethod The interpolation method to set.
     */
    virtual void SetInterpolationMethod(uint16_t dictionaryValue, InterpolationMethod interpMethod) = 0;

    /**
     * @brief Resets the animator to its initial state.
     */
    virtual void Reset() = 0;

    /**
     * @brief Applies the current animation values to the parameters.
     */
    virtual void SetParameters() = 0;

    /**
     * @brief Updates the animator, advancing all animations.
     */
    virtual void Update() = 0;
};
