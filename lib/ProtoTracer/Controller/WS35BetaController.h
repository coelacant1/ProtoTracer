/**
 * @file WS35BetaController.h
 * @brief Declares the WS35BetaController class for managing WS2812-based displays on the Beta Protogen head.
 *
 * This file defines the WS35BetaController class, which extends the Controller base class.
 * It provides functionality for controlling and displaying content on four WS35 WS2812-based displays
 * designed for the Beta Protogen head.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <stdint.h> ///< Include for fixed-width integer types.
#include <OctoWS2811.h> ///< Include for OctoWS2811 LED library.
#include "Controller.h" ///< Include for base controller functionality.
#include "../Camera/CameraManager/CameraManager.h" ///< Include for camera management.
#include "../Camera/Pixels/PixelGroup.h" ///< Include for pixel group management.

/**
 * @class WS35BetaController
 * @brief Manages WS2812-based displays for the Beta Protogen head.
 *
 * The WS35BetaController class extends the Controller base class to provide specific
 * functionality for initializing, controlling, and displaying content on WS2812-based
 * LED displays.
 */
class WS35BetaController : public Controller {
private:
    const int ledsPerStrip = 346; ///< Number of LEDs per strip.
    int drawingMemory[346 * 6]; ///< Memory buffer for LED data.
    const int config = WS2811_GRB | WS2811_800kHz; ///< LED configuration: GRB color order and 800kHz signal.
    OctoWS2811 leds; ///< Instance of OctoWS2811 for controlling the LEDs.

public:
    /**
     * @brief Constructs a WS35BetaController with specified parameters.
     *
     * @param cameras Pointer to the CameraManager for managing camera data.
     * @param maxBrightness Maximum brightness for the displays.
     */
    WS35BetaController(CameraManager* cameras, uint8_t maxBrightness);

    /**
     * @brief Initializes the WS35BetaController and sets up the displays.
     */
    void Initialize() override;

    /**
     * @brief Updates and displays the content on the WS2812 displays.
     */
    void Display() override;

    /**
     * @brief Sets the color of a specific LED on a specific strip.
     *
     * @param strip The strip number (0-based).
     * @param led The LED number (0-based).
     * @param rgb The RGB color to set.
     */
    void SetPixels(uint8_t strip, uint16_t led, RGBColor rgb);

    /**
     * @brief Sets the maximum brightness for the displays.
     *
     * @param maxBrightness The maximum brightness value (0-255).
     */
    void SetBrightness(uint8_t maxBrightness) override;

    /**
     * @brief Sets the maximum accent brightness (not used for this controller).
     *
     * @param maxAccentBrightness The maximum accent brightness value (0-255).
     */
    void SetAccentBrightness(uint8_t maxAccentBrightness) override;
};