#include "ButtonHandler.h"

long ButtonHandler::previousMillisISR;
long ButtonHandler::previousMillisHold;
uint16_t ButtonHandler::holdingToggle;
uint8_t ButtonHandler::currentValue;
uint8_t ButtonHandler::maxValue;
uint8_t ButtonHandler::pin;
bool ButtonHandler::holdingState;

void ButtonHandler::isr() {
    if (millis() - previousMillisISR > 250) {
        currentValue += 1;
        if (currentValue > maxValue) currentValue = 0;

        previousMillisISR = millis();
    }
}

void ButtonHandler::Initialize(uint8_t pin, uint8_t maxValue, uint16_t holdingToggle) {
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), isr, FALLING);

    ButtonHandler::maxValue = maxValue;
    ButtonHandler::pin = pin;
    ButtonHandler::holdingToggle = holdingToggle;
}

bool ButtonHandler::GetHoldingState() {
    long currentTime = millis();

    if (digitalRead(pin)) {  // Pin is on, button not pressed
        previousMillisHold = currentTime;
    } else if (currentTime - previousMillisHold > holdingToggle) {
        previousMillisHold = currentTime;
        holdingState = !holdingState;
    }

    return holdingState;
}

uint8_t ButtonHandler::GetValue() {
    return currentValue;
}
