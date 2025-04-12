#pragma once

template <uint8_t menuCount>
bool MenuHandler<menuCount>::previousState;

template <uint8_t menuCount>
long MenuHandler<menuCount>::previousMillis;

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::inputCount;

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::currentMenu;

template <uint8_t menuCount>
uint16_t MenuHandler<menuCount>::inputStream[4];

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::currentValue[menuCount];

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::maxValue[menuCount];

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::pin;

template <uint8_t menuCount>
void MenuHandler<menuCount>::Begin() {
    previousMillis = millis();
    previousState = false;
}

template <uint8_t menuCount>
void MenuHandler<menuCount>::Update() {
    bool pinState = !digitalRead(pin);
    long timeOn = millis() - previousMillis;

    if (timeOn < 40) return;

    if (!pinState && inputCount > 0 && timeOn > 500) {
        uint32_t mask = 0;
        if (inputStream[0] > 0) mask |= (inputStream[0] < 150 ? 1 : 2) << 0; // 1 2
        if (inputStream[1] > 0) mask |= (inputStream[1] < 150 ? 1 : 2) << 2; // 4 8
        if (inputStream[2] > 0) mask |= (inputStream[2] < 150 ? 1 : 2) << 4; // 16 32
        if (inputStream[3] > 0) mask |= (inputStream[3] < 150 ? 1 : 2) << 6; // 64 128

        uint8_t val;
        switch (mask) {
            case 9:   val = 1;  break; // A: .-
            case 86:  val = 2;  break; // B: -...
            case 102: val = 3;  break; // C: -.-.
            case 22:  val = 4;  break; // D: -..
            case 1:   val = 5;  break; // E: .
            case 101: val = 6;  break; // F: ..-.
            case 26:  val = 7;  break; // G: --.
            case 85:  val = 8;  break; // H: ....
            case 5:   val = 9;  break; // I: ..
            case 169: val = 10; break; // J: .---
            case 38:  val = 11; break; // K: -.-
            case 89:  val = 12; break; // L: .-..
            case 10:  val = 13; break; // M: --
            case 6:   val = 14; break; // N: -.
            case 42:  val = 15; break; // O: ---
            case 105: val = 16; break; // P: .--.
            case 154: val = 17; break; // Q: --.-
            case 25:  val = 18; break; // R: .-.
            case 21:  val = 19; break; // S: ...
            case 2:   val = 20; break; // T: -
            case 37:  val = 21; break; // U: ..-
            case 149: val = 22; break; // V: ...-
            case 41:  val = 23; break; // W: .--
            case 150: val = 24; break; // X: -..-
            case 166: val = 25; break; // Y: -.--
            case 90:  val = 26; break; // Z: --..
            default:  val =  0; break;
        }

        if (val == 20) {
            // T (long press) is used to advance menu, to keep it similar to default menu navigation
            WriteEEPROM(currentMenu, currentValue[currentMenu]);
            currentMenu = (currentMenu + 1) % menuCount;
        } else if (currentMenu > 0) {
            // When in the menu
            switch (val) {
                case 5:
                    // E (short press) is used to advance selection in non-face menu, to keep it similar to default menu navigation
                    currentValue[currentMenu] = (currentValue[currentMenu] + 1) % maxValue[currentMenu];
                    break;
                case 9:
                    // I (2 short presses) is used to go back a selection in non-face menu
                    val = currentValue[currentMenu];
                    if (val == 0) val += maxValue[currentMenu];
                    currentValue[currentMenu] = val - 1;
                    break;
                case 13:
                    // M (2 long presses) is used to go back a menu
                    WriteEEPROM(currentMenu, currentValue[currentMenu]);
                    currentMenu = (currentMenu - 1) % menuCount;
                    break;
                case 15:
                    // O (3 long presses) is used to exit the menu
                    WriteEEPROM(currentMenu, currentValue[currentMenu]);
                    currentMenu = 0;
                    break;
            }
        } else {
            if (maxValue[currentMenu] > 0) val = val % maxValue[currentMenu]; // If max is set, wrap value
            currentValue[currentMenu] = val;
        }

        std::fill_n(inputStream, inputCount, 0);
        inputCount = 0;
        previousState = false;
        return;
    }

    if (pinState == previousState) return;

    if (!pinState && inputCount < 4) {
        inputStream[inputCount] = timeOn;
        inputCount += 1;
    }

    previousMillis = millis();
    previousState = pinState;
}

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::ReadEEPROM(uint16_t index) {
    return EEPROM.read(index);
}

template <uint8_t menuCount>
void MenuHandler<menuCount>::WriteEEPROM(uint16_t index, uint8_t value) {
    EEPROM.write(index, value);
}

template <uint8_t menuCount>
bool MenuHandler<menuCount>::Initialize(uint8_t pin, uint16_t _holdingTime) {
    MenuHandler::pin = pin;
    MenuHandler::previousState = false;

    pinMode(pin, INPUT_PULLUP);

    for (uint8_t i = 0; i < menuCount; i++) {
        currentValue[i] = ReadEEPROM(i);
    }

    return ReadEEPROM(menuCount + 1) != 255;
}

template <uint8_t menuCount>
void MenuHandler<menuCount>::SetDefaultValue(uint16_t menu, uint8_t value) {
    if (menu >= menuCount) return;

    currentValue[menu] = value;

    WriteEEPROM(menu, value);
}

template <uint8_t menuCount>
void MenuHandler<menuCount>::SetInitialized() {
    WriteEEPROM(menuCount + 1, 0);
}

template <uint8_t menuCount>
void MenuHandler<menuCount>::SetMenuMax(uint8_t menu, uint8_t maxValue) {
    if (menu >= menuCount) return;

    MenuHandler::maxValue[menu] = maxValue;
}

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::GetMenuValue(uint8_t menu) {
    return currentValue[menu];
}

template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::GetCurrentMenu() {
    return currentMenu;
}
