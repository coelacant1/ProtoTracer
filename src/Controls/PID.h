#pragma once

#include <Arduino.h>

class PID {
private:
	float integral = 0;
	float error = 0;
	float previousError = 0;
	float output = 0;
	float kp;
	float ki;
	float kd;
    unsigned long previousMillis;

public:
	PID() {
        this->kp = 1.0f;
        this->ki = 0.0f;
        this->kd = 0.0f;

        previousMillis = millis();
    }

	~PID();

	PID(float kp, float ki, float kd){
        this->kp = kp;
        this->ki = ki;
        this->kd = kd;

        previousMillis = millis();
    }

	float Calculate(float setpoint, float processVariable){
        float POut, IOut, DOut;

        unsigned long currentMillis = millis();
        float dT = ((float)(currentMillis - previousMillis)) / 1000.0f;

        error = setpoint - processVariable;
        integral += error * dT;

        POut = kp * error;
        IOut = ki * integral;
        DOut = kd * ((error - previousError) / dT);

        output = POut + IOut + DOut;
        previousError = error;
        
        previousMillis = currentMillis;

        return output;
    }
};
