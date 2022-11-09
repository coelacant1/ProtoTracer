#pragma once

#include "..\Animation.h"
#include "..\AnimationTracks\BlinkTrack.h"
#include "..\KeyFrameTrack.h"
#include "..\EasyEaseAnimator.h"
#include "..\..\Objects\Background.h"
#include "..\..\Objects\LEDStripBackground.h"
#include "..\..\Morph\Commissions\WarzoneFace.h"
#include "..\..\Morph\Commissions\WarzoneExtras.h"
#include "..\..\Render\Scene.h"
#include "..\..\Menu\Menu.h"
#include "..\..\Signals\FunctionGenerator.h"
#include "..\..\Signals\FFTVoiceDetection.h"
#include "..\..\Sensors\BoopSensor.h"
#include "..\..\Sensors\MicrophoneFourier_MAX9814.h"
#include "..\..\Render\ObjectAlign.h"

#include "..\..\Materials\Animated\RainbowNoise.h"
#include "..\..\Materials\Animated\RainbowSpiral.h"
#include "..\..\Materials\Animated\SpectrumAnalyzer.h"
#include "..\..\Materials\Animated\AudioReactiveGradient.h"
#include "..\..\Materials\Animated\Oscilloscope.h"
#include "..\..\Materials\MaterialAnimator.h"



class BroookAnimation : public Animation<4> {
private:
    WarzoneFace pM;
    WarzoneExtras pME;
    Background background;
    LEDStripBackground ledStripBackground;
    EasyEaseAnimator<25> eEA = EasyEaseAnimator<25>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    
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
    
