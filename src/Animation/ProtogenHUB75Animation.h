#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Objects\Background.h"
#include "..\Morph\NukudeFace.h"
#include "..\Render\Scene.h"
#include "..\Signals\FunctionGenerator.h"
#include "..\Menu\Menu.h"
#include "..\Sensors\BoopSensor.h"

#include "..\Materials\Animated\SpectrumAnalyzer.h"
#include "..\Materials\Animated\RainbowNoise.h"
#include "..\Materials\Animated\RainbowSpiral.h"

#include "..\Materials\MaterialAnimator.h"

#include "AnimationTracks\BlinkTrack.h"

#include "..\Signals\FFTVoiceDetection.h"

#include "..\Sensors\MicrophoneFourier_MAX9814.h"

class ProtogenHUB75Animation : public Animation<3> {
private:
    NukudeFace pM;
    Background background;
    EasyEaseAnimator<20> eEA = EasyEaseAnimator<20>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    
    //Materials
    RainbowNoise rainbowNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    
    RGBColor gradientSpectrum[2] = {RGBColor(5, 162, 232), RGBColor(10, 170, 255)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);
    
    MaterialAnimator<5> materialAnimator;
    MaterialAnimator<2> backgroundMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(200, 100), Vector2D(100, 50), true, true); 

    //Animation controllers
    BlinkTrack<1> blink;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 5.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 6.7f);
    FunctionGenerator fGenMatHue = FunctionGenerator(FunctionGenerator::Triangle, 0.0f, 360.0f, 17.3f);

    FunctionGenerator fGenMatXMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 1.1f);
    FunctionGenerator fGenMatYMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 2.7f);
    FunctionGenerator fGenMatRMenu = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 1.7f);

    BoopSensor boop;

    FFTVoiceDetection<128> voiceDetection;


    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Anger), NukudeFace::Anger, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Sadness), NukudeFace::Sadness, 50, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Surprised), NukudeFace::Surprised, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Doubt), NukudeFace::Doubt, 25, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Frown), NukudeFace::Frown, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookUp), NukudeFace::LookUp, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookDown), NukudeFace::LookDown, 30, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ee), NukudeFace::vrc_v_ee, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ih), NukudeFace::vrc_v_ih, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_dd), NukudeFace::vrc_v_dd, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_rr), NukudeFace::vrc_v_rr, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ch), NukudeFace::vrc_v_ch, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_aa), NukudeFace::vrc_v_aa, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_oh), NukudeFace::vrc_v_oh, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ss), NukudeFace::vrc_v_ss, 2, 0.0f, 1.0f);
        
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::HideBlush), NukudeFace::HideBlush, 30, 1.0f, 0.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(NukudeFace::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(NukudeFace::HideBlush, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(NukudeFace::Sadness, EasyEaseInterpolation::Cosine);
        
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ee, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ih, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_dd, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_rr, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ch, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_aa, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_oh, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ss, EasyEaseInterpolation::Linear);
    }

    void SetMaterialLayers(){
        materialAnimator.SetBaseMaterial(Material::Add, &gradientMat);
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Lighten, &rainbowNoise, 40, 0.35f, 1.0f);//layer 4

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 40, 0.0f, 1.0f);
    }

public:
    ProtogenHUB75Animation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(background.GetObject());
        scene.AddObject(Menu::GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        pM.GetObject()->SetMaterial(&materialAnimator);

        boop.Initialize(5);

        background.GetObject()->SetMaterial(&backgroundMaterial);

        MicrophoneFourier::Initialize(A0, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
        Menu::Initialize(7, 20, 500);//7 is number of faces
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){}

    void Angry(){
        eEA.AddParameterFrame(NukudeFace::Anger, 1.0f);
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
    }

    void Sad(){
        eEA.AddParameterFrame(NukudeFace::Sadness, 1.0f);
        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);
        materialAnimator.AddMaterialFrame(blueMaterial, 0.8f);
    }

    void Surprised(){
        eEA.AddParameterFrame(NukudeFace::Surprised, 1.0f);
        eEA.AddParameterFrame(NukudeFace::HideBlush, 0.0f);
        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }
    
    void Doubt(){
        eEA.AddParameterFrame(NukudeFace::Doubt, 1.0f);
    }
    
    void Frown(){
        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);
    }

    void LookUp(){
        eEA.AddParameterFrame(NukudeFace::LookUp, 1.0f);
    }

    void LookDown(){
        eEA.AddParameterFrame(NukudeFace::LookDown, 1.0f);
    }

    void SpectrumAnalyzerFace(){
        
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            eEA.AddParameterFrame(NukudeFace::vrc_v_ss, MicrophoneFourier::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourier::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourier::GetFourierFiltered(), MicrophoneFourier::GetSampleRate());
        
                eEA.AddParameterFrame(NukudeFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(NukudeFace::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(NukudeFace::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.UH));
                eEA.AddParameterFrame(NukudeFace::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
                eEA.AddParameterFrame(NukudeFace::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(NukudeFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(NukudeFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
            }
        }
    }

    void Update(float ratio) override {
        pM.Reset();
        //menuBackground.GetObject()->Disable();

        float xOffset = fGenMatXMove.Update();
        float yOffset = fGenMatYMove.Update();
        
        Menu::Update();
        float menuRatio = Menu::ShowMenu();


        bool isBooped = Menu::UseBoopSensor() ? boop.isBooped() : 0;
        uint8_t mode = Menu::GetFaceState();//change by button press

        MicrophoneFourier::Update();
        sA.Update(MicrophoneFourier::GetFourierFiltered());
        sA.SetHueAngle(ratio * 360.0f * 4.0f);
        sA.SetMirrorYState(Menu::MirrorSpectrumAnalyzer());
        sA.SetFlipYState(!Menu::MirrorSpectrumAnalyzer());
        
        UpdateFFTVisemes();

        if (isBooped && mode != 6){
            Surprised();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Angry();
            else if (mode == 2) Doubt();
            else if (mode == 3) Frown();
            else if (mode == 4) LookUp();
            else if (mode == 5) Sad();
            else SpectrumAnalyzerFace();
        }

        UpdateKeyFrameTracks();

        pM.SetMorphWeight(NukudeFace::BiggerNose, 1.0f);
        pM.SetMorphWeight(NukudeFace::MoveEye, 1.0f);

        eEA.Update();
        pM.Update();
        
        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();
        backgroundMaterial.Update();


        //gradientMat.HueShift(fGenMatHue.Update());
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, -7.5f));

        uint8_t faceSize = Menu::GetFaceSize();

        float scale = menuRatio * 0.6f + 0.4f;
        float xShift = (1.0f - menuRatio) * 60.0f;
        float yShift = (1.0f - menuRatio) * 20.0f;
        float adjustFacePos = float(4 - faceSize) * 5.0f;
        float adjustFaceX = float(faceSize) * 0.05f;
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(102.5f + xOffset - xShift + adjustFacePos, -22.5f + yOffset + yShift, 600.0f));
        pM.GetObject()->GetTransform()->SetScale(Vector3D(-1.05f + adjustFaceX, 0.585f, 0.8f).Multiply(scale));

        pM.GetObject()->UpdateTransform();
    }
};
