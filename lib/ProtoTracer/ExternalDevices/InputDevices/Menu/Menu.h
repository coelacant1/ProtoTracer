/**
 * @file Menu.h
 * @brief Provides the Menu class for controlling various parameters of the program.
 *
 * The Menu class allows interaction with system parameters such as face selection,
 * brightness, microphone usage, boop sensor activation, spectrum analyzer settings,
 * color/hue options, and more. It also manages the internal UI display (using 
 * TextEngine) and handles user input via button/NeoTrellis or other methods.
 */

#pragma once

#include "../../../Physics/Utils/DampedSpring.h"
#include "../../../Scene/Materials/Animated/RainbowNoise.h"
#include "../../../Scene/Materials/Special/Overlays/Text/TextEngine.h"

#include "../../../Animation/AnimationTracks/EffectChangeTrack.h"
#include "../../../Scene/Screenspace/Passthrough.h"
#include "../../../Scene/Screenspace/GlitchX.h"
#include "../../../Scene/Screenspace/Fisheye.h"
#include "../../../Scene/Screenspace/HorizontalBlur.h"
#include "../../../Scene/Screenspace/PhaseOffsetX.h"
#include "../../../Scene/Screenspace/PhaseOffsetY.h"
#include "../../../Scene/Screenspace/PhaseOffsetR.h"
#include "../../../Scene/Screenspace/Magnet.h"
#include "../../../Scene/Screenspace/Overflow.h"
#include "../../../Scene/Screenspace/RadialBlur.h"
#include "../../../Scene/Screenspace/ShiftR.h"
#include "../../../Scene/Screenspace/VerticalBlur.h"

#include "../../../Examples/UserConfiguration.h"

#ifdef NEOTRELLISMENU
#include "../NeoTrellisMenuHandler.h"
#elif defined MORSEBUTTON
#include "../SingleButtonMorseHandler.h"
#else
#include "../SingleButtonMenuHandler.h"
#endif

/**
 * @class Menu
 * @brief A class responsible for displaying and controlling a parameter menu within
 *        the project. It allows the user to change various settings (e.g., brightness,
 *        microphone level, boop sensor, effects) and to navigate through menu items.
 *
 * The Menu system integrates a TextEngine-based UI, plus optional interactive
 * hardware inputs (button, NeoTrellis, etc.). It also provides visual "wiggle"
 * effects and manages transitions via DampedSpring.
 */
class Menu {
public:
    /**
     * @enum MenuState
     * @brief Enumerates different parameter items or states in the menu.
     */
    enum MenuState {
        Faces,           ///< Controls the current face index.
        Bright,          ///< Controls the overall brightness.
        AccentBright,    ///< Controls the accent brightness.
        Microphone,      ///< Toggles microphone usage (on/off).
        MicLevel,        ///< Controls microphone level (gain).
        BoopSensor,      ///< Toggles boop sensor usage (on/off).
        SpectrumMirror,  ///< Toggles mirror effect for SpectrumAnalyzer (on/off).
        FaceSize,        ///< Controls the size of the face mesh or display.
        Color,           ///< Controls the face color selection.
        HueF,            ///< Controls the front hue value.
        HueB,            ///< Controls the back hue value.
        EffectS,         ///< Controls which post-processing effect is active.
        FanSpeed         ///< Controls the fan speed.
    };

private:
    /**
     * @brief Total number of menu items.
     */
    static const uint8_t menuCount = 13;

    /**
     * @brief A RainbowNoise material (used for text styling, if desired).
     */
    static RainbowNoise material;

    /**
     * @brief DampedSpring objects used for smooth transitions in the X-direction and for menu visibility.
     */
    static DampedSpring dampedSpringX;    ///< Controls the horizontal positioning of the menu.
    static DampedSpring dampedSpringShow; ///< Controls the show/hide ratio of the menu.

    /**
     * @brief UI geometry: size, position, offsets, and rotation.
     */
    static Vector2D size;          ///< The total size of the menu in screen-space.
    static Vector2D position;      ///< The current position of the menu.
    static Vector2D positionOffset;///< Additional offset to apply to the menu's position.
    static Vector2D rotationOffset;///< Offset for pivoting the menu (e.g., around its center).
    static float rotation;         ///< Rotation angle (in degrees or radians, depending on usage).
    static float showMenuRatio;    ///< Normalized ratio (0.0 to 100.0) controlling how much the menu is shown.

