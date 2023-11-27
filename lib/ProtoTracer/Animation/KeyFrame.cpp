#include "KeyFrame.h"

KeyFrame::KeyFrame() {}

KeyFrame::KeyFrame(float time, float value) {
    this->Time = time;
    this->Value = value;
}

void KeyFrame::Set(float time, float value) {
    this->Time = time;
    this->Value = value;
}
