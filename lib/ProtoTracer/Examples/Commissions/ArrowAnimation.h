#pragma once

#include "../Templates/ProtogenProjectTemplate.h"
#include "../../Assets/Models/OBJ/DeltaDisplayBackground.h"
#include "../../Assets/Models/FBX/Commissions/ArrowFace.h"
#include "../../Assets/Models/OBJ/LEDStripBackground.h"

#include "../../Camera/CameraManager/Implementations/HUB75DeltaCameras.h"
#include "../../Controller/HUB75Controller.h"

#include "../../Scene/Materials/Animated/HorizontalRainbow.h"

class ArrowAnimation : public ProtogenProject {
private:
    HUB75DeltaCameraManager cameras;
    HUB75Controller controller = HUB75Controller(&cameras, 50, 50);
    ArrowFace pM;
    DeltaDisplayBackground deltaDisplayBackground;
    LEDStripBackground ledStripBackground;
    HorizontalRainbow hRainbow;
    
	const __FlashStringHelper* faceArray[12] = {F("DEFAULT"), F("ANGRY"), F("EXCITED"), F("HAPPY"), F("HEART"), F("OWO"), F("UNAMUSE"), F("UWU"), F("AUDIO1"), F("AUDIO2"), F("AUDIO3")};

    void LinkControlParameters() override {//Called from parent
        AddParameter(ArrowFace::AngryEyesFlip, pM.GetMorphWeightReference(ArrowFace::AngryEyesFlip), 15);
        AddParameter(ArrowFace::AngryMouth, pM.GetMorphWeightReference(ArrowFace::AngryMouth), 15, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(ArrowFace::ExcitedEyes, pM.GetMorphWeightReference(ArrowFace::ExcitedEyes), 10);
        AddParameter(ArrowFace::ExcitedMouthTODO, pM.GetMorphWeightReference(ArrowFace::ExcitedMouthTODO), 10);
        AddParameter(ArrowFace::HappyEyes, pM.GetMorphWeightReference(ArrowFace::HappyEyes), 10);
        AddParameter(ArrowFace::HeartEyes, pM.GetMorphWeightReference(ArrowFace::HeartEyes), 15);
        AddParameter(ArrowFace::OwoEyes, pM.GetMorphWeightReference(ArrowFace::OwoEyes), 15);
        AddParameter(ArrowFace::OwoMouth, pM.GetMorphWeightReference(ArrowFace::OwoMouth), 15);
        AddParameter(ArrowFace::UnamusedEyes, pM.GetMorphWeightReference(ArrowFace::UnamusedEyes), 45);
        AddParameter(ArrowFace::UnamusedMouth, pM.GetMorphWeightReference(ArrowFace::UnamusedMouth), 45);
        AddParameter(ArrowFace::UwuEyes, pM.GetMorphWeightReference(ArrowFace::UwuEyes), 30);

        AddViseme(Viseme::MouthShape::EE, pM.GetMorphWeightReference(ArrowFace::vrc_v_ee));
        AddViseme(Viseme::MouthShape::AH, pM.GetMorphWeightReference(ArrowFace::vrc_v_aa));
        AddViseme(Viseme::MouthShape::UH, pM.GetMorphWeightReference(ArrowFace::vrc_v_dd));
        AddViseme(Viseme::MouthShape::AR, pM.GetMorphWeightReference(ArrowFace::vrc_v_rr));
        AddViseme(Viseme::MouthShape::ER, pM.GetMorphWeightReference(ArrowFace::vrc_v_ch));
        AddViseme(Viseme::MouthShape::OO, pM.GetMorphWeightReference(ArrowFace::vrc_v_oh));
        AddViseme(Viseme::MouthShape::SS, pM.GetMorphWeightReference(ArrowFace::vrc_v_ss));

        AddBlinkParameter(pM.GetMorphWeightReference(ArrowFace::Blink));
    }

    void Default(){
        ledStripBackground.GetObject()->SetMaterial(GetFaceMaterial());
    }

    void Angry(){
        AddParameterFrame(ArrowFace::AngryEyesFlip, 1.0f);
        AddParameterFrame(ArrowFace::AngryMouth, 1.0f);
        AddMaterialFrame(Color::CRED, 0.8f);
    }

    void Excited(){
        AddParameterFrame(ArrowFace::ExcitedEyes, 1.0f);
        AddParameterFrame(ArrowFace::ExcitedMouthTODO, 1.0f);
        AddMaterialFrame(Color::CRAINBOW, 0.8f);
    }

    void Happy() {
        AddParameterFrame(ArrowFace::HappyEyes, 1.0f);
        AddMaterialFrame(Color::CRAINBOW, 0.8f);
    }

    void Heart() {
        AddParameterFrame(ArrowFace::HeartEyes, 1.0f);
        AddMaterialFrame(Color::CRAINBOW, 0.8f);
    }

    void Owo() {
        AddParameterFrame(ArrowFace::OwoEyes, 1.0f);
        AddParameterFrame(ArrowFace::OwoMouth, 1.0f);
        AddMaterialFrame(Color::CRAINBOW, 0.8f);
    }

    void Unamused() {
        AddParameterFrame(ArrowFace::UnamusedEyes, 1.0f);
        AddParameterFrame(ArrowFace::UnamusedMouth, 1.0f);
    }

    void Uwu() {
        AddParameterFrame(ArrowFace::UwuEyes, 1.0f);
        AddParameterFrame(ArrowFace::OwoMouth, 1.0f);
        AddMaterialFrame(Color::CRAINBOW, 0.8f);
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
    ArrowAnimation() : ProtogenProject(&cameras, &controller, 3, Vector2D(), Vector2D(192.0f, 94.0f), A0, 20, 11){
        scene.AddObject(pM.GetObject());
        scene.AddObject(deltaDisplayBackground.GetObject());
        scene.AddObject(ledStripBackground.GetObject());

        pM.GetObject()->SetMaterial(GetFaceMaterial());
        deltaDisplayBackground.GetObject()->SetMaterial(GetFaceMaterial());
        ledStripBackground.GetObject()->SetMaterial(GetFaceMaterial());

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

        UpdateFace(ratio);

        pM.Update();

        AlignObjectFace(pM.GetObject(), 90.75f);

        pM.GetObject()->GetTransform()->SetPosition(GetWiggleOffset());
        pM.GetObject()->UpdateTransform();
    }

    void SelectFace(uint8_t code) {
        if (IsBooped() && code < 8) {
            Heart();
            return;
        }

        switch(code) {
            case 0: Default();  break;
            case 1: Angry();    break;
            case 2: Excited();    break;
            case 3: Happy();    break;
            case 4: Heart();   break;
            case 5: Owo();      break;
            case 6: Unamused();      break;
            case 7: Uwu();      break;
            case 8: AudioReactiveGradientFace();    break;
            case 9: OscilloscopeFace();             break;
            default: SpectrumAnalyzerFace();        break;
        }
    }
};
