#pragma once

#include "Arduino.h"
#include "..\Math\Transform.h"

class CameraLayout{
public:
    enum ForwardAxis{
        XForward,
        YForward,
        ZForward,
        XNForward,
        YNForward,
        ZNForward
    };

    enum UpAxis{
        XUp,
        YUp,
        ZUp,
        XNUp,
        YNUp,
        ZNUp
    };

private:
    Quaternion rotation;
    ForwardAxis forwardAxis;
    UpAxis upAxis;

    bool VerifyTransform(){//verifies that up and forward axes are not aligned
        if(forwardAxis == XForward || forwardAxis == XNForward){
            return !(upAxis == XUp || upAxis == XNUp);
        }
        else if(forwardAxis == YForward || forwardAxis == YNForward){
            return !(upAxis == YUp || upAxis == YNUp);
        }
        else {
            return !(upAxis == ZUp || upAxis == ZNUp);
        }
    }

    void CalculateTransform(){//transform from input to YUp, ZForward
        Vector3D upVector = Vector3D();
        Vector3D forwardVector = Vector3D();
        Vector3D rightVector = Vector3D();

        if (VerifyTransform()){
            switch (upAxis){
                case XUp:
                    upVector.X = 1;
                    break;
                case ZUp:
                    upVector.Z = 1;
                    break;
                case XNUp:
                    upVector.X = -1;
                    break;
                case YNUp:
                    upVector.Y = -1;
                    break;
                case ZNUp:
                    upVector.Z = -1;
                    break;
                default:
                    upVector.Y = 1;
                    break;
            }

            switch (forwardAxis){
                case XForward:
                    forwardVector.X = 1;
                    break;
                case YForward:
                    forwardVector.Y = 1;
                    break;
                case XNForward:
                    forwardVector.X = -1;
                    break;
                case YNForward:
                    forwardVector.Y = -1;
                    break;
                case ZNForward:
                    forwardVector.Z = -1;
                    break;
                default:
                    forwardVector.Z = 1;
                    break;
            }

            rightVector = upVector.CrossProduct(forwardVector);

            rotation = Rotation(rightVector, forwardVector, upVector).GetQuaternion().UnitQuaternion();
        }
        else{
            Serial.println("Bad transform");
        }
    }

public:
    CameraLayout(ForwardAxis forwardAxis, UpAxis upAxis){
        this->forwardAxis = forwardAxis;
        this->upAxis = upAxis;

        CalculateTransform();
    }

    //create transform from up and forwardaxis
    Quaternion GetRotation(){
        return rotation;
    }

};