    /**
     * @brief Dimensions for the internal text layout, e.g., number of columns/rows.
     */
    static const uint8_t menuLength = 12; ///< Number of characters per menu segment.
    static const uint8_t menuRows = 2;    ///< Number of rows in the text display.

    /**
     * @brief Total "expanded" count for text engine usage.
     */
    static const uint8_t menuCountEng = menuCount;

    /**
     * @brief Text engine for rendering menu lines.
     */
    static TextEngine<menuRows, menuLength * menuCountEng> textEngine;

    /**
     * @brief Face count for how many faces are selectable in this project.
     */
    static uint8_t faceCount;

    /**
     * @brief Tracks the currently active menu index (if using isSecondary mode).
     */
    static uint8_t currentMenu;

    /**
     * @brief Wiggle effect parameters for the menu's animation.
     */
    static float wiggleRatio;  ///< How pronounced the wiggle effect is.
    static float wiggleSpeedX; ///< Speed of horizontal wiggle.
    static float wiggleSpeedY; ///< Speed of vertical wiggle.
    static float wiggleSpeedR; ///< Speed of rotational wiggle.

    /**
     * @brief Indicates whether this Menu is in "secondary" mode (no hardware input, used externally).
     */
    static bool isSecondary;

    /**
     * @brief Stored state for each menu item (if isSecondary is true).
     */
    static uint8_t faceState;       ///< Currently selected face index.
    static uint8_t bright;          ///< Brightness level.
    static uint8_t accentBright;    ///< Accent brightness level.
    static uint8_t microphone;      ///< Microphone usage toggle.
    static uint8_t micLevel;        ///< Microphone level setting.
    static uint8_t boopSensor;      ///< Boop sensor usage toggle.
    static uint8_t spectrumMirror;  ///< Spectrum mirroring toggle.
    static uint8_t faceSize;        ///< Face size setting.
    static uint8_t color;           ///< Current color setting.
    static uint8_t huef;            ///< Front hue setting.
    static uint8_t hueb;            ///< Back hue setting.
    static uint8_t effect;          ///< Current effect index.
    static uint8_t fanSpeed;        ///< Fan speed setting.

    /**
     * @brief Raw string lines for the textual interface (line1 as label row, line2 as value row).
     */
    static String line1;
    static String line2;

    /**
     * @brief EffectChangeTrack for smoothly transitioning the effect strength.
     */
    static EffectChangeTrack<1> effectChange;
    static float effectStrength; ///< The current strength ratio for the applied effect.
    static uint8_t previousMenu; ///< Tracks a previous face state to detect changes.

    /**
     * @brief Various post-processing effects instantiated.
     */
    static Passthrough passthrough;
    static Fisheye fisheye;
    static GlitchX glitchX;
    static HorizontalBlur blurH;
    static VerticalBlur blurV;
    static Magnet magnet;
    static RadialBlur blurR;
    static PhaseOffsetX phaseX;
    static PhaseOffsetY phaseY;
    static PhaseOffsetR phaseR;
    static ShiftR shiftR;
    static Overflow overflow;

    /**
     * @brief Defines the maximum allowed values for each menu parameter.
     */
    static void SetMaxEntries();

    /**
     * @brief Sets default values for each menu parameter (e.g., on initial load).
     */
    static void SetDefaultEntries();

public:
    /**
     * @brief Initializes the Menu using a face count, input pin, holding time, and size.
     *
     * This overload is typically used in single-button mode (not NeoTrellis):
     * it sets up the DampedSpring, the text engine, and hardware input for user navigation.
     *
     * @param faceCount The maximum number of faces selectable.
     * @param pin The GPIO pin for the button input.
     * @param holdingTime The time threshold for press-and-hold actions.
     * @param size The size (width, height) for the menu in screen coordinates.
     */
    static void Initialize(uint8_t faceCount, uint8_t pin, uint16_t holdingTime,
                           Vector2D size = Vector2D(240, 50));

