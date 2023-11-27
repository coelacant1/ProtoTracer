#pragma once

#include "..\..\Utils\RGBColor.h"
#include "..\..\Utils\Math\Vector3D.h"

class Material{
public:
    enum Method{
        Base,
        Add,
        Subtract,
        Multiply,
        Divide,
        Darken,
        Lighten,
        Screen,
        Overlay,
        SoftLight,
        Replace,
        EfficientMask,
        Bypass
    };

    virtual RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) = 0;
  
};
