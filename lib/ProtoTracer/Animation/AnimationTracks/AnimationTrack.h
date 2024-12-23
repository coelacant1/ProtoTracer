/**
 * @file AnimationTrack.h
 * @brief Declares the AnimationTrack template class for managing animation tracks with keyframes.
 *
 * This file contains the definition of the AnimationTrack template class, designed
 * to handle animations with a fixed number of parameters and keyframes.
 * The class integrates functionality for adding parameters, playing, pausing,
 * and updating animation tracks.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

#include "../KeyFrameTrack.h" ///< Include for KeyFrameTrack dependency.

/**
 * @class AnimationTrack
 * @brief A template class for managing animation tracks with keyframes.
 *
 * This class handles the management of animation parameters and their associated
 * keyframes, supporting playback controls, parameter updates, and interpolation.
 *
 * @tparam maxParameters The maximum number of parameters this animation track can handle.
 * @tparam maxKeyFrames The maximum number of keyframes this animation track can contain.
 */
template<size_t maxParameters, size_t maxKeyFrames>
class AnimationTrack {
protected:
    /**
     * @brief Internal track object for keyframe management.
     *
     * This KeyFrameTrack instance handles the underlying keyframe operations
     * for the AnimationTrack class.
     */
    KeyFrameTrack<maxParameters, maxKeyFrames> track;

private:
    /**
     * @brief Pure virtual function to add keyframes to the track.
     *
     * This function must be implemented by derived classes to define
     * how keyframes are added to the animation track.
     */
    virtual void AddKeyFrames() = 0;

public:
    /**
     * @brief Default constructor.
     *
     * Constructs an AnimationTrack object with default settings.
     */
    AnimationTrack();

    /**
     * @brief Parameterized constructor.
     *
     * Initializes an AnimationTrack object with the given range and interpolation method.
     *
     * @param min The minimum value of the parameter range.
     * @param max The maximum value of the parameter range.
     * @param interpMethod The interpolation method to be used for the track.
     */
    AnimationTrack(float min, float max, KeyFrameInterpolation::InterpolationMethod interpMethod);

    /**
     * @brief Starts or resumes playback of the animation track.
     */
    void Play();

    /**
     * @brief Pauses playback of the animation track.
     */
    void Pause();

    /**
     * @brief Restarts the animation track's time to the beginning.
     */
    void RestartTime();

    /**
     * @brief Prints the current time of the animation track.
     *
     * This function outputs the current time of the track for debugging purposes.
     */
    void PrintTime();

    /**
     * @brief Resets the animation track to its initial state.
     */
    void Reset();

    /**
     * @brief Retrieves the current parameter value of the animation track.
     *
     * @return The current value of the parameter being animated.
     */
    float GetParameterValue();

    /**
     * @brief Updates the animation track and returns the current parameter value.
     *
     * This function advances the animation track based on the elapsed time
     * and computes the interpolated parameter value.
     *
     * @return The updated parameter value.
     */
    float Update();

    /**
     * @brief Adds a parameter to the animation track.
     *
     * @param parameter A pointer to the parameter to be animated.
     */
    void AddParameter(float* parameter);
};

#include "AnimationTrack.tpp" ///< Include the template implementation.
