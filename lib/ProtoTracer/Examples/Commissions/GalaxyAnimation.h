#pragma once

#include "../Animation.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Morph/Commissions/GalaxyFace.h"
#include "../../Render/Scene.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Menu/SingleButtonMenu.h"
#include "../../Sensors/APDS9960.h"

#include "../../Materials/Animated/SpectrumAnalyzer.h"
#include "../../Materials/Animated/AudioReactiveGradient.h"
#include "../../Materials/Animated/Oscilloscope.h"
#include "../../Materials/Animated/RainbowNoise.h"
#include "../../Materials/Animated/RainbowSpiral.h"

#include "../../Materials/MaterialAnimator.h"
#include "../../Materials/MaterialMask.h"
#include "../../Shapes/Ellipse.h"

#include "../AnimationTracks/BlinkTrack.h"
#include "../AnimationTracks/EyeMoveTrack.h"
#include "../../Sensors/MicrophoneFourier_MAX9814.h"
#include "../../Render/ObjectAlign.h"


class GalaxyAnimation : public Animation<2> {
private:
    GalaxyFace pM;
    Background background;
    EasyEaseAnimator<20> eEA = EasyEaseAnimator<20>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    
    Ellipse blush = Ellipse(Vector2D(98.0f, 26.0f), Vector2D(60.0f, 45.0f), 0.0f);

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
    
    RGBColor gradientSpectrum[2] = {RGBColor(5, 162, 232), RGBColor(10, 170, 255)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);
    
    MaterialMask blushMask = MaterialMask(&redMaterial, &gradientMat, &blush);

