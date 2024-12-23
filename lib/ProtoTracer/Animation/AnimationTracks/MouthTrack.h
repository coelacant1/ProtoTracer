/**
 * @file MouthTrack.h
 * @brief Declares the MouthTrack template class for animating mouth movements.
 *
 * This file defines the MouthTrack class, which inherits from AnimationTrack
 * and provides a predefined animation sequence for simulating mouth movements.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

#include "AnimationTrack.h" ///< Include for base AnimationTrack class.

/**
 * @class MouthTrack
 * @brief A template class for animating mouth movements using keyframes.
 *
 * The MouthTrack class inherits from AnimationTrack and provides a specific
 * keyframe animation sequence to simulate the opening and closing of a mouth.
 *
 * @tparam parameters The number of parameters for the mouth movement animation.
 */
template<size_t parameters>
class MouthTrack : public AnimationTrack<parameters, 5> {
private:
    /**
     * @brief Adds predefined keyframes for the mouth movement animation.
     *
     * This function initializes the keyframes to create the mouth movement sequence,
     * including timings for opening and closing.
     */
    void AddKeyFrames() {
        this->track.AddKeyFrame(0.0f, 0.0f);   ///< Mouth closed at time 0.0.
        this->track.AddKeyFrame(1.5f, 1.0f);  ///< Mouth fully open at time 1.5.
        this->track.AddKeyFrame(4.0f, 0.0f);  ///< Mouth closed again at time 4.0.
    }

public:
    /**
     * @brief Default constructor.
     *
     * Constructs a MouthTrack object and initializes the mouth movement animation keyframes.
     */
    MouthTrack() {
        AddKeyFrames();
    }
};