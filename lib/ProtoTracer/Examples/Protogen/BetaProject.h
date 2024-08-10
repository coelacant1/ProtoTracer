#pragma once

#include "../Templates/ProtogenProjectTemplate.h"
#include "../../Assets/Models/FBX/BetaFront.h"
#include "../../Assets/Models/FBX/BetaRear.h"
#include "../../Assets/Models/OBJ/LEDStripBackground.h"

#include "../../Animation/KeyFrameTrack.h"

#include "../../Camera/CameraManager/Implementations/WS35Beta.h"
#include "../../Controller/WS35BetaController.h"

class BetaProject : public ProtogenProject {
private:
    WS35BetaCameraManager cameras;
    WS35BetaController controller = WS35BetaController(&cameras, 50);
    BetaFront pM;
    BetaRear rear;
    LEDStripBackground ledStripBackground;
    
	const __FlashStringHelper* faceArray[9] = {F("DEFAULT"), F("SAD"), F("HEART"), F("DEAD"), F("ANGRY"), F("AUDIO1"), F("AUDIO2"), F("AUDIO3")};

    KeyFrameTrack<1, 10> botFinLR1 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR2 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR3 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR4 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);
    KeyFrameTrack<1, 10> botFinLR5 = KeyFrameTrack<1, 10>(0.0f, 1.0f, KeyFrameInterpolation::Cosine);

    void LinkControlParameters() override {
        AddParameter(BetaFront::BlushEye, pM.GetMorphWeightReference(BetaFront::BlushEye), 40);
        AddParameter(BetaFront::HideBlush, pM.GetMorphWeightReference(BetaFront::HideBlush), 10, IEasyEaseAnimator::InterpolationMethod::Cosine, true);
        AddParameter(BetaFront::HideEyeBrow, pM.GetMorphWeightReference(BetaFront::HideEyeBrow), 10, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(BetaFront::HideSecondEye, pM.GetMorphWeightReference(BetaFront::HideSecondEye), 10, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(BetaFront::OwOMouth, pM.GetMorphWeightReference(BetaFront::OwOMouth), 60);
        AddParameter(BetaFront::SadEye, pM.GetMorphWeightReference(BetaFront::SadEye), 70, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(BetaFront::SadEyeBrow, pM.GetMorphWeightReference(BetaFront::SadEyeBrow), 80, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(BetaFront::SadMouth, pM.GetMorphWeightReference(BetaFront::SadMouth), 90, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(BetaFront::FlatMouth, pM.GetMorphWeightReference(BetaFront::FlatMouth), 50);
        AddParameter(BetaFront::DeadEye, pM.GetMorphWeightReference(BetaFront::DeadEye), 1);
        AddParameter(BetaFront::HeartEye, pM.GetMorphWeightReference(BetaFront::HeartEye), 30);
        AddParameter(BetaFront::AlphaGenCircle,pM.GetMorphWeightReference(BetaFront::AlphaGenCircle),  90, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(BetaFront::HideAll,pM.GetMorphWeightReference(BetaFront::HideAll),  90);
        AddParameter(BetaFront::AngryEyeMouth,pM.GetMorphWeightReference(BetaFront::AngryEyeMouth),  90);
        
        AddBlinkParameter(pM.GetMorphWeightReference(BetaFront::ClosedEye));
        
        AddViseme(Viseme::MouthShape::EE, pM.GetMorphWeightReference(BetaFront::vrc_v_ee));
        AddViseme(Viseme::MouthShape::AH, pM.GetMorphWeightReference(BetaFront::vrc_v_aa));
        AddViseme(Viseme::MouthShape::UH, pM.GetMorphWeightReference(BetaFront::vrc_v_dd));
        AddViseme(Viseme::MouthShape::AR, pM.GetMorphWeightReference(BetaFront::vrc_v_rr));
        AddViseme(Viseme::MouthShape::ER, pM.GetMorphWeightReference(BetaFront::vrc_v_ch));
        AddViseme(Viseme::MouthShape::OO, pM.GetMorphWeightReference(BetaFront::vrc_v_oh));
        AddViseme(Viseme::MouthShape::SS, pM.GetMorphWeightReference(BetaFront::vrc_v_ss));
        
        botFinLR1.AddParameter(rear.GetMorphWeightReference(BetaRear::Move1));
        botFinLR2.AddParameter(rear.GetMorphWeightReference(BetaRear::Move2));
        botFinLR3.AddParameter(rear.GetMorphWeightReference(BetaRear::Move3));
        botFinLR4.AddParameter(rear.GetMorphWeightReference(BetaRear::Move4));
        botFinLR5.AddParameter(rear.GetMorphWeightReference(BetaRear::Move5));
    }

    void AddBotFinKeyFrames(){
        botFinLR1.AddKeyFrame(0.0f, 0.0f);
        botFinLR2.AddKeyFrame(0.0f, 0.0f);
        botFinLR3.AddKeyFrame(0.0f, 0.0f);
        botFinLR4.AddKeyFrame(0.0f, 0.0f);
        botFinLR5.AddKeyFrame(0.0f, 1.0f);

        botFinLR1.AddKeyFrame(0.5f, 1.0f);
        botFinLR2.AddKeyFrame(0.5f, 0.0f);
        botFinLR3.AddKeyFrame(0.5f, 0.0f);
        botFinLR4.AddKeyFrame(0.5f, 0.0f);
        botFinLR5.AddKeyFrame(0.5f, 0.0f);

        botFinLR1.AddKeyFrame(1.0f, 0.0f);
        botFinLR2.AddKeyFrame(1.0f, 1.0f);
        botFinLR3.AddKeyFrame(1.0f, 0.0f);
        botFinLR4.AddKeyFrame(1.0f, 0.0f);
        botFinLR5.AddKeyFrame(1.0f, 0.0f);

        botFinLR1.AddKeyFrame(1.5f, 0.0f);
        botFinLR2.AddKeyFrame(1.5f, 0.0f);
        botFinLR3.AddKeyFrame(1.5f, 1.0f);
        botFinLR4.AddKeyFrame(1.5f, 0.0f);
        botFinLR5.AddKeyFrame(1.5f, 0.0f);

        botFinLR1.AddKeyFrame(2.0f, 0.0f);
        botFinLR2.AddKeyFrame(2.0f, 0.0f);
        botFinLR3.AddKeyFrame(2.0f, 0.0f);
        botFinLR4.AddKeyFrame(2.0f, 1.0f);
        botFinLR5.AddKeyFrame(2.0f, 0.0f);
        
        botFinLR1.AddKeyFrame(2.5f, 0.0f);
        botFinLR2.AddKeyFrame(2.5f, 0.0f);
        botFinLR3.AddKeyFrame(2.5f, 0.0f);
        botFinLR4.AddKeyFrame(2.5f, 0.0f);
        botFinLR5.AddKeyFrame(2.5f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        botFinLR1.Update();
        botFinLR2.Update();
        botFinLR3.Update();
        botFinLR4.Update();
        botFinLR5.Update();
    }

    
    void Default(){
        EnableBlinking();

        AddParameterFrame(BetaFront::HideSecondEye, 1.0f);
    }

    void OwO(){
        DisableBlinking();
        AddParameterFrame(BetaFront::BlushEye, 1.0f);
        AddParameterFrame(BetaFront::HideBlush, 0.0f);
        AddParameterFrame(BetaFront::HideEyeBrow, 1.0f);
        AddParameterFrame(BetaFront::HideSecondEye, 1.0f);
        AddParameterFrame(BetaFront::OwOMouth, 1.0f);

        AddMaterialFrame(Color::CRAINBOW, 0.8f);
    }

    void Sad(){
        EnableBlinking();
        AddParameterFrame(BetaFront::SadEye, 1.0f);
        AddParameterFrame(BetaFront::SadEyeBrow, 1.0f);
        AddParameterFrame(BetaFront::SadMouth, 1.0f);
        AddParameterFrame(BetaFront::HideSecondEye, 1.0f);
        
        AddMaterialFrame(Color::CBLUE, 0.8f);
    }

    void Dead(){
        DisableBlinking();
        AddParameterFrame(BetaFront::FlatMouth, 1.0f);
        AddParameterFrame(BetaFront::DeadEye, 1.0f);
        AddParameterFrame(BetaFront::HideSecondEye, 1.0f);

        AddMaterialFrame(Color::CRED, 0.8f);
    }
    
    void Heart(){
        DisableBlinking();
        AddParameterFrame(BetaFront::HeartEye, 1.0f);
        AddParameterFrame(BetaFront::HideEyeBrow, 1.0f);
        AddParameterFrame(BetaFront::OwOMouth, 1.0f);
        AddParameterFrame(BetaFront::HideSecondEye, 1.0f);

        AddMaterialFrame(Color::CRAINBOW, 0.8f);
    }
    
    void OwO2(){
        DisableBlinking();
        AddParameterFrame(BetaFront::HideBlush, 0.0f);
        AddParameterFrame(BetaFront::HideEyeBrow, 0.0f);
        
        AddMaterialFrame(Color::CRAINBOW, 0.8f);
    }

    void AlphaGenCircle(){
        EnableBlinking();
        AddParameterFrame(BetaFront::HideBlush, 0.0f);
        AddParameterFrame(BetaFront::HideEyeBrow, 0.0f);
        AddParameterFrame(BetaFront::AlphaGenCircle, 1.0f);
        AddParameterFrame(BetaFront::HideSecondEye, 0.0f);

        AddMaterialFrame(Color::CRAINBOWNOISE, 0.8f);
    }

    void AngryFace(){
        EnableBlinking();
        
        AddParameterFrame(BetaFront::HideBlush, 1.0f);
        AddParameterFrame(BetaFront::HideEyeBrow, 1.0f);
        AddParameterFrame(BetaFront::AngryEyeMouth, 1.0f);
        AddParameterFrame(BetaFront::HideSecondEye, 0.0f);
        
        AddMaterialFrame(Color::CRED, 0.8f);
    }

    void UpdateKeyframeTracks(){
        botFinLR1.Update();
        botFinLR2.Update();
        botFinLR3.Update();
        botFinLR4.Update();
        botFinLR5.Update();
    }

    void SpectrumAnalyzerCallback() override {
        AddMaterialFrame(Color::CHORIZONTALRAINBOW, 0.8f);
    }

    void AudioReactiveGradientCallback() override {
        AddMaterialFrame(Color::CHORIZONTALRAINBOW, 0.8f);
    }

    void OscilloscopeCallback() override {
        AddMaterialFrame(Color::CHORIZONTALRAINBOW, 0.8f);
    }

public:
    BetaProject() : ProtogenProject(&cameras, &controller, 3, Vector2D(), Vector2D(192.0f, 105.0f), 22, 23, 8){
        scene.AddObject(pM.GetObject());
        scene.AddObject(rear.GetObject());
        scene.AddObject(ledStripBackground.GetObject());
        
        pM.GetObject()->SetMaterial(GetFaceMaterial());
        rear.GetObject()->SetMaterial(GetFaceMaterial());
        ledStripBackground.GetObject()->SetMaterial(GetFaceMaterial());

        LinkControlParameters();
        AddBotFinKeyFrames();
        
        hud.SetFaceArray(faceArray);

        SetCameraRear(Vector2D(251.11f, 49.43f), Vector2D(408.9f, 215.2f));
        
        SetWiggleSpeed(5.0f);
        SetMenuWiggleSpeed(0.0f, 0.0f, 0.0f);
        SetMenuOffset(Vector2D(2.5f, -3.0f));
        SetMenuSize(Vector2D(240, 64));
    }

    void Update(float ratio) override {
        pM.Reset();
        rear.Reset();
        
        Menu::Update(ratio);

        uint8_t mode = Menu::GetFaceState();//change by button press
        
        controller.SetBrightness(Menu::GetBrightness());
        controller.SetAccentBrightness(Menu::GetAccentBrightness());

        UpdateKeyFrameTracks();
        SelectFace(mode);
        UpdateFace(ratio);

        pM.Update();
        rear.Update();

        AlignObjectFace(pM.GetObject(), 0.0f, 2.0f, false);
        AlignObjectRear(rear.GetObject(), -25.0f, 2.0f, false);
        
        pM.GetObject()->GetTransform()->SetPosition(GetWiggleOffset());
        pM.GetObject()->UpdateTransform();
        
        rear.GetObject()->GetTransform()->SetPosition(GetWiggleOffset());
        rear.GetObject()->UpdateTransform();
    }
    
    void SelectFace(uint8_t code) {
        if (IsBooped()) {
            OwO();
            return;
        }

        switch(code) {
            case 0: Default();  break;
            case 1: Sad();    break;
            case 2: Heart();    break;
            case 3: Dead();    break;
            case 4: AngryFace();      break;
            case 5: AudioReactiveGradientFace();    break;
            case 6: OscilloscopeFace();             break;
            default: SpectrumAnalyzerFace();        break;
        }
    }
};
