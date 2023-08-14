#pragma once

#include <Arduino.h>
#include "..\Controls\DampedSpring.h"
#include "..\Materials\Animated\RainbowNoise.h"
#include "..\Materials\Menu\TextEngine.h"

#include "..\Animation\AnimationTracks\EffectChangeTrack.h"
#include "..\Screenspace\Passthrough.h"
#include "..\Screenspace\GlitchX.h"
#include "..\Screenspace\Fisheye.h"
#include "..\Screenspace\HorizontalBlur.h"
#include "..\Screenspace\PhaseOffsetX.h"
#include "..\Screenspace\PhaseOffsetY.h"
#include "..\Screenspace\PhaseOffsetR.h"
#include "..\Screenspace\Magnet.h"
#include "..\Screenspace\Overflow.h"
#include "..\Screenspace\RadialBlur.h"
#include "..\Screenspace\ShiftR.h"
#include "..\Screenspace\VerticalBlur.h"

#ifdef NEOTRELLISMENU
#include "..\Sensors\NeoTrellisMenuHandler.h"
#else
#include "..\Sensors\SingleButtonMenuHandler.h"
#endif

class Menu{
public:
    enum MenuState{
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
        EffectS
    };

private:
    static const uint8_t menuCount = 12;
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

    static void SetMaxEntries(){
        MenuHandler<menuCount>::SetMenuMax(Faces, faceCount);
        MenuHandler<menuCount>::SetMenuMax(Bright, 10);
        MenuHandler<menuCount>::SetMenuMax(AccentBright, 10);
        MenuHandler<menuCount>::SetMenuMax(Microphone, 2);
        MenuHandler<menuCount>::SetMenuMax(MicLevel, 10);
        MenuHandler<menuCount>::SetMenuMax(BoopSensor, 2);
        MenuHandler<menuCount>::SetMenuMax(SpectrumMirror, 2);
        MenuHandler<menuCount>::SetMenuMax(FaceSize, 10);
        MenuHandler<menuCount>::SetMenuMax(Color, 10);
        MenuHandler<menuCount>::SetMenuMax(HueF, 10);
        MenuHandler<menuCount>::SetMenuMax(HueB, 10);
        MenuHandler<menuCount>::SetMenuMax(EffectS, 10);
    }

    static void SetDefaultEntries(){
        MenuHandler<menuCount>::SetDefaultValue(Faces, 0);
        MenuHandler<menuCount>::SetDefaultValue(Bright, 3);
        MenuHandler<menuCount>::SetDefaultValue(AccentBright, 5);
        MenuHandler<menuCount>::SetDefaultValue(Microphone, 1);
        MenuHandler<menuCount>::SetDefaultValue(MicLevel, 5);
        MenuHandler<menuCount>::SetDefaultValue(BoopSensor, 1);
        MenuHandler<menuCount>::SetDefaultValue(SpectrumMirror, 0);
        MenuHandler<menuCount>::SetDefaultValue(FaceSize, 0);
        MenuHandler<menuCount>::SetDefaultValue(Color, 0);
        MenuHandler<menuCount>::SetDefaultValue(HueF, 0);
        MenuHandler<menuCount>::SetDefaultValue(HueB, 0);
        MenuHandler<menuCount>::SetDefaultValue(EffectS, 0);

        MenuHandler<menuCount>::SetInitialized();
    }

public:
    static void Initialize(uint8_t faceCount, uint8_t pin, uint16_t holdingTime, Vector2D size = Vector2D(240, 50)){
        Menu::faceCount = faceCount;

        dampedSpringX.SetConstants(1.0f, 0.5f);
        dampedSpringShow.SetConstants(1.0f, 0.5f);

        SetSize(size);

        textEngine.SetMaterial(&material);
        textEngine.SetPositionOffset(position);
        textEngine.SetBlinkTime(200);

        #ifdef NEOTRELLISMENU
        if (!MenuHandler<menuCount>::Initialize()){
            SetDefaultEntries();
        }
        #else
        if (!MenuHandler<menuCount>::Initialize(pin, holdingTime)){
            SetDefaultEntries();
        }
        #endif

        SetMaxEntries();

        #ifndef NEOTRELLISMENU
        MenuHandler<menuCount>::Begin();
        #endif
        isSecondary = false;

        effectChange.AddParameter(&effectStrength);
    }

