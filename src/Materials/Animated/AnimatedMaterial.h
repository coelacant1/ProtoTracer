#pragma once

#include "..\..\Materials\Material.h"

class AnimatedMaterial : public Material{
public:
    virtual void Update(float ratio);

    virtual Material* GetMaterial();
};
