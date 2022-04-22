#pragma once

class KalmanFilter {
private:
	float gain = 0.05f;
	int memory = 90;
	float* values;
  	int currentAmount = 0;

	float* ShiftArray(float arr[]);

public:
	KalmanFilter();
	KalmanFilter(float gain, int memory);
	float Filter(float value);

	void SetGain(float gain);
	void SetMemory(float memory);
};
