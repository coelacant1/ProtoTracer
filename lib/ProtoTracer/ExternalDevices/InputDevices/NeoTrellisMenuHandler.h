/**
 * @file MenuHandler.h
 * @brief Declares the MenuHandler template class for managing menu interactions using Adafruit NeoTrellis.
 *
 * This file defines the MenuHandler template class, which provides functionality for managing
 * multiple menus and settings through an Adafruit NeoTrellis keypad interface, including EEPROM
 * storage for persistent settings.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h> ///< Include for Arduino compatibility.
#include <EEPROM.h> ///< Include for EEPROM functionality.
#include "Adafruit_NeoTrellis.h" ///< Include for Adafruit NeoTrellis keypad support.

/**
 * @class MenuHandler
 * @brief Manages multiple menus and settings using Adafruit NeoTrellis.
 *
 * The MenuHandler class provides functionality for navigating and managing settings across
 * multiple menus, including support for EEPROM storage, custom settings, and dynamic updates.
 *
 * @tparam menuCount The number of menus to manage.
 */
template <uint8_t menuCount>
class MenuHandler {
private:
    static Adafruit_NeoTrellis trellis; ///< Instance of the Adafruit NeoTrellis keypad.
    static uint8_t currentMenu; ///< Index of the currently active menu.
    static uint8_t currentSetting; ///< Index of the currently active setting within the menu.
    static uint8_t currentValue[menuCount]; ///< Array of current values for each menu.
    static uint8_t maxValue[menuCount]; ///< Array of maximum values for each menu.
    static uint8_t faceChoices; ///< Number of face choices available.
    static bool menuActive; ///< Flag indicating whether the menu is active.
    static bool isReady; ///< Flag indicating whether the menu system is ready for interaction.
    static bool didBegin; ///< Flag indicating whether the initialization process has been completed.

    /**
     * @brief Generates a color value based on a position on a color wheel.
     *
     * @param WheelPos The position on the color wheel (0-255).
     * @return The corresponding 32-bit color value.
     */
    static uint32_t Wheel(byte WheelPos);

    /**
     * @brief Callback function for handling key events on the NeoTrellis keypad.
     *
     * @param evt The key event to process.
     * @return True if the event was handled successfully, false otherwise.
     */
    static TrellisCallback blink(keyEvent evt);

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

    /**
     * @brief Resets the I2C bus to recover from communication issues.
     */
    static void ResetI2CBus();

public:
    /**
     * @brief Updates the menu state and processes user interactions.
     */
    static void Update();

    /**
     * @brief Initializes the MenuHandler and sets up the NeoTrellis keypad.
     *
     * @return True if initialization was successful, false otherwise.
     */
    static bool Initialize();

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

#include "NeoTrellisMenuHandler.tpp" ///< Include the template implementation.