    static void Initialize(uint8_t faceCount, Vector2D size = Vector2D(240, 50)){
        Menu::faceCount = faceCount;

        dampedSpringX.SetConstants(1.0f, 0.5f);
        dampedSpringShow.SetConstants(1.0f, 0.5f);

        SetSize(size);

        textEngine.SetMaterial(&material);
        textEngine.SetPositionOffset(position);
        textEngine.SetBlinkTime(200);

        SetMaxEntries();

        isSecondary = true;
    }

    static Material* GetMaterial(){
        return &textEngine;
    }

    static Effect* GetEffect(){
        switch(GetEffectS()){
            case 0:
                return &passthrough;
                break;
            case 1:
                return &phaseY;
                break;
            case 2:
                return &phaseX;
                break;
            case 3:
                return &phaseR;
                break;
            case 4:
                return &glitchX;
                break;
            case 5:
                return &magnet;
                break;
            case 6:
                return &fisheye;
                break;
            case 7:
                return &blurH;
                break;
            case 8:
                return &blurV;
                break;
            default:
                return &blurR;
                break;
        }
    }

    static void SetCurrentMenu(uint8_t currentMenu){
        Menu::currentMenu = currentMenu;
    }

    static void Update(float ratio){
        float target = 0.0f;
        float menuTarget = 0.0f;

        if (isSecondary){
            target = (1.0f - float(currentMenu + 1) / float(menuCount)) * size.X + 25.0f;
            menuTarget = currentMenu != 0 ? 0.0f : 100.0f;
        }
        else{
            target = (1.0f - float(MenuHandler<menuCount>::GetCurrentMenu() + 1) / float(menuCount)) * size.X + 25.0f;
            menuTarget = MenuHandler<menuCount>::GetCurrentMenu() != 0 ? 0.0f : 100.0f;
        }

        float xPosition = dampedSpringX.Calculate(target, 0.25f);

        showMenuRatio = dampedSpringShow.Calculate(menuTarget, 0.25f);
        material.Update(ratio);

        ratio = sinf(ratio * Mathematics::MPI * 2.0f) * 4.0f;//Mathematics::Map(ratio, 0.0f, 1.0f, -4.0f, 4.0f);

        Menu::SetPosition(Vector2D(-xPosition + ratio * wiggleRatio, ratio * wiggleRatio + 40.0f + showMenuRatio * 3.0f));
        Menu::SetRotationOffset(Vector2D(200.0f / 2, 100.0f / 2));
        Menu::SetRotation(ratio);

        Menu::GenerateText();
        
        if (GetFaceState() != previousMenu){
            effectChange.RestartTime();
            previousMenu = GetFaceState();
        }
        
        effectChange.Update();

        GetEffect()->SetRatio(effectStrength);
    }

    static void SetWiggleRatio(float wiggleRatio){
        Menu::wiggleRatio = wiggleRatio;
    }

    static void SetSize(Vector2D size){
        size.X = size.X * menuCount;

        Menu::size = size;

        textEngine.SetSize(size);
    }

    static Vector2D GetPosition(){
        return Menu::position;
    }

    static void SetPosition(Vector2D position){
        Menu::position = position + positionOffset;
        textEngine.SetPositionOffset(Menu::position);
    }

    static void SetPositionOffset(Vector2D positionOffset){
        Menu::positionOffset = positionOffset;
    }

    static void SetRotationOffset(Vector2D rotationOffset){
        Menu::rotationOffset = rotationOffset;
        textEngine.SetRotationOffset(rotationOffset);
    }

    static float GetRotation(){
        return Menu::rotation;
    }
    
    static void SetRotation(float rotation){
        Menu::rotation = rotation;
        textEngine.SetRotationAngle(rotation);
    }

