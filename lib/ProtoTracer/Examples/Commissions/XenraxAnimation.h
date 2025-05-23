#pragma once

#include "../Animation.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Objects/LEDStripBackgroundWS35.h"

#include "../../Morph/Commissions/XenraxFace.h"

#include "../../Render/Scene.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Menu/SingleButtonMenu.h"
#include "../../Sensors/APDS9960.h"
#include "../../Sensors/MMC56X3.h"

#include "../../Materials/Animated/RainbowNoise.h"
#include "../../Materials/Animated/RainbowSpiral.h"
#include "../../Materials/Animated/SpectrumAnalyzer.h"
#include "../../Materials/Animated/AudioReactiveGradient.h"
#include "../../Materials/Animated/Oscilloscope.h"

#include "../../Materials/MaterialAnimator.h"

#include "../AnimationTracks/BlinkTrack.h"

#include "../../Signals/FFTVoiceDetection.h"

#include "../../Sensors/MicrophoneFourier_MAX9814.h"

#include "../../Render/ObjectAlign.h"

#include "../../Screenspace/GlitchX.h"
#include "../../Screenspace/Fisheye.h"
#include "../../Screenspace/HorizontalBlur.h"
#include "../../Screenspace/PhaseOffsetX.h"
#include "../../Screenspace/PhaseOffsetY.h"
#include "../../Screenspace/PhaseOffsetR.h"
#include "../../Screenspace/Magnet.h"
#include "../../Screenspace/Overflow.h"
#include "../../Screenspace/RadialBlur.h"
#include "../../Screenspace/ShiftR.h"
#include "../../Screenspace/VerticalBlur.h"
#include "../../Screenspace/Test.h"

class XenraxAnimation : public Animation<6> {
private:
    static const uint8_t faceCount = 9;
    XenraxFace pM;
    Background background;
    LEDStripBackgroundWS35 ledStripBackground;
    EasyEaseAnimator<30> eEA = EasyEaseAnimator<30>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    
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
    SimpleMaterial pinkMaterial = SimpleMaterial(RGBColor(255, 100, 200));
    
    RGBColor gradientSpectrum[2] = {RGBColor(85, 243, 226), RGBColor(67, 192, 178)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);

    RGBColor batterySpectrum[2] = {RGBColor(253, 0, 99), RGBColor(82, 246, 229)};
    GradientMaterial<2> batteryGrad = GradientMaterial<2>(batterySpectrum, 350.0f, false);
    
    RGBColor audioSpectrum[3] = {RGBColor(255, 165, 0), RGBColor(128, 0, 128), RGBColor(0, 255, 65)};
    GradientMaterial<3> audioGrad = GradientMaterial<3>(audioSpectrum, 350.0f, false);
    
    MaterialAnimator<15> materialAnimator;
    MaterialAnimator<5> backgroundMaterial;
    
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

