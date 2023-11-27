#pragma once

template<size_t maxParameters, size_t maxKeyFrames>
AnimationTrack<maxParameters, maxKeyFrames>::AnimationTrack() : track(KeyFrameTrack<maxParameters, maxKeyFrames>(0.0f, 1.0f, KeyFrameInterpolation::Cosine)){}
    
template<size_t maxParameters, size_t maxKeyFrames>
AnimationTrack<maxParameters, maxKeyFrames>::AnimationTrack(float min, float max, KeyFrameInterpolation::InterpolationMethod interpMethod) : track(KeyFrameTrack<maxParameters, maxKeyFrames>(min, max, interpMethod)){}

template<size_t maxParameters, size_t maxKeyFrames>
void AnimationTrack<maxParameters, maxKeyFrames>::Play(){
    track.Play();
}

template<size_t maxParameters, size_t maxKeyFrames>
void AnimationTrack<maxParameters, maxKeyFrames>::Pause(){
    track.Pause();
}

template<size_t maxParameters, size_t maxKeyFrames>
void AnimationTrack<maxParameters, maxKeyFrames>::RestartTime(){
    track.SetCurrentTime(0.0f);
}

template<size_t maxParameters, size_t maxKeyFrames>
void AnimationTrack<maxParameters, maxKeyFrames>::PrintTime(){
    Serial.println(track.GetCurrentTime());
}

template<size_t maxParameters, size_t maxKeyFrames>
void AnimationTrack<maxParameters, maxKeyFrames>::Reset(){
    track.Reset();
}

template<size_t maxParameters, size_t maxKeyFrames>
float AnimationTrack<maxParameters, maxKeyFrames>::GetParameterValue(){
    return track.GetParameterValue();
}

template<size_t maxParameters, size_t maxKeyFrames>
float AnimationTrack<maxParameters, maxKeyFrames>::Update(){
    return track.Update();
}

template<size_t maxParameters, size_t maxKeyFrames>
void AnimationTrack<maxParameters, maxKeyFrames>::AddParameter(float* parameter){
    track.AddParameter(parameter);
}
