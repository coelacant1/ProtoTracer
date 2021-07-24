#pragma once

#include "..\Flash\MouthObjs.h"
#include "..\Render\Object2D.h"
#include "..\Render\Object3D.h"
#include "..\Math\Vector2D.h"

class Mouth{
public:
    enum Emotion {
        Neutral,
        ClosedHappy,
        OpenHappy,
        Confuse,
        Confusion,
        Angry,
        Poggers,
        Monch,
        Derpy,
        Shocked,
        HappyRed,
        Angel,
        SuperHappy,
        Smirk,
        OhNo,
        LemmeIn,
        How,
        Seriously,
        Done,
        Mlem
    };
    
private:
    const byte emotionCount = 20;
    Object2D currentObj = Object2D(neutralString, 12, 10);
    Object2D neutralObj = Object2D(neutralString, 12, 10);
    Object2D openHappyObj = Object2D(openHappyString, 12, 10);
    Object2D closedHappyObj = Object2D(closedHappyString, 12, 10);
    Object2D confuseObj = Object2D(confuseString, 12, 10);
    Object2D confusionObj = Object2D(confusionString, 12, 10);
    Object2D angryObj = Object2D(angryString, 12, 10);
    Object2D poggersObj = Object2D(poggersString, 12, 10);
    Object2D monchObj = Object2D(monchString, 12, 10);
    Object2D derpyObj = Object2D(derpyString, 12, 10);
    Object2D shockedObj = Object2D(shockedString, 12, 10);
    Object2D happyRedObj = Object2D(happyRedString, 12, 10);
    Object2D angelObj = Object2D(angelString, 12, 10);
    Object2D superHappyObj = Object2D(superHappyString, 12, 10);
    Object2D smirkObj = Object2D(smirkString, 12, 10);
    Object2D ohNoObj = Object2D(ohNoString, 12, 10);
    Object2D lemmeInObj = Object2D(lemmeInString, 12, 10);
    Object2D howObj = Object2D(howString, 12, 10);
    Object2D seriouslyObj = Object2D(seriouslyString, 12, 10);
    Object2D doneObj = Object2D(doneString, 12, 10);
    Object2D mlemObj = Object2D(mlemString, 12, 10);

    Object3D current3DObj = Object3D(neutralString, 12, 10);
    
    Quaternion offsetRotation = Rotation(EulerAngles(Vector3D(7, 0, 0), EulerConstants::EulerOrderXYZR)).GetQuaternion();
    Vector3D offsetPosition = Vector3D(-110, 70, 0);
    
    Object2D* GetEmotion(Emotion e){
        switch (e){
        case ClosedHappy:
            return &closedHappyObj;
        case OpenHappy:
            return &openHappyObj;
        case Confuse:
            return &confuseObj;
        case Confusion:
            return &confusionObj;
        case Angry:
            return &angryObj;
        case Poggers:
            return &poggersObj;
        case Monch:
            return &monchObj;
        case Derpy:
            return &derpyObj;
        case Shocked:
            return &shockedObj;
        case HappyRed:
            return &happyRedObj;
        case Angel:
            return &angelObj;
        case SuperHappy:
            return &superHappyObj;
        case Smirk:
            return &smirkObj;
        case OhNo:
            return &ohNoObj;
        case LemmeIn:
            return &lemmeInObj;
        case How:
            return &howObj;
        case Seriously:
            return &seriouslyObj;
        case Done:
            return &doneObj;
        case Mlem:
            return &mlemObj;
        default:
            return &neutralObj;
        }
    }

    void Interpolate(Emotion e, float rate){
        rate = Mathematics::Constrain(rate, 0.0f, 1.0f);
        
        for (int i = 0; i < currentObj.GetVertexAmount(); i++){
        currentObj.GetVertices()[i] = Vector2D::LERP(currentObj.GetVertices()[i], GetEmotion(e)->GetVertices()[i], rate);
        }
        
        for (int i = 0; i < currentObj.GetVertexAmount(); i++){
        current3DObj.GetVertices()[i].X = -currentObj.GetVertices()[i].X;
        current3DObj.GetVertices()[i].Y =  currentObj.GetVertices()[i].Y;
        current3DObj.GetVertices()[i].Z =  0;

        current3DObj.GetVerticesOriginal()[i].X = -currentObj.GetVertices()[i].X;
        current3DObj.GetVerticesOriginal()[i].Y =  currentObj.GetVertices()[i].Y;
        current3DObj.GetVerticesOriginal()[i].Z =  0;
        }
    }

    void LinkMouth(){
        
    }

    public:
    Mouth(){}

    void Talk(float* pointMultiplier){// 12 inputs required
        current3DObj.GetVertices()[0].Y = current3DObj.GetVertices()[0].Y + pointMultiplier[11];// top left
        current3DObj.GetVertices()[11].Y = current3DObj.GetVertices()[11].Y + pointMultiplier[9];// right 1
        current3DObj.GetVertices()[10].Y = current3DObj.GetVertices()[10].Y + pointMultiplier[7];// right 1
        current3DObj.GetVertices()[9].Y = current3DObj.GetVertices()[9].Y + pointMultiplier[5];// right 1
        current3DObj.GetVertices()[8].Y = current3DObj.GetVertices()[8].Y + pointMultiplier[3];// right 1
        //current3DObj.GetVertices()[7].Y = current3DObj.GetVertices()[7].Y + pointMultiplier[1];// top right
        //current3DObj.GetVertices()[6].Y = current3DObj.GetVertices()[6].Y - pointMultiplier[0];// top right
        current3DObj.GetVertices()[5].Y = current3DObj.GetVertices()[5].Y - pointMultiplier[2];// top right
        current3DObj.GetVertices()[4].Y = current3DObj.GetVertices()[4].Y - pointMultiplier[4];// top right
        current3DObj.GetVertices()[3].Y = current3DObj.GetVertices()[3].Y - pointMultiplier[6];// top right
        current3DObj.GetVertices()[2].Y = current3DObj.GetVertices()[2].Y - pointMultiplier[8];// top right
        current3DObj.GetVertices()[1].Y = current3DObj.GetVertices()[1].Y - pointMultiplier[10];// top right
    }

    Object3D* GetObject(){
        return &current3DObj;
    }

    void Update(Emotion e, float rate){
        Interpolate(e, rate);

        current3DObj.Rotate(offsetRotation);
        current3DObj.MoveRelative(offsetPosition);
    }
};
