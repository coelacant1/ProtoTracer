#pragma once

#include "../Animation.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Objects/LEDStripBackground.h"
#include "../../Morph/Commissions/AphoriFace.h"
#include "../../Render/Scene.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Menu/NeoTrellisMenu.h"
#include "../../Sensors/APDS9960.h"

#include "../../Materials/Animated/RainbowNoise.h"
#include "../../Materials/Animated/RainbowSpiral.h"
#include "../../Materials/Animated/SpectrumAnalyzer.h"
#include "../../Materials/Animated/AudioReactiveGradient.h"
#include "../../Materials/Animated/Oscilloscope.h"
#include "../../Materials/MaterialMask.h"
#include "../../Shapes/Circle.h"
#include "../../Shapes/Rectangle.h"

#include "../../Materials/MaterialAnimator.h"

#include "../AnimationTracks/BlinkTrack.h"

#include "../../Signals/FFTVoiceDetection.h"

#include "../../Sensors/MicrophoneFourier_MAX9814.h"

#include "../../Render/ObjectAlign.h"

class AphoriAnimation : public Animation<3> {
private:
    static const uint8_t faceCount = 12;
    AphoriFace pM;
    Background background;
    LEDStripBackground ledStripBackground;
    EasyEaseAnimator<25> eEA = EasyEaseAnimator<25>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    
    Circle angryEyeCirc = Circle(Vector2D(102.0f, 62.0f), 12.0f);
    Rectangle toastEyeRect = Rectangle(Vector2D(60.0f, 34.0f), Vector2D(80.0f, 50.0f), 0.0f);
    Rectangle blushRect = Rectangle(Vector2D(75.0f, 20.0f), Vector2D(40.0f, 15.0f), 0.0f);
    Rectangle sadRect = Rectangle(Vector2D(75.0f, 18.0f), Vector2D(40.0f, 15.0f), 0.0f);

    //Materials
    RainbowNoise rainbowNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial orangeMaterial = SimpleMaterial(RGBColor(255, 165, 0));
    SimpleMaterial whiteMaterial = SimpleMaterial(RGBColor(255, 255, 255));
    SimpleMaterial greenMaterial = SimpleMaterial(RGBColor(0, 255, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    SimpleMaterial yellowMaterial = SimpleMaterial(RGBColor(255, 255, 0));
    SimpleMaterial purpleMaterial = SimpleMaterial(RGBColor(255, 0, 255));
    SimpleMaterial pinkMaterial = SimpleMaterial(RGBColor(227, 11, 92));
    MaterialMask angryEyeMaterial = MaterialMask(&redMaterial, &whiteMaterial, &angryEyeCirc);
    MaterialMask toastEyeMaterial = MaterialMask(&redMaterial, &whiteMaterial, &toastEyeRect);
    MaterialMask blushMaterial = MaterialMask(&pinkMaterial, &whiteMaterial, &blushRect);
    MaterialMask sadMaterial = MaterialMask(&blueMaterial, &whiteMaterial, &sadRect);
    
    RGBColor gradientSpectrum[2] = {RGBColor(175, 175, 175), RGBColor(175, 175, 175)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);
    
    MaterialAnimator<15> materialAnimator;
    MaterialAnimator<4> backgroundMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(200, 100), Vector2D(100, 50), true, true); 
    AudioReactiveGradient aRG = AudioReactiveGradient(Vector2D(160, 160), Vector2D(0, 0), true, true); 
    Oscilloscope oSC = Oscilloscope(Vector2D(192, 96), Vector2D(0, 0));

    //Animation controllers
    BlinkTrack<1> blink;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 1.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 1.7f);
    FunctionGenerator fGenMatHue = FunctionGenerator(FunctionGenerator::Triangle, 0.0f, 360.0f, 17.3f);

