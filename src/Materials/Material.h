#pragma once

#include "RGBColor.h"
#include "..\Math\Vector3D.h"

class Material{
public:
    virtual RGBColor GetRGB(Vector3D position, Vector3D normal) = 0;
  
};
