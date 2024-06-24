#include "Menu.h"

// Define static member variables
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
float Menu::wiggleSpeedX = 1.0f;
float Menu::wiggleSpeedY = 1.0f;
float Menu::wiggleSpeedR = 1.0f;
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
uint8_t Menu::fanSpeed = 0;

//                    111111111111222222222222333333333333444444444444555555555555666666666666777777777777888888888888999999999999111111111111222222222222333333333333444444444444
String Menu::line1 = "               BRIGHT    SDE BRIGHT     MIC      MIC LEVEL      BOOP        SPEC        SIZE       COLOR       HUE F       HUE B       EFFECT    FAN SPEED  ";
String Menu::line2 = " a b c d e f   12^45       12^45       ON off     123456|8     on OFF      ON off      12^45      123456|8    123456|8    123456|8    123456|8    123456|8  ";

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

void Menu::SetMaxEntries() {
    // Define your max entries here
#ifdef MORSEBUTTON
    MenuHandler<menuCount>::SetMenuMax(Faces, 27); // 1 unset + 26 letters
#else
    MenuHandler<menuCount>::SetMenuMax(Faces, faceCount);
#endif
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
    MenuHandler<menuCount>::SetMenuMax(FanSpeed, 10);
}

void Menu::SetDefaultEntries() {
    // Define your default entries here
    MenuHandler<menuCount>::SetDefaultValue(Faces, 0);
    MenuHandler<menuCount>::SetDefaultValue(Bright, 3);
    MenuHandler<menuCount>::SetDefaultValue(AccentBright, 5);
    MenuHandler<menuCount>::SetDefaultValue(Microphone, 1);
    MenuHandler<menuCount>::SetDefaultValue(MicLevel, 5);
    MenuHandler<menuCount>::SetDefaultValue(BoopSensor, 1);
    MenuHandler<menuCount>::SetDefaultValue(SpectrumMirror, 1);
    MenuHandler<menuCount>::SetDefaultValue(FaceSize, 7);
    MenuHandler<menuCount>::SetDefaultValue(Color, 0);
    MenuHandler<menuCount>::SetDefaultValue(HueF, 0);
    MenuHandler<menuCount>::SetDefaultValue(HueB, 0);
    MenuHandler<menuCount>::SetDefaultValue(EffectS, 0);
    MenuHandler<menuCount>::SetDefaultValue(FanSpeed, 0);

    MenuHandler<menuCount>::SetInitialized();
}

