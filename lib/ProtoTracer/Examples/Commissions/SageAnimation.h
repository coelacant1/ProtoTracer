#pragma once

#include "../Templates/ProtogenProjectTemplate.h"
#include "../../Assets/Models/FBX/Commissions/SageSchlo.h"
#include "../../Assets/Models/FBX/Commissions/SageSchloSideDisplay.h"

#include "../../Camera/CameraManager/Implementations/HUB75DeltaCameras.h"
#include "../../Controller/HUB75Controller.h"

class SageAnimation : public ProtogenProject {
private:
    SageSchlo pM;
    SageSchloSideDisplay sageSideDisplay;
    
    HUB75DeltaCameraManager cameras;
    HUB75Controller controller = HUB75Controller(&cameras, 50, 50);
    
	const __FlashStringHelper* faceArray[14] = {F("NEUTRAL"), F("SURPRISE"), F("DIZZY"), F("ANGRY1"), F("ANGRY2"), F("ANGRY3"), F("OWO"), F("TIRED"), F("SAD"), F("AUDIO1"), F("AUDIO2"), F("AUDIO3")};

    FunctionGenerator batteryChargeFunc = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 6.0f);

    bool wiggle = false;

    void LinkControlParameters() override {
        AddParameter(SageSchlo::Surprised, pM.GetMorphWeightReference(SageSchlo::Surprised), 40);
        AddParameter(SageSchlo::Blush, pM.GetMorphWeightReference(SageSchlo::Blush), 15, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(SageSchlo::Dizzy, pM.GetMorphWeightReference(SageSchlo::Dizzy), 25);
        AddParameter(SageSchlo::Angry1, pM.GetMorphWeightReference(SageSchlo::Angry1), 20, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(SageSchlo::Angry2, pM.GetMorphWeightReference(SageSchlo::Angry2), 15, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(SageSchlo::Angry3, pM.GetMorphWeightReference(SageSchlo::Angry3), 10, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(SageSchlo::OwO, pM.GetMorphWeightReference(SageSchlo::OwO), 10);
        AddParameter(SageSchlo::Tired, pM.GetMorphWeightReference(SageSchlo::Tired), 50, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(SageSchlo::Sad, pM.GetMorphWeightReference(SageSchlo::Sad), 45, IEasyEaseAnimator::InterpolationMethod::Cosine);

        AddParameter(SageSchloSideDisplay::Battery + 20, sageSideDisplay.GetMorphWeightReference(SageSchloSideDisplay::Battery), 45);
        AddParameter(SageSchloSideDisplay::BatteryFull + 20, sageSideDisplay.GetMorphWeightReference(SageSchloSideDisplay::BatteryFull), 45);
        AddParameter(SageSchloSideDisplay::Dizzy + 20, sageSideDisplay.GetMorphWeightReference(SageSchloSideDisplay::Dizzy), 45);
        AddParameter(SageSchloSideDisplay::Exclamation + 20, sageSideDisplay.GetMorphWeightReference(SageSchloSideDisplay::Exclamation), 45);

        AddViseme(Viseme::MouthShape::EE, pM.GetMorphWeightReference(SageSchlo::vrc_v_ee));
        AddViseme(Viseme::MouthShape::AH, pM.GetMorphWeightReference(SageSchlo::vrc_v_aa));
        AddViseme(Viseme::MouthShape::UH, pM.GetMorphWeightReference(SageSchlo::vrc_v_dd));
        AddViseme(Viseme::MouthShape::AR, pM.GetMorphWeightReference(SageSchlo::vrc_v_rr));
        AddViseme(Viseme::MouthShape::ER, pM.GetMorphWeightReference(SageSchlo::vrc_v_ch));
        AddViseme(Viseme::MouthShape::OO, pM.GetMorphWeightReference(SageSchlo::vrc_v_oh));
        AddViseme(Viseme::MouthShape::SS, pM.GetMorphWeightReference(SageSchlo::vrc_v_ss));

        AddBlinkParameter(pM.GetMorphWeightReference(SageSchlo::Blink));
    }

    void Default(){}

    void Surprised(){
        AddParameterFrame(SageSchlo::Surprised, 1.0f);

        AddParameterFrame(SageSchloSideDisplay::Exclamation + 20, 1.0f);
        
        DisableBlinking();
    }

    void Blush(){
        AddParameterFrame(SageSchlo::Blush, 1.0f);

        DisableBlinking();
    }

    void Dizzy(){
        AddParameterFrame(SageSchlo::Dizzy, 1.0f);

        AddParameterFrame(SageSchloSideDisplay::Dizzy + 20, 1.0f);

        DisableBlinking();

        wiggle = true;
    }
    
    void Angry1(){
        AddParameterFrame(SageSchlo::Angry1, 1.0f);

        AddParameterFrame(SageSchloSideDisplay::Exclamation + 20, 1.0f);
    }
    
    void Angry2(){
        AddParameterFrame(SageSchlo::Angry2, 1.0f);
        AddMaterialFrame(Color::CYELLOW);

        AddParameterFrame(SageSchloSideDisplay::Exclamation + 20, 1.0f);
    }
    
    void Angry3(){
        AddParameterFrame(SageSchlo::Angry3, 1.0f);
        AddMaterialFrame(Color::CRED);

        AddParameterFrame(SageSchloSideDisplay::Exclamation + 20, 1.0f);
    }
    
    void OwO(){
        AddParameterFrame(SageSchlo::OwO, 1.0f);
        
        DisableBlinking();
    }

    void Tired(){
        AddParameterFrame(SageSchlo::Tired, 1.0f);
        
        AddParameterFrame(SageSchloSideDisplay::Battery + 20, 1.0f);
        AddParameterFrame(SageSchloSideDisplay::BatteryFull + 20, batteryChargeFunc.Update());

        DisableBlinking();
    }

    void Sad(){
        AddParameterFrame(SageSchlo::Sad, 1.0f);
    }

public:
    SageAnimation() : ProtogenProject(&cameras, &controller, 2, Vector2D(), Vector2D(192.0f, 94.0f), 22, 23, 12){
        scene.AddObject(pM.GetObject());
        scene.AddObject(sageSideDisplay.GetObject());

        pM.GetObject()->SetMaterial(GetFaceMaterial());
        sageSideDisplay.GetObject()->SetMaterial(GetFaceMaterial());

        LinkControlParameters();

        hud.SetFaceArray(faceArray);
    }

    void Update(float ratio) override {
        pM.Reset();
        sageSideDisplay.Reset();

        EnableBlinking();
        wiggle = false;

        controller.SetBrightness(Menu::GetBrightness());
        controller.SetAccentBrightness(Menu::GetAccentBrightness());

        uint8_t mode = Menu::GetFaceState();//change by button press

        if (IsBooped()){
            Blush();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Surprised();
            else if (mode == 2) Dizzy();
            else if (mode == 3) Angry1();
            else if (mode == 4) Angry2();
            else if (mode == 5) Angry3();
            else if (mode == 6) OwO();
            else if (mode == 7) Tired();
            else if (mode == 8) Sad();
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

        pM.Update();
        sageSideDisplay.Update();

        AlignObjectFace(pM.GetObject(), 0.0f);
        AlignObjectNoScaleRear(sageSideDisplay.GetObject(), 0.0f, 0.0f);

        SetWiggleSpeed(5.0f);
        SetMenuWiggleSpeed(0.0f, 0.0f, 0.0f);
        SetMenuOffset(Vector2D(17.5f, -3.0f));
        SetMenuSize(Vector2D(192, 56));
        
        pM.GetObject()->GetTransform()->SetPosition(GetWiggleOffset());
        pM.GetObject()->UpdateTransform();

        if(wiggle){
            sageSideDisplay.GetObject()->GetTransform()->SetPosition(GetWiggleOffset());
        }
        else{
            sageSideDisplay.GetObject()->GetTransform()->SetPosition(Vector3D(2.0f, 0.0f, 0.0f));
        }

        sageSideDisplay.GetObject()->GetTransform()->SetScaleOffset(sageSideDisplay.GetObject()->GetCenterOffset());
        sageSideDisplay.GetObject()->GetTransform()->SetScale(Vector3D(1.45f, 1.45f, 1.45f));
        
        sageSideDisplay.GetObject()->UpdateTransform();
    }
};
