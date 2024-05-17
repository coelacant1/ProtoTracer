#pragma once

#include "Effect.h"
#include "../../Utils/Signals/FunctionGenerator.h"
#include "../../Utils/Math/Vector2D.h"

class Fisheye : public Effect {
private:
    Vector2D offset = Vector2D(0.0f, 0.0f);
    float amplitude;
    FunctionGenerator fGenSize = FunctionGenerator(FunctionGenerator::Sine, 1.0f, 48.0f, 2.3f);
    FunctionGenerator fGenX = FunctionGenerator(FunctionGenerator::Sine, -96.0f, 96.0f, 2.7f);
    FunctionGenerator fGenY = FunctionGenerator(FunctionGenerator::Sine, -96.0f, 96.0f, 1.7f);
    FunctionGenerator fGenWarp = FunctionGenerator(FunctionGenerator::Sine, 1.0f, 100.0f, 3.7f);

public:
    Fisheye(float amplitude = 0.5f);

    void SetPosition(Vector2D offset);

    void SetAmplitude(float amplitude);

    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
