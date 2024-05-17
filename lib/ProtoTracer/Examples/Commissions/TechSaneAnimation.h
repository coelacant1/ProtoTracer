#pragma once

#include "../Animation.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Morph/NukudeFace.h"
#include "../../Morph/TechSane.h"
#include "../../Morph/TechSaneM.h"
#include "../../Render/Scene.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Menu/Menu.h"
#include "../../Sensors/BoopSensor.h"

#include "../../Materials/Animated/RainbowNoise.h"
#include "../../Materials/Animated/RainbowSpiral.h"
#include "../../Materials/Animated/FlowNoise.h"
#include "../../Materials/Animated/SpectrumAnalyzer.h"
#include "../../Materials/Animated/AudioReactiveGradient.h"
#include "../../Materials/Animated/Oscilloscope.h"

#include "../../Materials/MaterialAnimator.h"

#include "../AnimationTracks/BlinkTrack.h"

#include "../../Signals/FFTVoiceDetection.h"

#include "../../Sensors/MicrophoneFourier_MAX9814.h"

class TechSaneAnimation : public Animation<4> {
private:
    NukudeFace pM;
    TechSane tS;
    TechSaneM tSM;
    Background background;
    EasyEaseAnimator<25> eEA = EasyEaseAnimator<25>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    
    //Materials
    RainbowNoise rainbowNoise;
    FlowNoise flowNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial orangeMaterial = SimpleMaterial(RGBColor(255, 165, 0));
    SimpleMaterial whiteMaterial = SimpleMaterial(RGBColor(255, 255, 255));
    SimpleMaterial greenMaterial = SimpleMaterial(RGBColor(0, 255, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    SimpleMaterial yellowMaterial = SimpleMaterial(RGBColor(255, 255, 0));
    SimpleMaterial purpleMaterial = SimpleMaterial(RGBColor(255, 0, 255));
    
    RGBColor gradientSpectrum[2] = {RGBColor(255, 0, 0), RGBColor(0, 0, 255)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);
    
    MaterialAnimator<10> materialAnimator;
    MaterialAnimator<4> backgroundMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(200, 100), Vector2D(100, 50), true, true); 
    AudioReactiveGradient aRG = AudioReactiveGradient(Vector2D(160, 160), Vector2D(0, 0), true, true); 
    Oscilloscope oSC = Oscilloscope(Vector2D(200, 100), Vector2D(0, 0));

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

    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    float techSaneLogo = 0.0f;
    uint8_t offsetFaceIndSA = 50;
    uint8_t offsetFaceIndARG = 51;
    uint8_t offsetFaceIndOSC = 52;
    uint8_t techSaneLogoInd = 53;
    bool mirror = false;

    float xOffset = 0.0f;
    float yOffset = 0.0f;
    float adjustTS = 0.0f;

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
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::HideBlush), NukudeFace::HideBlush, 30, 1.0f, 0.0f);

        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
        eEA.AddParameter(&techSaneLogo, techSaneLogoInd, 40, 2.0f, 0.0f);
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
        materialAnimator.SetBaseMaterial(Material::Add, &flowNoise);
        materialAnimator.AddMaterial(Material::Replace, &orangeMaterial, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &whiteMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &greenMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Replace, &yellowMaterial, 40, 0.0f, 1.0f);//layer 4
        materialAnimator.AddMaterial(Material::Replace, &purpleMaterial, 40, 0.0f, 1.0f);//layer 5
        materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 6
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 7
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 8
        materialAnimator.AddMaterial(Material::Lighten, &rainbowNoise, 40, 0.35f, 1.0f);//layer 9

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
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
        eEA.AddParameterFrame(offsetFaceIndSA, 1.0f);

        backgroundMaterial.AddMaterialFrame(sA, offsetFaceSA);
    }

    void AudioReactiveGradientFace(){
        eEA.AddParameterFrame(offsetFaceIndARG, 1.0f);

        backgroundMaterial.AddMaterialFrame(aRG, offsetFaceARG);
    }

    void OscilloscopeFace(){
        eEA.AddParameterFrame(offsetFaceIndOSC, 1.0f);

        backgroundMaterial.AddMaterialFrame(oSC, offsetFaceOSC);
    }

    void TechSaneFace(){
        eEA.AddParameterFrame(techSaneLogoInd, 0.0f);
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

    void SetMaterialColor(){
        switch(Menu::GetFaceColor()){
            case 1: materialAnimator.AddMaterialFrame(redMaterial, 0.8f); break;
            case 2: materialAnimator.AddMaterialFrame(orangeMaterial, 0.8f); break;
            case 3: materialAnimator.AddMaterialFrame(whiteMaterial, 0.8f); break;
            case 4: materialAnimator.AddMaterialFrame(greenMaterial, 0.8f); break;
            case 5: materialAnimator.AddMaterialFrame(blueMaterial, 0.8f); break;
            case 6: materialAnimator.AddMaterialFrame(yellowMaterial, 0.8f); break;
            case 7: materialAnimator.AddMaterialFrame(purpleMaterial, 0.8f); break;
            case 8: materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f); break;
            case 9: materialAnimator.AddMaterialFrame(rainbowNoise, 0.8f); break;
            default: break;
        }
    }

