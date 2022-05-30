#pragma once

template<size_t memory>
class KalmanFilter {
private:
	float gain = 0.1f;
	float values[memory];
  	uint8_t currentAmount = 0;

	void ShiftArray(float* arr){
		for(uint8_t i = 0; i < memory; i++){
			arr[i] = arr[i + 1];
		}

		arr[memory - 1] = 0.0f;
	}

public:
	KalmanFilter() {
		this->gain = 0.25f;
	}

	KalmanFilter(float gain){
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
			ShiftArray(values);//pop first
			values[memory - 1] = value;
		}

		for(int i = 0; i < currentAmount; i++){
			sum += values[i];
		}

		if (currentAmount > 0) {
			avg = sum / currentAmount;
		}

		return (gain * value) + (gainInverse * avg);
	}

};
