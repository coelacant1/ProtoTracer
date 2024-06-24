#pragma once

#include "../Animation.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Objects/LEDStripBackground.h"
#include "../../Morph/Commissions/InfraredFace.h"
#include "../../Render/Scene.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Sensors/APDS9960.h"

#include "../../Menu/SingleButtonMenu.h"
#include "../../Materials/Animated/SpectrumAnalyzer.h"
#include "../../Materials/Animated/AudioReactiveGradient.h"
#include "../../Materials/Animated/Oscilloscope.h"
#include "../../Materials/Animated/RainbowNoise.h"
#include "../../Materials/Animated/RainbowSpiral.h"

#include "../../Materials/MaterialAnimator.h"

#include "../AnimationTracks/BlinkTrack.h"

#include "../../Signals/FFTVoiceDetection.h"

#include "../../Sensors/MicrophoneFourier_MAX9814.h"

class InfraredAnimation : public Animation<3> {
private:
    InfraredFace pM;
    Background background;
    LEDStripBackground ledStripBackground;
    EasyEaseAnimator<21> eEA = EasyEaseAnimator<21>(EasyEaseInterpolation::Cosine, 1.0f, 0.35f);
    
    //Materials
    RainbowNoise rainbowNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    
    RGBColor gradientSpectrum[2] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);
    
    MaterialAnimator<5> materialAnimator;
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

    APDS9960 boop;

    FFTVoiceDetection<128> voiceDetection;

    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    uint8_t offsetFaceIndSA = 50;
    uint8_t offsetFaceIndARG = 51;
    uint8_t offsetFaceIndOSC = 52;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(InfraredFace::Angry), InfraredFace::Angry, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(InfraredFace::Sad), InfraredFace::Sad, 50, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(InfraredFace::Calm), InfraredFace::Calm, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(InfraredFace::Determination), InfraredFace::Determination, 20, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(InfraredFace::Happy), InfraredFace::Happy, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(InfraredFace::Mad), InfraredFace::Mad, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(InfraredFace::Flatten), InfraredFace::Flatten, 30, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(InfraredFace::TalkA), InfraredFace::TalkA, 3, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(InfraredFace::TalkB), InfraredFace::TalkB, 3, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(InfraredFace::TalkC), InfraredFace::TalkC, 3, 0.0f, 1.0f);
        
        eEA.AddParameter(pM.GetMorphWeightReference(InfraredFace::Blush), InfraredFace::Blush, 30, 0.0f, 1.0f);

        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(InfraredFace::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(InfraredFace::TalkA, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(InfraredFace::TalkB, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(InfraredFace::TalkC, EasyEaseInterpolation::Linear);
    }

    void SetMaterialLayers(){
        materialAnimator.SetBaseMaterial(Material::Add, &redMaterial);
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Lighten, &rainbowNoise, 40, 0.35f, 1.0f);//layer 3

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
    }

public:
    InfraredAnimation() {
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

        boop.Initialize(10);

        Menu::Initialize(10, 20, 500);//10 is number of faces
        MicrophoneFourierIT::Initialize(15, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){
        blink.Play();

        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);

        pM.SetMorphWeight(InfraredFace::EyeBrowThicker, 1.0f);
        pM.SetMorphWeight(InfraredFace::EyeBigger, 1.0f);
    }

    void Angry(){
        blink.Play();
        eEA.AddParameterFrame(InfraredFace::Angry, 1.0f);
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);

        pM.SetMorphWeight(InfraredFace::EyeBrowThicker, 1.0f);
        pM.SetMorphWeight(InfraredFace::EyeBigger, 1.0f);

    }

    void Sad(){
        blink.Pause();
        eEA.AddParameterFrame(InfraredFace::Sad, 1.0f);
        materialAnimator.AddMaterialFrame(blueMaterial, 0.8f);

        pM.SetMorphWeight(InfraredFace::EyeBrowThicker, 1.0f);
        pM.SetMorphWeight(InfraredFace::EyeBigger, 1.0f);
    }

    void Surprised(){
        blink.Pause();
        eEA.AddParameterFrame(InfraredFace::Blush, 1.0f);
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.2f);

        pM.SetMorphWeight(InfraredFace::EyeBrowThicker, 1.0f);
        pM.SetMorphWeight(InfraredFace::EyeBigger, 1.0f);
    }

    void Happy(){
        blink.Pause();
        eEA.AddParameterFrame(InfraredFace::Happy, 1.0f);
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);

        pM.SetMorphWeight(InfraredFace::EyeBrowThicker, 1.0f);
        pM.SetMorphWeight(InfraredFace::EyeBigger, 1.0f);
    }
    
    void Determination(){
        blink.Play();
        eEA.AddParameterFrame(InfraredFace::Determination, 1.0f);
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);

        pM.SetMorphWeight(InfraredFace::EyeBrowThicker, 1.0f);
        pM.SetMorphWeight(InfraredFace::EyeBigger, 1.0f);
    }
    
    void Calm(){
        blink.Play();
        eEA.AddParameterFrame(InfraredFace::Calm, 1.0f);
        materialAnimator.AddMaterialFrame(blueMaterial, 0.8f);

        pM.SetMorphWeight(InfraredFace::EyeBrowThicker, 1.0f);
        pM.SetMorphWeight(InfraredFace::EyeBigger, 1.0f);
    }

    void Mad(){
        blink.Play();
        eEA.AddParameterFrame(InfraredFace::Mad, 1.0f);
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);

        pM.SetMorphWeight(InfraredFace::EyeBrowThicker, 1.0f);
        pM.SetMorphWeight(InfraredFace::EyeBigger, 1.0f);
    }

    void SpectrumAnalyzerFace(){
        blink.Pause();
        eEA.AddParameterFrame(offsetFaceIndSA, 1.0f);

        backgroundMaterial.AddMaterialFrame(sA, offsetFaceSA);

        eEA.AddParameterFrame(InfraredFace::Flatten, 1.0f);

        pM.SetMorphWeight(InfraredFace::EyeBrowThicker, 0.0f);
        pM.SetMorphWeight(InfraredFace::EyeBigger, 0.0f);
    }

    void AudioReactiveGradientFace(){
        blink.Pause();
        eEA.AddParameterFrame(offsetFaceIndARG, 1.0f);

        backgroundMaterial.AddMaterialFrame(aRG, offsetFaceARG);

        eEA.AddParameterFrame(InfraredFace::Flatten, 1.0f);

        pM.SetMorphWeight(InfraredFace::EyeBrowThicker, 0.0f);
        pM.SetMorphWeight(InfraredFace::EyeBigger, 0.0f);
    }

    void OscilloscopeFace(){
        blink.Pause();
        eEA.AddParameterFrame(offsetFaceIndOSC, 1.0f);

        backgroundMaterial.AddMaterialFrame(oSC, offsetFaceOSC);

        eEA.AddParameterFrame(InfraredFace::Flatten, 1.0f);

        pM.SetMorphWeight(InfraredFace::EyeBrowThicker, 0.0f);
        pM.SetMorphWeight(InfraredFace::EyeBigger, 0.0f);
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

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            eEA.AddParameterFrame(InfraredFace::TalkA, MicrophoneFourierIT::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourierIT::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourierIT::GetFourierFiltered(), MicrophoneFourierIT::GetSampleRate());
        
                eEA.AddParameterFrame(InfraredFace::TalkB, voiceDetection.GetViseme(voiceDetection.EE));
                //eEA.AddParameterFrame(InfraredFace::TalkA, voiceDetection.GetViseme(voiceDetection.UH));
                //eEA.AddParameterFrame(InfraredFace::TalkB, voiceDetection.GetViseme(voiceDetection.AR));
                //eEA.AddParameterFrame(InfraredFace::TalkC, voiceDetection.GetViseme(voiceDetection.ER));
                //eEA.AddParameterFrame(InfraredFace::TalkA, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(InfraredFace::TalkC, voiceDetection.GetViseme(voiceDetection.OO));
            }
        }
    }

    void Update(float ratio) override {
        pM.Reset();

        float xOffset = fGenMatXMove.Update();
        float yOffset = fGenMatYMove.Update();
        
        Menu::Update(ratio);

        bool isBooped = Menu::UseBoopSensor() ? boop.isBooped() : 0;
        uint8_t mode = Menu::GetFaceState();//change by button press

        MicrophoneFourierIT::Update();

        sA.Update(MicrophoneFourierIT::GetFourierFiltered());
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
            Surprised();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Angry();
            else if (mode == 2) Mad();
            else if (mode == 3) Determination();
            else if (mode == 4) Happy();
            else if (mode == 5) Calm();
            else if (mode == 6) Sad();
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
        
        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();
        backgroundMaterial.Update();

        gradientMat.HueShift(fGenMatHue.Update());

        background.GetObject()->GetTransform()->SetPosition(Vector3D(0.0f, 0.0f, 1200.0f));

        background.GetObject()->UpdateTransform();

        int8_t faceSize = Menu::GetFaceSize();
        float menuRatio = Menu::ShowMenu();
        float scale = menuRatio * 0.6f + 0.4f;
        float xShift = (1.0f - menuRatio) * 80.0f;
        float yShift = (1.0f - menuRatio) * 30.0f + offsetFaceSA * -200.0f + offsetFaceARG * -200.0f + offsetFaceOSC * -200.0f;
        float adjustFacePos = float(faceSize) * 6.0f;
        float adjustFaceX = float(faceSize) * 0.05f;
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, -7.5f));
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(135.0f - xShift + xOffset - adjustFacePos, 67.5f - yShift + yOffset, 600.0f));
        pM.GetObject()->GetTransform()->SetScale(Vector3D(-0.625f + adjustFaceX, 0.825f, 1.0f).Multiply(scale));

        pM.GetObject()->UpdateTransform();
    }
};
