/**
 * @file EyeMoveTrack.h
 * @brief Declares the EyeMoveTrack template class for animating eye movements.
 *
 * This file defines the EyeMoveTrack class, which inherits from AnimationTrack
 * and provides a predefined animation sequence for simulating eye movements.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

#include "AnimationTrack.h" // Include for base AnimationTrack class.

/**
 * @class EyeMoveTrack
 * @brief A template class for animating eye movements using keyframes.
 *
 * The EyeMoveTrack class inherits from AnimationTrack and provides a specific
 * keyframe animation sequence to simulate smooth and controlled eye movements.
 *
 * @tparam parameters The number of parameters for the eye movement animation.
 */
template<size_t parameters>
class EyeMoveTrack : public AnimationTrack<parameters, 10> {
private:
    /**
     * @brief Adds predefined keyframes for the eye movement animation.
     *
     * This function initializes the keyframes to create the eye movement sequence,
     * including timings for directional changes and pauses.
     */
    void AddKeyFrames() {
        this->track.AddKeyFrame(0.0f, 0.0f);   ///< Eyes at initial position at time 0.0.
        this->track.AddKeyFrame(2.5f, 1.0f);  ///< Eyes move to position 1.0 at time 2.5.
        this->track.AddKeyFrame(5.0f, 0.0f);  ///< Eyes return to initial position at time 5.0.
        this->track.AddKeyFrame(25.0f, 0.0f); ///< Eyes remain stationary until time 25.0.
    }

public:
    /**
     * @brief Default constructor.
     *
     * Constructs an EyeMoveTrack object and initializes the eye movement animation keyframes.
     */
    EyeMoveTrack() {
        AddKeyFrames();
    }
};
