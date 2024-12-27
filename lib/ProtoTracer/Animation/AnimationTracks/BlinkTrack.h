/**
 * @file BlinkTrack.h
 * @brief Declares the BlinkTrack template class for animating eye blinking.
 *
 * This file defines the BlinkTrack class, which inherits from AnimationTrack
 * and provides a predefined animation sequence for blinking eyes.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

#include "AnimationTrack.h" // Include for base AnimationTrack class.

/**
 * @class BlinkTrack
 * @brief A template class for animating eye blinking using keyframes.
 *
 * The BlinkTrack class inherits from AnimationTrack and provides a specific
 * keyframe animation sequence to simulate eye blinking. The animation defines
 * keyframes for opening and closing the eyes at precise time intervals.
 *
 * @tparam parameters The number of parameters for the blink animation.
 */
template<size_t parameters>
class BlinkTrack : public AnimationTrack<parameters, 10> {
private:
    /**
     * @brief Adds predefined keyframes for the blink animation.
     *
     * This function initializes the keyframes to create the blinking effect,
     * including the timing for opening and closing the eyes.
     */
    void AddKeyFrames() {
        this->track.AddKeyFrame(0.0f, 0.0f);   ///< Eyes fully open at time 0.0.
        this->track.AddKeyFrame(2.75f, 0.0f); ///< Eyes remain open until time 2.75.
        this->track.AddKeyFrame(3.0f, 1.0f);  ///< Eyes start to close at time 3.0.
        this->track.AddKeyFrame(3.25f, 0.0f); ///< Eyes fully open again at time 3.25.
        this->track.AddKeyFrame(9.75f, 0.0f); ///< Eyes remain open until time 9.75.
        this->track.AddKeyFrame(10.0f, 1.0f); ///< Eyes start to close at time 10.0.
        this->track.AddKeyFrame(10.25f, 0.0f); ///< Eyes fully open again at time 10.25.
        this->track.AddKeyFrame(10.75f, 0.0f); ///< Eyes remain open until time 10.75.
        this->track.AddKeyFrame(11.0f, 1.0f); ///< Eyes start to close at time 11.0.
        this->track.AddKeyFrame(11.25f, 0.0f); ///< Eyes fully open again at time 11.25.
        this->track.AddKeyFrame(15.0f, 0.0f); ///< Eyes remain open until time 15.0.
    }

public:
    /**
     * @brief Default constructor.
     *
     * Constructs a BlinkTrack object and initializes the blink animation keyframes.
     */
    BlinkTrack() {
        AddKeyFrames();
    }
};