    static char IntToBlink(char value){
        switch(value){
            case '0': return '[';
            case '1': return '\\';
            case '2': return ']';
            case '3': return '^';
            case '4': return '_';
            case '5': return '`';
            case '6': return '{';
            case '7': return '|';
            case '8': return '}';
            case '9': return '~';
            default: return ' ';
        }
    }

    static String GenerateLine(uint8_t options, uint8_t selection){
        String text;
        uint8_t spacing = options >= 5 ? 3 : (menuLength - options) / 2;

        for(uint8_t i = 0; i < spacing; i++){//pad spacing
            text += " ";
        }

        for(uint8_t i = 0; i < 5; i++){
            if(selection < 5 && i < options){
                char value = '0' + i;

                if(i == selection){
                    text += IntToBlink(value);
                }
                else{
                    text += value;
                }
            }
            else if (selection >= 5 && i + 5 < options){
                char value = '5' + i;

                if(i + 5 == selection){
                    text += IntToBlink(value);
                }
                else{
                    text += value;
                }
            }
        }
        
        while(text.length() < 12){
            text += " ";
        }

        return text;
    }


    static void GenerateText(){
        textEngine.SetText(0, line1, false);

        line2 = "            ";

        line2 += GenerateLine(10, GetBrightness());
        line2 += GenerateLine(10, GetAccentBrightness());
        line2 += UseMicrophone() ? "   on OFF   " : "   ON off   ";
        line2 += GenerateLine(10, GetMicLevel());
        line2 += UseBoopSensor() ? "   on OFF   " : "   ON off   ";
        line2 += MirrorSpectrumAnalyzer() ? "   on OFF   " : "   ON off   ";
        line2 += GenerateLine(10, GetFaceSize());
        line2 += GenerateLine(10, GetFaceColor());
        line2 += GenerateLine(10, GetHueF());
        line2 += GenerateLine(10, GetHueB());
        line2 += GenerateLine(10, GetEffectS());

        textEngine.SetText(1, line2, false);
    }

    static void SetFaceState(uint8_t faceState){
        Menu::faceState = faceState;
    }

    static uint8_t GetFaceState(){
        if(isSecondary) return faceState;
        else return MenuHandler<menuCount>::GetMenuValue(Faces);
    }

    static void SetBrightness(uint8_t bright){
        Menu::bright = bright;
    }

    static uint8_t GetBrightness(){
        if(isSecondary) return bright;
        else return MenuHandler<menuCount>::GetMenuValue(Bright);
    }

    static void SetAccentBrightness(uint8_t accentBright){
        Menu::accentBright = accentBright;
    }

    static uint8_t GetAccentBrightness(){
        if(isSecondary) return accentBright;
        else return MenuHandler<menuCount>::GetMenuValue(AccentBright);
    }

    static void SetUseMicrophone(uint8_t microphone){
        Menu::microphone = microphone;
    }

    static uint8_t UseMicrophone(){
        if(isSecondary) return microphone;
        else return MenuHandler<menuCount>::GetMenuValue(Microphone);
    }

    static void SetMicLevel(uint8_t micLevel){
        Menu::micLevel = micLevel;
    }

    static uint8_t GetMicLevel(){
        if(isSecondary) return micLevel;
        else return MenuHandler<menuCount>::GetMenuValue(MicLevel);
    }

    static void SetUseBoopSensor(uint8_t boopSensor){
        Menu::boopSensor = boopSensor;
    }

    static uint8_t UseBoopSensor(){
        if(isSecondary) return boopSensor;
        else return MenuHandler<menuCount>::GetMenuValue(BoopSensor);
    }

    static void SetMirrorSpectrumAnalyzer(uint8_t spectrumMirror){
        Menu::spectrumMirror = spectrumMirror;
    }

    static uint8_t MirrorSpectrumAnalyzer(){
        if(isSecondary) return spectrumMirror;
        else return MenuHandler<menuCount>::GetMenuValue(SpectrumMirror);
    }

