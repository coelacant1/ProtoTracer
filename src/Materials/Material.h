#pragma once

#include "RGBColor.h"
#include "..\Math\Vector3D.h"

class Material{
public:
    enum Method{
        Add,
        Subtract,
        Multiply,
        Divide,
        Darken,
        Lighten,
        Screen,
        Overlay,
        SoftLight,
        Replace
    };

    virtual RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) = 0;
  
};