    FunctionGenerator fGenMatXMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 1.1f);
    FunctionGenerator fGenMatYMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 2.7f);
    FunctionGenerator fGenMatRMenu = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 1.7f);

    APDS9960 boop;

    FFTVoiceDetection<128> voiceDetection;

    ObjectAlign objA = ObjectAlign(Vector2D(0.0f, 0.0f), Vector2D(189.0f, 93.0f), Quaternion());

    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::Happy), AphoriFace::Happy, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::Concern), AphoriFace::Concern, 25, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::Blush), AphoriFace::Blush, 25, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::Upset), AphoriFace::Upset, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::Angry), AphoriFace::Angry, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::Sad), AphoriFace::Sad, 50, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::Nervous), AphoriFace::Nervous, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::Thrilled), AphoriFace::Thrilled, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::Toast), AphoriFace::Toast, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::Boop), AphoriFace::Boop, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::HideU), AphoriFace::HideU, 30, 1.0f, 0.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::vrc_v_ee), AphoriFace::vrc_v_ee, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::vrc_v_ih), AphoriFace::vrc_v_ih, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::vrc_v_dd), AphoriFace::vrc_v_dd, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::vrc_v_rr), AphoriFace::vrc_v_rr, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::vrc_v_ch), AphoriFace::vrc_v_ch, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::vrc_v_aa), AphoriFace::vrc_v_aa, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::vrc_v_oh), AphoriFace::vrc_v_oh, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(AphoriFace::vrc_v_ss), AphoriFace::vrc_v_ss, 2, 0.0f, 1.0f);

        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(AphoriFace::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(AphoriFace::Sad, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(AphoriFace::Angry, EasyEaseInterpolation::Cosine);
        
        eEA.SetInterpolationMethod(AphoriFace::vrc_v_ee, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AphoriFace::vrc_v_ih, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AphoriFace::vrc_v_dd, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AphoriFace::vrc_v_rr, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AphoriFace::vrc_v_ch, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AphoriFace::vrc_v_aa, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AphoriFace::vrc_v_oh, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AphoriFace::vrc_v_ss, EasyEaseInterpolation::Linear);
    }

    void SetMaterialLayers(){
        materialAnimator.SetBaseMaterial(Material::Add, &gradientMat);
        materialAnimator.AddMaterial(Material::Replace, &orangeMaterial, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &whiteMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &greenMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Replace, &yellowMaterial, 40, 0.0f, 1.0f);//layer 4
        materialAnimator.AddMaterial(Material::Replace, &pinkMaterial, 40, 0.0f, 1.0f);//layer 5
        materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 6
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 7
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 8
        materialAnimator.AddMaterial(Material::Replace, &rainbowNoise, 40, 0.15f, 1.0f);//layer 9
        materialAnimator.AddMaterial(Material::Replace, &toastEyeMaterial, 40, 0.0f, 1.0f);//
        materialAnimator.AddMaterial(Material::Replace, &angryEyeMaterial, 40, 0.0f, 1.0f);//
        materialAnimator.AddMaterial(Material::Replace, &blushMaterial, 40, 0.0f, 1.0f);//
        materialAnimator.AddMaterial(Material::Replace, &sadMaterial, 40, 0.0f, 1.0f);//

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){
        eEA.AddParameterFrame(AphoriFace::Happy, 1.0f);
    }

    void Concern(){
        eEA.AddParameterFrame(AphoriFace::Concern, 1.0f);
    }

    void Blush(){
        eEA.AddParameterFrame(AphoriFace::Blush, 1.0f);
        eEA.AddParameterFrame(AphoriFace::HideU, 0.0f);
        materialAnimator.AddMaterialFrame(blushMaterial, 0.8f);
    }

    void Upset(){
        eEA.AddParameterFrame(AphoriFace::Upset, 1.0f);
    }

    void Angry(){
        eEA.AddParameterFrame(AphoriFace::Angry, 1.0f);
        materialAnimator.AddMaterialFrame(angryEyeMaterial, 0.8f);
    }

    void Sad(){
        eEA.AddParameterFrame(AphoriFace::Sad, 0.75f);
        materialAnimator.AddMaterialFrame(sadMaterial, 0.8f);
    }

    void Nervous(){
        eEA.AddParameterFrame(AphoriFace::Nervous, 1.0f);
        eEA.AddParameterFrame(AphoriFace::HideU, 0.0f);
    }

    void Thrilled(){
        eEA.AddParameterFrame(AphoriFace::Thrilled, 1.0f);
        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }
    
    void Toast(){
        eEA.AddParameterFrame(AphoriFace::Toast, 1.0f);
        eEA.AddParameterFrame(AphoriFace::HideU, 0.0f);
        materialAnimator.AddMaterialFrame(toastEyeMaterial, 1.0f);
    }

    void Boop(){
        eEA.AddParameterFrame(AphoriFace::Boop, 1.0f);
        materialAnimator.AddMaterialFrame(pinkMaterial, 0.5f);
    }

    void SpectrumAnalyzerFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndSA, 1.0f);

        backgroundMaterial.AddMaterialFrame(sA, offsetFaceSA);
    }

    void AudioReactiveGradientFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndARG, 1.0f);

        backgroundMaterial.AddMaterialFrame(aRG, offsetFaceARG);
    }

    void OscilloscopeFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndOSC, 1.0f);

        backgroundMaterial.AddMaterialFrame(oSC, offsetFaceOSC);
    }

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            eEA.AddParameterFrame(AphoriFace::vrc_v_ss, MicrophoneFourierIT::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourierIT::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourierIT::GetFourierFiltered(), MicrophoneFourierIT::GetSampleRate());
        
                eEA.AddParameterFrame(AphoriFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(AphoriFace::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(AphoriFace::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.UH));
                eEA.AddParameterFrame(AphoriFace::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
                eEA.AddParameterFrame(AphoriFace::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(AphoriFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(AphoriFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
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
    AphoriAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(background.GetObject());
        scene.AddObject(ledStripBackground.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        pM.GetObject()->SetMaterial(&materialAnimator);
        background.GetObject()->SetMaterial(&backgroundMaterial);
        ledStripBackground.GetObject()->SetMaterial(&materialAnimator);

        boop.Initialize(5);

        MicrophoneFourierIT::Initialize(15, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
        Menu::Initialize(faceCount);//7 is number of faces

        objA.SetJustification(ObjectAlign::Stretch);
        objA.SetMirrorX(true);
    }

    uint8_t GetAccentBrightness(){
        return Menu::GetAccentBrightness();
    };

    uint8_t GetBrightness(){
        return Menu::GetBrightness();
    };

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    void Update(float ratio) override {
        pM.Reset();

        float xOffset = fGenMatXMove.Update();
        float yOffset = fGenMatYMove.Update();
        
        Menu::Update(ratio);

        SetMaterialColor();

        bool isBooped = Menu::UseBoopSensor() ? boop.isBooped() : 0;
        uint8_t mode = Menu::GetFaceState();//change by button press

        MicrophoneFourierIT::Update();
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
        
        voiceDetection.SetThreshold(map(Menu::GetMicLevel(), 0, 10, 1000, 50));

        UpdateFFTVisemes();

        if (isBooped && mode != 8){
            Boop();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Concern();
            else if (mode == 2) Blush();
            else if (mode == 3) Upset();
            else if (mode == 4) Angry();
            else if (mode == 5) Sad();
            else if (mode == 6) Nervous();
            else if (mode == 7) Thrilled();
            else if (mode == 8) Toast();
            else if (mode == 9) {
                aRG.Update(MicrophoneFourierIT::GetFourierFiltered());
                AudioReactiveGradientFace();
            }
            else if (mode == 10){
                oSC.Update(MicrophoneFourierIT::GetSamples());
                OscilloscopeFace();
            }
            else {
                sA.Update(MicrophoneFourierIT::GetFourierFiltered());
                SpectrumAnalyzerFace();
            }
        }

        UpdateKeyFrameTracks();

        eEA.Update();
        pM.Update();

        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();
        backgroundMaterial.Update();

        uint8_t faceSize = Menu::GetFaceSize();
        float scale = Menu::ShowMenu() * 0.6f + 0.4f;
        float faceSizeOffset = faceSize * 8.0f;

        objA.SetPlaneOffsetAngle(-7.5f);
        objA.SetEdgeMargin(2.0f);
        objA.SetCameraMax(Vector2D(110.0f + faceSizeOffset, 93.0f - 93.0f * offsetFace).Multiply(scale));

        objA.AlignObjects(scene.GetObjects(), 1);
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset, yOffset, 0.0f));
        pM.GetObject()->UpdateTransform();
    }
};