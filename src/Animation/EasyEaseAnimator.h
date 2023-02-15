#pragma once

#include <Arduino.h>
#include "KeyFrame.h"
#include "..\Math\Mathematics.h"
#include "..\Controls\DampedSpring.h"
#include "..\Filter\RampFilter.h"

class EasyEaseInterpolation{
public:
    enum InterpolationMethod{
        Cosine,
        Bounce,
        Linear,
        Overshoot
    };
};

template<size_t maxParameters>
class EasyEaseAnimator : public EasyEaseInterpolation{
private:
    InterpolationMethod interpMethod;
    DampedSpring dampedSpring[maxParameters];
    RampFilter rampFilter[maxParameters];
    float* parameters[maxParameters];
    float parameterFrame[maxParameters];
    float previousSet[maxParameters];
    float basis[maxParameters];
    float goal[maxParameters];
    uint8_t interpolationMethods[maxParameters];
    uint16_t dictionary[maxParameters];
    uint16_t currentParameters = 0;
    bool isActive = true;

public:
    EasyEaseAnimator(InterpolationMethod interpMethod, float springConstant = 1.0f, float dampingConstant = 0.5f) {
        this->interpMethod = interpMethod;

        for (uint8_t i = 0; i < maxParameters; i++){
            interpolationMethods[i] = interpMethod;

            dampedSpring[i].SetConstants(springConstant, dampingConstant);
        }
    }
    
    void SetConstants(uint16_t dictionaryValue, float springConstant, float damping){
        for(uint16_t i = 0; i < currentParameters; i++){
            if(dictionary[i] == dictionaryValue){
                dampedSpring[i].SetConstants(springConstant, damping);
                break;
            }
        }
    }

    float GetValue(uint16_t dictionaryValue){
        for(uint16_t i = 0; i < currentParameters; i++){
            if(dictionary[i] == dictionaryValue){
                return *parameters[i];
            }
        }
        
        return 0.0f;
    }

    float GetTarget(uint16_t dictionaryValue){
        for(uint16_t i = 0; i < currentParameters; i++){
            if(dictionary[i] == dictionaryValue){
                return goal[i];
            }
        }
        
        return 0.0f;
    }

    void AddParameter(float* parameter, uint16_t dictionaryValue, uint16_t frames, float basis, float goal){
        if(currentParameters < maxParameters){
            bool addValue = true;
            for(uint16_t i = 0; i < currentParameters; i++){
                if(dictionary[i] == dictionaryValue){
                    addValue = false;
                    break;
                }
            }

            if(addValue){
                this->basis[currentParameters] = basis;
                this->goal[currentParameters] = goal;
                parameters[currentParameters] = parameter;
                parameterFrame[currentParameters] = 0.0f;
                previousSet[currentParameters] = 0.0f;
                dictionary[currentParameters] = dictionaryValue;
                rampFilter[currentParameters].SetFrames(frames);
                currentParameters++;
            }
        }
    }

    void AddParameterFrame(uint16_t dictionaryValue, float value){
        for(uint16_t i = 0; i < currentParameters; i++){
            if(dictionary[i] == dictionaryValue){
                parameterFrame[i] = value;
                break;
            }
        }
    }

    void SetInterpolationMethod(uint16_t dictionaryValue, InterpolationMethod interpMethod){
        for(uint16_t i = 0; i < currentParameters; i++){
            if(dictionary[i] == dictionaryValue){
                interpolationMethods[i] = interpMethod;

                break;
            }
        }
    }

    void Reset(){
        for(uint16_t i = 0; i < currentParameters; i++){
            *(this->parameters[i]) = basis[i];
        }
    }

    void SetParameters(){//Used to set parameters but not update interpolation
        for(uint16_t i = 0; i < currentParameters; i++){
            float set = previousSet[i];
            float fullRange = Mathematics::Map(set, basis[i], goal[i], 0.0f, 1.0f);

            switch(interpolationMethods[i]){
                case Cosine:
                    *parameters[i] = Mathematics::CosineInterpolation(basis[i], goal[i], fullRange);
                    break;
                case Bounce:
                    *parameters[i] = Mathematics::BounceInterpolation(basis[i], goal[i], fullRange);
                    break;
                case Overshoot:
                    *parameters[i] = dampedSpring[i].GetCurrentPosition();
                    break;
                default://Linear
                    *parameters[i] = set;
                    break;
            }
        }
    }

    void Update(){
        //parameterFrame is the target, if no parameter is given for the frame, it will move towards the basis value
        for(uint16_t i = 0; i < currentParameters; i++){

            float set = rampFilter[i].Filter(parameterFrame[i]);
            float fullRange = Mathematics::Map(set, basis[i], goal[i], 0.0f, 1.0f);

            previousSet[i] = set;

            //basis at 0.5f does not go to 0.5f but to zero with linear
            //when using set, it defaults the blush is shown the inverted 1.0f to 0.0f does not work

            switch(interpolationMethods[i]){
                case Cosine:
                    *parameters[i] = Mathematics::CosineInterpolation(basis[i], goal[i], fullRange);
                    break;
                case Bounce:
                    *parameters[i] = Mathematics::BounceInterpolation(basis[i], goal[i], fullRange);
                    break;
                case Overshoot:
                    *parameters[i] = dampedSpring[i].Calculate(parameterFrame[i], 0.25f);
                    break;
                default://Linear
                    *parameters[i] = set;
                    break;
            }

            parameterFrame[i] = basis[i];
        }
    }
};