void Menu::Initialize(uint8_t faceCount, uint8_t pin, uint16_t holdingTime, Vector2D size) {
    Menu::faceCount = faceCount;

    dampedSpringX.SetConstants(1.0f, 0.5f);
    dampedSpringShow.SetConstants(1.0f, 0.5f);

    SetSize(size);

    textEngine.SetMaterial(&material);
    textEngine.SetPositionOffset(position);
    textEngine.SetBlinkTime(200);

#ifndef NEOTRELLISMENU
    if (!MenuHandler<menuCount>::Initialize(pin, holdingTime)) {
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

void Menu::Initialize(uint8_t faceCount, Vector2D size) {
    Menu::faceCount = faceCount;

    dampedSpringX.SetConstants(1.0f, 0.5f);
    dampedSpringShow.SetConstants(1.0f, 0.5f);

    SetSize(size);

    textEngine.SetMaterial(&material);
    textEngine.SetPositionOffset(position);
    textEngine.SetBlinkTime(200);

#ifdef NEOTRELLISMENU
    if (!MenuHandler<menuCount>::Initialize()) {
        SetDefaultEntries();
    }

    isSecondary = false;
#else
    isSecondary = true;
#endif

    SetMaxEntries();
}

Material* Menu::GetMaterial() {
    return &textEngine;
}

Effect* Menu::GetEffect() {
    switch (GetEffectS()) {
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
            return &passthrough;//&magnet;
            break;
        case 6:
            return &passthrough;//&fisheye;
            break;
        case 7:
            return &passthrough;//&blurH;
            break;
        case 8:
            return &passthrough;//&blurV;
            break;
        case 9:
            return &passthrough;//&blurR
        default:
            return &passthrough;
            break;
    }
}

uint8_t Menu::GetCurrentMenu(){
    return MenuHandler<menuCount>::GetCurrentMenu();
}

uint8_t Menu::GetCurrentMenuValue(){
    return MenuHandler<menuCount>::GetMenuValue(GetCurrentMenu());
}

void Menu::SetCurrentMenu(uint8_t currentMenu) {
    Menu::currentMenu = currentMenu;
}

void Menu::Update(float ratio) {
#if defined NEOTRELLISMENU || defined MORSEBUTTON
    MenuHandler<menuCount>::Update();
#endif

    float target = 0.0f;
    float menuTarget = 0.0f;

    if (isSecondary) {
        target = (1.0f - float(currentMenu + 1) / float(menuCount)) * size.X + 25.0f;
        menuTarget = currentMenu != 0 ? 0.0f : 100.0f;
    } else {
        target = (1.0f - float(MenuHandler<menuCount>::GetCurrentMenu() + 1) / float(menuCount)) * size.X + 25.0f;
        menuTarget = MenuHandler<menuCount>::GetCurrentMenu() != 0 ? 0.0f : 100.0f;
    }

    float xPosition = dampedSpringX.Calculate(target, 0.25f);

    showMenuRatio = dampedSpringShow.Calculate(menuTarget, 0.25f);
    material.Update(ratio);

    float ratioX = sinf(ratio * Mathematics::MPI * 2.0f * wiggleSpeedX) * 4.0f;
    float ratioY = sinf(ratio * Mathematics::MPI * 2.0f * wiggleSpeedY) * 4.0f;
    float ratioR = sinf(ratio * Mathematics::MPI * 2.0f * wiggleSpeedR) * 4.0f;

    Menu::SetPosition(Vector2D(-xPosition + ratioX * wiggleRatio, ratioY * wiggleRatio + 40.0f + showMenuRatio * 3.0f));
    Menu::SetRotationOffset(Vector2D(200.0f / 2, 100.0f / 2));
    Menu::SetRotation(ratioR);

    Menu::GenerateText();

    if (GetFaceState() != previousMenu) {
        effectChange.RestartTime();
        previousMenu = GetFaceState();
    }

    effectChange.Update();

    GetEffect()->SetRatio(effectStrength);
}

void Menu::SetWiggleRatio(float wiggleRatio) {
    Menu::wiggleRatio = wiggleRatio;
}

void Menu::SetWiggleSpeed(float wiggleSpeedX, float wiggleSpeedY, float wiggleSpeedR) {
    Menu::wiggleSpeedX = wiggleSpeedX;
    Menu::wiggleSpeedY = wiggleSpeedY;
    Menu::wiggleSpeedR = wiggleSpeedR;
}

void Menu::SetSize(Vector2D size) {
    size.X = size.X * menuCount;

    Menu::size = size;

    textEngine.SetSize(size);
}

Vector2D Menu::GetPosition() {
    return Menu::position;
}

void Menu::SetPosition(Vector2D position) {
    Menu::position = position + positionOffset;
    textEngine.SetPositionOffset(Menu::position);
}

void Menu::SetPositionOffset(Vector2D positionOffset) {
    Menu::positionOffset = positionOffset;
}

void Menu::SetRotationOffset(Vector2D rotationOffset) {
    Menu::rotationOffset = rotationOffset;
    textEngine.SetRotationOffset(rotationOffset);
}

float Menu::GetRotation() {
    return Menu::rotation;
}

void Menu::SetRotation(float rotation) {
    Menu::rotation = rotation;
    textEngine.SetRotationAngle(rotation);
}

char Menu::IntToBlink(char value) {
    switch (value) {
        case '0':
            return '[';
        case '1':
            return '\\';
        case '2':
            return ']';
        case '3':
            return '^';
        case '4':
            return '_';
        case '5':
            return '`';
        case '6':
            return '{';
        case '7':
            return '|';
        case '8':
            return '}';
        case '9':
            return '~';
        default:
            return ' ';
    }
}

String Menu::GenerateLine(uint8_t options, uint8_t selection) {
    String text;
    uint8_t spacing = options >= 5 ? 3 : (menuLength - options) / 2;

    for (uint8_t i = 0; i < spacing; i++) {
        text += " ";
    }

    for (uint8_t i = 0; i < 5; i++) {
        if (selection < 5 && i < options) {
            char value = '0' + i;

            if (i == selection) {
                text += IntToBlink(value);
            } else {
                text += value;
            }
        } else if (selection >= 5 && i + 5 < options) {
            char value = '5' + i;

            if (i + 5 == selection) {
                text += IntToBlink(value);
            } else {
                text += value;
            }
        }
    }

    while (text.length() < menuLength) {
        text += " ";
    }

    return text;
}

void Menu::GenerateText() {
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
    line2 += GenerateLine(10, GetFanSpeed());

    textEngine.SetText(1, line2, false);
}

void Menu::SetFaceState(uint8_t faceState) {
    Menu::faceState = faceState;
}

uint8_t Menu::GetFaceState() {
    if (isSecondary) return faceState;
    else return MenuHandler<menuCount>::GetMenuValue(Faces);
}

void Menu::SetBrightness(uint8_t bright) {
    Menu::bright = bright;
}

uint8_t Menu::GetBrightness() {
    if (isSecondary) return bright;
    else return MenuHandler<menuCount>::GetMenuValue(Bright);
}

void Menu::SetAccentBrightness(uint8_t accentBright) {
    Menu::accentBright = accentBright;
}

uint8_t Menu::GetAccentBrightness() {
    if (isSecondary) return accentBright;
    else return MenuHandler<menuCount>::GetMenuValue(AccentBright);
}

void Menu::SetUseMicrophone(uint8_t microphone) {
    Menu::microphone = microphone;
}

uint8_t Menu::UseMicrophone() {
    if (isSecondary) return microphone;
    else return MenuHandler<menuCount>::GetMenuValue(Microphone);
}

void Menu::SetMicLevel(uint8_t micLevel) {
    Menu::micLevel = micLevel;
}

uint8_t Menu::GetMicLevel() {
    if (isSecondary) return micLevel;
    else return MenuHandler<menuCount>::GetMenuValue(MicLevel);
}

void Menu::SetUseBoopSensor(uint8_t boopSensor) {
    Menu::boopSensor = boopSensor;
}

uint8_t Menu::UseBoopSensor() {
    if (isSecondary) return boopSensor;
    else return MenuHandler<menuCount>::GetMenuValue(BoopSensor);
}

void Menu::SetMirrorSpectrumAnalyzer(uint8_t spectrumMirror) {
    Menu::spectrumMirror = spectrumMirror;
}

uint8_t Menu::MirrorSpectrumAnalyzer() {
    if (isSecondary) return spectrumMirror;
    else return MenuHandler<menuCount>::GetMenuValue(SpectrumMirror);
}

void Menu::SetFaceSize(uint8_t faceSize) {
    Menu::faceSize = faceSize;
}

uint8_t Menu::GetFaceSize() {
    if (isSecondary) return faceSize;
    else return MenuHandler<menuCount>::GetMenuValue(FaceSize);
}

void Menu::SetFaceColor(uint8_t color) {
    Menu::color = color;
}

uint8_t Menu::GetFaceColor() {
    if (isSecondary) return color;
    else return MenuHandler<menuCount>::GetMenuValue(Color);
}

void Menu::SetHueF(uint8_t huef) {
    Menu::huef = huef;
}

uint8_t Menu::GetHueF() {
    if (isSecondary) return huef;
    else return MenuHandler<menuCount>::GetMenuValue(HueF);
}

void Menu::SetHueB(uint8_t hueb) {
    Menu::hueb = hueb;
}

uint8_t Menu::GetHueB() {
    if (isSecondary) return hueb;
    else return MenuHandler<menuCount>::GetMenuValue(HueB);
}

void Menu::SetEffectS(uint8_t effect) {
    Menu::effect = effect;
}

uint8_t Menu::GetEffectS() {
    if (isSecondary) return effect;
    else return MenuHandler<menuCount>::GetMenuValue(EffectS);
}

void Menu::SetFanSpeed(uint8_t fanSpeed) {
    Menu::fanSpeed = fanSpeed;
}

uint8_t Menu::GetFanSpeed() {
    if (isSecondary) return fanSpeed;
    else return MenuHandler<menuCount>::GetMenuValue(FanSpeed);
}

float Menu::ShowMenu() {
    return showMenuRatio / 100.0f;
}