    MaterialAnimator<10> materialAnimator;
    MaterialAnimator<4> backgroundMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(200, 100), Vector2D(100, 50), true, true); 
    AudioReactiveGradient aRG = AudioReactiveGradient(Vector2D(160, 160), Vector2D(0, 0), true, true); 
    Oscilloscope oSC = Oscilloscope(Vector2D(200, 100), Vector2D(0, 0));

    //Animation controllers
    BlinkTrack<1> blink;
    EyeMoveTrack<1> eyeMove;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 2.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 2.7f);
    FunctionGenerator fGenMatHue = FunctionGenerator(FunctionGenerator::Triangle, 0.0f, 360.0f, 17.3f);
    FunctionGenerator fGenEyeLook1 = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 2.5f);

    APDS9960 boop;
    
    ObjectAlign objA = ObjectAlign(Vector2D(0.0f, 0.0f), Vector2D(170.0f, 125.0f), Quaternion());
    
    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    float eyeMoveParameter = 0.0f;
    float eyeBack = 0.0f;
    float eyePos = 0.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;
    uint8_t eyeForwardInd = 54;
    bool mirror = false;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(GalaxyFace::OvO), GalaxyFace::OvO, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(GalaxyFace::EyeBack), GalaxyFace::EyeBack, 100, 0.0f, 1.0f);
        eEA.AddParameter(&eyeBack, GalaxyFace::EyeBack2, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(GalaxyFace::HappyEye), GalaxyFace::HappyEye, 50, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(GalaxyFace::HappyMouth), GalaxyFace::HappyMouth, 90, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(GalaxyFace::Talk), GalaxyFace::Talk, 4, 0.0f, 1.0f);
        
        eEA.AddParameter(pM.GetMorphWeightReference(GalaxyFace::HideBlush), GalaxyFace::HideBlush, 60, 1.0f, 0.0f);

        eEA.AddParameter(&offsetFace, offsetFaceInd, 80, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 80, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 80, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 80, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(GalaxyFace::Blink));
        eyeMove.AddParameter(&eyeMoveParameter);
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(GalaxyFace::HideBlush, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(GalaxyFace::EyeBack, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(GalaxyFace::EyeBack2, EasyEaseInterpolation::Cosine);
        
        eEA.SetInterpolationMethod(GalaxyFace::Talk, EasyEaseInterpolation::Linear);

        eEA.SetInterpolationMethod(eyeForwardInd, EasyEaseInterpolation::Cosine);
    }

    void SetMaterialLayers(){
        materialAnimator.SetBaseMaterial(Material::Add, &blushMask);
        materialAnimator.AddMaterial(Material::Replace, &orangeMaterial, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &whiteMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &greenMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Replace, &yellowMaterial, 40, 0.0f, 1.0f);//layer 4
        materialAnimator.AddMaterial(Material::Replace, &purpleMaterial, 40, 0.0f, 1.0f);//layer 5
        materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 6
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 7
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 8
        materialAnimator.AddMaterial(Material::Lighten, &rainbowNoise, 40, 0.0f, 1.0f);//layer 9
        
        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
        eyeMove.Update();
    }

    void Default(){}

    void Blush(){
        eEA.AddParameterFrame(GalaxyFace::OvO, 1.0f);
        eEA.AddParameterFrame(GalaxyFace::HideBlush, 0.0f);
    }

    void EyeBack(){
        eEA.AddParameterFrame(GalaxyFace::EyeBack, 1.0f);
    }

    void EyeBack2(){
        eEA.AddParameterFrame(GalaxyFace::EyeBack2, 1.0f);
    }
    
    void Happy(){
        eEA.AddParameterFrame(GalaxyFace::HappyEye, 1.0f);
        eEA.AddParameterFrame(GalaxyFace::HappyMouth, 1.0f);
    }

    void HappyRainbow(){
        eEA.AddParameterFrame(GalaxyFace::HappyEye, 1.0f);
        eEA.AddParameterFrame(GalaxyFace::HappyMouth, 1.0f);
        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
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
            eEA.AddParameterFrame(GalaxyFace::Talk, MicrophoneFourierIT::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourierIT::GetCurrentMagnitude() > 0.05f){
                //voiceDetection.Update(MicrophoneFourierIT::GetFourierFiltered(), MicrophoneFourierIT::GetSampleRate());
        
                //eEA.AddParameterFrame(GalaxyFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                //eEA.AddParameterFrame(GalaxyFace::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.AH));
                //eEA.AddParameterFrame(GalaxyFace::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.UH));
                //eEA.AddParameterFrame(GalaxyFace::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
                //eEA.AddParameterFrame(GalaxyFace::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                //eEA.AddParameterFrame(GalaxyFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                //eEA.AddParameterFrame(GalaxyFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
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
    GalaxyAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(background.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        pM.GetObject()->SetMaterial(&materialAnimator);
        background.GetObject()->SetMaterial(&backgroundMaterial);

        boop.Initialize(5);

        MicrophoneFourierIT::Initialize(22, 8000, 30.0f, 100.0f);//8KHz sample rate, 50dB min, 120dB max
        Menu::Initialize(4, 0, 500);//7 is number of faces

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
    
    void SetCameraMirror(bool mirror){
        this->mirror = mirror;
    }

    void Update(float ratio) override {

        if(!mirror){
            pM.Reset();

            float xOffset = fGenMatXMove.Update();
            float yOffset = fGenMatYMove.Update();
            
            Menu::Update(ratio * 2.0f - floor(ratio));

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
            
            UpdateFFTVisemes();

            if (isBooped){
                Blush();
            }
            else{
                if (mode == 0) Default();
                else if (mode == 1) EyeBack2();
                else if (mode == 2) Happy();
                else HappyRainbow();
            }

            UpdateKeyFrameTracks();

            eyePos = fGenEyeLook1.Update();
            
            float leftEye = eyePos > 0.5f ? Mathematics::Map(eyePos, 0.5f, 1.0f, 0.0f, 1.0f) : 0.0f;

            //left eye
            pM.SetMorphWeight(GalaxyFace::EyeBack2, leftEye * eyeMoveParameter * eyeBack);

            eEA.Update();
            pM.Update();

            blushMask.SetOpacity(eEA.GetValue(GalaxyFace::OvO));
            
            float menuRatio = Menu::ShowMenu();

            rainbowNoise.Update(ratio);
            rainbowSpiral.Update(ratio);
            materialAnimator.Update();
            backgroundMaterial.Update();
            
            pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, -7.5f));

            uint8_t faceSize = Menu::GetFaceSize();

            float scale = menuRatio * 0.5f + 0.5f;
            float faceSizeOffset = faceSize * 8.0f;
            
            objA.SetEdgeMargin(2.0f);
            objA.SetCameraMax(Vector2D(110.0f + faceSizeOffset, 125.0f).Multiply(scale));

            objA.AlignObjects(scene.GetObjects(), 1);

            pM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset + 5.0f, yOffset - 150.0f * offsetFace + 5.0f, 0.0f));
            pM.GetObject()->UpdateTransform();
        }
        else {
            pM.Reset();

            UpdateKeyFrameTracks();

            float xOffset = fGenMatXMove.Update();
            float yOffset = fGenMatYMove.Update();
            
            float rightEye = eyePos <= 0.5f ? Mathematics::Map(eyePos, 0.5f, 0.0f, 0.0f, 1.0f) : 0.0f;

            //right eye
            pM.SetMorphWeight(GalaxyFace::EyeBack2, rightEye * eyeMoveParameter * eyeBack);
            
            eEA.SetParameters();
            pM.Update();

            pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, -7.5f));

            uint8_t faceSize = Menu::GetFaceSize();

            float menuRatio = Menu::ShowMenu();
            float scale = menuRatio * 0.5f + 0.5f;
            float faceSizeOffset = faceSize * 8.0f;
            
            objA.SetEdgeMargin(2.0f);
            objA.SetCameraMax(Vector2D(110.0f + faceSizeOffset, 125.0f).Multiply(scale));

            objA.AlignObjects(scene.GetObjects(), 1);

            pM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset + 5.0f, yOffset - 150.0f * offsetFace + 5.0f, 0.0f));
            pM.GetObject()->UpdateTransform();
        }
    }
};
