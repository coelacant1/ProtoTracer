#pragma once

#include <Arduino.h>
#include "KeyFrame.h"
#include "..\Math\Mathematics.h"
#include "..\Controls\DampedSpring.h"

class EasyEaseAnimator{
public:
    enum InterpolationMethod{
        Cosine,
        Bounce,
        Linear,
        Overshoot
    };
    
private:
    InterpolationMethod interpMethod;
    DampedSpring** dampedSpring;
    const uint16_t maxParameters;
    float** parameters;
    float* parameterFrame;
    float* previousChangedTarget;
    float* previousTarget;
    float* basis;
    float springConstant;
    float dampingConstant;
    uint8_t* interpolationMethods;
    uint16_t* rampFrames = 0;
    uint16_t* targetChangeStep;
    uint16_t* dictionary;
    uint16_t currentParameters = 0;
    bool isActive = true;

public:
    EasyEaseAnimator(uint16_t maxParameters, InterpolationMethod interpMethod, float springConstant = 0.5f, float dampingConstant = 10.0f) : maxParameters(maxParameters) {
        this->basis = basis;
        this->interpMethod = interpMethod;
        this->springConstant = springConstant;
        this->dampingConstant = dampingConstant;

        parameters = new float*[maxParameters];
        parameterFrame = new float[maxParameters];
        previousChangedTarget = new float[maxParameters];
        previousTarget = new float[maxParameters];
        basis = new float[maxParameters];
        rampFrames = new uint16_t[maxParameters];
        targetChangeStep = new uint16_t[maxParameters];
        dictionary = new uint16_t[maxParameters];
        interpolationMethods = new uint8_t[maxParameters];
        dampedSpring = new DampedSpring*[maxParameters];

        for (uint8_t i = 0; i < maxParameters; i++){
            interpolationMethods[i] = interpMethod;

            dampedSpring[i] = new DampedSpring(springConstant, dampingConstant);
        }

    }

    ~EasyEaseAnimator(){
        delete[] parameterFrame;
        delete[] previousChangedTarget;
        delete[] previousTarget;
        delete[] basis;
        delete[] rampFrames;
        delete[] targetChangeStep;
        delete[] dictionary;
        delete[] interpolationMethods;
        delete[] dampedSpring;

        delete parameters;
        delete parameterFrame;
        delete previousChangedTarget;
        delete previousTarget;
        delete basis;
        delete rampFrames;
        delete targetChangeStep;
        delete dictionary;
        delete interpolationMethods;
        delete dampedSpring;
    }

    void AddParameter(float* parameter, uint16_t dictionaryValue, uint16_t rampFrames, float basis){
        if(currentParameters < maxParameters){
            bool addValue = true;
            for(uint16_t i = 0; i < currentParameters; i++){
                if(dictionary[i] == dictionaryValue){
                    addValue = false;
                    break;
                }
            }

            if(addValue){
                this->rampFrames[currentParameters] = rampFrames;
                this->basis[currentParameters] = basis;
                parameters[currentParameters] = parameter;
                dictionary[currentParameters] = dictionaryValue;
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

    void Update(){
        //parameterFrame is the target, if no parameter is given for the frame, it will move towards the basis value

        //Reset frame parameters to basis value
        for(uint16_t i = 0; i < currentParameters; i++){
            if(!Mathematics::IsClose(parameterFrame[i], previousTarget[i], 0.01f)){//parameter target is not the same, target has changed
                //new basis is the previous parameterFrame
                previousChangedTarget[i] = previousTarget[i];
                targetChangeStep[i] = 0;
            }

            //ramp from previous changed target to parameterframe by factor of targetChangeStep / framecount
            float ratio = 0.0f;

            if(targetChangeStep[i] >= rampFrames[i]){
                ratio = 1.0f;
            }
            else{
                ratio = ((float)targetChangeStep[i]) / ((float)rampFrames[i]);
            }

            switch(interpolationMethods[i]){
                case Cosine:
                    *parameters[i] = Mathematics::CosineInterpolation(previousChangedTarget[i], parameterFrame[i], ratio);
                    break;
                case Bounce:
                    *parameters[i] = Mathematics::BounceInterpolation(previousChangedTarget[i], parameterFrame[i], ratio);
                    break;
                case Overshoot:
                    *parameters[i] = dampedSpring[i]->Calculate(parameterFrame[i]);
                    break;
                default://Linear
                    *parameters[i] = Mathematics::Map(ratio, 0.0f, 1.0f, previousChangedTarget[i], parameterFrame[i]);
                    break;
            }

            previousTarget[i] = parameterFrame[i];
            parameterFrame[i] = basis[i];
            targetChangeStep[i]++;
        }
    }
};
