#pragma once

#include <Arduino.h>

template<size_t memory>
class RunningAverageFilter {
private:
	float gain = 0.1f;
	float values[memory];
  	uint8_t currentAmount = 0;

public:
	RunningAverageFilter() {
		this->gain = 0.25f;
	}

	RunningAverageFilter(float gain){
		this->gain = gain;
	}

	void SetGain(float gain){
		this->gain = gain;
	}

	float Filter(float value) {
		float sum = 0.0f;
		float avg = 0.0f;
		float gainInverse = (1.0f - gain);

		if(currentAmount < memory){
			values[currentAmount++] = value;
		}
		else{
			for(uint8_t i = 0; i < memory - 1; i++){
				values[i] = values[i + 1];
			}

			values[memory - 1] = value;
		}

		for(uint8_t i = 0; i < currentAmount; i++){
			sum += values[i];
		}

		if (currentAmount > 0) {
			avg = sum / currentAmount;
		}

		return (gain * value) + (gainInverse * avg);
	}

};
