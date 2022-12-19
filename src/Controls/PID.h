#pragma once

#include <Arduino.h>

class PID {
private:
	float integral = 0.0f;
	float error = 0.0f;
	float previousError = 0.0f;
	float output = 0.0f;
	float kp = 1.0f;
	float ki = 0.0f;
	float kd = 0.0f;
    float previousSeconds = 0.0f;

public:
	PID() {
        this->kp = 1.0f;
        this->ki = 0.0f;
        this->kd = 0.0f;

        previousSeconds = millis();
    }

	~PID();

	PID(float kp, float ki, float kd){
        this->kp = kp;
        this->ki = ki;
        this->kd = kd;

        previousSeconds = millis();
    }

	float Calculate(float setpoint, float processVariable){
        float POut, IOut, DOut;

        float currentSeconds = millis() / 1000.0f;
        float dT = currentSeconds - previousSeconds;

        error = setpoint - processVariable;
        integral += error * dT;

        POut = kp * error;
        IOut = ki * integral;
        DOut = kd * ((error - previousError) / dT);

        output = POut + IOut + DOut;
        previousError = error;
        
        previousSeconds = currentSeconds;

        return output;
    }
};
