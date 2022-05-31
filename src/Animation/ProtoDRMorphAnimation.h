#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Morph\ProtoDRMorph.h"
#include "..\Render\Scene.h"
#include "..\Materials\GradientMaterial.h"
#include "..\Materials\SimplexNoise.h"
#include "..\Signals\FunctionGenerator.h"
#include "..\Sensors\SerialSync.h"
#include "..\Materials\SpectrumAnalyzer.h"
#include "..\Sensors\ButtonHandler.h"
#include "..\Materials\NormalMaterial.h"

#include "..\Objects\Spyro.h"
#include "..\Objects\SolidCube.h"

#include "..\Materials\StripeMaterial.h"
#include "..\Materials\CombineMaterial.h"


class ProtoDRMorphAnimation : public Animation{
private:
    ProtoDR pM;
    SolidCube cube;
    float cubeSize = 0.0f;
    float colorRed = 0.0f;
    EasyEaseAnimator<30> eEA = EasyEaseAnimator<30>(EasyEaseInterpolation::Cosine);
    
    RGBColor spectrum[10] = {RGBColor(121, 35, 190), RGBColor(36, 120, 255), RGBColor(16, 207, 190), RGBColor(36, 239, 138), 
                             RGBColor(240, 235, 19), RGBColor(255, 186, 0), RGBColor(255, 138, 0), RGBColor(255, 85, 0), 
                             RGBColor(255, 0, 0), RGBColor(199, 0, 69)};
    GradientMaterial gNoiseMat = GradientMaterial(10, spectrum, 2.0f, false, false);
    SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);
    SimpleMaterial blackMaterial = SimpleMaterial(RGBColor(0,0,0));

    NormalMaterial normalMaterial;

    RGBColor spectrum1[6] = {RGBColor(255, 255, 0), RGBColor(0, 0, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 0), RGBColor(255, 0, 255), RGBColor(0, 0, 0)};
    FunctionGenerator fGenMatSize = FunctionGenerator(FunctionGenerator::Sine, 450.0f, 550.0f, 2.1f);
    FunctionGenerator fGenMatWidth = FunctionGenerator(FunctionGenerator::Sine, 150.0f, 500.0f, 4.0f);
    FunctionGenerator fGenMatPeriod = FunctionGenerator(FunctionGenerator::Sine, 200.0f, 500.0f, 6.3f);
    FunctionGenerator fGenMatAmplitude = FunctionGenerator(FunctionGenerator::Sine, -100.0f, 100.0f, 2.7f);
    FunctionGenerator fGenMatOpacity = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 0.5f);
    StripeMaterial stripe1 = StripeMaterial(6, spectrum1, 200.0f, 160.0f, 20.0f);
    SimpleMaterial red = SimpleMaterial(RGBColor(255, 0, 0));

    Material* materials[2] = {&sNoise, &red};
    CombineMaterial material = CombineMaterial(CombineMaterial::Darken, 2, materials);
    
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);

    KeyFrameTrack blink = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack topFinOuter = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    KeyFrameTrack topFinInner = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    KeyFrameTrack topFinGap = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    KeyFrameTrack midFin = KeyFrameTrack(3, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR1 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR2 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR3 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR4 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR5 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack mouth = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);

    Spyro spyro;
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    
    //Spectrum Analyzer
    RGBColor spectrum3[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    
    GradientMaterial gM = GradientMaterial(6, spectrum3, 1.0f, false);
    SpectrumAnalyzer sA = SpectrumAnalyzer(A8, Vector2D(430, 300), Vector2D(15, 135), &gM, true, true);
    
    Material* spectrumMaterials[2] = {&sA, &sNoise};
    CombineMaterial spectrumMaterial = CombineMaterial(CombineMaterial::Lighten, 2, spectrumMaterials);

    bool talk = true;

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

        eEA.AddParameter(&colorRed, 98, 45, 0.0f, 1.0f);
        eEA.AddParameter(&cubeSize, 99, 45, 0.0f, 1.0f);
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
    ProtoDRMorphAnimation() : Animation(3) {
        scene->AddObject(pM.GetObject());
        scene->AddObject(spyro.GetObject());
        scene->AddObject(cube.GetObject());

        LinkEasyEase();
        LinkParameters();

        AddBlinkKeyFrames();
        AddTopFinKeyFrames();
        AddMidFinKeyFrames();
        AddBotFinKeyFrames();
        AddMouthKeyFrames();

        pM.GetObject()->SetMaterial(&material);
        cube.GetObject()->SetMaterial(&sA);

        SerialSync::Initialize();
        ButtonHandler::Initialize(15, 11);
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
        eEA.AddParameterFrame(98, 1.0f);
        
        talk = false;
    }

    void FullScreenDisplay(){
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
        
        eEA.AddParameterFrame(99, 1.0f);
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    float offset = 0.0f;

    void Update(float ratio) override {
        pM.GetObject()->Enable();//Due to Spyro track
        spyro.GetObject()->Disable();
        
        sA.Update();
        sA.SetRotation(20.0f);
        sA.SetHueAngle(ratio * 360.0f * 4.0f);
        

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
        float mouthMove = sA.GetFourierData()[5];

        uint8_t mode = ButtonHandler::GetValue();
        SerialSync::SetMouthMove(mouthMove);
        SerialSync::SetMode(mode);
        SerialSync::SetRatio(ratio);
        SerialSync::Send();
        #endif

        #ifdef DEMOMODE
        ratio = fmod(ratio - offset, 1.0f);//override input to synchronize from esp
        mode = floor(Mathematics::Map(ratio, 0, 1, 0, 1.99f));
        #endif

        if (mode == 0) FullScreenDisplay();
        else if (mode == 1) OwO();
        else if (mode == 2) Sad();
        else if (mode == 3) Dead();
        else if (mode == 4) Heart();
        else if (mode == 5) SpyroDisplay(ratio, false);
        else if (mode == 6) SpyroDisplay(ratio, true);
        else if (mode == 7) AlphaGenSquare();
        //else if (mode == 8) AlphaGenCircle();
        else if (mode == 8) HideAll();
        else if (mode == 9) Default();
        else if (mode == 10) AngryFace();
        else OwO2();
        

        float shiftMat = fGenMatPos.Update();
        stripe1.SetStripeWidth(fGenMatWidth.Update());
        stripe1.SetWavePeriod(fGenMatPeriod.Update());
        stripe1.SetWaveAmplitude(fGenMatAmplitude.Update());
        stripe1.SetRotationAngle(ratio * 360.0f);
        stripe1.SetPositionOffset(Vector2D(shiftMat, shiftMat));
        material.SetFirstLayerOpacity(1.0f - colorRed);

        UpdateKeyFrameTracks();

        if(talk) pM.SetMorphWeight(ProtoDR::OpenToothMouth, mouthMove);
        eEA.Update();
        pM.Update();
        
        float x = sinf(ratio * 3.14159f / 180.0f * 360.0f * 2.0f) * 3.0f;
        float y = cosf(ratio * 3.14159f / 180.0f * 360.0f * 3.0f) * 3.0f;
        
        float linSweep = ratio > 0.5f ? 1.0f - ratio : ratio;
        float sShift = linSweep * 0.002f + 0.005f;

        gNoiseMat.SetGradientPeriod(1.0f + linSweep * 6.0f);
        //gNoiseMat.HueShift(ratio * 360 * 2);
        sNoise.SetScale(Vector3D(sShift, sShift, sShift));
        sNoise.SetZPosition(x * 1.0f);
        
        cube.GetObject()->ResetVertices();
        cube.GetObject()->GetTransform()->SetPosition(Vector3D(0, 135, 6000));
        cube.GetObject()->GetTransform()->SetScale(Vector3D(5.0f * cubeSize + 0.01f, 3.0f * cubeSize + 0.01f, 0.01f));
        cube.GetObject()->UpdateTransform();
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0, 180.0f, 0.0f));
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(x, y, 600.0f));
        pM.GetObject()->GetTransform()->Scale(Vector3D(1.0f, 1.0f, 1.0f));

        pM.GetObject()->UpdateTransform();
    }
};
