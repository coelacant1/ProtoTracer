/**
 * @file SingleButtonMenuHandler.h
 * @brief Declares the MenuHandler template class for managing single-button menu interactions.
 *
 * This file defines the MenuHandler template class, which provides functionality for handling
 * single-button menu navigation and persistent settings storage using EEPROM. It also includes
 * an IntervalTimer for managing menu change timing.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h> // Include for Arduino compatibility.
#include <EEPROM.h> // Include for EEPROM functionality.
#include <IntervalTimer.h> // Include for IntervalTimer support.

/**
 * @class MenuHandler
 * @brief Manages single-button menu navigation and settings storage.
 *
 * The MenuHandler class provides functionality for navigating through menus and managing settings
 * using a single button. It supports persistent storage through EEPROM and leverages an IntervalTimer
 * for handling button hold and state transitions.
 *
 * @tparam menuCount The number of menus to manage.
 */
template <uint8_t menuCount>
class MenuHandler {
private:
    static IntervalTimer menuChangeTimer; ///< Timer for handling menu change intervals.
    static long previousMillisHold; ///< Tracks the last hold event time in milliseconds.
    static uint16_t holdingTime; ///< Time threshold for detecting holding behavior in milliseconds.
    static uint8_t currentMenu; ///< Index of the currently active menu.
    static uint8_t currentValue[menuCount]; ///< Array of current values for each menu.
    static uint8_t maxValue[menuCount]; ///< Array of maximum values for each menu.
    static uint8_t pin; ///< The pin number associated with the button.
    static bool holdingState; ///< Indicates whether the button is in a holding state.
    static bool previousState; ///< Tracks the previous state of the button.

    /**
     * @brief Updates the button state and menu navigation.
     */
    static void UpdateState();

    /**
     * @brief Reads a value from EEPROM at the specified index.
     *
     * @param index The EEPROM address to read from.
     * @return The value read from EEPROM.
     */
    static uint8_t ReadEEPROM(uint16_t index);

    /**
     * @brief Writes a value to EEPROM at the specified index.
     *
     * @param index The EEPROM address to write to.
     * @param value The value to write to EEPROM.
     */
    static void WriteEEPROM(uint16_t index, uint8_t value);

public:
    /**
     * @brief Begins the menu handling process, setting up necessary states.
     */
    static void Begin();

    /**
     * @brief Initializes the MenuHandler with specified parameters.
     *
     * @param pin The pin number associated with the button.
     * @param holdingTime The time threshold for detecting holding behavior in milliseconds.
     * @return True if initialization was successful, false otherwise.
     */
    static bool Initialize(uint8_t pin, uint16_t holdingTime);

    /**
     * @brief Sets a default value for a specific menu.
     *
     * @param menu The menu index to set the default value for.
     * @param value The default value to set.
     */
    static void SetDefaultValue(uint16_t menu, uint8_t value);

    /**
     * @brief Marks the menu system as initialized.
     */
    static void SetInitialized();

    /**
     * @brief Sets the maximum value for a specific menu.
     *
     * @param menu The menu index to set the maximum value for.
     * @param maxValue The maximum value to set.
     */
    static void SetMenuMax(uint8_t menu, uint8_t maxValue);

    /**
     * @brief Retrieves the current value of a specific menu.
     *
     * @param menu The menu index to retrieve the value from.
     * @return The current value of the menu.
     */
    static uint8_t GetMenuValue(uint8_t menu);

    /**
     * @brief Retrieves the index of the currently active menu.
     *
     * @return The index of the active menu.
     */
    static uint8_t GetCurrentMenu();
};

#include "SingleButtonMenuHandler.tpp" // Include the template implementation.
