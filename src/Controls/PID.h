#pragma once

class PID {
private:
    float integral;
    float error;
    float previousError;
    float output;
    float kp;
    float ki;
    float kd;
    float previousSeconds;

public:
    PID();
    PID(float kp, float ki, float kd);
    ~PID();
    float Calculate(float setpoint, float processVariable, unsigned long currentMillis);
    float Calculate(float setpoint, float processVariable, float dT);
};