public:
    TechSaneAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(tS.GetObject());
        scene.AddObject(tSM.GetObject());
        scene.AddObject(background.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        pM.GetObject()->SetMaterial(&materialAnimator);
        background.GetObject()->SetMaterial(&backgroundMaterial);
        tS.GetObject()->SetMaterial(&flowNoise);
        tSM.GetObject()->SetMaterial(&flowNoise);

        boop.Initialize(5);

        MicrophoneFourier::Initialize(A0, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
        Menu::Initialize(10, 20, 500);//7 is number of faces
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    void SetCameraMirror(bool mirror){
        this->mirror = mirror;
    }

    void Update(float ratio) override {
        if(!mirror){
            gradientSpectrum[0].SetColor(253, 253, 251);
            gradientSpectrum[1].SetColor(0, 80, 175);
            gradientMat.UpdateRGB();

            pM.Reset();

            xOffset = fGenMatXMove.Update();
            yOffset = fGenMatYMove.Update();

            Menu::Update();

            SetMaterialColor();

            bool isBooped = Menu::UseBoopSensor() ? boop.isBooped() : 0;
            uint8_t mode = Menu::GetFaceState();//change by button press

            MicrophoneFourier::Update();
            sA.SetHueAngle(ratio * 360.0f * 4.0f);
            sA.SetMirrorYState(Menu::MirrorSpectrumAnalyzer());
            sA.SetFlipYState(!Menu::MirrorSpectrumAnalyzer());
            
            aRG.SetRadius((xOffset + 2.0f) * 2.0f + 25.0f);
            aRG.SetSize(Vector2D((xOffset + 2.0f) * 10.0f + 50.0f, (xOffset + 2.0f) * 10.0f + 50.0f));
            aRG.SetHueAngle(ratio * 360.0f * 8.0f);
            aRG.SetRotation(ratio * 360.0f * 2.0f);
            aRG.SetPosition(Vector2D(80.0f + xOffset * 4.0f, 48.0f + yOffset * 4.0f));

            oSC.SetSize(Vector2D(200.0f, 100.0f));
            oSC.SetHueAngle(ratio * 360.0f * 8.0f);
            oSC.SetPosition(Vector2D(100.0f, 50.0f));

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
                else if (mode == 6) TechSaneFace();
                else if (mode == 7) {
                    aRG.Update(MicrophoneFourier::GetFourierFiltered());
                    AudioReactiveGradientFace();
                }
                else if (mode == 8){
                    oSC.Update(MicrophoneFourier::GetSamples());
                    OscilloscopeFace();
                }
                else {
                    sA.Update(MicrophoneFourier::GetFourierFiltered());
                    SpectrumAnalyzerFace();
                }
            }
            
            UpdateKeyFrameTracks();

            pM.SetMorphWeight(NukudeFace::BiggerNose, 1.0f);
            pM.SetMorphWeight(NukudeFace::MoveEye, 1.0f);

            eEA.Update();
            pM.Update();
            tS.Update();
            
            rainbowNoise.Update(ratio);
            flowNoise.Update(ratio);
            rainbowSpiral.Update(ratio);
            materialAnimator.Update();
            backgroundMaterial.Update();
            
            uint8_t faceSize = 0;//Menu::GetFaceSize();
            float menuRatio = Menu::ShowMenu();
            float scale = menuRatio * 0.6f + 0.4f;
            float xShift = (1.0f - menuRatio) * 60.0f;
            float yShift = (1.0f - menuRatio) * 20.0f + offsetFaceSA * -100.0f + offsetFaceARG * -100.0f + offsetFaceOSC * -100.0f + (2.0f - techSaneLogo) * -50.0f;
            float adjustFacePos = float(4 - faceSize) * 5.0f;
            float adjustFaceX = float(faceSize) * 0.05f;
            
            pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, -7.5f));
            pM.GetObject()->GetTransform()->SetPosition(Vector3D(102.5f + xOffset - xShift + adjustFacePos, -22.5f + yOffset + yShift, 600.0f));
            pM.GetObject()->GetTransform()->SetScale(Vector3D(-1.05f + adjustFaceX, 0.585f, 0.8f).Multiply(scale));

            pM.GetObject()->UpdateTransform();

            adjustTS = 1.0f - (float(faceSize) * 0.15f);

            tS.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset / 2.0f, 5.0f + yOffset / 2.0f - techSaneLogo * 30.0f, 300.0f));
            tS.GetObject()->GetTransform()->SetScale(Vector3D(1.0f * adjustTS + xOffset / 40.0f, 1.15f - techSaneLogo, 1.0f));

            tS.GetObject()->UpdateTransform();

            tS.GetObject()->Enable();
            tSM.GetObject()->Disable();
        }
        else{
            gradientSpectrum[0].SetColor(253, 253, 251);
            gradientSpectrum[1].SetColor(175, 40, 120);
            gradientMat.UpdateRGB();

            tSM.Update();

            tSM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset / 2.0f, 5.0f + yOffset / 2.0f - techSaneLogo * 30.0f, 300.0f));
            tSM.GetObject()->GetTransform()->SetScale(Vector3D(1.0f * adjustTS + xOffset / 40.0f, 1.15f - techSaneLogo, 1.0f));

            tSM.GetObject()->UpdateTransform();

            tS.GetObject()->Disable();
            tSM.GetObject()->Enable();
        }
    }
};
