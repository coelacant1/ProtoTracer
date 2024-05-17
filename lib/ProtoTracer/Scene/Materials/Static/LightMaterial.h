#pragma once

#include "../Material.h"
#include "../../../Utils/Math/Vector2D.h"
#include "../../../Renderer/Lights/Light.h"

template<size_t lightCount>
class LightMaterial : public Material {
private:
    Light lights[lightCount];

public:
    LightMaterial();

    Light* GetLights();
    uint8_t GetLightCount();

    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};

#include "LightMaterial.tpp"