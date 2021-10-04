#pragma once

#include "Arduino.h"
#include "KeyFrame.h"
#include "..\Math\Mathematics.h"

class EasyEaseAnimator{
private:
    const unsigned int maxParameters;
    float** parameters;
    float* parameterFrame;
    float* previousChangedTarget;
    float* previousTarget;
    float* basis;
    unsigned int* rampFrames = 0;
    unsigned int* targetChangeStep;
    unsigned int* dictionary;
    unsigned int currentParameters = 0;
    bool isActive = true;

public:
    EasyEaseAnimator(unsigned int maxParameters) : maxParameters(maxParameters) {
        this->basis = basis;

        parameters = new float*[maxParameters];
        parameterFrame = new float[maxParameters];
        previousChangedTarget = new float[maxParameters];
        previousTarget = new float[maxParameters];
        basis = new float[maxParameters];
        rampFrames = new unsigned int[maxParameters];
        targetChangeStep = new unsigned int[maxParameters];
        dictionary = new unsigned int[maxParameters];
    }

    ~EasyEaseAnimator(){
        delete[] parameterFrame;
        delete[] previousChangedTarget;
        delete[] previousTarget;
        delete[] basis;
        delete[] rampFrames;
        delete[] targetChangeStep;
        delete[] dictionary;

        delete parameters;
        delete parameterFrame;
        delete previousChangedTarget;
        delete previousTarget;
        delete basis;
        delete rampFrames;
        delete targetChangeStep;
        delete dictionary;
    }

    void AddParameter(float* parameter, unsigned int dictionaryValue, unsigned int rampFrames, float basis){
        if(currentParameters < maxParameters){
            bool addValue = true;
            for(unsigned int i = 0; i < currentParameters; i++){
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

    void AddParameterFrame(unsigned int dictionaryValue, float value){
        for(unsigned int i = 0; i < currentParameters; i++){
            if(dictionary[i] == dictionaryValue){
                parameterFrame[i] = value;
                break;
            }
        }
    }

    void Reset(){
        for(unsigned int i = 0; i < currentParameters; i++){
            *(this->parameters[i]) = basis[i];
        }
    }

    void Update(){
        //parameterFrame is the target, if no parameter is given for the frame, it will move towards the basis value

        //Reset frame parameters to basis value
        for(unsigned int i = 0; i < currentParameters; i++){
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
            
            *parameters[i] = Mathematics::CosineInterpolation(previousChangedTarget[i], parameterFrame[i], ratio);

            previousTarget[i] = parameterFrame[i];
            parameterFrame[i] = basis[i];
            targetChangeStep[i]++;
        }
    }
};
