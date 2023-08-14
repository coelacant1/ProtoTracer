#pragma once

#include "AnimationTrack.h"

template<size_t parameters>
class EffectChangeTrack : public AnimationTrack<parameters, 5>{
private:
    void AddKeyFrames(){
        this->track.AddKeyFrame(0.0f, 0.0f);
        this->track.AddKeyFrame(0.5f, 1.0f);
        this->track.AddKeyFrame(1.0f, 0.0f);
        this->track.AddKeyFrame(1000000.0f, 0.0f);
    }

public:
    EffectChangeTrack(){
        AddKeyFrames();
    }

};
