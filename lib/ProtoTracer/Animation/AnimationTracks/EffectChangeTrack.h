/**
 * @file EffectChangeTrack.h
 * @brief Declares the EffectChangeTrack template class for animating effect changes.
 *
 * This file defines the EffectChangeTrack class, which inherits from AnimationTrack
 * and provides a predefined animation sequence for transitioning effects.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

#include "AnimationTrack.h" ///< Include for base AnimationTrack class.

/**
 * @class EffectChangeTrack
 * @brief A template class for animating effect transitions using keyframes.
 *
 * The EffectChangeTrack class inherits from AnimationTrack and provides a specific
 * keyframe animation sequence to simulate the transition of effects. This includes
 * changes in intensity over time.
 *
 * @tparam parameters The number of parameters for the effect animation.
 */
template<size_t parameters>
class EffectChangeTrack : public AnimationTrack<parameters, 5> {
private:
    /**
     * @brief Adds predefined keyframes for the effect animation.
     *
     * This function initializes the keyframes to create the effect transition,
     * including the timing for intensity changes.
     */
    void AddKeyFrames() {
        this->track.AddKeyFrame(0.0f, 0.0f); ///< Effect off at time 0.0.
        this->track.AddKeyFrame(0.5f, 1.0f); ///< Effect fully active at time 0.5.
        this->track.AddKeyFrame(1.0f, 0.0f); ///< Effect turns off at time 1.0.
        this->track.AddKeyFrame(1000000.0f, 0.0f); ///< Effect remains off indefinitely after time 1,000,000.0.
    }

public:
    /**
     * @brief Default constructor.
     *
     * Constructs an EffectChangeTrack object and initializes the effect animation keyframes.
     */
    EffectChangeTrack() {
        AddKeyFrames();
    }
};
