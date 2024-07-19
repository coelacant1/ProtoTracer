#pragma once

#include "../Templates/ProtogenProjectTemplate.h"
#include "../../Assets/Models/OBJ/DeltaDisplayBackground.h"
#include "../../Assets/Models/FBX/Commissions/SplatFace.h"
#include "../../Assets/Models/OBJ/LEDStripBackground.h"

#include "../../Camera/CameraManager/Implementations/HUB75DeltaCameras.h"
#include "../../Controller/HUB75Controller.h"

#include "../../Scene/Materials/Animated/HorizontalRainbow.h"

class SplatAnimation : public ProtogenProject {
private:
    HUB75DeltaCameraManager cameras;
    HUB75Controller controller = HUB75Controller(&cameras, 50, 50);
    SplatFace pM;
    DeltaDisplayBackground deltaDisplayBackground;
    LEDStripBackground ledStripBackground;
    HorizontalRainbow hRainbow;
    
	const __FlashStringHelper* faceArray[13] = {F("DEFAULT"), F("ANGRY"), F("CONFUSE"), F("DISAPPO"), F("FCIRCLE"), F("EXCITED"), F("HEART"), F("HCIRCLE"), F("SLEEPY"), F("AUDIO1"), F("AUDIO2"), F("AUDIO3")};

