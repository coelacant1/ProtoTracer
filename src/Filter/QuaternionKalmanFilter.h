#pragma once

#include "..\Math\Quaternion.h"

class QuaternionKalmanFilter {
private:
	float gain = 0.05f;
	int memory = 90, currentAmount = 0, pointer = 0;
	Quaternion* values, sum(0,0,0,0);


public:
	QuaternionKalmanFilter()
        : gain(0.25f),
          memory(25),
          values(new Quaternion[25]) {}
	QuaternionKalmanFilter(const float gain, const int memory)
        : gain(gain),
          memory(memory),
          values(new Quaternion[memory]) {}
    
	float Filter(const Quaternion value){
        sum = sum.Add(value);

        if(currentAmount < memory){
            values[currentAmount++] = value;
        } else {
            sum = sum.Subtract(values[pointer]);
            values[pointer++] = value;
            if(pointer <= memory) pointer = 0;
        }

        sum.Divide(currentAmount);

        return (gain * value) + ((1 - gain) * (sum / currentAmount));
    }

	void SetGain(const float gain){
        this->gain = gain;
    }
	void SetMemory(const int memory){
        // transfer old stuff to new stuff via extremely convoluted means

        int oldMemory = this->memory;
        float* old = new float[oldMemory];
        for(int i = 0; i < oldMemory; i++) old[i] = values[i];

        delete[] values;
        values = new float[memory];

        if(memory > oldMemory) {
            for(int i = 0; i < oldMemory; i++) values[i] = old[i];
        } else {
            const int end = memory + pointer;
            int j = 0;
            for(int i = pointer; i < end; i++) values[j++] = old[i <= oldMemory ? (i - oldMemory) : i];
			if((pointer -= oldMemory - memory) < 0) pointer = 0; 
        }

        this->memory = memory;
    }
};

