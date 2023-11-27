#pragma once

//shift array from position
template<size_t maxParameters, size_t maxKeyFrames>
void KeyFrameTrack<maxParameters, maxKeyFrames>::ShiftKeyFrameArray(int position){
    for(uint8_t i = position; i < currentFrames; i++){
        keyFrames[i + 1] = keyFrames[i];
    }
}

template<size_t maxParameters, size_t maxKeyFrames>
KeyFrameTrack<maxParameters, maxKeyFrames>::KeyFrameTrack(float min, float max, InterpolationMethod interpMethod){
    this->min = min;
    this->max = max;
    this->interpMethod = interpMethod;
}

template<size_t maxParameters, size_t maxKeyFrames>
float KeyFrameTrack<maxParameters, maxKeyFrames>::GetCurrentTime(){
    currentTime = fmod(millis() / 1000.0f + timeOffset, stopFrameTime - startFrameTime) + startFrameTime;//normalize time and add offset

    return currentTime;
}

template<size_t maxParameters, size_t maxKeyFrames>
void KeyFrameTrack<maxParameters, maxKeyFrames>::SetCurrentTime(float setTime){
    float currentSecs = millis() / 1000.0f;

    //Test case: current time = 1.32s, set time = 1.09s, 1.59s
    timeOffset = setTime - currentSecs;//1.59 - 1.32 = 0.27, 1.09 - 1.32 = -0.23

}

template<size_t maxParameters, size_t maxKeyFrames>
void KeyFrameTrack<maxParameters, maxKeyFrames>::Pause(){
    isActive = false;
}

template<size_t maxParameters, size_t maxKeyFrames>
void KeyFrameTrack<maxParameters, maxKeyFrames>::Play(){
    isActive = true;
}

template<size_t maxParameters, size_t maxKeyFrames>
void KeyFrameTrack<maxParameters, maxKeyFrames>::AddParameter(float* parameter){
    if(currentParameters < maxParameters){
        parameters[currentParameters] = parameter;
        currentParameters++;
    }
}

template<size_t maxParameters, size_t maxKeyFrames>
void KeyFrameTrack<maxParameters, maxKeyFrames>::AddKeyFrame(float time, float value){
    if (currentFrames < maxKeyFrames){
        value = Mathematics::Constrain(value, min, max);

        if(currentFrames == 0){
            keyFrames[0].Set(time, value);
        }
        else if (time > this->stopFrameTime){
            keyFrames[currentFrames].Set(time, value);
        }
        else{
            for(int i = 0; i < currentFrames; i++){
                if(time < keyFrames[i].Time){
                    ShiftKeyFrameArray(i);
                    keyFrames[i].Set(time, value);
                    break;
                }
            }
        }
        
        currentFrames++;

        this->startFrameTime = time < this->startFrameTime ? time : this->startFrameTime;//set new min time if lesser than current
        this->stopFrameTime = time > this->stopFrameTime ? time : this->stopFrameTime;//Set new max time if greater than current
    }
}

template<size_t maxParameters, size_t maxKeyFrames>
float KeyFrameTrack<maxParameters, maxKeyFrames>::GetParameterValue(){
    return parameterValue;
}

template<size_t maxParameters, size_t maxKeyFrames>
void KeyFrameTrack<maxParameters, maxKeyFrames>::Reset(){
    for(int i = 0; i < currentParameters; i++){
        *(this->parameters[i]) = min;
    }
}

template<size_t maxParameters, size_t maxKeyFrames>
float KeyFrameTrack<maxParameters, maxKeyFrames>::Update(){

    GetCurrentTime();

    byte previousFrame = 0, nextFrame = 0;

    //find current time, find keyframe before and after
    if(currentFrames > 0 && isActive){
        for (uint8_t i = currentFrames - 1; i >= 0; i--){
            if (currentTime >= keyFrames[i].Time){
                previousFrame = i;
                nextFrame = i + 1;

                break;
            }
        }

        float ratio = Mathematics::Map(currentTime, keyFrames[previousFrame].Time, keyFrames[nextFrame].Time, 0.0f, 1.0f);
        float parameter = 0.0f;

        switch(interpMethod){
            case Cosine:
                parameter = Mathematics::CosineInterpolation(keyFrames[previousFrame].Value, keyFrames[nextFrame].Value, ratio);
                break;
            case Step:
                parameter = keyFrames[previousFrame].Value;
                break;
            default://Linear
                parameter = Mathematics::Map(ratio, 0.0f, 1.0f, keyFrames[previousFrame].Value, keyFrames[nextFrame].Value);
                break;

        }

        parameterValue = parameter;

        if (currentParameters > 0){//Update if not parameters are linked
            for(uint8_t i = 0; i < currentParameters; i++){
                *(this->parameters[i]) = parameter;
            }
        }
    }

    return parameterValue;
}
