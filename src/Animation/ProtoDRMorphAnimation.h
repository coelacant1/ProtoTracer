#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Morph\ProtoDRMorph.h"
#include "..\Render\Scene.h"
#include "..\Signals\FunctionGenerator.h"

#include "..\Objects\Spyro.h"
#include "..\Objects\Background.h"

#include "..\Materials\Animated\SpectrumAnalyzer.h"
#include "..\Materials\Animated\RainbowNoise.h"
#include "..\Materials\Animated\RainbowSpiral.h"
#include "..\Materials\CombineMaterial.h"
#include "..\Materials\GradientMaterial.h"
#include "..\Materials\MaterialAnimator.h"
#include "..\Materials\NormalMaterial.h"
#include "..\Materials\StripeMaterial.h"

#include "..\Signals\FFTVoiceDetection.h"
#include "..\Sensors\MenuButtonHandler.h"
#include "..\Sensors\SerialSync.h"

class ProtoDRMorphAnimation : public Animation<2>{
private:
    ProtoDR pM;
    Background background;
    Spyro spyro;
    EasyEaseAnimator<30> eEA = EasyEaseAnimator<30>(EasyEaseInterpolation::Cosine);
    
    //Materials
    RGBColor gradientSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};

    RainbowNoise rainbowNoise;
    RainbowSpiral rainbowSpiral;
    StripeMaterial stripe1 = StripeMaterial(6, gradientSpectrum, 200.0f, 160.0f, 20.0f);
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255)); 
    SimpleMaterial blackMaterial = SimpleMaterial(RGBColor(0,0,0));
    NormalMaterial normalMaterial;
    
    GradientMaterial<6> gradientMat = GradientMaterial<6>(gradientSpectrum, 350.0f, false);
    
    MaterialAnimator<7> materialAnimator;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(A8, Vector2D(430, 300), Vector2D(15, 120), true, true);

    FunctionGenerator fGenMatSize = FunctionGenerator(FunctionGenerator::Sine, 450.0f, 550.0f, 2.1f);
    FunctionGenerator fGenMatWidth = FunctionGenerator(FunctionGenerator::Sine, 150.0f, 500.0f, 4.0f);
    FunctionGenerator fGenMatPeriod = FunctionGenerator(FunctionGenerator::Sine, 200.0f, 500.0f, 6.3f);
    FunctionGenerator fGenMatAmplitude = FunctionGenerator(FunctionGenerator::Sine, -100.0f, 100.0f, 2.7f);
    FunctionGenerator fGenMatOpacity = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 0.5f);
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);

    KeyFrameTrack<1, 10> blink = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 5> topFinOuter = KeyFrameTrack<1, 5>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 5> topFinInner = KeyFrameTrack<1, 5>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 5> topFinGap = KeyFrameTrack<1, 5>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 5> midFin = KeyFrameTrack<1, 5>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR1 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR2 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR3 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR4 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR5 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 5> mouth = KeyFrameTrack<1, 5>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);

    FFTVoiceDetection<128> voiceDetection;
    
    bool talk = true;

    void SetMaterialLayers(){
        materialAnimator.SetBaseMaterial(Material::Add, &rainbowNoise);
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &stripe1, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Replace, &normalMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Lighten, &gradientMat, 40, 0.25f, 1.0f);//layer 4
    }

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::BlushEye), ProtoDR::BlushEye, 40, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::HideBlush), ProtoDR::HideBlush, 10, 1.0f, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::HideEyeBrow), ProtoDR::HideEyeBrow, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::OwOMouth), ProtoDR::OwOMouth, 60, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::SadEye), ProtoDR::SadEye, 70, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::SadEyeBrow), ProtoDR::SadEyeBrow, 80, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::SadMouth), ProtoDR::SadMouth, 90, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::FlatMouth), ProtoDR::FlatMouth, 50, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::DeadEye), ProtoDR::DeadEye, 1, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::HeartEye), ProtoDR::HeartEye, 30, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::OwO), ProtoDR::OwO, 90, 0.0f, 1.0f);
        
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::AlphaGenCircle), ProtoDR::AlphaGenCircle, 90, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::AlphaGenSquare), ProtoDR::AlphaGenSquare, 90, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::HideAll), ProtoDR::HideAll, 90, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::NewFins), ProtoDR::NewFins, 90, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::AngryEyeMouth), ProtoDR::AngryEyeMouth, 90, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(ProtoDR::ClosedEye));

        topFinOuter.AddParameter(pM.GetMorphWeightReference(ProtoDR::TopFinOuterThin));
        topFinInner.AddParameter(pM.GetMorphWeightReference(ProtoDR::TopFinInnerThin));
        topFinGap.AddParameter(pM.GetMorphWeightReference(ProtoDR::TopFinInnerCloseGap));

        midFin.AddParameter(pM.GetMorphWeightReference(ProtoDR::MidFinBotThin));
        midFin.AddParameter(pM.GetMorphWeightReference(ProtoDR::MidFinMidBigger));
        midFin.AddParameter(pM.GetMorphWeightReference(ProtoDR::MidFinTopThin));

        botFinLR1.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR1Thin));
        botFinLR2.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR2Thin));
        botFinLR3.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR3Thin));
        botFinLR4.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR4Thin));
        botFinLR5.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR5Thin));

        mouth.AddParameter(pM.GetMorphWeightReference(ProtoDR::ShockedMouth));
    }

    void AddBlinkKeyFrames(){
        blink.AddKeyFrame(0.0f, 0.0f);
        blink.AddKeyFrame(2.75f, 0.0f);
        blink.AddKeyFrame(3.0f, 1.0f);
        blink.AddKeyFrame(3.25f, 0.0f);
        blink.AddKeyFrame(9.75f, 0.0f);
        blink.AddKeyFrame(10.0f, 1.0f);
        blink.AddKeyFrame(10.25f, 0.0f);
        blink.AddKeyFrame(10.75f, 0.0f);
        blink.AddKeyFrame(11.0f, 1.0f);
        blink.AddKeyFrame(11.25f, 0.0f);
        blink.AddKeyFrame(15.0f, 0.0f);
    }

    void AddTopFinKeyFrames(){
        topFinOuter.AddKeyFrame(0.0f, 0.0f);
        topFinOuter.AddKeyFrame(1.5f, 1.0f);
        topFinOuter.AddKeyFrame(3.0f, 0.0f);

        topFinInner.AddKeyFrame(0.0f, 0.0f);
        topFinInner.AddKeyFrame(0.5f, 0.0f);
        topFinInner.AddKeyFrame(1.5f, 1.0f);
        topFinInner.AddKeyFrame(2.5f, 0.0f);
        topFinInner.AddKeyFrame(3.0f, 0.0f);

        topFinGap.AddKeyFrame(0.0f, 0.0f);
        topFinGap.AddKeyFrame(1.0f, 0.0f);
        topFinGap.AddKeyFrame(1.5f, 1.0f);
        topFinGap.AddKeyFrame(2.0f, 0.0f);
        topFinGap.AddKeyFrame(3.0f, 0.0f);
    }

    void AddMidFinKeyFrames(){
        midFin.AddKeyFrame(0.0f, 0.0f);
        midFin.AddKeyFrame(2.5f, 1.0f);
        midFin.AddKeyFrame(5.0f, 0.0f);
    }

    void AddBotFinKeyFrames(){
        botFinLR1.AddKeyFrame(0.0f, 0.0f);
        botFinLR2.AddKeyFrame(0.0f, 0.0f);
        botFinLR3.AddKeyFrame(0.0f, 0.0f);
        botFinLR4.AddKeyFrame(0.0f, 0.0f);
        botFinLR5.AddKeyFrame(0.0f, 1.0f);

        botFinLR1.AddKeyFrame(0.25f, 1.0f);
        botFinLR2.AddKeyFrame(0.25f, 0.0f);
        botFinLR3.AddKeyFrame(0.25f, 0.0f);
        botFinLR4.AddKeyFrame(0.25f, 0.0f);
        botFinLR5.AddKeyFrame(0.25f, 0.0f);

        botFinLR1.AddKeyFrame(0.5f, 0.0f);
        botFinLR2.AddKeyFrame(0.5f, 1.0f);
        botFinLR3.AddKeyFrame(0.5f, 0.0f);
        botFinLR4.AddKeyFrame(0.5f, 0.0f);
        botFinLR5.AddKeyFrame(0.5f, 0.0f);

        botFinLR1.AddKeyFrame(0.75f, 0.0f);
        botFinLR2.AddKeyFrame(0.75f, 0.0f);
        botFinLR3.AddKeyFrame(0.75f, 1.0f);
        botFinLR4.AddKeyFrame(0.75f, 0.0f);
        botFinLR5.AddKeyFrame(0.75f, 0.0f);

        botFinLR1.AddKeyFrame(1.0f, 0.0f);
        botFinLR2.AddKeyFrame(1.0f, 0.0f);
        botFinLR3.AddKeyFrame(1.0f, 0.0f);
        botFinLR4.AddKeyFrame(1.0f, 1.0f);
        botFinLR5.AddKeyFrame(1.0f, 0.0f);
        
        botFinLR1.AddKeyFrame(1.25f, 0.0f);
        botFinLR2.AddKeyFrame(1.25f, 0.0f);
        botFinLR3.AddKeyFrame(1.25f, 0.0f);
        botFinLR4.AddKeyFrame(1.25f, 0.0f);
        botFinLR5.AddKeyFrame(1.25f, 1.0f);
    }

    void AddMouthKeyFrames(){
        mouth.AddKeyFrame(0.0f, 0.0f);
        mouth.AddKeyFrame(1.5f, 1.0f);
        mouth.AddKeyFrame(4.0f, 0.0f);
    }

