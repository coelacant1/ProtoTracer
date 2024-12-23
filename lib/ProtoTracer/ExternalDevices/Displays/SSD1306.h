/**
 * @file HeadsUpDisplay.h
 * @brief Declares the HeadsUpDisplay class for rendering and displaying information on SSD1306/SH1106 displays.
 *
 * This file defines the HeadsUpDisplay class, which extends the Effect interface to capture and process
 * rendered frames efficiently. It supports SSD1306 displays and provides an untested option for SH1106 displays.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h> ///< Include for Arduino compatibility.
#include <Wire.h> ///< Include for I2C communication.
#include <Adafruit_GFX.h> ///< Include for Adafruit GFX library.
#include <Fonts/Picopixel.h> ///< Include for additional font support.

#include "../../Examples/UserConfiguration.h" ///< Include for user-specific configurations.
#include "../InputDevices/Menu/Menu.h" ///< Include for menu input handling.
#include "../../Utils/Math/Mathematics.h" ///< Include for mathematical utilities.
#include "../../Scene/Screenspace/Effect.h" ///< Include for effect interface.
#include "../../Utils/Time/TimeStep.h" ///< Include for timestep utility.

#ifdef SH1106
#include "Adafruit_SH1106.h" ///< Include for SH1106 display (untested).
#else
#include <Adafruit_SSD1306.h> ///< Include for SSD1306 display.
#endif

/**
 * @class HeadsUpDisplay
 * @brief Renders and displays information on an SSD1306/SH1106 display.
 *
 * The HeadsUpDisplay class acts as an Effect, allowing it to intercept and process rendered
 * frames efficiently for display on OLED screens. It supports a variety of pre-configured
 * menus, effects, and face animations.
 */
class HeadsUpDisplay : public Effect {
private:
    static const uint16_t SCREEN_WIDTH = 128; ///< Width of the OLED screen.
    static const uint16_t SCREEN_HEIGHT = 64; ///< Height of the OLED screen.
    static const int8_t OLED_RESET = -1; ///< Reset pin for the display.
    static const uint8_t faceXMinPosition = 66; ///< Minimum X position for face rendering.
    static const uint8_t faceXMaxPosition = 124; ///< Maximum X position for face rendering.
    static const uint8_t faceYMinPosition = 35; ///< Minimum Y position for face rendering.
    static const uint8_t faceYMaxPosition = 60; ///< Maximum Y position for face rendering.
    static const uint32_t splashTime = 2500; ///< Duration for splash screen in milliseconds.
    static const int bufferSize = 2048; ///< Buffer size for display rendering.

    const __FlashStringHelper* percentArray[10] = {F("10%"), F("20%"), F("30%"), F("40%"), F("50%"), F("60%"), F("70%"), F("80%"), F("90%"), F("100%")};//!< Battery percentages.
    const __FlashStringHelper* effectArray[10] = {F("NONE"), F("PHASEY"), F("PHASEX"), F("PHASER"), F("GLITCHX"), F("MAGNET"), F("FISHEYE"), F("BLURH"), F("BLURV"), F("BLURR")};
    const __FlashStringHelper* colorArray[10] = {F("GRDIENT"), F("YELLOW"), F("ORANGE"), F("WHITE"), F("GREEN"), F("PURPLE"), F("RED"), F("BLUE"), F("RAINBOW"), F("NOISE")};
    const __FlashStringHelper* onOffArray[2] = {F("OFFLINE"), F("ONLINE")};//!< Online/Offline statuses.
    const __FlashStringHelper* hueArray[10] = {F("0 DEG"), F("36 DEG"), F("72 DEG"), F("108 DEG"), F("144 DEG"), F("180 DEG"), F("216 DEG"), F("252 DEG"), F("288 DEG"), F("324 DEG")};//!< Hue options.
    const __FlashStringHelper* faceArray[10] = {F("DEFAULT"), F("ANGRY"), F("DOUBT"), F("FROWN"), F("LOOKUP"), F("SAD"), F("AUDIO1"), F("AUDIO2"), F("AUDIO3")}; //!< Face names.

    const __FlashStringHelper** faceNames; ///< Names of each face to be displayed on the screen
    bool useExternalFace = false; ///< To decide if it uses faceArray or faceNames for the face

    Effect* subEffect; ///< Used to capture the complete rendered frame
    TimeStep timeStep = TimeStep(5); ///< Limits the display to update 5 times per second
    bool didBegin = false; ///< True if the I2C interface started correctly
    bool splashFinished = false; ///< True when the splash startup screen is finished
    Vector2D faceMin; ///< Minimum coordinate for face on display
    Vector2D faceMax; ///< Maximum coordinate for face on display
    uint32_t startMillis; ///< Start time of the display for the splash screen

#ifdef SH1106
    static Adafruit_SH1106 display;
#else
    static Adafruit_SSD1306 display;
#endif
    static uint8_t faceBitmap[bufferSize]; ///< Background template for displaying the grids

    static const uint8_t CoelaSplash[];
    static const uint8_t PrototracerSplash[];
    static const uint8_t FaceTemplate[];

    /**
     * @brief Resets the display buffer to a blank state.
     */
    void ResetDisplayBuffer();

    /**
     * @brief Enables rendering for a bitmap face within specified coordinates.
     *
     * @param xIn X-coordinate input for face rendering.
     * @param yIn Y-coordinate input for face rendering.
     */
    void EnableBitFaceRender(float xIn, float yIn);

    /**
     * @brief Updates face rendering information.
     */
    void UpdateFaceInformation();

public:
    /**
     * @brief Constructs a HeadsUpDisplay with face rendering boundaries.
     *
     * @param faceMin Minimum coordinates for face rendering.
     * @param faceMax Maximum coordinates for face rendering.
     */
    HeadsUpDisplay(Vector2D faceMin, Vector2D faceMax);

    /**
     * @brief Sets the array of face names.
     *
     * @param faceNames Pointer to an array of face names.
     */
    void SetFaceArray(const __FlashStringHelper** faceNames);

    /**
     * @brief Sets the minimum face rendering coordinates.
     *
     * @param faceMin Minimum coordinates for face rendering.
     */
    void SetFaceMin(Vector2D faceMin);

    /**
     * @brief Sets the maximum face rendering coordinates.
     *
     * @param faceMax Maximum coordinates for face rendering.
     */
    void SetFaceMax(Vector2D faceMax);

    /**
     * @brief Initializes the display and related components.
     */
    void Initialize();

    /**
     * @brief Resets the I2C bus in case of communication errors.
     */
    void ResetI2CBus();

    /**
     * @brief Updates the display content based on the current state.
     */
    void Update();

    /**
     * @brief Sets the sub-effect to be applied to the display.
     *
     * @param effect Pointer to the Effect to be applied.
     */
    void SetEffect(Effect* effect);

    /**
     * @brief Applies the effect to the specified pixel group.
     *
     * @param pixelGroup Pointer to the pixel group to process.
     */
    void ApplyEffect(IPixelGroup* pixelGroup);

    /**
     * @brief Prints text conditionally inverted based on menu selection.
     *
     * @param x X-coordinate for the text.
     * @param y Y-coordinate for the text.
     * @param menu Current menu index.
     * @param str The string to print.
     */
    void CheckInvertPrintText(int16_t x, int16_t y, uint8_t menu, const String& str);
};
