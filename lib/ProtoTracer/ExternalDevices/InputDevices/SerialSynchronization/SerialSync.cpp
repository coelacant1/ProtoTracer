#include "SerialSync.h"

SerialTransfer SerialSync::dataTransfer;
SerialSync::Data SerialSync::data;

void SerialSync::Initialize() {
    Serial4.begin(115200);
    dataTransfer.begin(Serial4, false);  // _debug = true
}

float SerialSync::GetRatio() {
    return data.ratio;
}

uint8_t SerialSync::GetMode() {
    return data.mode;
}

float SerialSync::GetMouthMove() {
    return data.mouthMove;
}

void SerialSync::Read() {
    if (dataTransfer.available()) {
        uint16_t receiveSize = 0;
        receiveSize = dataTransfer.rxObj(data, receiveSize);
    }
}

void SerialSync::SetRatio(float ratio) {
    data.ratio = ratio;
}

void SerialSync::SetMode(uint8_t mode) {
    data.mode = mode;
}

void SerialSync::SetMouthMove(float ratio) {
    data.mouthMove = ratio;
}

void SerialSync::Send() {
    uint16_t sendSize = 0;
    sendSize = dataTransfer.txObj(data, sendSize);
    dataTransfer.sendData(sendSize);
}

void SerialSync::SetFaceState(uint8_t faceState) {
    data.faceState = faceState;
}

uint8_t SerialSync::GetFaceState() {
    return data.faceState;
}

void SerialSync::SetBrightness(uint8_t bright) {
    data.bright = bright;
}

uint8_t SerialSync::GetBrightness() {
    return data.bright;
}

void SerialSync::SetAccentBrightness(uint8_t accentBright) {
    data.accentBright = accentBright;
}

uint8_t SerialSync::GetAccentBrightness() {
    return data.accentBright;
}

void SerialSync::SetUseMicrophone(uint8_t microphone) {
    data.microphone = microphone;
}

uint8_t SerialSync::UseMicrophone() {
    return data.microphone;
}

void SerialSync::SetMicLevel(uint8_t micLevel) {
    data.micLevel = micLevel;
}

uint8_t SerialSync::GetMicLevel() {
    return data.micLevel;
}

void SerialSync::SetUseBoopSensor(uint8_t boopSensor) {
    data.boopSensor = boopSensor;
}

uint8_t SerialSync::UseBoopSensor() {
    return data.boopSensor;
}

void SerialSync::SetMirrorSpectrumAnalyzer(uint8_t spectrumMirror) {
    data.spectrumMirror = spectrumMirror;
}

uint8_t SerialSync::MirrorSpectrumAnalyzer() {
    return data.spectrumMirror;
}

void SerialSync::SetFaceSize(uint8_t faceSize) {
    data.faceSize = faceSize;
}

uint8_t SerialSync::GetFaceSize() {
    return data.faceSize;
}

void SerialSync::SetFaceColor(uint8_t color) {
    data.color = color;
}

uint8_t SerialSync::GetFaceColor() {
    return data.color;
}

void SerialSync::SetCurrentMenu(uint8_t currentMenu) {
    data.currentMenu = currentMenu;
}

uint8_t SerialSync::GetCurrentMenu() {
    return data.currentMenu;
}

void SerialSync::SetDead(bool dead) {
    data.dead = dead;
}

bool SerialSync::GetDead() {
    return data.dead;
}

void SerialSync::SetBoop(bool boop) {
    data.boop = boop;
}

bool SerialSync::GetBoop() {
    return data.boop;
}