    /**
     * @brief Initializes the Menu using just a face count and size.
     *
     * This overload is typically used with NeoTrellis or other forms of input:
     * it sets up the DampedSpring, text engine, and handles the menu logic in isSecondary mode.
     *
     * @param faceCount The maximum number of faces selectable.
     * @param size The size (width, height) for the menu in screen coordinates.
     */
    static void Initialize(uint8_t faceCount, Vector2D size = Vector2D(240, 50));

    /**
     * @brief Provides a pointer to the material used for rendering the menu text.
     * @return A pointer to the TextEngine-based material.
     */
    static Material* GetMaterial();

    /**
     * @brief Retrieves the current effect (post-processing) based on the menu setting.
     * @return A pointer to the selected Effect object.
     */
    static Effect* GetEffect();

    /**
     * @brief Gets the currently selected menu index from the MenuHandler (if in hardware mode).
     * @return The active MenuState index (e.g., Bright, Microphone, etc.).
     */
    static uint8_t GetCurrentMenu();

    /**
     * @brief Gets the current value of the active menu parameter from the MenuHandler.
     * @return The parameter value associated with the active menu index.
     */
    static uint8_t GetCurrentMenuValue();

    /**
     * @brief Manually sets the current menu index (used in isSecondary mode).
     * @param currentMenu The new menu index to set.
     */
    static void SetCurrentMenu(uint8_t currentMenu);

    /**
     * @brief Updates the menu each frame, handling transitions, wiggle effects, and text generation.
     * @param ratio A normalized value typically used in animation loops (0.0f to 1.0f).
     */
    static void Update(float ratio);

    /**
     * @brief Sets the amplitude of the wiggle effect.
     * @param wiggleRatio A multiplier for the wiggle offsets.
     */
    static void SetWiggleRatio(float wiggleRatio);

    /**
     * @brief Sets the speed multipliers for X-axis, Y-axis, and rotational wiggle.
     * @param wiggleSpeedX Speed multiplier for the X direction.
     * @param wiggleSpeedY Speed multiplier for the Y direction.
     * @param wiggleSpeedR Speed multiplier for rotation.
     */
    static void SetWiggleSpeed(float wiggleSpeedX, float wiggleSpeedY, float wiggleSpeedR);

    /**
     * @brief Sets the overall menu size and updates the text engine accordingly.
     * @param size The new menu size in screen coordinates (width, height).
     */
    static void SetSize(Vector2D size);

    /**
     * @brief Returns the current screen-space position of the menu.
     * @return A Vector2D representing the menu's position.
     */
    static Vector2D GetPosition();

    /**
     * @brief Sets the base position of the menu (plus any existing offsets).
     * @param position The new position to assign to the menu.
     */
    static void SetPosition(Vector2D position);

    /**
     * @brief Sets an additional offset to be added on top of the base position.
     * @param positionOffset The new offset to store internally.
     */
    static void SetPositionOffset(Vector2D positionOffset);

    /**
     * @brief Sets the pivot or rotation offset for the text engine.
     * @param rotationOffset The pivot offset (typically the center of the menu).
     */
    static void SetRotationOffset(Vector2D rotationOffset);

    /**
     * @brief Gets the current menu rotation angle.
     * @return The rotation angle.
     */
    static float GetRotation();

    /**
     * @brief Sets the rotation angle for the menu (in degrees or radians, based on usage).
     * @param rotation The new rotation angle.
     */
    static void SetRotation(float rotation);

    /**
     * @brief Converts a digit character into a "blink" character for visual emphasis.
     * @param value The digit character (e.g., '0' to '9').
     * @return A corresponding blink character for highlighting the selection.
     */
    static char IntToBlink(char value);

    /**
     * @brief Generates a line of characters for displaying available options (0-9),
     *        visually highlighting the currently selected index.
     * @param options The total number of options (e.g., 10).
     * @param selection The currently selected option.
     * @return A String containing spaced/arranged characters for the menu display.
     */
    static String GenerateLine(uint8_t options, uint8_t selection);

    /**
     * @brief Generates the textual representation of the menu (two lines) and
     *        updates the TextEngine with that text.
     */
    static void GenerateText();

    /**
     * @brief Manually sets the face state (active face index) if in isSecondary mode.
     * @param faceState The new face index to set.
     */
    static void SetFaceState(uint8_t faceState);

    /**
     * @brief Retrieves the current face state. In hardware mode, it is read from the MenuHandler.
     * @return The current face index.
     */
    static uint8_t GetFaceState();

