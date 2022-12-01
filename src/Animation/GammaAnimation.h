#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Objects\Background.h"
#include "..\Objects\LEDStripBackground.h"
#include "..\Morph\GammaFace.h"
#include "..\Render\Scene.h"
#include "..\Signals\FunctionGenerator.h"
#include "..\Menu\Menu.h"
#include "..\Sensors\APDS9960.h"

#include "..\Materials\Animated\RainbowNoise.h"
#include "..\Materials\Animated\RainbowSpiral.h"
#include "..\Materials\Animated\SpectrumAnalyzer.h"
#include "..\Materials\Animated\AudioReactiveGradient.h"
#include "..\Materials\Animated\Oscilloscope.h"

#include "..\Materials\MaterialAnimator.h"

#include "AnimationTracks\BlinkTrack.h"

#include "..\Signals\FFTVoiceDetection.h"

#include "..\Sensors\MicrophoneFourier_MAX9814.h"

#include "..\Render\ObjectAlign.h"

#include "..\Sensors\SHARPGP2Y.h"
#include "..\Sensors\SerialSync.h"
#include "..\Filter\KalmanFilter.h"

#ifdef FRONTFACE
#include "..\Sensors\SSD1306.h"
#endif

//0x28, 0x39, 0x3C

class GammaAnimation : public Animation<2> {
private:
    GammaFace pM;
    Background background;
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
    
    RGBColor gradientSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    GradientMaterial<6> gradientMat = GradientMaterial<6>(gradientSpectrum, 350.0f, false);
    
