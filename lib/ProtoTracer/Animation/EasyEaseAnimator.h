/**
 * @file EasyEaseAnimator.h
 * @brief Declares the EasyEaseAnimator template class for advanced animation easing.
 *
 * This file defines the EasyEaseAnimator class, which implements the IEasyEaseAnimator
 * interface and provides functionalities for smooth and customizable animations using
 * various interpolation methods, damped springs, and ramp filters.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

#include "IEasyEaseAnimator.h" ///< Include for base interface class.

/**
 * @class EasyEaseAnimator
 * @brief A template class for implementing advanced animation easing.
 *
 * The EasyEaseAnimator class provides a framework for animating parameters with smooth
 * transitions using a combination of interpolation methods, damped springs, and ramp filters.
 *
 * @tparam maxParameters The maximum number of parameters this animator can handle.
 */
template<size_t maxParameters>
class EasyEaseAnimator : public IEasyEaseAnimator {
private:
    InterpolationMethod interpMethod; ///< The global interpolation method for the animator.
    DampedSpring dampedSpring[maxParameters]; ///< Array of damped springs for smooth animations.
    RampFilter rampFilter[maxParameters]; ///< Array of ramp filters for controlling transitions.
    float* parameters[maxParameters]; ///< Array of pointers to animated parameters.
    float parameterFrame[maxParameters]; ///< Current frame values for each parameter.
    float previousSet[maxParameters]; ///< Previous set values for each parameter.
    float basis[maxParameters]; ///< Basis values for each parameter.
    float goal[maxParameters]; ///< Target values for each parameter.
    uint8_t interpolationMethods[maxParameters]; ///< Interpolation methods for each parameter.
    uint16_t dictionary[maxParameters]; ///< Dictionary mapping for parameter lookup.
    uint16_t currentParameters = 0; ///< Number of currently active parameters.
    bool isActive = true; ///< Indicates whether the animator is active.

public:
    /**
     * @brief Constructs an EasyEaseAnimator object with the specified interpolation method.
     *
     * @param interpMethod The default interpolation method.
     * @param springConstant The default spring constant for damped springs.
     * @param dampingConstant The default damping constant for damped springs.
     */
    EasyEaseAnimator(InterpolationMethod interpMethod, float springConstant = 1.0f, float dampingConstant = 0.5f);

    /**
     * @brief Sets spring and damping constants for a specific parameter.
     *
     * @param dictionaryValue The parameter's dictionary identifier.
     * @param springConstant The spring constant to set.
     * @param damping The damping constant to set.
     */
    void SetConstants(uint16_t dictionaryValue, float springConstant, float damping) override;

    /**
     * @brief Gets the current value of a parameter.
     *
     * @param dictionaryValue The parameter's dictionary identifier.
     * @return The current value of the parameter.
     */
    float GetValue(uint16_t dictionaryValue) override;

    /**
     * @brief Gets the target value of a parameter.
     *
     * @param dictionaryValue The parameter's dictionary identifier.
     * @return The target value of the parameter.
     */
    float GetTarget(uint16_t dictionaryValue) override;

    /**
     * @brief Adds a parameter to the animator.
     *
     * @param parameter A pointer to the parameter to animate.
     * @param dictionaryValue The parameter's dictionary identifier.
     * @param frames The number of frames for the transition.
     * @param basis The initial basis value.
     * @param goal The target goal value.
     */
    void AddParameter(float* parameter, uint16_t dictionaryValue, uint16_t frames, float basis, float goal) override;

    /**
     * @brief Adds a single frame value for a parameter.
     *
     * @param dictionaryValue The parameter's dictionary identifier.
     * @param value The frame value to add.
     */
    void AddParameterFrame(uint16_t dictionaryValue, float value) override;

    /**
     * @brief Sets the interpolation method for a specific parameter.
     *
     * @param dictionaryValue The parameter's dictionary identifier.
     * @param interpMethod The interpolation method to set.
     */
    void SetInterpolationMethod(uint16_t dictionaryValue, InterpolationMethod interpMethod) override;

    /**
     * @brief Resets the animator to its initial state.
     */
    void Reset() override;

    /**
     * @brief Applies the current animation values to the parameters.
     */
    void SetParameters() override;

    /**
     * @brief Updates the animator, advancing all animations.
     */
    void Update() override;
};

#include "EasyEaseAnimator.tpp" ///< Include the template implementation.
