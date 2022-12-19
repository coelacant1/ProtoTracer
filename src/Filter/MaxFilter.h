#pragma once

template<size_t memory>
class MaxFilter {
private:
	const int maxMemory = ceil(memory / 10);
	float values[memory];
	float maxValues[memory / 10];
  	uint8_t currentAmount = 0;

	void ShiftArray(uint8_t mem, float* arr){
		for(uint8_t i = 0; i < mem; i++){
			arr[i] = arr[i + 1];
		}

		arr[mem - 1] = 0.0;
	}

public:
	MaxFilter() {
		// Initialize the maxValues array to 0.0f
		for (int i = 0; i < maxMemory; i++) {
			maxValues[i] = 0.0f;
		}
	}

	float Filter(float value) {
		float avg = 0;

		if(currentAmount < memory){
			values[currentAmount++] = value;
		}
		else{
			ShiftArray(memory, values);//pop first
			values[memory - 1] = value;
		}

		float currentMax = values[0];//1st element
		for(uint8_t i = 1; i < currentAmount; i++){
			if (values[i] > currentMax) currentMax = values[i];
		}

		if(maxValues[maxMemory - 1] != currentMax){//the current max is different than the first, shift back and add
			ShiftArray(maxMemory, maxValues);//pop first
			maxValues[maxMemory - 1] = currentMax;
		}

		for (uint8_t i = 0; i < maxMemory; i++){
			avg = avg + maxValues[i];
		}

		return avg / maxMemory;
	}

};