public:
    ProtoDRMorphAnimation() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(spyro.GetObject());
        scene.AddObject(background.GetObject());

        LinkEasyEase();
        LinkParameters();

        AddBlinkKeyFrames();
        AddTopFinKeyFrames();
        AddMidFinKeyFrames();
        AddBotFinKeyFrames();
        AddMouthKeyFrames();

        SetMaterialLayers();

        pM.GetObject()->SetMaterial(&materialAnimator);
        background.GetObject()->SetMaterial(&sA);

        SerialSync::Initialize();
        MenuButtonHandler::Initialize(15, 11, 1000);//7 is number of faces
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
        topFinOuter.Update();
        topFinInner.Update();
        topFinGap.Update();
        midFin.Update();
        botFinLR1.Update();
        botFinLR2.Update();
        botFinLR3.Update();
        botFinLR4.Update();
        botFinLR5.Update();
        mouth.Update();
    }

    void Default(){
        pM.Reset();
        blink.Play();
        mouth.Play();
        
        topFinOuter.Play();
        topFinInner.Play();
        topFinGap.Play();
        midFin.Play();
        botFinLR1.Play();
        botFinLR2.Play();
        botFinLR3.Play();
        botFinLR4.Play();
        botFinLR5.Play();

        talk = true;
    }

    void OwO(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Play();

        topFinOuter.Play();
        topFinInner.Play();
        topFinGap.Play();
        midFin.Play();
        botFinLR1.Play();
        botFinLR2.Play();
        botFinLR3.Play();
        botFinLR4.Play();
        botFinLR5.Play();

        eEA.AddParameterFrame(ProtoDR::BlushEye, 1.0f);
        eEA.AddParameterFrame(ProtoDR::HideBlush, 0.0f);
        eEA.AddParameterFrame(ProtoDR::HideEyeBrow, 1.0f);
        eEA.AddParameterFrame(ProtoDR::OwOMouth, 1.0f);
        
        talk = true;
    }

    void Sad(){
        pM.Reset();
        blink.Play();
        mouth.Pause();
        mouth.Reset();
        
        topFinOuter.Play();
        topFinInner.Play();
        topFinGap.Play();
        midFin.Play();
        botFinLR1.Play();
        botFinLR2.Play();
        botFinLR3.Play();
        botFinLR4.Play();
        botFinLR5.Play();

        eEA.AddParameterFrame(ProtoDR::SadEye, 1.0f);
        eEA.AddParameterFrame(ProtoDR::SadEyeBrow, 1.0f);
        eEA.AddParameterFrame(ProtoDR::SadMouth, 1.0f);
        
        materialAnimator.AddMaterialFrame(blueMaterial, 0.8f);

        talk = true;
    }

    void Dead(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();
        
        topFinOuter.Play();
        topFinInner.Play();
        topFinGap.Play();
        midFin.Play();
        botFinLR1.Play();
        botFinLR2.Play();
        botFinLR3.Play();
        botFinLR4.Play();
        botFinLR5.Play();
        
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);

        eEA.AddParameterFrame(ProtoDR::FlatMouth, 1.0f);
        eEA.AddParameterFrame(ProtoDR::DeadEye, 1.0f);

        talk = true;
    }

    void Heart(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Play();
        
        topFinOuter.Play();
        topFinInner.Play();
        topFinGap.Play();
        midFin.Play();
        botFinLR1.Play();
        botFinLR2.Play();
        botFinLR3.Play();
        botFinLR4.Play();
        botFinLR5.Play();
        
        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);

        eEA.AddParameterFrame(ProtoDR::HeartEye, 1.0f);
        eEA.AddParameterFrame(ProtoDR::HideEyeBrow, 1.0f);
        eEA.AddParameterFrame(ProtoDR::OwOMouth, 1.0f);

        talk = true;
    }

    void OwO2(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();
        
        topFinOuter.Pause();
        topFinInner.Pause();
        topFinGap.Pause();
        midFin.Pause();
        botFinLR1.Pause();
        botFinLR2.Pause();
        botFinLR3.Pause();
        botFinLR4.Pause();
        botFinLR5.Pause();
        
        topFinOuter.Reset();
        topFinInner.Reset();
        topFinGap.Reset();
        midFin.Reset();
        botFinLR1.Reset();
        botFinLR2.Reset();
        botFinLR3.Reset();
        botFinLR4.Reset();
        botFinLR5.Reset();
        
        eEA.AddParameterFrame(ProtoDR::HideBlush, 0.0f);
        eEA.AddParameterFrame(ProtoDR::HideEyeBrow, 0.0f);
        eEA.AddParameterFrame(ProtoDR::OwO, 1.0f);
        
        materialAnimator.AddMaterialFrame(stripe1, 0.8f);

        talk = false;
    }

    void AlphaGenSquare(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();
        
        topFinOuter.Pause();
        topFinInner.Pause();
        topFinGap.Pause();
        midFin.Pause();
        botFinLR1.Pause();
        botFinLR2.Pause();
        botFinLR3.Pause();
        botFinLR4.Pause();
        botFinLR5.Pause();

        topFinOuter.Reset();
        topFinInner.Reset();
        topFinGap.Reset();
        midFin.Reset();
        botFinLR1.Reset();
        botFinLR2.Reset();
        botFinLR3.Reset();
        botFinLR4.Reset();
        botFinLR5.Reset();

        pM.SetMorphWeight(ProtoDR::HideSecondEye, 0.0f);
        
        eEA.AddParameterFrame(ProtoDR::HideBlush, 0.0f);
        eEA.AddParameterFrame(ProtoDR::HideEyeBrow, 0.0f);
        eEA.AddParameterFrame(ProtoDR::AlphaGenSquare, 1.0f);
        
        talk = false;
    }

    void AlphaGenCircle(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();
        
        topFinOuter.Pause();
        topFinInner.Pause();
        topFinGap.Pause();
        midFin.Pause();
        botFinLR1.Pause();
        botFinLR2.Pause();
        botFinLR3.Pause();
        botFinLR4.Pause();
        botFinLR5.Pause();

        topFinOuter.Reset();
        topFinInner.Reset();
        topFinGap.Reset();
        midFin.Reset();
        botFinLR1.Reset();
        botFinLR2.Reset();
        botFinLR3.Reset();
        botFinLR4.Reset();
        botFinLR5.Reset();
        
        pM.SetMorphWeight(ProtoDR::HideSecondEye, 0.0f);
        
        eEA.AddParameterFrame(ProtoDR::HideBlush, 0.0f);
        eEA.AddParameterFrame(ProtoDR::HideEyeBrow, 0.0f);
        eEA.AddParameterFrame(ProtoDR::AlphaGenCircle, 1.0f);

        talk = false;
    }

    void HideAll(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();
        
        topFinOuter.Pause();
        topFinInner.Pause();
        topFinGap.Pause();
        midFin.Pause();
        botFinLR1.Pause();
        botFinLR2.Pause();
        botFinLR3.Pause();
        botFinLR4.Pause();
        botFinLR5.Pause();

        topFinOuter.Reset();
        topFinInner.Reset();
        topFinGap.Reset();
        midFin.Reset();
        botFinLR1.Reset();
        botFinLR2.Reset();
        botFinLR3.Reset();
        botFinLR4.Reset();
        botFinLR5.Reset();
        
        pM.SetMorphWeight(ProtoDR::HideSecondEye, 0.0f);
        
        eEA.AddParameterFrame(ProtoDR::HideBlush, 0.0f);
        eEA.AddParameterFrame(ProtoDR::HideEyeBrow, 0.0f);
        eEA.AddParameterFrame(ProtoDR::HideAll, 1.0f);
        
        materialAnimator.AddMaterialFrame(blackMaterial, 1.0f);
        
        talk = false;
    }

    void SpyroDisplay(float ratio, bool normal){
        pM.GetObject()->Disable();
        spyro.GetObject()->Enable();

        float x = fGenRotation.Update();
        float sx = fGenScale.Update();
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, ratio * 720.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        spyro.GetObject()->ResetVertices();

        spyro.GetObject()->GetTransform()->SetRotation(rotation);
        spyro.GetObject()->GetTransform()->SetScale(Vector3D(sx, sx, sx));
        spyro.GetObject()->GetTransform()->SetPosition(Vector3D(0.0f, 30.0f, 600.0f));

        spyro.GetObject()->UpdateTransform();

        if(!normal){
            spyro.GetObject()->SetMaterial(&spyro.material);
        }
        else{
            spyro.GetObject()->SetMaterial(&normalMaterial);
        }
        
        talk = false;
    }
    
    void AngryFace(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();
        
        topFinOuter.Pause();
        topFinInner.Pause();
        topFinGap.Pause();
        midFin.Pause();
        botFinLR1.Pause();
        botFinLR2.Pause();
        botFinLR3.Pause();
        botFinLR4.Pause();
        botFinLR5.Pause();

        topFinOuter.Reset();
        topFinInner.Reset();
        topFinGap.Reset();
        midFin.Reset();
        botFinLR1.Reset();
        botFinLR2.Reset();
        botFinLR3.Reset();
        botFinLR4.Reset();
        botFinLR5.Reset();

        pM.SetMorphWeight(ProtoDR::HideSecondEye, 1.0f);
        
        eEA.AddParameterFrame(ProtoDR::HideBlush, 1.0f);
        eEA.AddParameterFrame(ProtoDR::HideEyeBrow, 1.0f);
        eEA.AddParameterFrame(ProtoDR::NewFins, 1.0f);
        eEA.AddParameterFrame(ProtoDR::AngryEyeMouth, 1.0f);
        
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
        
        talk = false;
    }

    void FullScreenDisplay(){
        background.GetObject()->Enable();
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();
        
        topFinOuter.Pause();
        topFinInner.Pause();
        topFinGap.Pause();
        midFin.Pause();
        botFinLR1.Pause();
        botFinLR2.Pause();
        botFinLR3.Pause();
        botFinLR4.Pause();
        botFinLR5.Pause();

        topFinOuter.Reset();
        topFinInner.Reset();
        topFinGap.Reset();
        midFin.Reset();
        botFinLR1.Reset();
        botFinLR2.Reset();
        botFinLR3.Reset();
        botFinLR4.Reset();
        botFinLR5.Reset();
        
        pM.SetMorphWeight(ProtoDR::HideSecondEye, 0.0f);
        
        eEA.AddParameterFrame(ProtoDR::HideBlush, 0.0f);
        eEA.AddParameterFrame(ProtoDR::HideEyeBrow, 0.0f);
        eEA.AddParameterFrame(ProtoDR::HideAll, 1.0f);
        
        talk = false;
        
        materialAnimator.AddMaterialFrame(blackMaterial, 1.0f);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    float offset = 0.0f;

    void UpdateFFTVisemes(){
        if(MenuButtonHandler::UseMicrophone()){
            //eEA.AddParameterFrame(ProtoDR::::vrc_v_ss, MicrophoneFourier::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourier::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourier::GetFourierFiltered(), MicrophoneFourier::GetSampleRate());
        
                //eEA.AddParameterFrame(NukudeFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                //eEA.AddParameterFrame(NukudeFace::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.AH));
                //eEA.AddParameterFrame(NukudeFace::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.UH));
                //eEA.AddParameterFrame(NukudeFace::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
                //eEA.AddParameterFrame(NukudeFace::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                //eEA.AddParameterFrame(NukudeFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                //eEA.AddParameterFrame(NukudeFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
            }
        }
    }

    void Update(float ratio) override {
        pM.GetObject()->Enable();//Due to Spyro track
        spyro.GetObject()->Disable();
        background.GetObject()->Disable();

        MicrophoneFourier::Update();
        sA.Update(MicrophoneFourier::GetFourierFiltered());
        sA.SetRotation(20.0f);
        sA.SetHueAngle(ratio * 360.0f * 4.0f);
        sA.SetMirrorYState(true);//MenuButtonHandler::MirrorSpectrumAnalyzer());
        sA.SetFlipYState(false);//!MenuButtonHandler::MirrorSpectrumAnalyzer());
        
        UpdateFFTVisemes();

        #ifdef RIGHTFACE
        SerialSync::Read();

        //update offset only 2% of the time
        if(SerialSync::GetRatio() < 0.02f){
            if(ratio > SerialSync::GetRatio()) offset = ratio - 1.0f - SerialSync::GetRatio();
            else offset = ratio - SerialSync::GetRatio();
        }

        //adjust current frame sync to new esp32
        ratio = fmod(ratio - offset, 1.0f);//override input to synchronize from esp

        uint8_t mode = SerialSync::GetMode();
        float mouthMove = SerialSync::GetMouthMove();
        #else
        float mouthMove = MicrophoneFourier::GetCurrentMagnitude() / 2.0f;

        uint8_t mode = MenuButtonHandler::GetFaceState();//change by button press
        SerialSync::SetMouthMove(mouthMove);
        SerialSync::SetMode(mode);
        SerialSync::SetRatio(ratio);
        SerialSync::Send();
        #endif

        #ifdef DEMOMODE
        ratio = fmod(ratio - offset, 1.0f);//override input to synchronize from esp
        mode = floor(Mathematics::Map(ratio, 0, 1, 0, 1.99f));
        #endif

        if (mode == 0) Default();
        else if (mode == 1) OwO();
        else if (mode == 2) Sad();
        else if (mode == 3) Dead();
        else if (mode == 4) Heart();
        else if (mode == 5) SpyroDisplay(ratio, false);
        else if (mode == 6) SpyroDisplay(ratio, true);
        else if (mode == 7) AlphaGenSquare();//AlphaGenCircle();
        else if (mode == 8) HideAll();
        else if (mode == 9) FullScreenDisplay();
        else if (mode == 10) AngryFace();
        else OwO2();
        

        float shiftMat = fGenMatPos.Update();
        stripe1.SetStripeWidth(fGenMatWidth.Update());
        stripe1.SetWavePeriod(fGenMatPeriod.Update());
        stripe1.SetWaveAmplitude(fGenMatAmplitude.Update());
        stripe1.SetRotationAngle(ratio * 360.0f);
        stripe1.SetPositionOffset(Vector2D(shiftMat, shiftMat));
        
        rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();

        UpdateKeyFrameTracks();

        //if(talk) pM.SetMorphWeight(ProtoDR::OpenToothMouth, mouthMove);
        eEA.Update();
        pM.Update();
        
        float x = sinf(ratio * 3.14159f / 180.0f * 360.0f * 2.0f) * 3.0f;
        float y = cosf(ratio * 3.14159f / 180.0f * 360.0f * 3.0f) * 3.0f;
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0, 180.0f, 0.0f));
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(x, y, 600.0f));
        pM.GetObject()->GetTransform()->Scale(Vector3D(1.0f, 1.0f, 1.0f));

        pM.GetObject()->UpdateTransform();
    }
};
