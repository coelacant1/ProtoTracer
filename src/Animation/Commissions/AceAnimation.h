#pragma once

#include "..\ProtogenAnimation.h"
#include "..\..\Objects\Background.h"
#include "..\..\Objects\LEDStripBackground.h"
#include "..\..\Morph\Commissions\AceFace.h"
#include "..\..\Morph\Commissions\AceCrash.h"
#include "..\..\Morph\Commissions\AceCrashBackground.h"

class AceAnimation : public ProtogenAnimation<3> {
private:
    AceFace pM;
    AceCrash crash;
    AceCrashBackground crashBackground;

    SimpleMaterial lBlueMaterial = SimpleMaterial(RGBColor(0, 25, 32));
    SimpleMaterial whiteMaterial = SimpleMaterial(RGBColor(255, 255, 255));
    SimpleMaterial blackMaterial = SimpleMaterial(RGBColor(0, 0, 0));
    
    MaterialAnimator<2> crashMaterial;
    MaterialAnimator<2> crashBackgroundMaterial;
    
	const __FlashStringHelper* faceArray[12] = {F("DEFAULT"), F("SMIRK"), F("CONTENT"), F("SRPRISE"), F("SRSLY"), F("ANGRY"), F("SCRUNCHY"), F("HAPPY"), F("CRASH"), F("AUDIO1"), F("AUDIO2"), F("AUDIO3")};

    void LinkControlParameters() override {
        AddParameter(AceFace::Smirk, pM.GetMorphWeightReference(AceFace::Smirk), 25, EasyEaseInterpolation::InterpolationMethod::Cosine);
        AddParameter(AceFace::Blush, pM.GetMorphWeightReference(AceFace::Blush), 35);
        AddParameter(AceFace::Content, pM.GetMorphWeightReference(AceFace::Content), 40);
        AddParameter(AceFace::Surprised, pM.GetMorphWeightReference(AceFace::Surprised), 15);
        AddParameter(AceFace::Seriously, pM.GetMorphWeightReference(AceFace::Seriously), 30);
        AddParameter(AceFace::Angry, pM.GetMorphWeightReference(AceFace::Angry), 20);
        AddParameter(AceFace::Scrunchy, pM.GetMorphWeightReference(AceFace::Scrunchy), 35);
        AddParameter(AceFace::Happy, pM.GetMorphWeightReference(AceFace::Happy), 45);

        AddViseme(Viseme::MouthShape::EE, pM.GetMorphWeightReference(AceFace::vrc_v_ee));
        AddViseme(Viseme::MouthShape::AH, pM.GetMorphWeightReference(AceFace::vrc_v_aa));
        AddViseme(Viseme::MouthShape::UH, pM.GetMorphWeightReference(AceFace::vrc_v_dd));
        AddViseme(Viseme::MouthShape::AR, pM.GetMorphWeightReference(AceFace::vrc_v_rr));
        AddViseme(Viseme::MouthShape::ER, pM.GetMorphWeightReference(AceFace::vrc_v_ch));
        AddViseme(Viseme::MouthShape::OO, pM.GetMorphWeightReference(AceFace::vrc_v_oh));
        AddViseme(Viseme::MouthShape::SS, pM.GetMorphWeightReference(AceFace::vrc_v_ss));

        AddBlinkParameter(pM.GetMorphWeightReference(AceFace::Blink));

        
        crashMaterial.SetBaseMaterial(Material::Add, &blackMaterial);
        crashMaterial.AddMaterial(Material::Replace, &whiteMaterial, 20, 0.0f, 1.0f);
        
        crashBackgroundMaterial.SetBaseMaterial(Material::Add, &blackMaterial);
        crashBackgroundMaterial.AddMaterial(Material::Replace, &lBlueMaterial, 20, 0.0f, 1.0f);
    }

    void Default(){}

    void Smirk(){
        AddParameterFrame(AceFace::Smirk, 1.0f);
    } 

    void Blush(){
        AddParameterFrame(AceFace::Blush, 1.0f);
        AddMaterialFrame(Color::CRAINBOW);
    }

    void Content(){
        DisableBlinking();
        AddParameterFrame(AceFace::Content, 1.0f);
    }
    
