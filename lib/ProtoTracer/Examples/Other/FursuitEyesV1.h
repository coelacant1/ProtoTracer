#pragma once

#include "../Templates/ProtogenProjectTemplate.h"
#include "../../Assets/Models/OBJ/DeltaDisplayBackground.h"
#include "../../Assets/Models/FBX/Commissions/RoboEyes.h"

#include "../../Scene/Materials/Animated/TVStatic.h"

#include "../../Camera/CameraManager/Implementations/APA102CamerasV1.h"
#include "../../Controller/APA102Controller.h"

class FursuitEyesV1 : public ProtogenProject {
private:
    APA102CamerasV1 cameras;
    APA102Controller controller = APA102Controller(&cameras, 50, 50);
    RoboEyes pML;
    RoboEyes pMR;

    TVStatic tvStatic;
    
	const __FlashStringHelper* faceArray[10] = {F("DEFAULT"), F("CLOSE"), F("DOT"), F("SAD"), F("QUESTION"), F("DISAPPOI"), F("ANGRY"), F("HEART"), F("AUDIO1"), F("AUDIO2")};

    void LinkControlParameters() override {//Called from parent
        AddParameter(RoboEyes::Close, pML.GetMorphWeightReference(RoboEyes::Close), 60);
        AddParameter(RoboEyes::Dot, pML.GetMorphWeightReference(RoboEyes::Dot), 90, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(RoboEyes::Sad, pML.GetMorphWeightReference(RoboEyes::Sad), 120, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(RoboEyes::Question, pML.GetMorphWeightReference(RoboEyes::Question), 120);
        AddParameter(RoboEyes::Disappoint, pML.GetMorphWeightReference(RoboEyes::Disappoint), 100);
        AddParameter(RoboEyes::Angry, pML.GetMorphWeightReference(RoboEyes::Angry), 80, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(RoboEyes::Heart, pML.GetMorphWeightReference(RoboEyes::Heart), 120);
        AddParameter(RoboEyes::MirrorQuestion, pML.GetMorphWeightReference(RoboEyes::MirrorQuestion), 60);
        
        AddParameter(RoboEyes::Close + 10, pMR.GetMorphWeightReference(RoboEyes::Close), 60);
        AddParameter(RoboEyes::Dot + 10, pMR.GetMorphWeightReference(RoboEyes::Dot), 90, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(RoboEyes::Sad + 10, pMR.GetMorphWeightReference(RoboEyes::Sad), 120, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(RoboEyes::Question + 10, pMR.GetMorphWeightReference(RoboEyes::Question), 120);
        AddParameter(RoboEyes::Disappoint + 10, pMR.GetMorphWeightReference(RoboEyes::Disappoint), 100);
        AddParameter(RoboEyes::Angry + 10, pMR.GetMorphWeightReference(RoboEyes::Angry), 80, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(RoboEyes::Heart + 10, pMR.GetMorphWeightReference(RoboEyes::Heart), 120);
        AddParameter(RoboEyes::MirrorQuestion + 10, pMR.GetMorphWeightReference(RoboEyes::MirrorQuestion), 60);

        AddViseme(Viseme::MouthShape::EE, pML.GetMorphWeightReference(RoboEyes::Empty));
        AddViseme(Viseme::MouthShape::AH, pML.GetMorphWeightReference(RoboEyes::Empty));
        AddViseme(Viseme::MouthShape::UH, pML.GetMorphWeightReference(RoboEyes::Empty));
        AddViseme(Viseme::MouthShape::AR, pML.GetMorphWeightReference(RoboEyes::Empty));
        AddViseme(Viseme::MouthShape::ER, pML.GetMorphWeightReference(RoboEyes::Empty));
        AddViseme(Viseme::MouthShape::OO, pML.GetMorphWeightReference(RoboEyes::Empty));
        AddViseme(Viseme::MouthShape::SS, pML.GetMorphWeightReference(RoboEyes::Empty));

        AddBlinkParameter(pML.GetMorphWeightReference(RoboEyes::Blink));
        AddBlinkParameter(pMR.GetMorphWeightReference(RoboEyes::Blink));
    }

    void Default(){
        EnableBlinking();
    }

    void Close(){
        AddParameterFrame(RoboEyes::Close, 1.0f);
        AddParameterFrame(RoboEyes::Close + 10, 1.0f);

        DisableBlinking();
    } 

    void Dot(){
        AddParameterFrame(RoboEyes::Dot, 1.0f);
        AddParameterFrame(RoboEyes::Dot + 10, 1.0f);
        AddMaterialFrame(Color::CBLUE);
        
        EnableBlinking();
    }

    void Sad(){
        AddParameterFrame(RoboEyes::Sad, 1.0f);
        AddParameterFrame(RoboEyes::Sad + 10, 1.0f);
        
        EnableBlinking();
    }
    
    void Question(){
        if(millis() % 2000 > 1000) {
            AddParameterFrame(RoboEyes::Question, 1.0f);
            AddParameterFrame(RoboEyes::Question + 10, 1.0f);
        }
        else{
            AddParameterFrame(RoboEyes::MirrorQuestion, 1.0f);
            AddParameterFrame(RoboEyes::MirrorQuestion + 10, 1.0f);
        }
        
        DisableBlinking();
    }
    
    void Disappoint(){
        AddParameterFrame(RoboEyes::Disappoint, 1.0f);
        AddParameterFrame(RoboEyes::Disappoint + 10, 1.0f);
        
        EnableBlinking();
    }

    void Angry(){
        AddParameterFrame(RoboEyes::Angry, 1.0f);
        AddParameterFrame(RoboEyes::Angry + 10, 1.0f);
        AddMaterialFrame(Color::CRED);
        
        EnableBlinking();
    }

    void Heart(){
        AddParameterFrame(RoboEyes::Heart, 1.0f);
        AddParameterFrame(RoboEyes::Heart + 10, 1.0f);
        
        EnableBlinking();
    }

public:
    FursuitEyesV1() : ProtogenProject(&cameras, &controller, 2, Vector2D(-110.0f, -36.0f), Vector2D(110.0f, 36.0f), 15, 21, 10){
        scene.AddObject(pML.GetObject());
        scene.AddObject(pMR.GetObject());

        pML.GetObject()->SetMaterial(GetFaceMaterial());
        pMR.GetObject()->SetMaterial(GetFaceMaterial());

        hud.SetFaceArray(faceArray);

        LinkControlParameters();
        
        SetWiggleSpeed(5.0f);
        SetMenuWiggleSpeed(0.0f, 0.0f, 0.0f);
        SetMenuOffset(Vector2D(-110.0f, -36.0f));
        SetMenuSize(Vector2D(220.0f, 72.0f));
    }

    void Update(float ratio) override {
        pML.Reset();
        pMR.Reset();

        uint8_t mode = Menu::GetFaceState();//change by button press

        controller.SetBrightness(Menu::GetBrightness());
        controller.SetAccentBrightness(Menu::GetAccentBrightness());

        SelectFace(mode);

        UpdateFace(ratio);

        pML.Update();
        pMR.Update();
        

        AlignObject(Vector2D(-123.0f, -48.0f), Vector2D(-14.0f, 48.0f), pML.GetObject(), 0.0f);
        AlignObject(Vector2D(18.0f, -48.0f), Vector2D(127.0f, 48.0f), pMR.GetObject(), 0.0f);

        

        pML.GetObject()->GetTransform()->SetPosition(GetWiggleOffset() * 2.0f);
        pML.GetObject()->UpdateTransform();
        
        pMR.GetObject()->GetTransform()->SetScale(Vector3D(-1.0f, 1.0f, 1.0f));
        pMR.GetObject()->GetTransform()->SetScaleOffset(pMR.GetObject()->GetCenterOffset());
        pMR.GetObject()->GetTransform()->SetPosition(GetWiggleOffset() * Vector3D(-2.0f, 2.0f, 2.0f));
        pMR.GetObject()->UpdateTransform();
    }

    void SelectFace(uint8_t code) {
        switch(code) {
            case 0: Default();      break;
            case 1: Close();        break;
            case 2: Dot();          break;
            case 3: Sad();          break;
            case 4: Question();     break;
            case 5: Disappoint();   break;
            case 6: Angry();        break;
            case 7: Heart();        break;
            case 8: SpectrumAnalyzerFace(); break;
            default: OscilloscopeFace();    break;
        }
    }
};
