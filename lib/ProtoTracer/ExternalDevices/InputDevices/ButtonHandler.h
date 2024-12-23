/**
 * @file ButtonHandler.h
 * @brief Declares the ButtonHandler class for managing button input and state.
 *
 * This file defines the ButtonHandler class, which provides static methods for
 * initializing a button, handling interrupts, and retrieving button states and values.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h> ///< Include for Arduino compatibility.

/**
 * @class ButtonHandler
 * @brief Manages button input and state with interrupt support.
 *
 * The ButtonHandler class provides static methods for initializing a button,
 * handling button press and hold logic, and retrieving the current state and value.
 */
class ButtonHandler {
private:
    static long previousMillisISR; ///< Tracks the last interrupt service routine (ISR) trigger time in milliseconds.
    static long previousMillisHold; ///< Tracks the last hold event time in milliseconds.
    static uint16_t holdingToggle; ///< Time threshold for detecting holding behavior in milliseconds.
    static uint8_t currentValue; ///< The current value of the button (e.g., press count).
    static uint8_t maxValue; ///< The maximum value for the button press count.
    static uint8_t pin; ///< The pin number associated with the button.
    static bool holdingState; ///< Indicates whether the button is in a holding state.

    /**
     * @brief Interrupt service routine (ISR) for handling button presses.
     */
    static void isr();

public:
    /**
     * @brief Initializes the ButtonHandler with specified parameters.
     *
     * @param pin The pin number associated with the button.
     * @param maxValue The maximum value for the button press count.
     * @param holdingToggle The time threshold for detecting holding behavior in milliseconds.
     */
    static void Initialize(uint8_t pin, uint8_t maxValue, uint16_t holdingToggle);

    /**
     * @brief Retrieves the holding state of the button.
     *
     * @return True if the button is being held, false otherwise.
     */
    static bool GetHoldingState();

    /**
     * @brief Retrieves the current value of the button.
     *
     * @return The current button value (e.g., press count).
     */
    static uint8_t GetValue();
};
