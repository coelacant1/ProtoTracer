#pragma once

class MinFilter {
private:
	int memory;
	int minMemory;
	float* values;
	float* minValues;
  	int currentAmount = 0;

	float* ShiftArray(int mem, float arr[]);

public:
	MinFilter();
	MinFilter(int memory);
	float Filter(float value);

};
