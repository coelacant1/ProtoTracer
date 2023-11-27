#include "Clock.h"

Clock::Clock(bool hour24) {
    this->hour24 = hour24;

    tE.SetMaterial(&mat);

    tE.SetBlinkTime(200);
}

void Clock::SetMaterial(Material* material) {
    tE.SetMaterial(material);
}

void Clock::SetTime(uint8_t hour, uint8_t minute, uint8_t second) {
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

void Clock::SetDate(uint8_t day, uint8_t month, uint8_t year, uint8_t wDay) {
    this->day = day;
    this->month = month;
    this->year = year;
    this->wDay = wDay;
}

void Clock::SetSize(Vector2D size) {
    tE.SetSize(size);
}

void Clock::SetPosition(Vector2D position) {
    tE.SetPositionOffset(position);
}

void Clock::SetRotation(float rotation) {
    tE.SetRotationAngle(rotation);
}

void Clock::Update() {
    String secondString = second < 10 ? "0" + String(second) : String(second);
    String minuteString = minute < 10 ? "0" + String(minute) : String(minute);
    String hourMinSec = String(hour) + ":" + minuteString + ":" + secondString;
    String date = String(month) + "/" + String(day) + "/" + String(year);

    String dayOfWeek;

    switch (wDay) {
        case 0:
            dayOfWeek = "SATURDAY";
            break;
        case 1:
            dayOfWeek = "SUNDAY";
            break;
        case 2:
            dayOfWeek = "MONDAY";
            break;
        case 3:
            dayOfWeek = "TUESDAY";
            break;
        case 4:
            dayOfWeek = "WEDNESDAY";
            break;
        case 5:
            dayOfWeek = "THURSDAY";
            break;
        case 6:
            dayOfWeek = "FRIDAY";
            break;
        default:
            dayOfWeek = "BROKEN";
            break;
    }

    tE.SetText(0, hourMinSec, false);
    tE.SetText(1, date, false);
    tE.SetText(2, dayOfWeek, false);
}

RGBColor Clock::GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) {
    return tE.GetRGB(position, normal, uvw);
}