    void LinkControlParameters() override {//Called from parent
        AddParameter(SplatFace::AngryEyes, pM.GetMorphWeightReference(SplatFace::AngryEyes), 15);
        AddParameter(SplatFace::AngryMouth, pM.GetMorphWeightReference(SplatFace::AngryMouth), 15);
        AddParameter(SplatFace::ConfusedEyes, pM.GetMorphWeightReference(SplatFace::ConfusedEyes), 25);
        AddParameter(SplatFace::ConfusedMouth, pM.GetMorphWeightReference(SplatFace::ConfusedMouth), 25);
        AddParameter(SplatFace::DisappointedEyes, pM.GetMorphWeightReference(SplatFace::DisappointedEyes), 25);
        AddParameter(SplatFace::DisappointedMouth, pM.GetMorphWeightReference(SplatFace::DisappointedMouth), 25);
        AddParameter(SplatFace::ExcitedEyes, pM.GetMorphWeightReference(SplatFace::ExcitedEyes), 25);
        AddParameter(SplatFace::FullCircleEyes, pM.GetMorphWeightReference(SplatFace::FullCircleEyes), 25);
        AddParameter(SplatFace::HeartEyes, pM.GetMorphWeightReference(SplatFace::HeartEyes), 25);
        AddParameter(SplatFace::HollowCircleEyes, pM.GetMorphWeightReference(SplatFace::HollowCircleEyes), 25);
        AddParameter(SplatFace::SleepyEyes, pM.GetMorphWeightReference(SplatFace::SleepyEyes), 50, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(SplatFace::SleepyMouth, pM.GetMorphWeightReference(SplatFace::SleepyMouth), 50, IEasyEaseAnimator::InterpolationMethod::Cosine);

        AddParameter(SplatFace::HideBlush, pM.GetMorphWeightReference(SplatFace::HideBlush), 15, IEasyEaseAnimator::InterpolationMethod::Cosine, true);

        AddViseme(Viseme::MouthShape::EE, pM.GetMorphWeightReference(SplatFace::vrc_v_ee));
        AddViseme(Viseme::MouthShape::AH, pM.GetMorphWeightReference(SplatFace::vrc_v_aa));
        AddViseme(Viseme::MouthShape::UH, pM.GetMorphWeightReference(SplatFace::vrc_v_dd));
        AddViseme(Viseme::MouthShape::AR, pM.GetMorphWeightReference(SplatFace::vrc_v_rr));
        AddViseme(Viseme::MouthShape::ER, pM.GetMorphWeightReference(SplatFace::vrc_v_ch));
        AddViseme(Viseme::MouthShape::OO, pM.GetMorphWeightReference(SplatFace::vrc_v_oh));
        AddViseme(Viseme::MouthShape::SS, pM.GetMorphWeightReference(SplatFace::vrc_v_ss));

        //AddBlinkParameter(pM.GetMorphWeightReference(SplatFace::Blink));
    }

    void Default(){
        //AddMaterialFrame(Color::CWHITE, 0.8f);
        AddMaterialFrame(hRainbow, 0.8f);
        
        ledStripBackground.GetObject()->SetMaterial(GetFaceMaterial());
    }

    void Angry(){
        AddParameterFrame(SplatFace::AngryEyes, 1.0f);
        AddParameterFrame(SplatFace::AngryMouth, 1.0f);
        AddMaterialFrame(Color::CRED, 0.8f);
    } 

    void Confused(){
        AddParameterFrame(SplatFace::ConfusedEyes, 1.0f);
        AddParameterFrame(SplatFace::ConfusedMouth, 1.0f);
        AddParameterFrame(SplatFace::HideBlush, 0.0f);
        //AddMaterialFrame(Color::CRAINBOW, 0.8f);
        AddMaterialFrame(hRainbow, 0.8f);
    }

    void Disappointed(){
        AddParameterFrame(SplatFace::DisappointedEyes, 1.0f);
        AddParameterFrame(SplatFace::DisappointedMouth, 1.0f);
        //AddMaterialFrame(Color::CRAINBOW, 0.8f);
        AddMaterialFrame(hRainbow, 0.8f);
    }

    void Excited(){
        AddParameterFrame(SplatFace::ExcitedEyes, 1.0f);
        AddParameterFrame(SplatFace::HideBlush, 0.0f);
        //AddMaterialFrame(Color::CRAINBOW, 0.8f);
        AddMaterialFrame(hRainbow, 0.8f);
    }
    
    void FullCircle(){
        AddParameterFrame(SplatFace::FullCircleEyes, 1.0f);
        //AddMaterialFrame(Color::CRAINBOW, 0.8f);
        AddMaterialFrame(hRainbow, 0.8f);
    }

    void Heart(){
        AddParameterFrame(SplatFace::HeartEyes, 1.0f);
        AddParameterFrame(SplatFace::HideBlush, 0.0f);
        //AddMaterialFrame(Color::CRAINBOW, 0.8f);
        AddMaterialFrame(hRainbow, 0.8f);
    }

    void HollowCircle(){
        AddParameterFrame(SplatFace::HollowCircleEyes, 1.0f);
        //AddMaterialFrame(Color::CRAINBOW, 0.8f);
        AddMaterialFrame(hRainbow, 0.8f);
    }

    void Sleepy(){
        AddParameterFrame(SplatFace::SleepyEyes, 1.0f);
        AddParameterFrame(SplatFace::SleepyMouth, 1.0f);
        AddMaterialFrame(Color::CBLUE, 0.8f);
    }

    void SpectrumAnalyzerCallback() override {
        deltaDisplayBackground.GetObject()->SetMaterial(&hRainbow);
        ledStripBackground.GetObject()->SetMaterial(&hRainbow);
    }

    void AudioReactiveGradientCallback() override {
        deltaDisplayBackground.GetObject()->SetMaterial(&hRainbow);
        ledStripBackground.GetObject()->SetMaterial(&hRainbow);
    }

    void OscilloscopeCallback() override {
        deltaDisplayBackground.GetObject()->SetMaterial(&hRainbow);
        ledStripBackground.GetObject()->SetMaterial(&hRainbow);
    }

public:
    SplatAnimation() : ProtogenProject(&cameras, &controller, 3, Vector2D(), Vector2D(192.0f, 94.0f), 14, 20, 12){
        scene.AddObject(pM.GetObject());
        scene.AddObject(deltaDisplayBackground.GetObject());
        scene.AddObject(ledStripBackground.GetObject());

        pM.GetObject()->SetMaterial(GetFaceMaterial());
        deltaDisplayBackground.GetObject()->SetMaterial(GetFaceMaterial());
        ledStripBackground.GetObject()->SetMaterial(GetFaceMaterial());

        AddMaterial(Material::Replace, &hRainbow, 40, 0.0f, 1.0f);

        hud.SetFaceArray(faceArray);

        LinkControlParameters();
        
        SetWiggleSpeed(5.0f);
        SetMenuWiggleSpeed(0.0f, 0.0f, 0.0f);
        SetMenuOffset(Vector2D(17.5f, -3.0f));
        SetMenuSize(Vector2D(192, 56));
    }

    void Update(float ratio) override {
        pM.Reset();

        uint8_t mode = Menu::GetFaceState();//change by button press

        controller.SetBrightness(Menu::GetBrightness());
        controller.SetAccentBrightness(Menu::GetAccentBrightness());

        SelectFace(mode);
        
        hRainbow.Update(ratio);

        UpdateFace(ratio);

        pM.Update();

        AlignObjectFace(pM.GetObject(), 95.0f);

        pM.GetObject()->GetTransform()->SetPosition(GetWiggleOffset());
        pM.GetObject()->UpdateTransform();
    }

    void SelectFace(uint8_t code) {
        if (IsBooped() && code < 9) {
            Excited();
            return;
        }

        switch(code) {
            case 0: Default();          break;
            case 1: Angry();            break;
            case 2: Confused();         break;
            case 3: Disappointed();     break;
            case 4: FullCircle();       break;
            case 5: Excited();          break;
            case 6: Heart();            break;
            case 7: HollowCircle();     break;
            case 8: Sleepy();           break;
            case 9: AudioReactiveGradientFace();    break;
            case 10: OscilloscopeFace();            break;
            default: SpectrumAnalyzerFace();        break;
        }
    }

};
