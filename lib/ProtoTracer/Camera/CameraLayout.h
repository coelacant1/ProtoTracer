#pragma once

#include "../Utils/Math/Transform.h"

class CameraLayout {
public:
    enum ForwardAxis {
        XForward, 
        YForward, 
        ZForward, 
        XNForward, 
        YNForward, 
        ZNForward
    };

    enum UpAxis {
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

    bool VerifyTransform();
    void CalculateTransform();

public:
    CameraLayout(ForwardAxis forwardAxis, UpAxis upAxis);

    ForwardAxis GetForwardAxis();
    UpAxis GetUpAxis();
    Vector3D GetForwardVector();
    Vector3D GetUpVector();
    Quaternion GetRotation();
};
