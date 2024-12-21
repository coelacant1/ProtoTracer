#pragma once

#include "../Templates/ProtogenProjectTemplate.h"
#include "../../Assets/Models/FBX/Commissions/DrGonzoFace.h"
#include "../../Assets/Models/FBX/Commissions/DrGonzoSD.h"
#include "../../Assets/Models/FBX/Commissions/DrGonzoTears.h"

#include "../../Camera/CameraManager/Implementations/HUB75DeltaCameras.h"
#include "../../Controller/HUB75Controller.h"

#include "../../Animation/MorphTransform.h"

//#define NEOTRELLISMENU

class DrGonzoProject : public ProtogenProject {
private:
    HUB75DeltaCameraManager cameras;
    HUB75Controller controller = HUB75Controller(&cameras, 255, 100);

    DrGonzoFace pM;
    DrGonzoSD sideDisplay;
    DrGonzoTears tears;
    //DeltaDisplayBackground deltaDisplayBackground;

    SimpleMaterial lBlue = SimpleMaterial(RGBColor(50, 126, 180));

    MaterialAnimator<2> sideDisplayMaterial = MaterialAnimator<2>();

    FunctionGenerator drip1 = FunctionGenerator(FunctionGenerator::Gravity, 0.0f, 1.0f, 2.73f);
    FunctionGenerator drip2 = FunctionGenerator(FunctionGenerator::Gravity, 0.0f, 1.0f, 2.41f);
    FunctionGenerator drip3 = FunctionGenerator(FunctionGenerator::Gravity, 0.0f, 1.0f, 2.16f);

