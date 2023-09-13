#pragma once

#include "ProtogenAnimation.h"
#include "..\Objects\Background.h"
#include "..\Objects\LEDStripBackground.h"
#include "..\Morph\NukudeFlat.h"

class HUB75Protogen : public ProtogenAnimation<2> {
private:
    NukudeFace pM;
    LEDStripBackground ledStripBackground;
    
	const __FlashStringHelper* faceArray[10] = {F("DEFAULT"), F("ANGRY"), F("DOUBT"), F("FROWN"), F("LOOKUP"), F("SAD"), F("AUDIO1"), F("AUDIO2"), F("AUDIO3")};

    void LinkControlParameters() override {
        AddParameter(NukudeFace::Anger, pM.GetMorphWeightReference(NukudeFace::Anger), 15);
        AddParameter(NukudeFace::Sadness, pM.GetMorphWeightReference(NukudeFace::Sadness), 15, EasyEaseInterpolation::InterpolationMethod::Cosine);
        AddParameter(NukudeFace::Surprised, pM.GetMorphWeightReference(NukudeFace::Surprised), 15);
        AddParameter(NukudeFace::Doubt, pM.GetMorphWeightReference(NukudeFace::Doubt), 15);
        AddParameter(NukudeFace::Frown, pM.GetMorphWeightReference(NukudeFace::Frown), 15);
        AddParameter(NukudeFace::LookUp, pM.GetMorphWeightReference(NukudeFace::LookUp), 15);
        AddParameter(NukudeFace::LookDown, pM.GetMorphWeightReference(NukudeFace::LookDown), 15);

        AddParameter(NukudeFace::HideBlush, pM.GetMorphWeightReference(NukudeFace::HideBlush), 15, EasyEaseInterpolation::InterpolationMethod::Cosine, true);

        AddViseme(Viseme::MouthShape::EE, pM.GetMorphWeightReference(NukudeFace::vrc_v_ee));
        AddViseme(Viseme::MouthShape::AH, pM.GetMorphWeightReference(NukudeFace::vrc_v_aa));
        AddViseme(Viseme::MouthShape::UH, pM.GetMorphWeightReference(NukudeFace::vrc_v_dd));
        AddViseme(Viseme::MouthShape::AR, pM.GetMorphWeightReference(NukudeFace::vrc_v_rr));
        AddViseme(Viseme::MouthShape::ER, pM.GetMorphWeightReference(NukudeFace::vrc_v_ch));
        AddViseme(Viseme::MouthShape::OO, pM.GetMorphWeightReference(NukudeFace::vrc_v_oh));
        AddViseme(Viseme::MouthShape::SS, pM.GetMorphWeightReference(NukudeFace::vrc_v_ss));

        AddBlinkParameter(pM.GetMorphWeightReference(NukudeFace::Blink));
    }

    void Default(){}

    void Angry(){
        AddParameterFrame(NukudeFace::Anger, 1.0f);
        AddMaterialFrame(Color::CRED);
    } 

    void Sad(){
        AddParameterFrame(NukudeFace::Sadness, 1.0f);
        AddParameterFrame(NukudeFace::Frown, 1.0f);
        AddMaterialFrame(Color::CBLUE);
    }

    void Surprised(){
        AddParameterFrame(NukudeFace::Surprised, 1.0f);
        AddParameterFrame(NukudeFace::HideBlush, 0.0f);
        AddMaterialFrame(Color::CRAINBOW);
    }
    
    void Doubt(){
        AddParameterFrame(NukudeFace::Doubt, 1.0f);
    }
    
    void Frown(){
        AddParameterFrame(NukudeFace::Frown, 1.0f);
    }

    void LookUp(){
        AddParameterFrame(NukudeFace::LookUp, 1.0f);
    }

    void LookDown(){
        AddParameterFrame(NukudeFace::LookDown, 1.0f);
    }

public:
    HUB75Protogen() : ProtogenAnimation(Vector2D(), Vector2D(192.0f, 96.0f), A2, 20, 9){
        scene.AddObject(pM.GetObject());
        scene.AddObject(ledStripBackground.GetObject());

        pM.GetObject()->SetMaterial(GetFaceMaterial());
        ledStripBackground.GetObject()->SetMaterial(GetFaceMaterial());

        LinkControlParameters();

        hud.SetFaceArray(faceArray);
    }

    void Update(float ratio) override {
        pM.Reset();

        uint8_t mode = Menu::GetFaceState();//change by button press

        if (IsBooped() && mode != 6){
            Surprised();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Angry();
            else if (mode == 2) Doubt();
            else if (mode == 3) Frown();
            else if (mode == 4) LookUp();
            else if (mode == 5) Sad();
            else if (mode == 6) {
                AudioReactiveGradientFace();
            }
            else if (mode == 7){
                OscilloscopeFace();
            }
            else {
                SpectrumAnalyzerFace();
            }
        }

        UpdateFace(ratio);

        pM.Update();

        AlignObject(pM.GetObject());
        
        pM.GetObject()->GetTransform()->SetPosition(GetWiggleOffset());
        pM.GetObject()->UpdateTransform();
    }
};
