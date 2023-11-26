#pragma once

#include "..\..\Static\SimpleMaterial.h"
#include "..\Overlays\Text\TextEngine.h"
#include "..\..\Material.h"

class Clock : public Material {
private:
    TextEngine<3, 12> tE = TextEngine<3, 12>(false);
    SimpleMaterial mat = SimpleMaterial(RGBColor(255, 255, 255));
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t wDay;
    bool hour24 = false;

public:
    Clock(bool hour24);

    void SetMaterial(Material* material);

    void SetTime(uint8_t hour, uint8_t minute, uint8_t second);

    void SetDate(uint8_t day, uint8_t month, uint8_t year, uint8_t wDay);

    void SetSize(Vector2D size);

    void SetPosition(Vector2D position);

    void SetRotation(float rotation);

    void Update();

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override;
};
