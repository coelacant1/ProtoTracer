#pragma once

#include "AnimationTrack.h"

template<size_t parameters>
class MouthTrack : public AnimationTrack<parameters, 5>{
private:
    void AddKeyFrames(){
        this->track.AddKeyFrame(0.0f, 0.0f);
        this->track.AddKeyFrame(1.5f, 1.0f);
        this->track.AddKeyFrame(4.0f, 0.0f);
    }

public:
    MouthTrack(){
        AddKeyFrames();
    }

};
    