#pragma once

#include "../Animation.h"
#include "../KeyFrameTrack.h"
#include "../EasyEaseAnimator.h"
#include "../../Objects/Background.h"
#include "../../Morph/MyntFace.h"
#include "../../Morph/MyntFood.h"
#include "../../Morph/MyntPacman.h"
#include "../../Morph/MyntSOS.h"
#include "../../Morph/MyntZZZ.h"
#include "../../Render/Scene.h"
#include "../../Signals/FunctionGenerator.h"
#include "../../Sensors/MenuButtonHandler.h"
#include "../../Sensors/BoopSensor.h"
#include "../../Sensors/MicrophoneFourier_MAX9814.h"

#include "../../Materials/Animated/SpectrumAnalyzer.h"
#include "../../Materials/Animated/RainbowNoise.h"
#include "../../Materials/Animated/RainbowSpiral.h"

#include "../../Materials/CombineMaterial.h"

#include "../AnimationTracks/BlinkTrack.h"

#include "../../Signals/FFTVoiceDetection.h"

class MyntAnimation : public Animation<6> {
private:
    MyntFace pM;
    MyntFood pacmanFood;
    MyntPacman pacman;
    MyntSOS sos;
    MyntZZZ zzz;
    Background background;
    //PacmanBody pacman;
    //PacmanFood pacmanFood;
    //SOS sos;
    EasyEaseAnimator<30> eEA = EasyEaseAnimator<30>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);

    //Materials
    RainbowNoise rainbowNoise;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial greenMaterial = SimpleMaterial(RGBColor(0, 255, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    SimpleMaterial yellowMaterial = SimpleMaterial(RGBColor(255, 255, 0));
    SimpleMaterial pinkMaterial = SimpleMaterial(RGBColor(255, 0, 255));

    //pacman food
    SimpleMaterial tealMaterial = SimpleMaterial(RGBColor(34, 248, 251));
    
    CombineMaterial<5> faceMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(250, 110), Vector2D(125, 60), true, true);

    //Animation controllers
    BlinkTrack<1> blink;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -3.5f, 3.5f, 2.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -3.5f, 3.5f, 2.7f);
    
    FunctionGenerator fGenMatPacman = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 0.4f);
    FunctionGenerator fGenMatScaleAnim = FunctionGenerator(FunctionGenerator::Sine, 1.0f, 2.0f, 1.3f);
    FunctionGenerator fGenMatScalePacman = FunctionGenerator(FunctionGenerator::Sine, 1.0f, 1.2f, 2.8f);

    BoopSensor boop;
    float redFaceMix = 0.0f;
    float pinkFaceMix = 0.0f;
    float blueFaceMix = 0.0f;
    uint8_t redFaceIndex = 51;
    uint8_t pinkFaceIndex = 52;
    uint8_t blueFaceIndex = 53;

    FFTVoiceDetection<128> voiceDetection;
    bool talk = true;
    bool hideFace = false;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::EyesAngry), MyntFace::EyesAngry, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::EyesDead), MyntFace::EyesDead, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::EyesHappy), MyntFace::EyesHappy, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::EyesHeart), MyntFace::EyesHeart, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::EyesHeartB), MyntFace::EyesHeartB, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::EyesClosed), MyntFace::EyesClosed, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::HideEyes), MyntFace::HideEyes, 60, 0.0f, 1.0f);
        
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::HideNose), MyntFace::HideNose, 60, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::MouthAngry), MyntFace::MouthAngry, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::MouthDead), MyntFace::MouthDead, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::MouthHappy), MyntFace::MouthHappy, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::MouthLove), MyntFace::MouthLove, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::MouthSleepy), MyntFace::MouthSleepy, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::HideMouth), MyntFace::HideMouth, 60, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::MouthTalk), MyntFace::MouthTalk, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MyntFace::MouthTalk2), MyntFace::MouthTalk2, 2, 0.0f, 1.0f);
        
        eEA.AddParameter(&redFaceMix, redFaceIndex, 40, 0.0f, 1.0f);
        eEA.AddParameter(&pinkFaceMix, pinkFaceIndex, 40, 0.0f, 1.0f);
        eEA.AddParameter(&blueFaceMix, blueFaceIndex, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(MyntFace::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(redFaceIndex, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(pinkFaceIndex, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(blueFaceIndex, EasyEaseInterpolation::Cosine);

        eEA.SetInterpolationMethod(MyntFace::EyesAngry, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(MyntFace::MouthAngry, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(MyntFace::EyesClosed, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(MyntFace::MouthSleepy, EasyEaseInterpolation::Cosine);

        eEA.SetInterpolationMethod(MyntFace::HideEyes, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(MyntFace::HideMouth, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(MyntFace::HideNose, EasyEaseInterpolation::Cosine);
        
        eEA.SetInterpolationMethod(MyntFace::MouthTalk, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(MyntFace::MouthTalk2, EasyEaseInterpolation::Linear);
    }

    void SetMaterials(){
        faceMaterial.AddMaterial(Material::Add, &greenMaterial, 1.0f);
        faceMaterial.AddMaterial(Material::Replace, &redMaterial, 0.0f);
        faceMaterial.AddMaterial(Material::Replace, &pinkMaterial, 0.0f);
        faceMaterial.AddMaterial(Material::Replace, &blueMaterial, 0.0f);
        faceMaterial.AddMaterial(Material::Lighten, &rainbowNoise, 0.1f);
    }

public:
    MyntAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(background.GetObject());
        scene.AddObject(pacmanFood.GetObject());
        scene.AddObject(pacman.GetObject());
        scene.AddObject(sos.GetObject());
        scene.AddObject(zzz.GetObject());


        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterials();

        pM.GetObject()->SetMaterial(&faceMaterial);
        pacmanFood.GetObject()->SetMaterial(&tealMaterial);//Default color is white
        pacman.GetObject()->SetMaterial(&yellowMaterial);
        sos.GetObject()->SetMaterial(&yellowMaterial);
        zzz.GetObject()->SetMaterial(&blueMaterial);

        MenuButtonHandler::Initialize(0, 9, 1000);//8 is number of faces

        MicrophoneFourier::Initialize(22, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max

        boop.Initialize(5);

        background.GetObject()->SetMaterial(&sA);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){}

    void Angry(){
        eEA.AddParameterFrame(MyntFace::EyesAngry, 1.0f);
        eEA.AddParameterFrame(MyntFace::MouthAngry, 1.0f);
        eEA.AddParameterFrame(redFaceIndex, 0.8f);
    }

    void Dead(){
        blink.Pause();
        eEA.AddParameterFrame(MyntFace::EyesDead, 1.0f);
        eEA.AddParameterFrame(MyntFace::MouthDead, 1.0f);
        eEA.AddParameterFrame(redFaceIndex, 0.8f);
    }

    void Happy(){
        eEA.AddParameterFrame(MyntFace::EyesHappy, 1.0f);
        eEA.AddParameterFrame(MyntFace::MouthHappy, 1.0f);
    }
    
    void Love(){
        eEA.AddParameterFrame(MyntFace::EyesHeart, 1.0f);
        eEA.AddParameterFrame(MyntFace::MouthLove, 1.0f);
        eEA.AddParameterFrame(pinkFaceIndex, 0.8f);
    }
    
    void Sleepy(){
        blink.Pause();
        eEA.AddParameterFrame(MyntFace::EyesClosed, 1.0f);
        eEA.AddParameterFrame(MyntFace::MouthSleepy, 1.0f);
        eEA.AddParameterFrame(blueFaceIndex, 0.8f);
    }

    void SleepyZZZ(){
        zzz.Reset();

        zzz.GetObject()->Enable();

        blink.Pause();
        eEA.AddParameterFrame(MyntFace::HideEyes, 1.0f);
        eEA.AddParameterFrame(MyntFace::HideMouth, 1.0f);
        eEA.AddParameterFrame(MyntFace::HideNose, 1.0f);
        eEA.AddParameterFrame(blueFaceIndex, 0.8f);

        talk = false;
        hideFace = true;
    }

    void SOSFace(){
        sos.Reset();

        sos.GetObject()->Enable();

        blink.Pause();
        eEA.AddParameterFrame(MyntFace::HideEyes, 1.0f);
        eEA.AddParameterFrame(MyntFace::HideMouth, 1.0f);
        eEA.AddParameterFrame(MyntFace::HideNose, 1.0f);

        talk = false;
        hideFace = true;
    }

    void PacmanFace(){
        pacmanFood.GetObject()->Enable();
        pacman.GetObject()->Enable();

        pacmanFood.Reset();
        pacman.Reset();

        blink.Pause();
        eEA.AddParameterFrame(MyntFace::HideEyes, 1.0f);
        eEA.AddParameterFrame(MyntFace::HideMouth, 1.0f);
        eEA.AddParameterFrame(MyntFace::HideNose, 1.0f);
        
        talk = false;
        hideFace = true;
    }

    void SpectrumAnalyzerFace(){
        blink.Pause();
        pM.GetObject()->Disable();
        background.GetObject()->Enable();

        talk = false;
        hideFace = true;
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    void UpdateFFTVisemes(){
        if(MenuButtonHandler::UseMicrophone() && talk){
            float mouthOpen = MicrophoneFourier::GetCurrentMagnitude() / 3.0f;
            float mouthForward = 0.0f;

            if(MicrophoneFourier::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourier::GetFourierFiltered(), MicrophoneFourier::GetSampleRate());

                mouthOpen += voiceDetection.GetViseme(voiceDetection.EE) + voiceDetection.GetViseme(voiceDetection.AH) + voiceDetection.GetViseme(voiceDetection.UH) +
                    voiceDetection.GetViseme(voiceDetection.AH);
                mouthForward = voiceDetection.GetViseme(voiceDetection.AR) + voiceDetection.GetViseme(voiceDetection.ER) + voiceDetection.GetViseme(voiceDetection.OO);
    
                mouthOpen = Mathematics::Constrain(mouthOpen, 0.0f, 1.0f);
                mouthForward = Mathematics::Constrain(mouthForward, 0.0f, 1.0f);
                
                eEA.AddParameterFrame(MyntFace::MouthTalk, mouthOpen);
                eEA.AddParameterFrame(MyntFace::MouthTalk2, mouthForward);
            }
        }
    }

    void Update(float ratio) override {
        pM.Reset();

        pM.GetObject()->Enable();
        background.GetObject()->Disable();
        pacmanFood.GetObject()->Disable();
        pacman.GetObject()->Disable();
        sos.GetObject()->Disable();
        zzz.GetObject()->Disable();

        blink.Play();
        talk = true;
        hideFace = false;

        bool isBooped = MenuButtonHandler::UseBoopSensor() ? boop.isBooped() : 0;
        uint8_t mode = MenuButtonHandler::GetFaceState();//change by button press

        MicrophoneFourier::Update();
        sA.Update(MicrophoneFourier::GetFourierFiltered());
        sA.SetHueAngle(ratio * 360.0f * 4.0f);
        sA.SetMirrorYState(MenuButtonHandler::MirrorSpectrumAnalyzer());
        sA.SetFlipYState(!MenuButtonHandler::MirrorSpectrumAnalyzer());

        if (isBooped && mode != 6){
            Angry();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Dead();
            else if (mode == 2) Happy();
            else if (mode == 3) Love();
            else if (mode == 4) Sleepy();
            else if (mode == 5) SleepyZZZ();
            else if (mode == 6) SOSFace();
            else if (mode == 7) PacmanFace();
            else SpectrumAnalyzerFace();
        }
        
        UpdateFFTVisemes();
        UpdateKeyFrameTracks();
        
        pM.SetMorphWeight(MyntFace::IncreaseSize, 1.0f);
        pacman.SetMorphWeight(MyntPacman::MouthClosed, fGenMatPacman.Update());

        eEA.Update();
        pM.Update();
        pacmanFood.Update();
        pacman.Update();
        zzz.Update();
        sos.Update();
        
        rainbowNoise.Update(ratio);
    
        faceMaterial.SetOpacity(1, redFaceMix);//set face to angry
        faceMaterial.SetOpacity(2, pinkFaceMix);//set face to angry
        faceMaterial.SetOpacity(3, blueFaceMix);//set face to angry

        float x = fGenMatXMove.Update();
        float y = fGenMatYMove.Update();

        if(hideFace){
            pM.GetObject()->GetTransform()->SetPosition(Vector3D(0, -1000.0f, 600.0f));
        }
        else{
            pM.GetObject()->GetTransform()->SetPosition(Vector3D(x, y, 600.0f));
        }
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 0.0f));
        pM.GetObject()->GetTransform()->SetScale(Vector3D(1.0f, 1.0f, 1.0f));
        pM.GetObject()->UpdateTransform();

        float scalePacman = fGenMatScalePacman.Update();
        float pacmanPos = 400.0f * (0.5f - ratio);
        int pacmanFoodPos = pacmanPos < 0 ? (int(pacmanPos) / 25) * 25 : -(int(pacmanPos) / 25) * 50;

        Vector3D pCenter = pacman.GetObject()->GetCenterOffset();
        pacmanFood.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 0.0f));
        pacmanFood.GetObject()->GetTransform()->SetPosition(Vector3D(x + pacmanFoodPos, y, 700.0f));
        pacmanFood.GetObject()->GetTransform()->SetScale(Vector3D(scalePacman, scalePacman, scalePacman));
        pacmanFood.GetObject()->GetTransform()->SetScaleOffset(pCenter);
        pacmanFood.GetObject()->UpdateTransform();
        
        pacman.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 0.0f));
        pacman.GetObject()->GetTransform()->SetPosition(Vector3D(x + pacmanPos, y, 600.0f));
        pacman.GetObject()->GetTransform()->SetScale(Vector3D(scalePacman, scalePacman, scalePacman));
        pacman.GetObject()->GetTransform()->SetScaleOffset(pCenter);
        pacman.GetObject()->UpdateTransform();

        float scaleAnim = fGenMatScaleAnim.Update();
        float scaleSOS = 0.5f + scaleAnim / 2.0f;

        Vector3D sosCenter = sos.GetObject()->GetCenterOffset();
        sos.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, ratio * 360.0f, 0.0f));
        sos.GetObject()->GetTransform()->SetRotationOffset(sosCenter);
        sos.GetObject()->GetTransform()->SetPosition(Vector3D(x - 5.0f, y - 15.0f, 600.0f));
        sos.GetObject()->GetTransform()->SetScale(Vector3D(scaleSOS, scaleSOS, scaleSOS));
        sos.GetObject()->GetTransform()->SetScaleOffset(sosCenter);
        sos.GetObject()->UpdateTransform();

        float scaleZZZ = 0.9f + scaleAnim / 5.0f;

        Vector3D zzzCenter = zzz.GetObject()->GetCenterOffset();
        zzz.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, ratio * 360.0f, 0.0f));
        zzz.GetObject()->GetTransform()->SetRotationOffset(zzzCenter);
        zzz.GetObject()->GetTransform()->SetPosition(Vector3D(x - 15.0f, y - 15.0f, 600.0f));
        zzz.GetObject()->GetTransform()->SetScale(Vector3D(scaleZZZ, scaleZZZ, scaleZZZ));
        zzz.GetObject()->GetTransform()->SetScaleOffset(zzzCenter);
        zzz.GetObject()->UpdateTransform();
    }
};