    RGBColor gradientSpectrum[2] = {RGBColor(222, 217, 141), RGBColor(100, 120, 211)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 50.0f, false);
    
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
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::BasisMouth), WarzoneFace::BasisMouth, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::UwUEyes), WarzoneFace::UwUEyes, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::UwUMouth), WarzoneFace::UwUMouth, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::SpiralEyes), WarzoneFace::SpiralEyes, 20, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::SpiralMouth), WarzoneFace::SpiralMouth, 20, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::HappyEyes), WarzoneFace::HappyEyes, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::HappyMouth), WarzoneFace::HappyMouth, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::CircleEyes), WarzoneFace::CircleEyes, 20, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::CircleMouth), WarzoneFace::CircleMouth, 20, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::DeadEyes), WarzoneFace::DeadEyes, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::DeadMouth), WarzoneFace::DeadMouth, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::HappyClosed), WarzoneFace::HappyClosed, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::SempaiEyes), WarzoneFace::SempaiEyes, 40, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::SempaiMouth), WarzoneFace::SempaiMouth, 40, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::UpsetEyes), WarzoneFace::UpsetEyes, 40, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::UpsetMouth), WarzoneFace::UpsetMouth, 40, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::Hide), WarzoneFace::Hide, 30, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(WarzoneFace::vrc_v_ee), WarzoneFace::vrc_v_ee, 2, 0.0f, 1.0f);

        eEA.AddParameter(pME.GetMorphWeightReference(WarzoneExtras::HideBlush), WarzoneExtras::HideBlush + 100, 30, 0.0f, 1.0f);
        eEA.AddParameter(pME.GetMorphWeightReference(WarzoneExtras::HideZZZ), WarzoneExtras::HideZZZ + 100, 30, 0.0f, 1.0f);
        eEA.AddParameter(pME.GetMorphWeightReference(WarzoneExtras::Move2ZZZ), WarzoneExtras::Move2ZZZ + 100, 50, 0.0f, 1.0f);
        eEA.AddParameter(pME.GetMorphWeightReference(WarzoneExtras::MoveZZZ), WarzoneExtras::MoveZZZ + 100, 15, 0.0f, 1.0f);
        eEA.AddParameter(pME.GetMorphWeightReference(WarzoneExtras::ScaleZZZ), WarzoneExtras::ScaleZZZ + 100, 50, 0.0f, 1.0f);

        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(WarzoneFace::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(WarzoneFace::vrc_v_ee, EasyEaseInterpolation::Linear);
        
        eEA.SetInterpolationMethod(WarzoneFace::DeadEyes, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(WarzoneFace::DeadMouth, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(WarzoneFace::HappyClosed, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(WarzoneFace::BasisMouth, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(WarzoneFace::SempaiEyes, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(WarzoneFace::SempaiMouth, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(WarzoneFace::UpsetEyes, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(WarzoneFace::UpsetMouth, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(WarzoneFace::Hide, EasyEaseInterpolation::Cosine);

        eEA.SetInterpolationMethod(WarzoneExtras::HideBlush + 100, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(WarzoneExtras::HideZZZ + 100, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(WarzoneExtras::Move2ZZZ + 100, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(WarzoneExtras::MoveZZZ + 100, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(WarzoneExtras::ScaleZZZ + 100, EasyEaseInterpolation::Cosine);
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
        materialAnimator.AddMaterial(Material::Lighten, &rainbowNoise, 40, 0.35f, 1.0f);//layer 9

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){
        eEA.AddParameterFrame(WarzoneExtras::None + 100, 1.0f);
        blink.Play();
    }

    void Determined(){
        eEA.AddParameterFrame(WarzoneFace::Determined2, 1.0f);
        eEA.AddParameterFrame(WarzoneExtras::None + 100, 1.0f);
        blink.Play();
    }

    void Upset(){
        eEA.AddParameterFrame(WarzoneFace::Upset3, 1.0f);
        eEA.AddParameterFrame(WarzoneExtras::None + 100, 1.0f);
        blink.Play();
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
    }

    void Sleepy(){
        eEA.AddParameterFrame(WarzoneFace::Sleepy4, 1.0f);
        eEA.AddParameterFrame(WarzoneExtras::Sleepy + 100, 1.0f);
        blink.Pause();
    }

    void Sad(){
        eEA.AddParameterFrame(WarzoneFace::Sad5, 1.0f);
        eEA.AddParameterFrame(WarzoneExtras::Sad + 100, 1.0f);
        blink.Play();
        materialAnimator.AddMaterialFrame(blueMaterial, 0.8f);
    }

    void Happy(){
        eEA.AddParameterFrame(WarzoneFace::Happy6, 1.0f);
        eEA.AddParameterFrame(WarzoneExtras::Happy + 100, 1.0f);
        blink.Pause();
        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }

    void Flustered(){
        eEA.AddParameterFrame(WarzoneFace::Flustered7, 1.0f);
        eEA.AddParameterFrame(WarzoneExtras::None + 100, 1.0f);
        blink.Pause();

        
        eEA.AddParameterFrame(WarzoneFace::Dead10, 0.0f);
        eEA.AddParameterFrame(WarzoneExtras::Dead + 100, 0.0f);
    }
    
    void Dot(){
        eEA.AddParameterFrame(WarzoneFace::Dot8, 1.0f);
        eEA.AddParameterFrame(WarzoneExtras::None + 100, 1.0f);
        blink.Play();
    }
    
    void Heart(){
        eEA.AddParameterFrame(WarzoneFace::Heart9, 1.0f);
        eEA.AddParameterFrame(WarzoneExtras::Heart + 100, 1.0f);
        blink.Pause();
        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }

    void Dead(){
        eEA.AddParameterFrame(WarzoneFace::Dead10, 1.0f);
        eEA.AddParameterFrame(WarzoneExtras::Dead + 100, 1.0f);
        blink.Pause();
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
    }

    void Question(){
        eEA.AddParameterFrame(WarzoneFace::Question11, 1.0f);
        blink.Pause();
        //Default Extra face
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
            eEA.AddParameterFrame(WarzoneFace::BasisMouth, MicrophoneFourier::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourier::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourier::GetFourierFiltered(), MicrophoneFourier::GetSampleRate());
        
                eEA.AddParameterFrame(WarzoneFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(WarzoneFace::DeadMouth, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(WarzoneFace::DeadMouth, voiceDetection.GetViseme(voiceDetection.UH));
                eEA.AddParameterFrame(WarzoneFace::BasisMouth, voiceDetection.GetViseme(voiceDetection.AR));
                eEA.AddParameterFrame(WarzoneFace::DeadMouth, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(WarzoneFace::CircleMouth, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(WarzoneFace::DeadMouth, voiceDetection.GetViseme(voiceDetection.OO));
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
    BroookAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(pME.GetObject());
        scene.AddObject(background.GetObject());
        scene.AddObject(ledStripBackground.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        pM.GetObject()->SetMaterial(&materialAnimator);
        pME.GetObject()->SetMaterial(&materialAnimator);
        background.GetObject()->SetMaterial(&backgroundMaterial);
        ledStripBackground.GetObject()->SetMaterial(&materialAnimator);

        boop.Initialize(5);

        MicrophoneFourier::Initialize(A0, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
        Menu::Initialize(13, 20, 500);//13 is number of faces

        gradientMat.SetRotationAngle(90);

        objA.SetJustification(ObjectAlign::Stretch);
        objA.SetMirrorX(true);
        objA.SetMirrorY(true);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    void Update(float ratio) override {
        pM.Reset();
        pME.Reset();

        float xOffset = fGenMatXMove.Update();
        float yOffset = fGenMatYMove.Update();
        
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
        
        voiceDetection.SetThreshold(map(Menu::GetMicLevel(), 0, 10, 1000, 50));

        UpdateFFTVisemes();

        if (isBooped){
            Happy();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Determined();
            else if (mode == 2) Upset();
            else if (mode == 3) Sleepy();
            else if (mode == 4) Sad();
            else if (mode == 5) Flustered();
            else if (mode == 6) Dot();
            else if (mode == 7) Heart();
            else if (mode == 8) Dead();
            else if (mode == 9) Question();
            else if (mode == 10) {
                aRG.Update(MicrophoneFourier::GetFourierFiltered());
                AudioReactiveGradientFace();
            }
            else if (mode == 11){
                oSC.Update(MicrophoneFourier::GetSamples());
                OscilloscopeFace();
            }
            else {
                sA.Update(MicrophoneFourier::GetFourierFiltered());
                SpectrumAnalyzerFace();
            }
        }

        UpdateKeyFrameTracks();

        eEA.Update();
        pM.Update();
        pME.Update();
        
        float menuRatio = Menu::ShowMenu();

        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();
        backgroundMaterial.Update();

        uint8_t faceSize = Menu::GetFaceSize();

        float scale = menuRatio * 0.6f + 0.4f;
        float faceSizeOffset = faceSize * 8.0f;

        //objA.SetPlaneOffsetAngle(360.0f * ratio);
        objA.SetEdgeMargin(2.0f);
        objA.SetCameraMax(Vector2D(110.0f + faceSizeOffset, 93.0f).Multiply(scale));

        objA.AlignObjects(scene.GetObjects(), 2);
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset, yOffset - 93.0f * offsetFace, 0.0f));
        pM.GetObject()->UpdateTransform();
        pME.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset, yOffset - 93.0f * offsetFace, 0.0f));
        pME.GetObject()->UpdateTransform();
    }
};