    FunctionGenerator fGenBattery = FunctionGenerator(FunctionGenerator::Sawtooth, 1.0f, 0.0f, 5.0f);
    FunctionGenerator fGenMove = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 2.0f);

    FunctionGenerator fGenBlur = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 1.5f);

    APDS9960 boop;
    MMC56X3 magnetometer;

    FFTVoiceDetection<128> voiceDetection;

    ObjectAlign objA = ObjectAlign(Vector2D(0.0f, 0.0f), Vector2D(170.0f, 125.0f), Quaternion());
    
    Fisheye fisheye = Fisheye();
    GlitchX glitchX = GlitchX(30);
    HorizontalBlur blurH = HorizontalBlur(8);
    VerticalBlur blurV = VerticalBlur(8);
    Magnet magnet = Magnet();
    RadialBlur blurR = RadialBlur(8);
    PhaseOffsetX phaseX = PhaseOffsetX(8);
    PhaseOffsetY phaseY = PhaseOffsetY(8);
    PhaseOffsetR phaseR = PhaseOffsetR(8);
    ShiftR shiftR = ShiftR(8);
    Overflow overflow = Overflow(8);
    Test screenspaceTest = Test();

    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    float magnetSK = 0.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;
    uint8_t magnetSKInd = 54;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::Battery), XenraxFace::Battery, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::BatteryFull), XenraxFace::BatteryFull, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::Boop), XenraxFace::Boop, 5, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::Angry), XenraxFace::Angry, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::Hypno), XenraxFace::Hypno, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::Hearts), XenraxFace::Hearts, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::Sleeping), XenraxFace::Sleeping, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::Dead), XenraxFace::Dead, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::BSOD), XenraxFace::BSOD, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::SpinSpiral), XenraxFace::SpinSpiral, 5, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::HideSpiral), XenraxFace::HideSpiral, 30, 1.0f, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::MoveZZZ), XenraxFace::MoveZZZ, 5, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::HideZZZ), XenraxFace::HideZZZ, 30, 1.0f, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::MoveHearts), XenraxFace::MoveHearts, 5, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::HideHearts), XenraxFace::HideHearts, 30, 1.0f, 0.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::vrc_v_ee), XenraxFace::vrc_v_ee, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::vrc_v_ih), XenraxFace::vrc_v_ih, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::vrc_v_dd), XenraxFace::vrc_v_dd, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::vrc_v_rr), XenraxFace::vrc_v_rr, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::vrc_v_ch), XenraxFace::vrc_v_ch, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::vrc_v_aa), XenraxFace::vrc_v_aa, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::vrc_v_oh), XenraxFace::vrc_v_oh, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(XenraxFace::vrc_v_ss), XenraxFace::vrc_v_ss, 2, 0.0f, 1.0f);

        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
        eEA.AddParameter(&magnetSK, magnetSKInd, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(XenraxFace::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(XenraxFace::vrc_v_ee, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(XenraxFace::vrc_v_ih, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(XenraxFace::vrc_v_dd, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(XenraxFace::vrc_v_rr, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(XenraxFace::vrc_v_ch, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(XenraxFace::vrc_v_aa, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(XenraxFace::vrc_v_oh, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(XenraxFace::vrc_v_ss, EasyEaseInterpolation::Linear);

        eEA.SetInterpolationMethod(magnetSKInd, EasyEaseInterpolation::Cosine);
    }

    void SetMaterialLayers(){
        materialAnimator.SetBaseMaterial(Material::Add, &gradientMat);
        materialAnimator.AddMaterial(Material::Replace, &orangeMaterial, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &whiteMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &greenMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Replace, &yellowMaterial, 40, 0.0f, 1.0f);//layer 4
        materialAnimator.AddMaterial(Material::Replace, &purpleMaterial, 40, 0.0f, 1.0f);//layer 5
        materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 6
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 7
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 8
        materialAnimator.AddMaterial(Material::Replace, &rainbowNoise, 40, 0.15f, 1.0f);//layer 9
        materialAnimator.AddMaterial(Material::Replace, &pinkMaterial, 40, 0.0f, 1.0f);//layer 10
        materialAnimator.AddMaterial(Material::Replace, &batteryGrad, 40, 0.0f, 1.0f);//layer 11
        materialAnimator.AddMaterial(Material::Replace, &audioGrad, 40, 0.0f, 1.0f);//layer 12

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &blueMaterial, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){
        //scene.SetEffect(&screenspaceTest);
        scene.DisableEffect();
        
        blink.Play();
    }

    void Battery(){
        scene.DisableEffect();
        
        eEA.AddParameterFrame(XenraxFace::Battery, 1.0f);
        eEA.AddParameterFrame(XenraxFace::BatteryFull, fGenBattery.Update());
        materialAnimator.AddMaterialFrame(batteryGrad, 1.0f);

        batteryGrad.SetRotationAngle(fGenBattery.Update() * 360.0f);

        blink.Pause();
    }

    void Boop(){
        scene.DisableEffect();

        eEA.AddParameterFrame(XenraxFace::Boop, 1.0f);
        materialAnimator.AddMaterialFrame(pinkMaterial, 1.0f);

        blink.Play();
    }

    void Angry(){
        scene.DisableEffect();

        eEA.AddParameterFrame(XenraxFace::Angry, 1.0f);
        materialAnimator.AddMaterialFrame(redMaterial, 1.0f);

        blink.Play();
    } 

    void Hypno(){
        scene.SetEffect(&magnet);
        scene.EnableEffect();

        eEA.AddParameterFrame(XenraxFace::Hypno, 1.0f);
        eEA.AddParameterFrame(XenraxFace::HideSpiral, 0.0f);
        eEA.AddParameterFrame(XenraxFace::SpinSpiral, fGenMove.Update());
        materialAnimator.AddMaterialFrame(pinkMaterial, 1.0f);

        blink.Pause();
    }

    void Hearts(){
        scene.DisableEffect();
        
        eEA.AddParameterFrame(XenraxFace::Hearts, 1.0f);
        eEA.AddParameterFrame(XenraxFace::HideHearts, 0.0f);
        eEA.AddParameterFrame(XenraxFace::MoveHearts, fGenMove.Update());

        blink.Play();
    }
    
    void Sleeping(){
        scene.DisableEffect();
        
        eEA.AddParameterFrame(XenraxFace::Sleeping, 1.0f);
        eEA.AddParameterFrame(XenraxFace::HideZZZ, 0.0f);
        eEA.AddParameterFrame(XenraxFace::MoveZZZ, fGenMove.Update());

        blink.Pause();
    }

    void Dead(){
        scene.DisableEffect();
        
        eEA.AddParameterFrame(XenraxFace::Dead, 1.0f);
        //materialAnimator.AddMaterialFrame(redMaterial, 1.0f);

        blink.Pause();
    }

    void BSOD(){
        scene.SetEffect(&magnet);
        scene.EnableEffect();
        
        eEA.AddParameterFrame(XenraxFace::BSOD, 1.0f);
        materialAnimator.AddMaterialFrame(whiteMaterial, 1.0f);
        backgroundMaterial.AddMaterialFrame(blueMaterial, 1.0f);

        blink.Pause();
    }

    void SpectrumAnalyzerFace(){
        scene.DisableEffect();
        
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndSA, 1.0f);

        materialAnimator.AddMaterialFrame(audioGrad, 1.0f);
        backgroundMaterial.AddMaterialFrame(sA, offsetFaceSA);
    }

    void AudioReactiveGradientFace(){
        scene.DisableEffect();
        
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndARG, 1.0f);

        materialAnimator.AddMaterialFrame(audioGrad, 1.0f);
        backgroundMaterial.AddMaterialFrame(aRG, offsetFaceARG);
    }

    void OscilloscopeFace(){
        scene.DisableEffect();
        
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndOSC, 1.0f);

        materialAnimator.AddMaterialFrame(audioGrad, 1.0f);
        backgroundMaterial.AddMaterialFrame(oSC, offsetFaceOSC);
    }

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            eEA.AddParameterFrame(XenraxFace::vrc_v_ss, MicrophoneFourierIT::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourierIT::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourierIT::GetFourierFiltered(), MicrophoneFourierIT::GetSampleRate());
        
                eEA.AddParameterFrame(XenraxFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(XenraxFace::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(XenraxFace::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.UH));
                eEA.AddParameterFrame(XenraxFace::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
                eEA.AddParameterFrame(XenraxFace::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(XenraxFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(XenraxFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
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
    XenraxAnimation() {
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
        //magnetometer.Initialize();

        MicrophoneFourierIT::Initialize(22, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
        //Menu::Initialize(9);//NeoTrellis
        Menu::Initialize(10, 0, 500);//11 is number of faces

        pinMode(3, INPUT);//Hall effect sensor

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

        //bool magnetBoop = !digitalRead(3);



        float xOffset = fGenMatXMove.Update();
        float yOffset = fGenMatYMove.Update();
        
        Menu::Update(ratio);

        //Menu::SetSize(Vector2D(280, 60));
        //Menu::SetPositionOffset(Vector2D(0.0f, -30.0f * yOffset));
        
        //glitchX.SetRatio(fGenBlur.Update());
        magnet.SetRatio(ratio);
        fisheye.SetRatio(fGenBlur.Update());
        blurH.SetRatio(fGenBlur.Update());
        blurV.SetRatio(fGenBlur.Update());
        blurR.SetRatio(fGenBlur.Update());
        phaseX.SetRatio(fGenBlur.Update());
        phaseY.SetRatio(fGenBlur.Update());
        phaseR.SetRatio(fGenBlur.Update());
        shiftR.SetRatio(fGenBlur.Update());

        audioGrad.GradientShift(ratio * 2.0f);
        //audioGrad.SetPositionOffset(Vector2D)
        //audioGrad.SetRotationAngle(fGenMove.Update());

        SetMaterialColor();

        bool isBooped = Menu::UseBoopSensor() ? boop.isBooped() : 0;
        Vector3D fieldPosition;// = magnetometer.EstimateMagnetPosition();
        bool isMagn = false;// = magnetometer.IsDetected();

        //magnet.SetAmplitude(magnetometer.GetMagnitude());
        magnet.SetPosition(Vector2D(fieldPosition.X - 80.0f, fieldPosition.Y + 50.0f));

        eEA.AddParameterFrame(magnetSKInd, isMagn);

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

        if (isBooped && mode != 6){
            Boop();
        }
        else if(isMagn && mode != 6){
            Hypno();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Battery();
            else if (mode == 2) Angry();
            else if (mode == 3) Hearts();
            else if (mode == 4) Sleeping();
            else if (mode == 5) Dead();
            else if (mode == 6) BSOD();
            else if (mode == 7) {
                aRG.Update(MicrophoneFourierIT::GetFourierFiltered());
                AudioReactiveGradientFace();
            }
            else if (mode == 8){
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
        
        //phaseR.SetRatio(eEA.GetValue(XenraxFace::Surprised));
        //glitchX.SetRatio(eEA.GetValue(XenraxFace::Surprised));

        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();
        backgroundMaterial.Update();

        uint8_t faceSize = Menu::GetFaceSize();
        float scale = Menu::ShowMenu() * 0.6f + 0.4f;
        float faceSizeOffset = faceSize * 8.0f;

        objA.SetPlaneOffsetAngle(0.0f);
        objA.SetEdgeMargin(4.0f);
        objA.SetCameraMax(Vector2D(110.0f + faceSizeOffset, 115.0f - 115.0f * offsetFace).Multiply(scale));

        objA.AlignObjects(scene.GetObjects(), 1);
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset, yOffset, 0.0f));
        pM.GetObject()->UpdateTransform();
    }
};
