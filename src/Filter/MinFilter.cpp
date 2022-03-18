#include "MinFilter.h"

MinFilter::MinFilter() {
	this->memory = 25;
    this->minMemory = 5;
    this->values = new float[25];
    this->minValues = new float[5];

    for (int i = 0; i < minMemory; i++){
        minValues[i] = 0.0f;
    }
}

MinFilter::MinFilter(int memory) {
	this->memory = memory;
    this->minMemory = memory / 10;
    this->values = new float[memory];
    this->minValues = new float[minMemory];

    for (int i = 0; i < minMemory; i++){
        minValues[i] = 0.0f;
    }
}

float MinFilter::Filter(float value) {
    float avg = 0;

    if(currentAmount < memory){
        values[currentAmount++] = value;
    }
    else{
        values = ShiftArray(memory, values);//pop first
        values[memory - 1] = value;
    }

    float currentMin = values[0];//1st element
    for(int i = 1; i < currentAmount; i++){
        if (values[i] < currentMin) currentMin = values[i];
    }

    if(minValues[minMemory - 1] != currentMin){//the current min is different than the first, shift back and add
        minValues = ShiftArray(minMemory, minValues);//pop first
        minValues[minMemory - 1] = currentMin;
    }

    for (int i = 0; i < minMemory; i++){
        avg = avg + minValues[i];
    }

	return avg / minMemory;
}

float* MinFilter::ShiftArray(int mem, float arr[]){
    for(int i = 0; i < mem; i++){
        arr[i] = arr[i + 1];
    }

    arr[mem - 1] = 0.0;

    return arr;
}