    void Surprised(){
        AddParameterFrame(AceFace::Surprised, 1.0f);
    }
    
    void Seriously(){
        AddParameterFrame(AceFace::Seriously, 1.0f);
    }

    void Angry(){
        AddParameterFrame(AceFace::Angry, 1.0f);
    }

    void Scrunchy(){
        DisableBlinking();
        AddParameterFrame(AceFace::Scrunchy, 1.0f);
    }

    void Happy(){
        DisableBlinking();
        AddParameterFrame(AceFace::Happy, 1.0f);
    }

    void Crash(){
        HideFace();

        crashMaterial.AddMaterialFrame(whiteMaterial, 1.0f);
        crashBackgroundMaterial.AddMaterialFrame(lBlueMaterial, 1.0f);
    }

public:
    AceAnimation() : ProtogenAnimation(Vector2D(10.0f, 5.0f), Vector2D(195.0f, 115.0f), 22, 0, 12){
        scene.AddObject(pM.GetObject());
        scene.AddObject(crash.GetObject());
        scene.AddObject(crashBackground.GetObject());

        pM.GetObject()->SetMaterial(GetFaceMaterial());
        crash.GetObject()->SetMaterial(&crashMaterial);
        crashBackground.GetObject()->SetMaterial(&crashBackgroundMaterial);

        LinkControlParameters();

        hud.SetFaceArray(faceArray);
    }

    void Update(float ratio) override {
        pM.Reset();
        crash.Reset();
        crashBackground.Reset();
        EnableBlinking();

        uint8_t mode = Menu::GetFaceState();//change by button press

        if (IsBooped() && mode != 6){
            Blush();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Smirk();
            else if (mode == 2) Content();
            else if (mode == 3) Surprised();
            else if (mode == 4) Seriously();
            else if (mode == 5) Angry();
            else if (mode == 6) Scrunchy();
            else if (mode == 7) Happy();
            else if (mode == 8) Crash();
            else if (mode == 9) {
                AudioReactiveGradientFace();
            }
            else if (mode == 10){
                OscilloscopeFace();
            }
            else {
                SpectrumAnalyzerFace();
            } 
        }

        UpdateFace(ratio);

        pM.SetMorphWeight(AceFace::MoveNose, 1.0f);

        pM.Update();
        crash.Update();
        crashBackground.Update();

        crashMaterial.Update();
        crashBackgroundMaterial.Update();

        Object3D* crashObjs[2] = {crash.GetObject(), crashBackground.GetObject()};

        AlignObject(pM.GetObject(), -7.5f);
        AlignObjectsNoScale(crashObjs, 2, -2.5f);

        SetWiggleSpeed(5.0f);
        SetMenuWiggleSpeed(0.0f, 0.0f, 0.0f);
        SetMenuOffset(Vector2D(2.5f, -3.0f));
        SetMenuSize(Vector2D(240, 64));
        
        pM.GetObject()->GetTransform()->SetPosition(GetWiggleOffset());
        pM.GetObject()->UpdateTransform();


        
        crash.GetObject()->GetTransform()->SetPosition(Vector3D(-8.0f, 60.0f, 600.0f) + GetWiggleOffset());
        crash.GetObject()->GetTransform()->SetScale(Vector3D(1.0f, crashMaterial.GetMaterialOpacity(whiteMaterial), 1.0f));
        //crash.GetObject()->GetTransform()->SetRotation(Vector3D(90.0f * crashMaterial.GetMaterialOpacity(whiteMaterial), 0.0f, 0.0f));
        crash.GetObject()->UpdateTransform();

        crashBackground.GetObject()->GetTransform()->SetPosition(Vector3D(-8.0f, 60.0f, 700.0f) + GetWiggleOffset());
        crashBackground.GetObject()->GetTransform()->SetScale(Vector3D(1.0f, crashBackgroundMaterial.GetMaterialOpacity(lBlueMaterial), 1.0f));
        //crashBackground.GetObject()->GetTransform()->SetRotation(Vector3D(90.0f * crashBackgroundMaterial.GetMaterialOpacity(lBlueMaterial), 0.0f, 0.0f));
        crashBackground.GetObject()->UpdateTransform();
    }
};


//rotate objects and move objects to center, no scale
//