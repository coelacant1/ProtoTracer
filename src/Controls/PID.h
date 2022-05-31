#pragma once

#include <Arduino.h>

class PID {
private:
    float integral = 0;
    float error = 0;
    float previousError = 0;
    float output = 0;
    float kp = 1.0f;
    float ki = 0.0f;
    float kd = 0.0f;
    unsigned long previousMillis = millis();

public:
    PID() {}
    PID(const float kp, const float ki, const float kd) 
        : kp(kp),
          ki(ki),
          kd(kd) {}
    ~PID();

    float Calculate(float setpoint, float processVariable) {
        const unsigned long currentMillis = millis();
        const float dT = ((float)(currentMillis - previousMillis)) * 1e-3f; // / 1000.0f

        error = setpoint - processVariable;
        integral += error * dT;

        const float POut = kp * error;
        const float IOut = ki * integral;
        const float DOut = kd * ((error - previousError) / dT);

        output = POut + IOut + DOut;
        previousError = error;

        previousMillis = currentMillis;

        return output;
    }
};
