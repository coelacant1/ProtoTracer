#include "KalmanFilter.h"

KalmanFilter::KalmanFilter() {
	this->gain = 0.25;
	this->memory = 25;
  values = new float[25];
}

KalmanFilter::KalmanFilter(float gain, int memory) {
	this->gain = gain;
	this->memory = memory;
  values = new float[memory];
}

float KalmanFilter::Filter(float value) {
	float sum = 0;
	float avg = 0;
	float gainInverse = (1 - gain);

  if(currentAmount < memory){
    values[currentAmount++] = value;
  }
  else{
    values = ShiftArray(values);//pop first
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

float* KalmanFilter::ShiftArray(float arr[]){
  for(int i = 0; i < memory; i++){
    arr[i] = arr[i + 1];
  }

  arr[memory - 1] = 0.0;

  return arr;
}
