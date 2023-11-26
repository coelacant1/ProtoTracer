#pragma once

#include <Arduino.h>
#include "Characters.h"
#include "..\..\..\Material.h"
#include "..\..\..\Static\SimpleMaterial.h"
#include "..\..\..\..\..\Utils\Math\Mathematics.h"
#include "..\..\..\..\..\Utils\Math\Rotation.h"
#include "..\..\..\..\..\Utils\Math\Vector2D.h"
#include "..\..\..\..\..\Utils\Math\Vector3D.h"

template<uint8_t lineCount, uint8_t characterWidth>
class TextEngine : public Material {
private:
    SimpleMaterial baseMaterial = SimpleMaterial(RGBColor(255, 255, 255));
    Material* material = &baseMaterial;
    RGBColor white = RGBColor(255, 255, 255);
    RGBColor black = RGBColor(0, 0, 0);
    Vector2D size;
    Vector2D positionOffset;
    Vector2D rotationOffset;
    float rotationAngle = 0.0f;//rotate input xyPosition
    char lines[lineCount][characterWidth];
    uint16_t blinkTime;
    bool isEfficient = false;

public:
    TextEngine(bool isEfficient = false);

    TextEngine(Vector2D size, Vector2D position, uint16_t blinkTime, bool isEfficient = false);

    void SetMaterial(Material* material);

    void SetSize(Vector2D size);

    void SetPositionOffset(Vector2D positionOffset);

    void SetRotationOffset(Vector2D rotationOffset);

    void SetRotationAngle(float rotationAngle);

    void SetBlinkTime(uint16_t blinkTime);

    void SetText(uint8_t line, String value, bool centerText = false);

    void ClearText();

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override;
};

#include "TextEngine.tpp"
