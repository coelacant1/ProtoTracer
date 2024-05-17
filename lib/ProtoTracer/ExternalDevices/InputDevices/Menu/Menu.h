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

class Menu {
public:
    enum MenuState {
        Faces,
        Bright,
        AccentBright,
        Microphone,
        MicLevel,
        BoopSensor,
        SpectrumMirror,
        FaceSize,
        Color,
        HueF,
        HueB,
        EffectS,
        FanSpeed
    };

private:
    static const uint8_t menuCount = 13;
    static RainbowNoise material;
    static DampedSpring dampedSpringX;
    static DampedSpring dampedSpringShow;

    static Vector2D size;
    static Vector2D position;
    static Vector2D positionOffset;
    static Vector2D rotationOffset;
    static float rotation;
    static float showMenuRatio;

    static const uint8_t menuLength = 12;
    static const uint8_t menuRows = 2;
    static const uint8_t menuCountEng = menuCount;
    static TextEngine<menuRows, menuLength * menuCountEng> textEngine;
    static uint8_t faceCount;
    static uint8_t currentMenu;
    static float wiggleRatio;
    static float wiggleSpeedX;
    static float wiggleSpeedY;
    static float wiggleSpeedR;
    static bool isSecondary;

    static uint8_t faceState;
    static uint8_t bright;
    static uint8_t accentBright;
    static uint8_t microphone;
    static uint8_t micLevel;
    static uint8_t boopSensor;
    static uint8_t spectrumMirror;
    static uint8_t faceSize;
    static uint8_t color;
    static uint8_t huef;
    static uint8_t hueb;
    static uint8_t effect;
    static uint8_t fanSpeed;

    static String line1;
    static String line2;

    static EffectChangeTrack<1> effectChange;
    static float effectStrength;
    static uint8_t previousMenu;

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

    static void SetMaxEntries();
    static void SetDefaultEntries();

public:
    static void Initialize(uint8_t faceCount, uint8_t pin, uint16_t holdingTime, Vector2D size = Vector2D(240, 50));
    static void Initialize(uint8_t faceCount, Vector2D size = Vector2D(240, 50));
    static Material* GetMaterial();
    static Effect* GetEffect();
    static void SetCurrentMenu(uint8_t currentMenu);
    static void Update(float ratio);
    static void SetWiggleRatio(float wiggleRatio);
    static void SetWiggleSpeed(float wiggleSpeedX, float wiggleSpeedY, float wiggleSpeedR);
    static void SetSize(Vector2D size);
    static Vector2D GetPosition();
    static void SetPosition(Vector2D position);
    static void SetPositionOffset(Vector2D positionOffset);
    static void SetRotationOffset(Vector2D rotationOffset);
    static float GetRotation();
    static void SetRotation(float rotation);
    static char IntToBlink(char value);
    static String GenerateLine(uint8_t options, uint8_t selection);
    static void GenerateText();
    static void SetFaceState(uint8_t faceState);
    static uint8_t GetFaceState();
    static void SetBrightness(uint8_t bright);
    static uint8_t GetBrightness();
    static void SetAccentBrightness(uint8_t accentBright);
    static uint8_t GetAccentBrightness();
    static void SetUseMicrophone(uint8_t microphone);
    static uint8_t UseMicrophone();
    static void SetMicLevel(uint8_t micLevel);
    static uint8_t GetMicLevel();
    static void SetUseBoopSensor(uint8_t boopSensor);
    static uint8_t UseBoopSensor();
    static void SetMirrorSpectrumAnalyzer(uint8_t spectrumMirror);
    static uint8_t MirrorSpectrumAnalyzer();
    static void SetFaceSize(uint8_t faceSize);
    static uint8_t GetFaceSize();
    static void SetFaceColor(uint8_t color);
    static uint8_t GetFaceColor();
    static void SetHueF(uint8_t huef);
    static uint8_t GetHueF();
    static void SetHueB(uint8_t hueb);
    static uint8_t GetHueB();
    static void SetEffectS(uint8_t effect);
    static uint8_t GetEffectS();
    static void SetFanSpeed(uint8_t fanSpeed);
    static uint8_t GetFanSpeed();
    static float ShowMenu();
};

