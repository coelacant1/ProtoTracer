#pragma once

#include "Animation.h"
#include "..\Objects\SolidCube.h"
#include "..\Materials\DepthMaterial.h"
#include "..\Materials\LightMaterial.h"
#include "..\Math\FunctionGenerator.h"

//#include "Flash\Images\CoelaToot.h"
//#include "Flash\ImageSequences\Hex2.h"
#include "..\Materials\StripeMaterial.h"
#include "..\Materials\SpiralMaterial.h"
#include "..\Materials\CombineMaterial.h"

//#include "Flash\ImageSequences\Rainbow.h"

class FullScreenAnimation : public Animation{
private:
    SolidCube cube;
    FunctionGenerator fGenSelection = FunctionGenerator(FunctionGenerator::Triangle, 0.0f, 1.0f, 20.0f);
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 1.5f);
    FunctionGenerator fGenMatSize = FunctionGenerator(FunctionGenerator::Sine, 400.0f, 550.0f, 2.1f);
    FunctionGenerator fGenMatRot = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 3.2f);
    FunctionGenerator fGenMatWidth = FunctionGenerator(FunctionGenerator::Sine, 150.0f, 500.0f, 4.0f);
    FunctionGenerator fGenMatPeriod = FunctionGenerator(FunctionGenerator::Sine, 200.0f, 500.0f, 6.3f);
    FunctionGenerator fGenMatAmplitude = FunctionGenerator(FunctionGenerator::Sine, -100.0f, 100.0f, 2.7f);
    FunctionGenerator fGenMatBend = FunctionGenerator(FunctionGenerator::Sine, 0.1f, 1.0f, 6.7f);
    FunctionGenerator fGenMatOpacity = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 0.5f);

    //Hex2Sequence gif = Hex2Sequence(Vector2D(500, 500), Vector2D(0, 0), 30);
    //RainbowSequence gif2 = RainbowSequence(Vector2D(300, 300), Vector2D(0, 0), 30);
    RGBColor spectrum1[6] = {RGBColor(255, 255, 0), RGBColor(0, 0, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 0), RGBColor(255, 0, 255), RGBColor(0, 0, 0)};
    RGBColor spectrum2[6] = {RGBColor(255, 0, 0), RGBColor(0, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 0), RGBColor(0, 0, 255), RGBColor(0, 0, 0)};
    RGBColor spectrum3[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    StripeMaterial stripe1 = StripeMaterial(6, spectrum1, 200.0f, 160.0f, 20.0f);
    StripeMaterial stripe2 = StripeMaterial(6, spectrum2, 200.0f, 160.0f, 20.0f);
    SpiralMaterial spiral = SpiralMaterial(6, spectrum3, 2.0f, 7.0f);
    //Material* materials[2] = {&stripe1, &spiral};

    //CombineMaterial material = CombineMaterial(CombineMaterial::Subtract, 2, materials);

public:
    FullScreenAnimation() : Animation(1) {
        scene->AddObject(cube.GetObject());
        
        cube.GetObject()->SetMaterial(&stripe1);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    void Reset(){
        //gif.Reset();
    }

    void Update(float ratio) override {
        float shift = fGenMatPos.Update();
        //float size = fGenMatSize.Update();
        //float rotate = fGenMatRot.Update();

        //gif.SetPosition(Vector2D(0.0f, 135.0f));
        //gif.SetSize(Vector2D(-size, size));
        //gif.SetRotation(15.0f + rotate);
        //gif.Update();

        //gif2.SetPosition(Vector2D(0.0f + shift, 135.0f + shift));
        //gif2.SetSize(Vector2D(-size, size));
        //gif2.SetRotation(15.0f + rotate);
        //gif2.Update();

        //material.SetFirstLayerOpacity(fGenMatOpacity.Update());
        
        stripe1.SetStripeWidth(fGenMatWidth.Update());
        stripe1.SetWavePeriod(fGenMatPeriod.Update());
        stripe1.SetWaveAmplitude(fGenMatAmplitude.Update());
        stripe1.SetRotationAngle(ratio * 360.0f);
        stripe1.SetPositionOffset(Vector2D(shift, shift));
        /*
        stripe2.SetStripeWidth(fGenMatWidth.Update());
        stripe2.SetWavePeriod(fGenMatPeriod.Update());
        stripe2.SetWaveAmplitude(-fGenMatAmplitude.Update());
        stripe2.SetRotationAngle((1.0f - ratio) * 360.0f);
        stripe2.SetPositionOffset(Vector2D(-shift, -shift));

        spiral.SetBend(fGenMatBend.Update());
        spiral.SetRotationAngle((1.0f - ratio) * 720.0f);
        spiral.SetPositionOffset(Vector2D(0, 135.0f));
        */

        cube.GetObject()->ResetVertices();
        cube.GetObject()->GetTransform()->SetScale(Vector3D(1000, 1000, 1));
        cube.GetObject()->UpdateTransform();
    }
};
