#pragma once

class KalmanFilter {
private:
	float gain;
	int memory;
	float* values;
  int currentAmount = 0;

  float* ShiftArray(float arr[]);

public:
	KalmanFilter();
	KalmanFilter(float gain, int memory);
	float Filter(float value);

};
