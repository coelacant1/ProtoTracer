#pragma once

#include <Arduino.h>
#include "..\Controls\DampedSpring.h"
#include "..\Sensors\MenuHandler.h"
#include "..\Materials\Animated\RainbowNoise.h"
#include "..\Materials\Menu\TextEngine.h"

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
        Color
    };

private:
    static RainbowNoise material;
    static DampedSpring dampedSpringX;
    static DampedSpring dampedSpringShow;

    static Vector2D size;
    static Vector2D position;
    static Vector2D positionOffset;
    static Vector2D rotationOffset;
    static float rotation;
    static float showMenuRatio;

    static const uint8_t menuCount = 9;
    static const uint8_t menuLength = 12;
    static TextEngine<2, menuLength * menuCount> textEngine;
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
    
    static String line1;
    static String line2;

    static void SetMaxEntries(){
        MenuHandler::SetMenuMax(Faces, faceCount);
        MenuHandler::SetMenuMax(Bright, 10);
        MenuHandler::SetMenuMax(AccentBright, 10);
        MenuHandler::SetMenuMax(Microphone, 2);
        MenuHandler::SetMenuMax(MicLevel, 10);
        MenuHandler::SetMenuMax(BoopSensor, 2);
        MenuHandler::SetMenuMax(SpectrumMirror, 2);
        MenuHandler::SetMenuMax(FaceSize, 10);
        MenuHandler::SetMenuMax(Color, 10);
    }

    static void SetDefaultEntries(){
        MenuHandler::SetDefaultValue(Faces, 0);
        MenuHandler::SetDefaultValue(Bright, 3);
        MenuHandler::SetDefaultValue(AccentBright, 5);
        MenuHandler::SetDefaultValue(Microphone, 1);
        MenuHandler::SetDefaultValue(MicLevel, 5);
        MenuHandler::SetDefaultValue(BoopSensor, 1);
        MenuHandler::SetDefaultValue(SpectrumMirror, 0);
        MenuHandler::SetDefaultValue(FaceSize, 0);
        MenuHandler::SetDefaultValue(Color, 0);

        MenuHandler::SetInitialized();
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

        if (!MenuHandler::Initialize(pin, holdingTime)){
            SetDefaultEntries();
        }

        SetMaxEntries();

        MenuHandler::Begin();
        isSecondary = false;
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
            target = (1.0f - float(MenuHandler::GetCurrentMenu() + 1) / float(menuCount)) * size.X + 25.0f;
            menuTarget = MenuHandler::GetCurrentMenu() != 0 ? 0.0f : 100.0f;
        }

        float xPosition = dampedSpringX.Calculate(target, 0.25f);

        showMenuRatio = dampedSpringShow.Calculate(menuTarget, 0.25f);
        material.Update(ratio);

        ratio = sinf(ratio * Mathematics::MPI * 2.0f) * 4.0f;//Mathematics::Map(ratio, 0.0f, 1.0f, -4.0f, 4.0f);

        Menu::SetPosition(Vector2D(-xPosition + ratio * wiggleRatio, ratio * wiggleRatio + 40.0f + showMenuRatio * 3.0f));
        Menu::SetRotationOffset(Vector2D(200.0f / 2, 100.0f / 2));
        Menu::SetRotation(ratio);

        Menu::GenerateText();
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

        textEngine.SetText(1, line2, false);
    }

    static void SetFaceState(uint8_t faceState){
        Menu::faceState = faceState;
    }

    static uint8_t GetFaceState(){
        if(isSecondary) return faceState;
        else return MenuHandler::GetMenuValue(Faces);
    }

    static void SetBrightness(uint8_t bright){
        Menu::bright = bright;
    }

    static uint8_t GetBrightness(){
        if(isSecondary) return bright;
        else return MenuHandler::GetMenuValue(Bright);
    }

    static void SetAccentBrightness(uint8_t accentBright){
        Menu::accentBright = accentBright;
    }

    static uint8_t GetAccentBrightness(){
        if(isSecondary) return accentBright;
        else return MenuHandler::GetMenuValue(AccentBright);
    }

    static void SetUseMicrophone(uint8_t microphone){
        Menu::microphone = microphone;
    }

    static uint8_t UseMicrophone(){
        if(isSecondary) return microphone;
        else return MenuHandler::GetMenuValue(Microphone);
    }

    static void SetMicLevel(uint8_t micLevel){
        Menu::micLevel = micLevel;
    }

    static uint8_t GetMicLevel(){
        if(isSecondary) return micLevel;
        else return MenuHandler::GetMenuValue(MicLevel);
    }

    static void SetUseBoopSensor(uint8_t boopSensor){
        Menu::boopSensor = boopSensor;
    }

    static uint8_t UseBoopSensor(){
        if(isSecondary) return boopSensor;
        else return MenuHandler::GetMenuValue(BoopSensor);
    }

    static void SetMirrorSpectrumAnalyzer(uint8_t spectrumMirror){
        Menu::spectrumMirror = spectrumMirror;
    }

    static uint8_t MirrorSpectrumAnalyzer(){
        if(isSecondary) return spectrumMirror;
        else return MenuHandler::GetMenuValue(SpectrumMirror);
    }

    static void SetFaceSize(uint8_t faceSize){
        Menu::faceSize = faceSize;
    }

    static uint8_t GetFaceSize(){
        if(isSecondary) return faceSize;
        else return MenuHandler::GetMenuValue(FaceSize);
    }

    static void SetFaceColor(uint8_t color){
        Menu::color = color;
    }

    static uint8_t GetFaceColor(){
        if(isSecondary) return color;
        else return MenuHandler::GetMenuValue(Color);
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

const uint8_t Menu::menuCount;
const uint8_t Menu::menuLength;
TextEngine<2, 12 * Menu::menuCount> Menu::textEngine;
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

//                    111111111111222222222222333333333333444444444444555555555555666666666666777777777777888888888888999999999999
String Menu::line1 = "               BRIGHT     SIDEBRT       MIC        LEVEL        BOOP        SPEC        SIZE       COLOR    ";
String Menu::line2 = " a b c d e f   12^45       12^45       ON off     123456|8     on OFF      ON off      12^45      123456|8  ";