    /**
     * @brief Sets the brightness level if in isSecondary mode.
     * @param bright The new brightness level.
     */
    static void SetBrightness(uint8_t bright);

    /**
     * @brief Gets the current brightness level. In hardware mode, it is read from the MenuHandler.
     * @return The brightness level.
     */
    static uint8_t GetBrightness();

    /**
     * @brief Sets the accent brightness level if in isSecondary mode.
     * @param accentBright The new accent brightness level.
     */
    static void SetAccentBrightness(uint8_t accentBright);

    /**
     * @brief Gets the current accent brightness level.
     * @return The accent brightness level.
     */
    static uint8_t GetAccentBrightness();

    /**
     * @brief Sets whether to use the microphone if in isSecondary mode.
     * @param microphone 0 or 1 representing off/on.
     */
    static void SetUseMicrophone(uint8_t microphone);

    /**
     * @brief Checks if the microphone usage is toggled on or off.
     * @return A uint8_t (0 or 1).
     */
    static uint8_t UseMicrophone();

    /**
     * @brief Sets the microphone level (gain) if in isSecondary mode.
     * @param micLevel The new microphone level (0 to 10).
     */
    static void SetMicLevel(uint8_t micLevel);

    /**
     * @brief Gets the current microphone level.
     * @return The microphone level (0 to 10).
     */
    static uint8_t GetMicLevel();

    /**
     * @brief Sets the boop sensor usage if in isSecondary mode.
     * @param boopSensor 0 or 1 representing off/on.
     */
    static void SetUseBoopSensor(uint8_t boopSensor);

    /**
     * @brief Checks if the boop sensor usage is toggled on or off.
     * @return A uint8_t (0 or 1).
     */
    static uint8_t UseBoopSensor();

    /**
     * @brief Sets whether the spectrum analyzer should be mirrored if in isSecondary mode.
     * @param spectrumMirror 0 or 1 representing off/on.
     */
    static void SetMirrorSpectrumAnalyzer(uint8_t spectrumMirror);

    /**
     * @brief Checks if the spectrum analyzer mirroring is toggled on or off.
     * @return A uint8_t (0 or 1).
     */
    static uint8_t MirrorSpectrumAnalyzer();

    /**
     * @brief Sets the face size if in isSecondary mode.
     * @param faceSize The new face size index (0-10).
     */
    static void SetFaceSize(uint8_t faceSize);

    /**
     * @brief Gets the current face size.
     * @return The face size index (0-10).
     */
    static uint8_t GetFaceSize();

    /**
     * @brief Sets the face color index if in isSecondary mode.
     * @param color The new color index (0-10).
     */
    static void SetFaceColor(uint8_t color);

    /**
     * @brief Gets the current face color index.
     * @return The color index (0-10).
     */
    static uint8_t GetFaceColor();

    /**
     * @brief Sets the front hue value if in isSecondary mode.
     * @param huef The new front hue (0-10).
     */
    static void SetHueF(uint8_t huef);

    /**
     * @brief Gets the front hue value.
     * @return The front hue (0-10).
     */
    static uint8_t GetHueF();

    /**
     * @brief Sets the back hue value if in isSecondary mode.
     * @param hueb The new back hue (0-10).
     */
    static void SetHueB(uint8_t hueb);

    /**
     * @brief Gets the back hue value.
     * @return The back hue (0-10).
     */
    static uint8_t GetHueB();

    /**
     * @brief Sets which effect is selected if in isSecondary mode.
     * @param effect The new effect index (0-9).
     */
    static void SetEffectS(uint8_t effect);

    /**
     * @brief Gets the currently selected effect index.
     * @return The effect index (0-9).
     */
    static uint8_t GetEffectS();

    /**
     * @brief Sets the fan speed if in isSecondary mode.
     * @param fanSpeed The new fan speed index (0-10).
     */
    static void SetFanSpeed(uint8_t fanSpeed);

    /**
     * @brief Gets the current fan speed index.
     * @return The fan speed index (0-10).
     */
    static uint8_t GetFanSpeed();

    /**
     * @brief Returns how much of the menu is shown, typically normalized (0.0 to 1.0).
     * @return A float representing the show menu ratio, scaled down by 100.
     */
    static float ShowMenu();
};