    FunctionGenerator loadingBar = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 7.23f);

    Transform tearTransform;

    MorphTransform<5> morphTransform = MorphTransform<5>(&eEA);
    
    const __FlashStringHelper* faceArray[14] = {F("DEFAULT"), F("HAPPY"), F("ANGY"), F("LEWD"), F("LOADING"), F("QUESTION"), F("DIZZY"), F("SAD"), F("OWO"), F("BOOP"), F("AUDIO1"), F("AUDIO2"), F("AUDIO3")};

    void LinkControlParameters() override {
        AddParameter(DrGonzoFace::Happy, pM.GetMorphWeightReference(DrGonzoFace::Happy), 30);
        AddParameter(DrGonzoFace::Angy, pM.GetMorphWeightReference(DrGonzoFace::Angy), 15);
        AddParameter(DrGonzoFace::Lewd, pM.GetMorphWeightReference(DrGonzoFace::Lewd), 35);
        AddParameter(DrGonzoFace::Loading, pM.GetMorphWeightReference(DrGonzoFace::Loading), 20);
        AddParameter(DrGonzoFace::LoadingB1, pM.GetMorphWeightReference(DrGonzoFace::LoadingB1), 30, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(DrGonzoFace::LoadingB2, pM.GetMorphWeightReference(DrGonzoFace::LoadingB2), 30, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(DrGonzoFace::LoadingB3, pM.GetMorphWeightReference(DrGonzoFace::LoadingB3), 30, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(DrGonzoFace::LoadingB4, pM.GetMorphWeightReference(DrGonzoFace::LoadingB4), 30, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(DrGonzoFace::LoadingB5, pM.GetMorphWeightReference(DrGonzoFace::LoadingB5), 30, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(DrGonzoFace::Question, pM.GetMorphWeightReference(DrGonzoFace::Question), 45);
        AddParameter(DrGonzoFace::Dizzy, pM.GetMorphWeightReference(DrGonzoFace::Dizzy), 45);
        AddParameter(DrGonzoFace::Sad, pM.GetMorphWeightReference(DrGonzoFace::Sad), 15, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(DrGonzoFace::OwO, pM.GetMorphWeightReference(DrGonzoFace::OwO), 40);
        AddParameter(DrGonzoFace::Boop, pM.GetMorphWeightReference(DrGonzoFace::Boop), 35);
        
        AddParameter(DrGonzoSD::Angy + 50, sideDisplay.GetMorphWeightReference(DrGonzoSD::Angy), 15);
        AddParameter(DrGonzoSD::Lewd + 50, sideDisplay.GetMorphWeightReference(DrGonzoSD::Lewd), 35);
        AddParameter(DrGonzoSD::OwO + 50, sideDisplay.GetMorphWeightReference(DrGonzoSD::OwO), 20);
        AddParameter(DrGonzoSD::Question + 50, sideDisplay.GetMorphWeightReference(DrGonzoSD::Question), 30);
        
        AddParameter(DrGonzoFace::HideBlush, pM.GetMorphWeightReference(DrGonzoFace::HideBlush), 15, IEasyEaseAnimator::InterpolationMethod::Cosine, true);

        AddViseme(Viseme::MouthShape::EE, pM.GetMorphWeightReference(DrGonzoFace::vrc_v_ee));
        AddViseme(Viseme::MouthShape::AH, pM.GetMorphWeightReference(DrGonzoFace::vrc_v_aa));
        AddViseme(Viseme::MouthShape::UH, pM.GetMorphWeightReference(DrGonzoFace::vrc_v_dd));
        AddViseme(Viseme::MouthShape::AR, pM.GetMorphWeightReference(DrGonzoFace::vrc_v_rr));
        AddViseme(Viseme::MouthShape::ER, pM.GetMorphWeightReference(DrGonzoFace::vrc_v_ch));
        AddViseme(Viseme::MouthShape::OO, pM.GetMorphWeightReference(DrGonzoFace::vrc_v_oh));
        AddViseme(Viseme::MouthShape::SS, pM.GetMorphWeightReference(DrGonzoFace::vrc_v_ss));

        AddBlinkParameter(pM.GetMorphWeightReference(DrGonzoFace::Blink));

        sideDisplayMaterial.SetBaseMaterial(Material::Method::Base, GetFaceMaterial());
        sideDisplayMaterial.AddMaterial(Material::Method::Replace, &lBlue, 40, 0.0f, 1.0f);

        morphTransform.AddMorph(DrGonzoFace::LoadingB1, Vector3D(0.0f, -17.5f, 0.0f), Vector3D(1.6f, 6.0f, 1.0f));
        morphTransform.AddMorph(DrGonzoSD::Angy + 50, Vector3D(), Vector3D(1.5f, 2.0f, 1.0f), Vector3D(0.0f, 0.0f, 0.0f));
        morphTransform.AddMorph(DrGonzoSD::Lewd + 50, Vector3D(), Vector3D(1.5f, 1.5f, 1.0f));
        morphTransform.AddMorph(DrGonzoSD::OwO + 50, Vector3D(1.0f, -8.5f, 0.0f), Vector3D(1.3f, 3.0f, 1.0f));
        morphTransform.AddMorph(DrGonzoSD::Question + 50, Vector3D(), Vector3D(1.0f, 1.1f, 1.0f));
    }

    void Default(){
        tears.GetObject()->Disable();
    }
    
    void Happy(){
        tears.GetObject()->Disable();

        AddParameterFrame(DrGonzoFace::Happy, 1.0f);
    }

    void Angy(){
        tears.GetObject()->Disable();
        
        AddParameterFrame(DrGonzoFace::Angy, 1.0f);
        AddParameterFrame(DrGonzoSD::Angy + 50, 1.0f);

    }

    void Lewd(){
        tears.GetObject()->Disable();
        
        AddParameterFrame(DrGonzoFace::HideBlush, 0.0f);
        AddParameterFrame(DrGonzoFace::Lewd, 1.0f);
        AddParameterFrame(DrGonzoSD::Lewd + 50, 1.0f);

        sideDisplayMaterial.AddMaterialFrame(lBlue, 1.0f);
    }

    void Loading(){
        tears.GetObject()->Disable();
        
        SetWiggleSpeed(1.0f);
        DisableBlinking();
        AddParameterFrame(DrGonzoFace::HideBlush, 0.0f);
        AddParameterFrame(DrGonzoFace::Loading, 1.0f);
        AddMaterialFrame(ProtogenProject::CGREEN);

        float loadingRatio = loadingBar.Update();
        float setRatio = 0.0f;

        if(loadingRatio < 0.15f){

        }    
        else if(loadingRatio < 0.30f){
            setRatio = Mathematics::Map(loadingRatio, 0.0f, 0.2f, 0.0f, 1.0f);
            
            AddParameterFrame(DrGonzoFace::LoadingB1, setRatio);
        }
        else if(loadingRatio < 0.55f){
            setRatio = Mathematics::Map(loadingRatio, 0.2f, 0.4f, 0.0f, 1.0f);
            
            AddParameterFrame(DrGonzoFace::LoadingB1, 1.0f);
            AddParameterFrame(DrGonzoFace::LoadingB2, setRatio);
        }
        else if(loadingRatio < 0.7f){
            setRatio = Mathematics::Map(loadingRatio, 0.4f, 0.6f, 0.0f, 1.0f);
            
            AddParameterFrame(DrGonzoFace::LoadingB1, 1.0f);
            AddParameterFrame(DrGonzoFace::LoadingB2, 1.0f);
            AddParameterFrame(DrGonzoFace::LoadingB3, setRatio);
        }
        else if(loadingRatio < 0.85f){
            setRatio = Mathematics::Map(loadingRatio, 0.6f, 0.8f, 0.0f, 1.0f);
            
            AddParameterFrame(DrGonzoFace::LoadingB1, 1.0f);
            AddParameterFrame(DrGonzoFace::LoadingB2, 1.0f);
            AddParameterFrame(DrGonzoFace::LoadingB3, 1.0f);
            AddParameterFrame(DrGonzoFace::LoadingB4, setRatio);
        }
        else{
            setRatio = Mathematics::Map(loadingRatio, 0.8f, 1.0f, 0.0f, 1.0f);
            
            AddParameterFrame(DrGonzoFace::LoadingB1, 1.0f);
            AddParameterFrame(DrGonzoFace::LoadingB2, 1.0f);
            AddParameterFrame(DrGonzoFace::LoadingB3, 1.0f);
            AddParameterFrame(DrGonzoFace::LoadingB4, 1.0f);
            AddParameterFrame(DrGonzoFace::LoadingB5, setRatio);
        }
    }
    
    void Question(){
        tears.GetObject()->Disable();
        
        DisableBlinking();
        AddParameterFrame(DrGonzoFace::Question, 1.0f);
        AddParameterFrame(DrGonzoSD::Question + 50, 1.0f);
    }
    
    void Dizzy(){
        tears.GetObject()->Disable();
        
        DisableBlinking();
        AddParameterFrame(DrGonzoFace::Dizzy, 1.0f);
    }

    void Sad(){
        tears.GetObject()->Enable();
        
        AddParameterFrame(DrGonzoFace::Sad, 1.0f);

        tears.SetMorphWeight(DrGonzoTears::DropTear1, drip1.Update());
        tears.SetMorphWeight(DrGonzoTears::DropTear2, drip2.Update());
        tears.SetMorphWeight(DrGonzoTears::DropTear3, drip3.Update());
    }

    void OwO(){
        tears.GetObject()->Disable();
        
        DisableBlinking();
        AddParameterFrame(DrGonzoFace::OwO, 1.0f);
        AddParameterFrame(DrGonzoSD::OwO + 50, 1.0f);

        //AddMaterialFrame(Color::CRAINBOW);
    }
    
    void Boop(){
        tears.GetObject()->Disable();
        
        AddParameterFrame(DrGonzoFace::Boop, 1.0f);
    }

public:
    DrGonzoProject() : ProtogenProject(&cameras, &controller, 3, Vector2D(), Vector2D(192.0f, 94.0f), 22, 23, 12){
        scene.AddObject(pM.GetObject());
        scene.AddObject(sideDisplay.GetObject());
        scene.AddObject(tears.GetObject());
        //scene.AddObject(deltaDisplayBackground.GetObject());

        pM.GetObject()->SetMaterial(GetFaceMaterial());
        sideDisplay.GetObject()->SetMaterial(&sideDisplayMaterial);
        tears.GetObject()->SetMaterial(&lBlue);
        //deltaDisplayBackground.GetObject()->SetMaterial(GetFaceMaterial());

        hud.SetFaceArray(faceArray);

        LinkControlParameters();
        
        SetMenuWiggleSpeed(0.0f, 0.0f, 0.0f);
        SetMenuOffset(Vector2D(17.5f, -3.0f));
        SetMenuSize(Vector2D(192, 56));
    }

    void Update(float ratio) override {
        SetWiggleSpeed(3.0f);
        EnableBlinking();
        
        pM.Reset();
        sideDisplay.Reset();
        tears.Reset();
        
        tears.GetObject()->ResetVertices();
        tearTransform = GetAlignmentTransform(Vector2D(100.0f * GetFaceScale(), 60.0f), Vector2D(140.0f * GetFaceScale(), 100.0f), tears.GetObject(), 0.0f);

        uint8_t mode = Menu::GetFaceState();//change by button press

        controller.SetBrightness(Menu::GetBrightness());
        controller.SetAccentBrightness(Menu::GetAccentBrightness());

        if (IsBooped()){
            Boop();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Happy();
            else if (mode == 2) Angy();
            else if (mode == 3) Lewd();
            else if (mode == 4) Loading();
            else if (mode == 5) Question();
            else if (mode == 6) Dizzy();
            else if (mode == 7) Sad();
            else if (mode == 8) OwO();
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

        *sideDisplay.GetMorphWeightReference(DrGonzoSD::Merge) = 1.0f;
        *sideDisplay.GetMorphWeightReference(DrGonzoSD::LoadingB1) = *pM.GetMorphWeightReference(DrGonzoFace::LoadingB1);
        *sideDisplay.GetMorphWeightReference(DrGonzoSD::LoadingB2) = *pM.GetMorphWeightReference(DrGonzoFace::LoadingB2);
        *sideDisplay.GetMorphWeightReference(DrGonzoSD::LoadingB3) = *pM.GetMorphWeightReference(DrGonzoFace::LoadingB3);
        *sideDisplay.GetMorphWeightReference(DrGonzoSD::LoadingB4) = *pM.GetMorphWeightReference(DrGonzoFace::LoadingB4);
        *sideDisplay.GetMorphWeightReference(DrGonzoSD::LoadingB5) = *pM.GetMorphWeightReference(DrGonzoFace::LoadingB5);

        pM.Update();
        sideDisplay.Update();
        tears.Update();

        sideDisplayMaterial.Update();

        AlignObjectFace(pM.GetObject(), 0.0f);
        AlignObjectRear(sideDisplay.GetObject(), 0.0f);

        pM.GetObject()->GetTransform()->SetPosition(GetWiggleOffset());
        pM.GetObject()->UpdateTransform();

        morphTransform.SetMorphPositionOffset(DrGonzoSD::Angy + 50, Vector3D(3.5f, -11.0f, 0.0f) + GetWiggleOffset());
        morphTransform.SetMorphPositionOffset(DrGonzoSD::Lewd + 50, Vector3D(10.0f, -10.0f, 0.0f) + GetWiggleOffset());
        morphTransform.SetMorphPositionOffset(DrGonzoSD::Question + 50, Vector3D(17.5f, -7.5f, 0.0f) + GetWiggleOffset());

        sideDisplay.GetObject()->GetTransform()->SetPosition(morphTransform.GetPositionOffset());
        sideDisplay.GetObject()->GetTransform()->SetScale(morphTransform.GetScaleOffset());
        sideDisplay.GetObject()->GetTransform()->SetScaleOffset(sideDisplay.GetObject()->GetCenterOffset());
        sideDisplay.GetObject()->GetTransform()->SetRotation(morphTransform.GetRotationOffset());
        sideDisplay.GetObject()->GetTransform()->SetRotationOffset(sideDisplay.GetObject()->GetCenterOffset());
        sideDisplay.GetObject()->UpdateTransform();

        //Serial.print(morphTransform.GetPositionOffset().ToString()); Serial.print('\t');
        //Serial.print(morphTransform.GetScaleOffset().ToString()); Serial.print('\t');
        //Serial.println(morphTransform.GetRotationOffset().ToString());

        tearTransform.SetPosition(tearTransform.GetPosition() + GetWiggleOffset() + Vector3D(0.0f, 0.0f, 200.0f));

        tears.GetObject()->SetTransform(tearTransform);
        tears.GetObject()->UpdateTransform();

        //Serial.println(tears.GetObject()->GetCenterOffset().ToString());
    }
};
