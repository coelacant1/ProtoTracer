/**
 * @file KeyFrameTrack.h
 * @brief Declares the KeyFrameTrack template class for managing keyframe-based animations.
 *
 * This file defines the KeyFrameTrack class, which provides functionality for managing
 * keyframe-based animations, including parameter updates, interpolation, and playback controls.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

#include "KeyFrame.h" ///< Include for keyframe data structure.
#include "../Utils/Math/Mathematics.h" ///< Include for mathematical utilities.

/**
 * @class KeyFrameInterpolation
 * @brief Base class providing interpolation methods for keyframe animations.
 *
 * This class defines the available interpolation methods, which can be used for
 * smooth transitions between keyframes in animations.
 */
class KeyFrameInterpolation {
public:
    /**
     * @enum InterpolationMethod
     * @brief Enumeration of interpolation methods.
     *
     * Provides various methods for transitioning between keyframe values.
     */
    enum InterpolationMethod {
        Linear, ///< Linear interpolation.
        Cosine, ///< Smooth cosine interpolation.
        Step    ///< Step interpolation (discrete transitions).
    };
};

/**
 * @class KeyFrameTrack
 * @brief A template class for managing animations with multiple parameters and keyframes.
 *
 * The KeyFrameTrack class handles animations by managing a set of parameters and their
 * corresponding keyframes. It supports playback controls, interpolation, and time-based updates.
 *
 * @tparam maxParameters The maximum number of parameters this track can handle.
 * @tparam maxKeyFrames The maximum number of keyframes this track can contain.
 */
template<size_t maxParameters, size_t maxKeyFrames>
class KeyFrameTrack : public KeyFrameInterpolation {
private:
    InterpolationMethod interpMethod; ///< The interpolation method for the track.
    float* parameters[maxParameters]; ///< Array of pointers to parameters being animated.
    KeyFrame keyFrames[maxKeyFrames]; ///< Array of keyframes defining the animation.
    float min = 0.0f; ///< Minimum value for the parameters.
    float max = 0.0f; ///< Maximum value for the parameters.
    float startFrameTime = Mathematics::FLTMAX; ///< Start time of the animation (initialized out of bounds).
    float stopFrameTime = Mathematics::FLTMIN; ///< End time of the animation (initialized out of bounds).
    uint8_t currentFrames = 0; ///< Current number of keyframes.
    uint8_t currentParameters = 0; ///< Current number of parameters.
    bool isActive = true; ///< Indicates whether the track is active.
    float parameterValue = 0.0f; ///< Current interpolated parameter value.
    float currentTime = 0.0f; ///< Current time of the animation.
    float timeOffset = 0.0f; ///< Offset for the animation time.

    /**
     * @brief Shifts the keyframe array starting at a specific position.
     *
     * Used for reorganizing keyframes when inserting or removing elements.
     *
     * @param position The index from which to shift the keyframe array.
     */
    void ShiftKeyFrameArray(int position);

public:
    /**
     * @brief Constructs a KeyFrameTrack object with the specified settings.
     *
     * @param min The minimum value for the parameters.
     * @param max The maximum value for the parameters.
     * @param interpMethod The interpolation method for the track.
     */
    KeyFrameTrack(float min, float max, InterpolationMethod interpMethod);

    /**
     * @brief Retrieves the current animation time.
     *
     * @return The current time of the animation.
     */
    float GetCurrentTime();

    /**
     * @brief Sets the current animation time.
     *
     * @param setTime The new current time to set.
     */
    void SetCurrentTime(float setTime);

    /**
     * @brief Pauses the animation.
     */
    void Pause();

    /**
     * @brief Resumes the animation.
     */
    void Play();

    /**
     * @brief Adds a parameter to the track.
     *
     * @param parameter A pointer to the parameter to be animated.
     */
    void AddParameter(float* parameter);

    /**
     * @brief Adds a keyframe to the track.
     *
     * @param time The time of the keyframe.
     * @param value The value of the keyframe.
     */
    void AddKeyFrame(float time, float value);

    /**
     * @brief Retrieves the current interpolated parameter value.
     *
     * @return The current value of the parameter.
     */
    float GetParameterValue();

    /**
     * @brief Resets the animation track to its initial state.
     */
    void Reset();

    /**
     * @brief Updates the animation track and computes the new parameter value.
     *
     * @return The updated parameter value.
     */
    float Update();
};

#include "KeyFrameTrack.tpp" ///< Include the template implementation.
