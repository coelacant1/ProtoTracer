#pragma once

#include "../Animation.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Objects/LEDStripBackground.h"
#include "../../Morph/Commissions/BroookFace.h"
#include "../../Morph/Commissions/BroookExtras.h"
#include "../../Render/Scene.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Menu/SingleButtonMenu.h"
#include "../../Sensors/APDS9960.h"

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

#include "Flash/ImageSequences/BadApple.h"

class BroookAnimation : public Animation<4> {
private:
    BroookFace pM;
    BroookExtras pME;
    Background background;
    LEDStripBackground ledStripBackground;
    EasyEaseAnimator<25> eEA = EasyEaseAnimator<25>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    
    bool boopExists = false;
    
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
    MaterialAnimator<5> backgroundMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(200, 100), Vector2D(100, 50), true, true); 
    AudioReactiveGradient aRG = AudioReactiveGradient(Vector2D(160, 160), Vector2D(0, 0), true, true); 
    Oscilloscope oSC = Oscilloscope(Vector2D(200, 100), Vector2D(0, 0));
    BadAppleSequence gif = BadAppleSequence(Vector2D(200, 145), Vector2D(100, 70), 18);

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

    APDS9960 boop;

    FFTVoiceDetection<128> voiceDetection;

    ObjectAlign objA = ObjectAlign(Vector2D(0.0f, 0.0f), Vector2D(189.0f, 93.0f), Quaternion());

    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    float offsetFaceBad = 0.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;
    uint8_t offsetFaceIndBad = 54;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::Determined2), BroookFace::Determined2, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::Upset3), BroookFace::Upset3, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::Sleepy4), BroookFace::Sleepy4, 50, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::Sad5), BroookFace::Sad5, 50, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::Happy6), BroookFace::Happy6, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::Flustered7), BroookFace::Flustered7, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::Dot8), BroookFace::Dot8, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::Heart9), BroookFace::Heart9, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::Dead10), BroookFace::Dead10, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::Question11), BroookFace::Question11, 30, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::vrc_v_ee), BroookFace::vrc_v_ee, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::vrc_v_aa), BroookFace::vrc_v_aa, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(BroookFace::vrc_v_oh), BroookFace::vrc_v_oh, 2, 0.0f, 1.0f);

        eEA.AddParameter(pME.GetMorphWeightReference(BroookExtras::Heart), BroookExtras::Heart + 100, 30, 0.0f, 1.0f);
        eEA.AddParameter(pME.GetMorphWeightReference(BroookExtras::Dead), BroookExtras::Dead + 100, 30, 0.0f, 1.0f);
        eEA.AddParameter(pME.GetMorphWeightReference(BroookExtras::Sleepy), BroookExtras::Sleepy + 100, 50, 0.0f, 1.0f);
        eEA.AddParameter(pME.GetMorphWeightReference(BroookExtras::Happy), BroookExtras::Happy + 100, 15, 0.0f, 1.0f);
        eEA.AddParameter(pME.GetMorphWeightReference(BroookExtras::Sad), BroookExtras::Sad + 100, 50, 0.0f, 1.0f);
        eEA.AddParameter(pME.GetMorphWeightReference(BroookExtras::None), BroookExtras::None + 100, 30, 0.0f, 1.0f);

        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceBad, offsetFaceIndBad, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(BroookFace::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(BroookFace::vrc_v_ee, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BroookFace::vrc_v_aa, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(BroookFace::vrc_v_oh, EasyEaseInterpolation::Linear);
        
        //eEA.SetInterpolationMethod(BroookFace::Determined2, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BroookFace::Upset3, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BroookFace::Sleepy4, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BroookFace::Sad5, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BroookFace::Happy6, EasyEaseInterpolation::Cosine);
        //eEA.SetInterpolationMethod(BroookFace::Flustered7, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BroookFace::Dot8, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BroookFace::Heart9, EasyEaseInterpolation::Cosine);
        //eEA.SetInterpolationMethod(BroookFace::Dead10, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BroookFace::Question11, EasyEaseInterpolation::Cosine);

        eEA.SetInterpolationMethod(BroookExtras::Heart + 100, EasyEaseInterpolation::Cosine);
        //eEA.SetInterpolationMethod(BroookExtras::Dead, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BroookExtras::Sleepy + 100, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BroookExtras::Happy + 100, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BroookExtras::Sad + 100, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(BroookExtras::None + 100, EasyEaseInterpolation::Cosine);
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
        backgroundMaterial.AddMaterial(Material::Add, &gif, 20, 0.0f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){
        eEA.AddParameterFrame(BroookExtras::None + 100, 1.0f);
        blink.Play();
    }

    void Determined(){
        eEA.AddParameterFrame(BroookFace::Determined2, 1.0f);
        eEA.AddParameterFrame(BroookExtras::None + 100, 1.0f);
        blink.Play();
    }

    void Upset(){
        eEA.AddParameterFrame(BroookFace::Upset3, 1.0f);
        eEA.AddParameterFrame(BroookExtras::None + 100, 1.0f);
        blink.Play();
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
    }

    void Sleepy(){
        eEA.AddParameterFrame(BroookFace::Sleepy4, 1.0f);
        eEA.AddParameterFrame(BroookExtras::Sleepy + 100, 1.0f);
        blink.Pause();
    }

    void Sad(){
        eEA.AddParameterFrame(BroookFace::Sad5, 1.0f);
        eEA.AddParameterFrame(BroookExtras::Sad + 100, 1.0f);
        blink.Play();
        materialAnimator.AddMaterialFrame(blueMaterial, 0.8f);
    }

    void Happy(){
        eEA.AddParameterFrame(BroookFace::Happy6, 0.8f);
        eEA.AddParameterFrame(BroookExtras::Happy + 100, 0.8f);
        blink.Pause();
        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }

    void Flustered(){
        eEA.AddParameterFrame(BroookFace::Flustered7, 1.0f);
        eEA.AddParameterFrame(BroookExtras::None + 100, 1.0f);
        blink.Pause();

        
        eEA.AddParameterFrame(BroookFace::Dead10, 0.0f);
        eEA.AddParameterFrame(BroookExtras::Dead + 100, 0.0f);
    }
    
    void Dot(){
        eEA.AddParameterFrame(BroookFace::Dot8, 0.95f);
        eEA.AddParameterFrame(BroookExtras::None + 100, 0.95f);
        blink.Play();
    }
    
    void Heart(){
        eEA.AddParameterFrame(BroookFace::Heart9, 1.0f);
        eEA.AddParameterFrame(BroookExtras::Heart + 100, 1.0f);
        blink.Pause();
        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }

    void Dead(){
        eEA.AddParameterFrame(BroookFace::Dead10, 1.0f);
        eEA.AddParameterFrame(BroookExtras::Dead + 100, 1.0f);
        blink.Pause();
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
    }

    void Question(){
        eEA.AddParameterFrame(BroookFace::Question11, 1.0f);
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

    void BadAppleFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndBad, 1.0f);

        backgroundMaterial.AddMaterialFrame(gif, offsetFaceBad);
    }

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            eEA.AddParameterFrame(BroookFace::vrc_v_aa, MicrophoneFourierIT::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourierIT::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourierIT::GetFourierFiltered(), MicrophoneFourierIT::GetSampleRate());
        
                eEA.AddParameterFrame(BroookFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(BroookFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(BroookFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.UH));
                eEA.AddParameterFrame(BroookFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AR));
                eEA.AddParameterFrame(BroookFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(BroookFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(BroookFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
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

        gradientMat.SetRotationAngle(90);

        objA.SetJustification(ObjectAlign::Stretch);
        objA.SetMirrorX(true);
        objA.SetMirrorY(true);
    }

    void Initialize() override {
        this->boopExists = boop.Initialize(5);

        MicrophoneFourierIT::Initialize(A0, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
        Menu::Initialize(14, 20, 500);//13 is number of faces
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
        pME.Reset();

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
        
        gif.SetPosition(Vector2D(96.0f, 48.0f));
        gif.SetSize(Vector2D(191.0f, 95.0f));
        //gif.SetRotation(15.0f);
        gif.Update();
        
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
                aRG.Update(MicrophoneFourierIT::GetFourierFiltered());
                AudioReactiveGradientFace();
            }
            else if (mode == 11){
                oSC.Update(MicrophoneFourierIT::GetSamples());
                OscilloscopeFace();
            }
            else if (mode == 12){
                sA.Update(MicrophoneFourierIT::GetFourierFiltered());
                SpectrumAnalyzerFace();
            }
            else{
                BadAppleFace();
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

        objA.SetPlaneOffsetAngle(0.0f);
        objA.SetEdgeMargin(2.0f);
        objA.SetCameraMax(Vector2D(110.0f + faceSizeOffset, 93.0f).Multiply(scale));

        objA.AlignObjects(scene.GetObjects(), 2);
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset, yOffset - 93.0f * offsetFace, 0.0f));
        pM.GetObject()->UpdateTransform();
        pME.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset, yOffset - 93.0f * offsetFace, 0.0f));
        pME.GetObject()->UpdateTransform();
    }
};
