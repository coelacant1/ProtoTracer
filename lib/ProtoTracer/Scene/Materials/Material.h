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

    virtual RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) = 0;
  
};