    static void SetFaceSize(uint8_t faceSize){
        Menu::faceSize = faceSize;
    }

    static uint8_t GetFaceSize(){
        if(isSecondary) return faceSize;
        else return MenuHandler<menuCount>::GetMenuValue(FaceSize);
    }

    static void SetFaceColor(uint8_t color){
        Menu::color = color;
    }

    static uint8_t GetFaceColor(){
        if(isSecondary) return color;
        else return MenuHandler<menuCount>::GetMenuValue(Color);
    }
    
    static void SetHueF(uint8_t huef){
        Menu::huef = huef;
    }

    static uint8_t GetHueF(){
        if(isSecondary) return huef;
        else return MenuHandler<menuCount>::GetMenuValue(HueF);
    }

    static void SetHueB(uint8_t hueb){
        Menu::hueb = hueb;
    }

    static uint8_t GetHueB(){
        if(isSecondary) return hueb;
        else return MenuHandler<menuCount>::GetMenuValue(HueB);
    }

    static void SetEffectS(uint8_t effect){
        Menu::effect = effect;
    }

    static uint8_t GetEffectS(){
        if(isSecondary) return effect;
        else return MenuHandler<menuCount>::GetMenuValue(EffectS);
    }

    static float ShowMenu(){
        return showMenuRatio / 100.0f;
    }
};

RainbowNoise Menu::material;
DampedSpring Menu::dampedSpringX;
DampedSpring Menu::dampedSpringShow;

Vector2D Menu::size;
Vector2D Menu::position;
Vector2D Menu::positionOffset;
Vector2D Menu::rotationOffset;
float Menu::rotation;
float Menu::showMenuRatio;

const uint8_t Menu::menuLength;
const uint8_t Menu::menuRows;
const uint8_t Menu::menuCountEng;
TextEngine<Menu::menuRows, Menu::menuLength * Menu::menuCountEng> Menu::textEngine;
uint8_t Menu::faceCount;
uint8_t Menu::currentMenu = 0;
float Menu::wiggleRatio = 1.0f;
bool Menu::isSecondary = 0;

uint8_t Menu::faceState = 0;
uint8_t Menu::bright = 0;
uint8_t Menu::accentBright = 0;
uint8_t Menu::microphone = 0;
uint8_t Menu::micLevel = 0;
uint8_t Menu::boopSensor = 0;
uint8_t Menu::spectrumMirror = 0;
uint8_t Menu::faceSize = 0;
uint8_t Menu::color = 0;
uint8_t Menu::huef = 0;
uint8_t Menu::hueb = 0;
uint8_t Menu::effect = 0;

EffectChangeTrack<1> Menu::effectChange;
float Menu::effectStrength = 0.0f;
uint8_t Menu::previousMenu = 0;

Passthrough Menu::passthrough = Passthrough();
Fisheye Menu::fisheye = Fisheye();
GlitchX Menu::glitchX = GlitchX(30);
HorizontalBlur Menu::blurH = HorizontalBlur(16);
VerticalBlur Menu::blurV = VerticalBlur(16);
Magnet Menu::magnet = Magnet();
RadialBlur Menu::blurR = RadialBlur(16);
PhaseOffsetX Menu::phaseX = PhaseOffsetX(20);
PhaseOffsetY Menu::phaseY = PhaseOffsetY(20);
PhaseOffsetR Menu::phaseR = PhaseOffsetR(20);
ShiftR Menu::shiftR = ShiftR(20);
Overflow Menu::overflow = Overflow(20);

//                    111111111111222222222222333333333333444444444444555555555555666666666666777777777777888888888888999999999999111111111111222222222222333333333333
String Menu::line1 = "               BRIGHT     SIDEBRT       MIC        LEVEL        BOOP        SPEC        SIZE       COLOR       HUE F       HUE B      EFFECT    ";
String Menu::line2 = " a b c d e f   12^45       12^45       ON off     123456|8     on OFF      ON off      12^45      123456|8    123456|8    123456|8    123456|8  ";

