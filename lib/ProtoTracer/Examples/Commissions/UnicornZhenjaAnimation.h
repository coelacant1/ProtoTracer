#pragma once

#include "../Templates/ProtogenProjectTemplate.h"
#include "../../Assets/Models/OBJ/DeltaDisplayBackground.h"
#include "../../Assets/Models/FBX/Commissions/UnicornZhenja.h"
#include "../../Scene/Materials/Animated/TVStatic.h"

#include "../../Camera/CameraManager/Implementations/HUB75DeltaCameras.h"
#include "../../Controller/HUB75Controller.h"

class UnicornZhenjaAnimation : public ProtogenProject {
private:
    HUB75DeltaCameraManager cameras;
    HUB75Controller controller = HUB75Controller(&cameras, 50, 50);
    UnicornZhenja pM;
    DeltaDisplayBackground deltaDisplayBackground;
    TVStatic tvStatic;
    
	const __FlashStringHelper* faceArray[14] = {F("DEFAULT"), F("UPSET"), F("SALTY"), F("SLEEPY"), F("SAD"), F("LOADING"), F("DIZZY"), F("HEART"), F("DEAD"), F("PUPIL"), F("STATIC"), F("AUDIO1"), F("AUDIO2"), F("AUDIO3")};

    void LinkControlParameters() override {//Called from parent
        AddParameter(UnicornZhenja::Upset, pM.GetMorphWeightReference(UnicornZhenja::Upset), 15, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(UnicornZhenja::Salty, pM.GetMorphWeightReference(UnicornZhenja::Salty), 20);
        AddParameter(UnicornZhenja::Sleepy, pM.GetMorphWeightReference(UnicornZhenja::Sleepy), 45, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(UnicornZhenja::Sad, pM.GetMorphWeightReference(UnicornZhenja::Sad), 45, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(UnicornZhenja::Loading, pM.GetMorphWeightReference(UnicornZhenja::Loading), 25, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(UnicornZhenja::Dizzy, pM.GetMorphWeightReference(UnicornZhenja::Dizzy), 40);
        AddParameter(UnicornZhenja::Heart, pM.GetMorphWeightReference(UnicornZhenja::Heart), 25);
        AddParameter(UnicornZhenja::Dead, pM.GetMorphWeightReference(UnicornZhenja::Dead), 15);
        AddParameter(UnicornZhenja::Pupil, pM.GetMorphWeightReference(UnicornZhenja::Pupil), 15);
        AddParameter(UnicornZhenja::Static, pM.GetMorphWeightReference(UnicornZhenja::Static), 60, IEasyEaseAnimator::InterpolationMethod::Cosine);

        AddParameter(UnicornZhenja::HideHeart, pM.GetMorphWeightReference(UnicornZhenja::HideHeart), 15, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(UnicornZhenja::HideLoading, pM.GetMorphWeightReference(UnicornZhenja::HideLoading), 15, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(UnicornZhenja::HideSpiral, pM.GetMorphWeightReference(UnicornZhenja::HideSpiral), 15, IEasyEaseAnimator::InterpolationMethod::Cosine);

        AddViseme(Viseme::MouthShape::EE, pM.GetMorphWeightReference(UnicornZhenja::vrc_v_ee));
        AddViseme(Viseme::MouthShape::AH, pM.GetMorphWeightReference(UnicornZhenja::vrc_v_aa));
        AddViseme(Viseme::MouthShape::UH, pM.GetMorphWeightReference(UnicornZhenja::vrc_v_dd));
        AddViseme(Viseme::MouthShape::AR, pM.GetMorphWeightReference(UnicornZhenja::vrc_v_rr));
        AddViseme(Viseme::MouthShape::ER, pM.GetMorphWeightReference(UnicornZhenja::vrc_v_ch));
        AddViseme(Viseme::MouthShape::OO, pM.GetMorphWeightReference(UnicornZhenja::vrc_v_oh));
        AddViseme(Viseme::MouthShape::SS, pM.GetMorphWeightReference(UnicornZhenja::vrc_v_ss));

        AddBlinkParameter(pM.GetMorphWeightReference(UnicornZhenja::Blink));
    }

    void Default(){
        AddParameterFrame(UnicornZhenja::HideHeart, 1.0f);
        AddParameterFrame(UnicornZhenja::HideLoading, 1.0f);
        AddParameterFrame(UnicornZhenja::HideSpiral, 1.0f);

        AddMaterialFrame(tvStatic);
    }

    void Upset(){
        AddParameterFrame(UnicornZhenja::Upset, 1.0f);
        AddParameterFrame(UnicornZhenja::HideHeart, 1.0f);
        AddParameterFrame(UnicornZhenja::HideLoading, 1.0f);
        AddParameterFrame(UnicornZhenja::HideSpiral, 1.0f);

        AddMaterialFrame(Color::CRED);
    }

    void Salty(){
        AddParameterFrame(UnicornZhenja::Salty, 1.0f);
        AddParameterFrame(UnicornZhenja::HideHeart, 1.0f);
        AddParameterFrame(UnicornZhenja::HideLoading, 1.0f);
        AddParameterFrame(UnicornZhenja::HideSpiral, 1.0f);

        AddMaterialFrame(tvStatic);
    }

    void Sleepy(){
        AddParameterFrame(UnicornZhenja::Sleepy, 1.0f);
        AddParameterFrame(UnicornZhenja::HideHeart, 1.0f);
        AddParameterFrame(UnicornZhenja::HideLoading, 1.0f);

        AddMaterialFrame(tvStatic);
    }

    void Sad(){
        AddParameterFrame(UnicornZhenja::Sad, 1.0f);
        AddParameterFrame(UnicornZhenja::HideHeart, 1.0f);
        AddParameterFrame(UnicornZhenja::HideLoading, 1.0f);
        AddParameterFrame(UnicornZhenja::HideSpiral, 1.0f);

        AddMaterialFrame(Color::CBLUE);
    }

    void Loading(){
        AddParameterFrame(UnicornZhenja::Loading, 1.0f);
        AddParameterFrame(UnicornZhenja::HideHeart, 1.0f);
        AddParameterFrame(UnicornZhenja::HideSpiral, 1.0f);

        AddMaterialFrame(tvStatic);
    }

    void Dizzy(){
        AddParameterFrame(UnicornZhenja::Dizzy, 1.0f);
        AddParameterFrame(UnicornZhenja::HideHeart, 1.0f);
        AddParameterFrame(UnicornZhenja::HideLoading, 1.0f);

        AddMaterialFrame(tvStatic);
    }

    void Heart(){
        AddParameterFrame(UnicornZhenja::Heart, 1.0f);
        AddParameterFrame(UnicornZhenja::HideLoading, 1.0f);
        AddParameterFrame(UnicornZhenja::HideSpiral, 1.0f);

        AddMaterialFrame(tvStatic);
    }

    void Dead(){
        AddParameterFrame(UnicornZhenja::Dead, 1.0f);
        AddParameterFrame(UnicornZhenja::HideHeart, 1.0f);
        AddParameterFrame(UnicornZhenja::HideLoading, 1.0f);

        AddMaterialFrame(tvStatic);
    }

    void Pupil(){
        AddParameterFrame(UnicornZhenja::Pupil, 1.0f);
        AddParameterFrame(UnicornZhenja::HideHeart, 1.0f);
        AddParameterFrame(UnicornZhenja::HideLoading, 1.0f);
        AddParameterFrame(UnicornZhenja::HideSpiral, 1.0f);

        AddMaterialFrame(tvStatic);
    }

    void Static(){
        HideFace();

        AddParameterFrame(UnicornZhenja::Loading, 1.0f);
        AddParameterFrame(UnicornZhenja::HideHeart, 1.0f);
        AddParameterFrame(UnicornZhenja::HideLoading, 1.0f);
        AddParameterFrame(UnicornZhenja::HideSpiral, 1.0f);

        AddMaterialFrame(tvStatic);
        AddBackgroundMaterialFrame(tvStatic);
    }

public:
    UnicornZhenjaAnimation() : ProtogenProject(&cameras, &controller, 2, Vector2D(), Vector2D(192.0f, 94.0f), 22, 23, 13){
        scene.AddObject(pM.GetObject());
        scene.AddObject(deltaDisplayBackground.GetObject());

        pM.GetObject()->SetMaterial(GetFaceMaterial());
        deltaDisplayBackground.GetObject()->SetMaterial(GetFaceMaterial());

        AddMaterial(Material::Add, &tvStatic, 40, 0.0f, 1.0f);
        AddBackgroundMaterial(Material::Add, &tvStatic, 40, 0.0f, 1.0f);

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

        if (IsBooped()){
            Static();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Upset();
            else if (mode == 2) Salty();
            else if (mode == 3) Sleepy();
            else if (mode == 4) Sad();
            else if (mode == 5) Loading();
            else if (mode == 6) Dizzy();
            else if (mode == 7) Heart();
            else if (mode == 8) Dead();
            else if (mode == 9) Pupil();
            else if (mode == 10) {
                AudioReactiveGradientFace();
            }
            else if (mode == 11){
                OscilloscopeFace();
            }
            else {
                SpectrumAnalyzerFace();
            }
        }
        
        tvStatic.Update(ratio);

        UpdateFace(ratio);

        pM.Update();

        AlignObjectFace(pM.GetObject(), 0.0f);

        pM.GetObject()->GetTransform()->SetPosition(GetWiggleOffset());
        pM.GetObject()->UpdateTransform();
    }
};
