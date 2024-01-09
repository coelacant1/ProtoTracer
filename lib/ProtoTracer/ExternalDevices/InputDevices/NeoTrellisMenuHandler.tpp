#pragma once

template <uint8_t menuCount>
Adafruit_NeoTrellis MenuHandler<menuCount>::trellis;
template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::currentMenu;
template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::currentSetting = 0;
template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::currentValue[menuCount];
template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::maxValue[menuCount];
template <uint8_t menuCount>
uint8_t MenuHandler<menuCount>::faceChoices = 0;
template <uint8_t menuCount>
bool MenuHandler<menuCount>::menuActive = false;
template <uint8_t menuCount>
bool MenuHandler<menuCount>::didBegin = false;

template <uint8_t menuCount>
uint32_t MenuHandler<menuCount>::Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return trellis.pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return trellis.pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
        WheelPos -= 170;
        return trellis.pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}

template <uint8_t menuCount>
TrellisCallback MenuHandler<menuCount>::blink(keyEvent evt) {
    if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
        trellis.pixels.setPixelColor(evt.bit.NUM, Wheel(map(uint16_t(evt.bit.NUM), uint16_t(0), trellis.pixels.numPixels(), uint16_t(0), uint16_t(255))));

        if (evt.bit.NUM < 8) {  // Set face on the current page
            currentMenu = 0;
            currentValue[0] = evt.bit.NUM + 8 * faceChoices;
        } else if (evt.bit.NUM >= 8 && evt.bit.NUM < 12) {  // Set face page
            currentMenu = 0;
            faceChoices = evt.bit.NUM - 8;
        } else if (evt.bit.NUM == 12) {
            menuActive = !menuActive;

            if (menuActive) {
                currentSetting = currentSetting == 0 ? 1 : currentSetting;
                currentMenu = currentSetting;
            } else {
                WriteEEPROM(currentMenu, currentValue[currentSetting]);

                currentMenu = 0;
            }
        } else if (evt.bit.NUM == 13) {  // Change current menu forward
            WriteEEPROM(currentMenu, currentValue[currentSetting]);

            currentSetting = currentSetting + 1 > menuCount ? menuCount : currentSetting + 1;
            currentMenu = currentSetting;
        } else if (evt.bit.NUM == 14) {  // Change current menu backward
            WriteEEPROM(currentMenu, currentValue[currentSetting]);

            currentSetting = currentSetting - 1 == 0 ? 1 : currentSetting - 1;
            currentMenu = currentSetting;
        } else if (evt.bit.NUM == 15) {
            currentValue[currentSetting] += 1;
            if (currentValue[currentSetting] >= maxValue[currentSetting]) currentValue[currentSetting] = 0;
        }
    } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
        trellis.pixels.setPixelColor(evt.bit.NUM, 0);
    }

    trellis.pixels.show();

    return 0;
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
void MenuHandler<menuCount>::ResetI2CBus() {
    Wire.end();    // Disable the I2C hardware
    delay(10);     // Wait a bit
    Wire.begin();  // Re-enable the I2C hardware
}

template <uint8_t menuCount>
void MenuHandler<menuCount>::Update() {
    unsigned long cmdTime = millis();

    if (didBegin) {
        trellis.read();
    }

    if (millis() - cmdTime > 250) {
        // Timeout occurred
        ResetI2CBus();
    }
}

template <uint8_t menuCount>
bool MenuHandler<menuCount>::Initialize() {
    Wire.setClock(50000);  // for longer-range transmissions

    if (!trellis.begin()) {
        Serial.println("Could not start Trellis, check wiring?");
        didBegin = false;
    } else {
        // Activate all keys and set callbacks
        for (int i = 0; i < NEO_TRELLIS_NUM_KEYS; i++) {
            trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
            trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
            trellis.registerCallback(i, blink);
        }

        didBegin = true;

        Serial.println("NeoPixel Trellis started");
    }

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
