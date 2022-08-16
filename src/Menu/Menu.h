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
        Brightness,
        Microphone,
        BoopSensor,
        SpectrumMirror,
        FaceSize,
        Color
    };

private:
    static RainbowNoise material;
    static DampedSpring dampedSpringX;
    static DampedSpring dampedSpringShow;

    static FunctionGenerator fGenMatXMenu;
    static FunctionGenerator fGenMatYMenu;
    static FunctionGenerator fGenMatRMenu;

    static Vector2D size;
    static Vector2D position;
    static Vector2D positionOffset;
    static Vector2D rotationOffset;
    static float rotation;
    static float showMenuRatio;

    static const uint8_t menuCount = 7;
    static const uint8_t menuLength = 12;
    static TextEngine<2, menuLength * menuCount> textEngine;
    static uint8_t faceCount;
    static float wiggleRatio;
    
    static String line1;
    static String line2;

    static void SetMaxEntries(){
        MenuHandler::SetMenuMax(Faces, faceCount);
        MenuHandler::SetMenuMax(Brightness, 6);
        MenuHandler::SetMenuMax(Microphone, 2);
        MenuHandler::SetMenuMax(BoopSensor, 2);
        MenuHandler::SetMenuMax(SpectrumMirror, 2);
        MenuHandler::SetMenuMax(FaceSize, 4);
        MenuHandler::SetMenuMax(Color, 10);
    }

    static void SetDefaultEntries(){
        MenuHandler::SetDefaultValue(Faces, 0);
        MenuHandler::SetDefaultValue(Brightness, 1);
        MenuHandler::SetDefaultValue(Microphone, 1);
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

        if (MenuHandler::Initialize(pin, holdingTime)){
            SetDefaultEntries();
        }

        SetMaxEntries();

        MenuHandler::Begin();
    }

    static Material* GetMaterial(){
        return &textEngine;
    }

    static void Update(){
        float target = (1.0f - float(MenuHandler::GetCurrentMenu() + 1) / float(menuCount)) * size.X + 25.0f;
        float xPosition = dampedSpringX.Calculate(target, 0.25f);
        float menuTarget = MenuHandler::GetCurrentMenu() != 0 ? 0.0f : 100.0f;

        showMenuRatio = dampedSpringShow.Calculate(menuTarget, 0.25f);
        material.Update(float(millis() % 15000) / 15000.0f);

        Menu::GenerateText();
        Menu::SetPosition(Vector2D(-xPosition + fGenMatXMenu.Update() * wiggleRatio, fGenMatYMenu.Update() * wiggleRatio + 40.0f + showMenuRatio));
        Menu::SetRotationOffset(Vector2D(200.0f / 2, 100.0f / 2));
        Menu::SetRotation(fGenMatRMenu.Update());
    }

    static void SetWiggleRatio(float wiggleRatio){
        Menu::wiggleRatio = wiggleRatio;
    }

    static void SetSize(Vector2D size){
        size.X = size.X * menuCount;

        Menu::size = size;

        textEngine.SetSize(size);
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

        line2 += GenerateLine(6, MenuHandler::GetMenuValue(Brightness));
        line2 += UseMicrophone() ? "   on OFF   " : "   ON off   ";
        line2 += UseBoopSensor() ? "   on OFF   " : "   ON off   ";
        line2 += MirrorSpectrumAnalyzer() ? "   on OFF   " : "   ON off   ";
        line2 += GenerateLine(4, GetFaceSize());
        line2 += GenerateLine(10, GetFaceColor());

        textEngine.SetText(1, line2, false);
    }

    static uint8_t GetFaceState(){
        return MenuHandler::GetMenuValue(Faces);
    }

    static uint8_t GetBrightness(){
        return (MenuHandler::GetMenuValue(Brightness) + 1) * 42;
    }

    static uint8_t UseMicrophone(){
        return MenuHandler::GetMenuValue(Microphone);
    }

    static uint8_t UseBoopSensor(){
        return MenuHandler::GetMenuValue(BoopSensor);
    }

    static uint8_t MirrorSpectrumAnalyzer(){
        return MenuHandler::GetMenuValue(SpectrumMirror);
    }

    static uint8_t GetFaceSize(){
        return MenuHandler::GetMenuValue(FaceSize);
    }

    static uint8_t GetFaceColor(){
        return MenuHandler::GetMenuValue(Color);
    }

    static float ShowMenu(){
        return showMenuRatio / 100.0f;
    }
};

RainbowNoise Menu::material;
DampedSpring Menu::dampedSpringX;
DampedSpring Menu::dampedSpringShow;

FunctionGenerator Menu::fGenMatXMenu = FunctionGenerator(FunctionGenerator::Sine, -4.0f, 4.0f, 1.12f);
FunctionGenerator Menu::fGenMatYMenu = FunctionGenerator(FunctionGenerator::Sine, -4.0f, 4.0f, 1.73f);
FunctionGenerator Menu::fGenMatRMenu = FunctionGenerator(FunctionGenerator::Sine, -4.0f, 4.0f, 0.76f);

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
float Menu::wiggleRatio = 1.0f;

//                    111111111111222222222222333333333333444444444444555555555555666666666666777777777777
String Menu::line1 = "               BRIGHT       MIC         BOOP        SPEC        SIZE       COLOR    ";
String Menu::line2 = " a b c d e f   12^45       ON off      on OFF      ON off      12^45      123456|8  ";