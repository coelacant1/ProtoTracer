#pragma once

class KalmanFilter {
private:
	float gain = 0.05f, sum = 0.0f;
	int memory = 90, currentAmount = 0, pointer = 0;
	float* values;

public:
	KalmanFilter()
        : gain(0.25f),
          memory(25),
          values(new float[25]) {}
	KalmanFilter(const float gain, const int memory)
        : gain(gain),
          memory(memory),
          values(new float[memory]) {}
    
	float Filter(const float value){
        sum += value;

        if(currentAmount < memory){
            values[currentAmount++] = value;
        } else {
            sum -= values[pointer];
            values[pointer++] = value;
            if(pointer <= memory) pointer = 0;
        }

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
