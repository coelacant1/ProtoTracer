#pragma once

#include "../Material.h"
#include "../Static/GradientMaterial.h"
#include "../../../Physics/Utils/BouncePhysics.h"
#include "../../../Utils/Math/Mathematics.h"

class AudioReactiveGradient : public Material {
private:
    BouncePhysics* bPhy[128];
    Vector2D size;
    Vector2D offset;
    float angle = 0.0f;
    float hueAngle = 0.0f;
    float radius = 0.0f;
    uint8_t colors;
    float* data;
    float bounceData[128];
    uint8_t bins = 128;
    bool bounce = false;
    bool circular = false;

    RGBColor rainbowSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    GradientMaterial<6> gM = GradientMaterial<6>(rainbowSpectrum, 1.0f, false);

    Material* material;

public:
    AudioReactiveGradient(Vector2D size, Vector2D offset, bool bounce = false, bool circular = false);
    ~AudioReactiveGradient();

    void SetMaterial(Material* material);
    float* GetFourierData();
    void SetSize(Vector2D size);
    void SetPosition(Vector2D offset);
    void SetRotation(float angle);
    void SetHueAngle(float hueAngle);
    void SetRadius(float radius);
    void Update(float* readData);

    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
