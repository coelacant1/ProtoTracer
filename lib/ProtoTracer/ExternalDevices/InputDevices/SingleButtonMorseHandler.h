/**
 * @file MenuHandler.h
 * @brief Declares the MenuHandler template class for managing single-button menu interactions with Morse code input.
 *
 * This file defines the MenuHandler template class, which provides functionality for handling
 * single-button menu navigation, Morse code input processing, and persistent settings storage using EEPROM.
 *
 * @date 22/12/2024
 * @author aaronze
 */

#pragma once

#include <Arduino.h> ///< Include for Arduino compatibility.
#include <EEPROM.h> ///< Include for EEPROM functionality.

/**
 * @class MenuHandler
 * @brief Manages single-button menu navigation and settings storage.
 *
 * The MenuHandler class provides functionality for navigating through menus and managing settings
 * using a single button. It supports Morse code input for advanced interaction and persistent storage through EEPROM.
 *
 * @tparam menuCount The number of menus to manage.
 */
template <uint8_t menuCount>
class MenuHandler {
private:
    static bool previousState; ///< Tracks the previous state of the button.
    static long previousMillis; ///< Tracks the last button press time in milliseconds.
    static uint8_t inputCount; ///< Number of Morse code inputs received.
    static uint16_t inputStream[4]; ///< Buffer for storing Morse code input.
    static uint8_t currentMenu; ///< Index of the currently active menu.
    static uint8_t currentValue[menuCount]; ///< Array of current values for each menu.
    static uint8_t maxValue[menuCount]; ///< Array of maximum values for each menu.
    static uint8_t pin; ///< The pin number associated with the button.

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
     * @brief Updates the menu system and processes button input.
     */
    static void Update();

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

#include "SingleButtonMorseHandler.tpp" ///< Include the template implementation.
