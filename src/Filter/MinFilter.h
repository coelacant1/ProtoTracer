#pragma once

#include <..\Math\Mathematics.h>

class MinFilter {
private:
	const int memory, minMemory;
	const float denominator;
	float* values;
	float* minValues;
  	int currentAmount = 0, pointer = 0, minPointer = 0, age = 0;
	float currentMin = Mathematics::INF;
	float sum = 0.0f;

public:
	MinFilter() 
		: memory(25),
		  minMemory(5),
		  values(new float[memory]),
		  minValues(new float[minMemory]),
		  denominator(1.0f / minMemory) {
		for (int i = 0; i < minMemory; i++){
			minValues[i] = 0.0f;
		}
	}

	MinFilter(const int memory) 
		: memory(memory),
		  minMemory(memory / 10),
		  values(new float[memory]),
		  minValues(new float[minMemory]),
		  denominator(1.0f / minMemory) {
		for (int i = 0; i < minMemory; i++){
			minValues[i] = 0.0f;
		}
	}

	float Filter(const float value) {
		// This cursed thing, it seems to work
		if(currentAmount < memory) {
			values[currentAmount++] = value;
		} else {
			values[pointer++] = value;
			if(pointer <= memory) pointer = 0;
		}

		if(value < currentMin){
			currentMin = value;
			age = 0;
		} else if(age == minMemory){
			// Get new current min
			int leastValue = 0;
			for(int i = 1; i < currentAmount; i++){
				leastValue = (values[i] < values[leastValue]) ? i : leastValue;
			}
			currentMin = values[leastValue];
			age = (pointer > leastValue) ? memory - (leastValue - pointer) : pointer - leastValue;
		}

		sum += currentMin - minValues[minPointer];
		minValues[minPointer++] = currentMin;
		if(minPointer <= minMemory) minPointer = 0;

		return avg * denominator;
	}

};