    MaterialAnimator<10> materialAnimator;
    MaterialAnimator<4> backgroundMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(400, 250), Vector2D(-150, 130), true, true); 
    AudioReactiveGradient aRG = AudioReactiveGradient(Vector2D(160, 160), Vector2D(-200, 100), true, true); 
    Oscilloscope oSC = Oscilloscope(Vector2D(200, 100), Vector2D(-200, 100));

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

    KalmanFilter<25> ratioCompensation = KalmanFilter<25>(0.1f);

    APDS9960 forehead;
    SHARPGP2Y boop = SHARPGP2Y(A9);
    #ifdef FRONTFACE
    SSD1306 oledDisplay;
    #endif

    FFTVoiceDetection<128> voiceDetection;

    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::BlushEye), GammaFace::BlushEye, 40, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::HideBlush), GammaFace::HideBlush, 10, 1.0f, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::HideEyeBrow), GammaFace::HideEyeBrow, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::HideSecondEye), GammaFace::HideSecondEye, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::OwOMouth), GammaFace::OwOMouth, 60, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::SadEye), GammaFace::SadEye, 70, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::SadEyeBrow), GammaFace::SadEyeBrow, 80, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::SadMouth), GammaFace::SadMouth, 90, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::FlatMouth), GammaFace::FlatMouth, 50, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::DeadEye), GammaFace::DeadEye, 1, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::HeartEye), GammaFace::HeartEye, 30, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::OwO), GammaFace::OwO, 90, 0.0f, 1.0f);
        
        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::AlphaGenCircle), GammaFace::AlphaGenCircle, 90, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::HideAll), GammaFace::HideAll, 90, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::AngryEyeMouth), GammaFace::AngryEyeMouth, 90, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(GammaFace::Gamma), GammaFace::Gamma, 20, 0.0f, 1.0f);

        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(GammaFace::ClosedEye));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(GammaFace::HideBlush, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(GammaFace::SadEye, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(GammaFace::SadEyeBrow, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(GammaFace::SadMouth, EasyEaseInterpolation::Cosine);

        eEA.SetInterpolationMethod(GammaFace::HideEyeBrow, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(GammaFace::HideSecondEye, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(GammaFace::AlphaGenCircle, EasyEaseInterpolation::Cosine);
    }

    void SetMaterialLayers(){
        materialAnimator.SetBaseMaterial(Material::Add, &rainbowNoise);
        materialAnimator.AddMaterial(Material::Replace, &orangeMaterial, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &whiteMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &greenMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Replace, &yellowMaterial, 40, 0.0f, 1.0f);//layer 4
        materialAnimator.AddMaterial(Material::Replace, &purpleMaterial, 40, 0.0f, 1.0f);//layer 5
        materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 6
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 7
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 8
        materialAnimator.AddMaterial(Material::Lighten, &gradientMat, 40, 0.1f, 1.0f);//layer 9

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){
        pM.Reset();
        blink.Play();

        eEA.AddParameterFrame(GammaFace::HideSecondEye, 1.0f);
        eEA.AddParameterFrame(GammaFace::Gamma, 1.0f);
    }

    void OwO(){
        blink.Pause();
        eEA.AddParameterFrame(GammaFace::BlushEye, 1.0f);
        eEA.AddParameterFrame(GammaFace::HideBlush, 0.0f);
        eEA.AddParameterFrame(GammaFace::HideEyeBrow, 1.0f);
        eEA.AddParameterFrame(GammaFace::HideSecondEye, 1.0f);
        eEA.AddParameterFrame(GammaFace::OwOMouth, 1.0f);
        eEA.AddParameterFrame(GammaFace::Gamma, 1.0f);

        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }

    void Sad(){
        blink.Play();
        eEA.AddParameterFrame(GammaFace::SadEye, 1.0f);
        eEA.AddParameterFrame(GammaFace::SadEyeBrow, 1.0f);
        eEA.AddParameterFrame(GammaFace::SadMouth, 1.0f);
        eEA.AddParameterFrame(GammaFace::Gamma, 1.0f);
        eEA.AddParameterFrame(GammaFace::HideSecondEye, 1.0f);
        
        materialAnimator.AddMaterialFrame(blueMaterial, 0.8f);
    }

    void Dead(){
        blink.Pause();
        eEA.AddParameterFrame(GammaFace::FlatMouth, 1.0f);
        eEA.AddParameterFrame(GammaFace::DeadEye, 1.0f);
        eEA.AddParameterFrame(GammaFace::Gamma, 1.0f);
        eEA.AddParameterFrame(GammaFace::HideSecondEye, 1.0f);

        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
    }
    
    void Heart(){
        blink.Pause();
        eEA.AddParameterFrame(GammaFace::HeartEye, 1.0f);
        eEA.AddParameterFrame(GammaFace::HideEyeBrow, 1.0f);
        eEA.AddParameterFrame(GammaFace::OwOMouth, 1.0f);
        eEA.AddParameterFrame(GammaFace::Gamma, 1.0f);
        eEA.AddParameterFrame(GammaFace::HideSecondEye, 1.0f);

        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }
    
    void OwO2(){
        blink.Pause();
        eEA.AddParameterFrame(GammaFace::HideBlush, 0.0f);
        eEA.AddParameterFrame(GammaFace::HideEyeBrow, 0.0f);
        eEA.AddParameterFrame(GammaFace::OwO, 1.0f);
        
        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }

    void AlphaGenCircle(){
        blink.Play();
        eEA.AddParameterFrame(GammaFace::HideBlush, 0.0f);
        eEA.AddParameterFrame(GammaFace::HideEyeBrow, 0.0f);
        eEA.AddParameterFrame(GammaFace::AlphaGenCircle, 1.0f);

        pM.SetMorphWeight(GammaFace::HideSecondEye, 0.0f);
    }

    void AngryFace(){
        blink.Play();
        pM.SetMorphWeight(GammaFace::HideSecondEye, 1.0f);
        
        eEA.AddParameterFrame(GammaFace::HideBlush, 1.0f);
        eEA.AddParameterFrame(GammaFace::HideEyeBrow, 1.0f);
        eEA.AddParameterFrame(GammaFace::AngryEyeMouth, 1.0f);
        eEA.AddParameterFrame(GammaFace::Gamma, 1.0f);
        pM.SetMorphWeight(GammaFace::HideSecondEye, 0.0f);
        
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
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
            //eEA.AddParameterFrame(GammaFace::vrc_v_ss, MicrophoneFourierIT::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourierIT::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourierIT::GetFourierFiltered(), MicrophoneFourierIT::GetSampleRate());
        
                //eEA.AddParameterFrame(GammaFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                //eEA.AddParameterFrame(GammaFace::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.AH));
                //eEA.AddParameterFrame(GammaFace::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.UH));
                //eEA.AddParameterFrame(GammaFace::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
                //eEA.AddParameterFrame(GammaFace::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                //eEA.AddParameterFrame(GammaFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                //eEA.AddParameterFrame(GammaFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
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
    GammaAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(background.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        pM.GetObject()->SetMaterial(&materialAnimator);
        background.GetObject()->SetMaterial(&backgroundMaterial);

        forehead.Initialize(5);
        #ifdef FRONTFACE
        oledDisplay.Initialize();
        #endif

        SerialSync::Initialize();
        MicrophoneFourierIT::Initialize(22, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max

        #ifdef FRONTFACE
        Menu::Initialize(9, 0, 500, Vector2D(380.0f, 180.0f));//7 is number of faces
        #elif defined(BACKFACE)
        Menu::Initialize(9, Vector2D(380.0f, 180.0f));//7 is number of faces
        #endif
        
        #ifdef FRONTFACE
        oledDisplay.Display();
        #endif
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    void Update(float ratio) override {
        pM.Reset();

        float xOffset = fGenMatXMove.Update();
        float yOffset = fGenMatYMove.Update();
        

        SetMaterialColor();

        MicrophoneFourierIT::Update();
        sA.SetHueAngle(ratio * 360.0f * 4.0f);
        sA.SetMirrorYState(Menu::MirrorSpectrumAnalyzer());
        sA.SetFlipYState(!Menu::MirrorSpectrumAnalyzer());
        
        aRG.SetRadius((xOffset + 2.0f) * 2.0f + 80.0f);
        aRG.SetSize(Vector2D((xOffset + 2.0f) * 10.0f + 50.0f, (xOffset + 2.0f) * 10.0f + 50.0f));
        aRG.SetHueAngle(ratio * 360.0f * 8.0f);
        aRG.SetRotation(ratio * 360.0f * 2.0f);
        aRG.SetPosition(Vector2D(-150.0f + xOffset * 4.0f, 130.0f + yOffset * 4.0f));

        oSC.SetRotation(20.0f);
        oSC.SetSize(Vector2D(400.0f, 200.0f));
        oSC.SetHueAngle(ratio * 360.0f * 8.0f);
        oSC.SetPosition(Vector2D(-150.0f, 130.0f));
        
        voiceDetection.SetThreshold(map(Menu::GetMicLevel(), 0, 10, 1000, 50));

        UpdateFFTVisemes();

        #ifdef BACKFACE

        SerialSync::Read();

        float currentOffset = 0.0f;
        if(ratio > SerialSync::GetRatio()) currentOffset = ratioCompensation.Filter(ratio - 1.0f - SerialSync::GetRatio());
        else currentOffset = ratioCompensation.Filter(ratio - SerialSync::GetRatio());

        //adjust current frame sync to new value
        ratio = fmod(ratio - currentOffset, 1.0f);//override input to synchronize from primary

        float mouthMove = SerialSync::GetMouthMove();

        Menu::SetFaceState(SerialSync::GetFaceState());
        Menu::SetBrightness(SerialSync::GetBrightness());
        Menu::SetAccentBrightness(SerialSync::GetAccentBrightness());
        Menu::SetUseMicrophone(SerialSync::UseMicrophone());
        Menu::SetMicLevel(SerialSync::GetMicLevel());
        Menu::SetUseBoopSensor(SerialSync::UseBoopSensor());
        Menu::SetMirrorSpectrumAnalyzer(SerialSync::MirrorSpectrumAnalyzer());
        Menu::SetFaceSize(SerialSync::GetFaceSize());
        Menu::SetFaceColor(SerialSync::GetFaceColor());

        bool isDead = SerialSync::GetDead();
        bool isBoop = SerialSync::GetBoop();

        Menu::SetCurrentMenu(SerialSync::GetCurrentMenu());

        Menu::Update(ratio);
        #else
        float mouthMove = MicrophoneFourierIT::GetCurrentMagnitude() / 2.0f;
        
        Menu::Update(ratio);

        SerialSync::SetMouthMove(mouthMove);
        SerialSync::SetMode(Menu::GetFaceState());
        SerialSync::SetRatio(ratio);
        
        SerialSync::SetFaceState(Menu::GetFaceState());
        SerialSync::SetBrightness(Menu::GetBrightness());
        SerialSync::SetAccentBrightness(Menu::GetAccentBrightness());
        SerialSync::SetUseMicrophone(Menu::UseMicrophone());
        SerialSync::SetMicLevel(Menu::GetMicLevel());
        SerialSync::SetUseBoopSensor(Menu::UseBoopSensor());
        SerialSync::SetMirrorSpectrumAnalyzer(Menu::MirrorSpectrumAnalyzer());
        SerialSync::SetFaceSize(Menu::GetFaceSize());
        SerialSync::SetFaceColor(Menu::GetFaceColor());

        bool isDead = forehead.GetValue() < 10;
        bool isBoop = boop.Update() > 2000;

        SerialSync::SetDead(isDead);
        SerialSync::SetBoop(isBoop);

        SerialSync::SetCurrentMenu(MenuHandler::GetCurrentMenu());

        SerialSync::Send();
        #endif

        Menu::SetPositionOffset(Vector2D(-300.0f, -40.0f));

        
        //bool isBooped = Menu::UseBoopSensor() ? boop.GetDistance(); : 0;
        uint8_t mode = Menu::GetFaceState();//change by button press

        if (isDead){
            Dead();
        }
        else if(isBoop){
            OwO();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Sad();
            else if (mode == 2) Heart();
            else if (mode == 3) OwO2();
            else if (mode == 4) AlphaGenCircle();
            else if (mode == 5) AngryFace();
            else if (mode == 6) {
                aRG.Update(MicrophoneFourierIT::GetFourierFiltered());
                AudioReactiveGradientFace();
            }
            else if (mode == 7){
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
        
        float menuRatio = 1.0f - Menu::ShowMenu();

        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();
        backgroundMaterial.Update();
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(-170.0f + xOffset * 2.0f, 30.0f + yOffset * 2.0f - offsetFace * 100.0f - menuRatio * 400.0f, 0.0f));
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 0.0f));
        pM.GetObject()->GetTransform()->SetScale(Vector3D(-1.0f, 1.0f - 2.0f * offsetFace, 1.0f));

        pM.GetObject()->UpdateTransform();
    }
};