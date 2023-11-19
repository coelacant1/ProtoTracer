#pragma once

#include "AnimationTrack.h"

template<size_t parameters>
class EyeMoveTrack : public AnimationTrack<parameters, 10>{
private:
    void AddKeyFrames(){
        this->track.AddKeyFrame(0.0f, 0.0f);
        this->track.AddKeyFrame(2.5f, 1.0f);
        this->track.AddKeyFrame(5.0f, 0.0f);
        this->track.AddKeyFrame(25.0f, 0.0f);
    }

public:
    EyeMoveTrack(){
        AddKeyFrames();
    }

};
    