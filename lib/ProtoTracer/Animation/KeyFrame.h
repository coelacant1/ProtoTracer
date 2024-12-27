/**
 * @file KeyFrame.h
 * @brief Declares the KeyFrame class for representing individual animation keyframes.
 *
 * This file defines the KeyFrame class, which encapsulates the properties of a single
 * keyframe in an animation, including its time and value.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

/**
 * @class KeyFrame
 * @brief Represents a single keyframe in an animation.
 *
 * The KeyFrame class stores the time and value for a specific point in an animation.
 * It provides methods for initialization and updating keyframe data.
 */
class KeyFrame {
public:
    float Time = 0.0f; ///< The time of the keyframe.
    float Value = 0.0f; ///< The value of the keyframe.

    /**
     * @brief Default constructor.
     *
     * Constructs a KeyFrame object with default time and value (0.0f).
     */
    KeyFrame();

    /**
     * @brief Parameterized constructor.
     *
     * Constructs a KeyFrame object with specified time and value.
     *
     * @param time The time of the keyframe.
     * @param value The value of the keyframe.
     */
    KeyFrame(float time, float value);

    /**
     * @brief Sets the time and value of the keyframe.
     *
     * Updates the properties of the keyframe to the specified time and value.
     *
     * @param time The new time of the keyframe.
     * @param value The new value of the keyframe.
     */
    void Set(float time, float value);
};
