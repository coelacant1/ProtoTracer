#pragma once

template <typename T>
class Color {
public:
    virtual Color(T R, T G, T B) = 0;

    virtual ~Color() {}

    virtual void SetColor(T R, T G, T B) = 0;

    virtual Color Scale(T maxBrightness) = 0;

    virtual Color Add(T value) = 0;

    virtual Color HueShift(float hueDeg) = 0;

    virtual Color InterpolateColors(Color color1, Color color2, float ratio) = 0;

    virtual String ToString() = 0;
};