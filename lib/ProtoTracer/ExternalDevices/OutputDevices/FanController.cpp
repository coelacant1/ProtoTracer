#include "FanController.h"

FanController::FanController(uint8_t pin) {
    this->pin = pin;
}

void FanController::Initialize() {
    pinMode(pin, OUTPUT);
}

void FanController::SetPWM(uint8_t pwm) {
    this->pwm = pwm;
    analogWrite(pin, pwm);
}

void FanController::SetSpeed(float ratio) {
    uint8_t pwm = uint8_t(Mathematics::Map(ratio, 0.0f, 1.0f, 0.0f, 255.0f));
    SetPWM(pwm);
}

uint8_t FanController::GetPWM() {
    return pwm;
}
