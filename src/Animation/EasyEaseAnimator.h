#pragma once

#include <Arduino.h>
#include "KeyFrame.h"
#include "..\Math\Mathematics.h"
#include "..\Controls\DampedSpring.h"
#include "..\Filter\RampFilter.h"

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
    RampFilter* rampFilter;
    const uint16_t maxParameters;
    float** parameters;
    float* parameterFrame;
    float* previousChangedTarget;
    float* basis;
    float* goal;
    float springConstant;
    float dampingConstant;
    uint8_t* interpolationMethods;
    uint16_t* dictionary;
    uint16_t currentParameters = 0;
    bool isActive = true;

public:
    EasyEaseAnimator(uint16_t maxParameters, InterpolationMethod interpMethod, float springConstant = 0.5f, float dampingConstant = 10.0f) : maxParameters(maxParameters) {
        this->interpMethod = interpMethod;
        this->springConstant = springConstant;
        this->dampingConstant = dampingConstant;

        parameters = new float*[maxParameters];
        parameterFrame = new float[maxParameters];
        previousChangedTarget = new float[maxParameters];
        basis = new float[maxParameters];
        goal = new float[maxParameters];
        dictionary = new uint16_t[maxParameters];
        interpolationMethods = new uint8_t[maxParameters];
        dampedSpring = new DampedSpring*[maxParameters];
        rampFilter = new RampFilter[maxParameters];

        for (uint8_t i = 0; i < maxParameters; i++){
            interpolationMethods[i] = interpMethod;

            dampedSpring[i] = new DampedSpring(springConstant, dampingConstant);
        }

    }

    ~EasyEaseAnimator(){
        delete[] parameterFrame;
        delete[] previousChangedTarget;
        delete[] basis;
        delete[] goal;
        delete[] dictionary;
        delete[] interpolationMethods;
        delete[] dampedSpring;
        delete[] rampFilter;

        delete parameters;
        delete parameterFrame;
        delete previousChangedTarget;
        delete basis;
        delete goal;
        delete dictionary;
        delete interpolationMethods;
        delete dampedSpring;
        delete rampFilter;
    }

    void AddParameter(float* parameter, uint16_t dictionaryValue, int frames, float basis, float goal){
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
                dictionary[currentParameters] = dictionaryValue;
                currentParameters++;

                rampFilter[currentParameters] = RampFilter(frames);
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
        for(uint16_t i = 0; i < currentParameters; i++){

            float set = rampFilter[i].Filter(parameterFrame[i]);

            float linear = Mathematics::Map(set, basis[i], goal[i], 0.0f, 1.0f);

            switch(interpolationMethods[i]){
                case Cosine:
                    *parameters[i] = Mathematics::CosineInterpolation(basis[i], goal[i], linear);
                    break;
                case Bounce:
                    *parameters[i] = Mathematics::BounceInterpolation(basis[i], goal[i], linear);
                    break;
                case Overshoot:
                    *parameters[i] = dampedSpring[i]->Calculate(parameterFrame[i]);
                    break;
                default://Linear
                    *parameters[i] = linear;
                    break;
            }

            parameterFrame[i] = basis[i];
        }
    }
};
