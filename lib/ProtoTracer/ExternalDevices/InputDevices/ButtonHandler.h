#include <Arduino.h>

class ButtonHandler{
private:
    static long previousMillisISR;
    static long previousMillisHold;
    static uint16_t holdingToggle;
    static uint8_t currentValue;
    static uint8_t maxValue;
    static uint8_t pin;
    static bool holdingState;

    static void isr() {
        if(millis() - previousMillisISR > 250){
            currentValue += 1;
            if (currentValue > maxValue) currentValue = 0;
        
            previousMillisISR = millis();
        }
    }

public:
    static void Initialize(uint8_t pin, uint8_t maxValue, uint16_t holdingToggle) {
        pinMode(pin, INPUT_PULLUP);
        attachInterrupt(pin, isr, FALLING);
        
        ButtonHandler::maxValue = maxValue;
        ButtonHandler::pin = pin;
        ButtonHandler::holdingToggle = holdingToggle;
    }

    static bool GetHoldingState(){
        long currentTime = millis();

        if(digitalRead(pin)){//pin on, not pressed
            previousMillisHold = currentTime;
        } else if(currentTime - previousMillisHold > holdingToggle){
            previousMillisHold = currentTime;
            holdingState = !holdingState;
        }

        return holdingState;
    }

    static uint8_t GetValue(){

        return currentValue;
    }
};

long ButtonHandler::previousMillisISR;
long ButtonHandler::previousMillisHold;
uint16_t ButtonHandler::holdingToggle;
uint8_t ButtonHandler::currentValue;
uint8_t ButtonHandler::maxValue;
uint8_t ButtonHandler::pin;
bool ButtonHandler::holdingState = true;