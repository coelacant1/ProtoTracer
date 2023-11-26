#include "CameraLayout.h"

CameraLayout::CameraLayout(ForwardAxis forwardAxis, UpAxis upAxis) {
    this->forwardAxis = forwardAxis;
    this->upAxis = upAxis;

    CalculateTransform();
}

bool CameraLayout::VerifyTransform() {
    if (forwardAxis == XForward || forwardAxis == XNForward) {
        return !(upAxis == XUp || upAxis == XNUp);
    } else if (forwardAxis == YForward || forwardAxis == YNForward) {
        return !(upAxis == YUp || upAxis == YNUp);
    } else {
        return !(upAxis == ZUp || upAxis == ZNUp);
    }
}

void CameraLayout::CalculateTransform() {
    Vector3D upVector, forwardVector, rightVector;

    if (VerifyTransform()) {
        upVector = GetUpVector();
        forwardVector = GetForwardVector();
        rightVector = upVector.CrossProduct(forwardVector);

        rotation = Rotation(rightVector, forwardVector, upVector).GetQuaternion().UnitQuaternion();
    }
    // else bad transform
}

CameraLayout::ForwardAxis CameraLayout::GetForwardAxis() {
    return forwardAxis;
}

CameraLayout::UpAxis CameraLayout::GetUpAxis() {
    return upAxis;
}

Vector3D CameraLayout::GetForwardVector() {
    Vector3D forwardVector;

    switch (forwardAxis) {
        case XForward: forwardVector.X = 1; break;
        case YForward: forwardVector.Y = 1; break;
        case XNForward: forwardVector.X = -1; break;
        case YNForward: forwardVector.Y = -1; break;
        case ZNForward: forwardVector.Z = -1; break;
        default: forwardVector.Z = 1; break;
    }

    return forwardVector;
}

Vector3D CameraLayout::GetUpVector() {
    Vector3D upVector;

    switch (upAxis) {
        case XUp: upVector.X = 1; break;
        case ZUp: upVector.Z = 1; break;
        case XNUp: upVector.X = -1; break;
        case YNUp: upVector.Y = -1; break;
        case ZNUp: upVector.Z = -1; break;
        default: upVector.Y = 1; break;
    }

    return upVector;
}

Quaternion CameraLayout::GetRotation() {
    return rotation;
}
