#pragma once

#include "..\Math\Quaternion.h"

class QuaternionKalmanFilter {
private:
	float gain = 0.05f;
	int memory = 90, currentAmount = 0, pointer = 0;
	Quaternion* values, sum = Quaternion(0,0,0,0);


public:
	QuaternionKalmanFilter()
        : gain(0.25f),
          memory(25),
          values(new Quaternion[25]) {}
	QuaternionKalmanFilter(const float gain, const int memory)
        : gain(gain),
          memory(memory),
          values(new Quaternion[memory]) {}
    ~QuaternionKalmanFilter(){
        delete[] values;
    }
    
	Quaternion Filter(const Quaternion value){
        sum += value;

        if(currentAmount < memory){
            values[currentAmount++] = value;
        } else {
            sum -= values[pointer];
            values[pointer++] = value;
            if(pointer <= memory) pointer = 0;
        }

        sum / currentAmount;

        return (value * gain) + ((sum / currentAmount) * (1.0f - gain));
    }

	void SetGain(const float gain){
        this->gain = gain;
    }
	void SetMemory(const int newMemory) {
        // transfer old stuff to new stuff via extremely convoluted means
        Quaternion *newValues = new Quaternion[newMemory];

        if (newMemory > memory) {
            for (int i = 0; i < memory; i++)
                newValues[i] = values[i];
        } else {
            if (currentAmount > newMemory) currentAmount = newMemory;
            const int start = (pointer > newMemory) ? pointer - newMemory : memory - (newMemory - pointer) ;
            const int end = start + newMemory;
            sum = Quaternion(0, 0, 0, 0);
            int j = 0;
            for (int i = start; i < end; i++)
                sum += newValues[j++] = values[i % memory];
            pointer = newMemory - (memory - newMemory);
        }

        memory = newMemory;

        delete[] values; // Let's be memory safe at least...
        values = newValues;
    }
};

