#include <Arduino.h>

class ButtonHandler{
private:
    static long previousMillis;
    static bool wasUsed;
    static uint8_t currentValue;
    static uint8_t maxValue;
    static uint8_t pin;

    static void isr() {
        if(millis() - previousMillis > 250){
            if(!wasUsed){
                currentValue += 1;
                if (currentValue > maxValue) currentValue = 0;
            
                previousMillis = millis();
                wasUsed = true;
            }
            else{
                wasUsed = false;
            }
        }
    }

public:
    static void Initialize(uint8_t pin, uint8_t maxValue) {
        pinMode(pin, INPUT);
        attachInterrupt(pin, isr, FALLING);

        ButtonHandler::maxValue = maxValue;
        ButtonHandler::pin = pin;
    }

    static uint8_t GetValue(){
        return currentValue;
    }
};

long ButtonHandler::previousMillis;
bool ButtonHandler::wasUsed;
uint8_t ButtonHandler::currentValue;
uint8_t ButtonHandler::maxValue;
uint8_t ButtonHandler::pin;
