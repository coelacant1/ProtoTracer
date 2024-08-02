#pragma once

#include "../../Utils/Math/Plane.h"
#include "../../Scene/Objects/Object3D.h"

class ObjectAlign {
public:
    enum Justification {
        UpperLeft,
        UpperMiddle,
        UpperRight,
        MiddleLeft,
        Middle,
        MiddleRight,
        LowerLeft,
        LowerMiddle,
        LowerRight,
        Stretch
    };

private:
    Justification jst = Middle;
    Quaternion targetOrientation;
    Vector3D forwardVector = Vector3D(0.0f, 0.0f, 1.0f);
    Vector2D cameraCenter;
    Vector2D camMin;
    Vector2D camMax;
    float offsetPlaneAngle = 0.0f;
    float edgeMargin = 10.0f;
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    bool mirrorX = false;
    bool mirrorY = false;
    
    void NormalizeObjectPlane(Object3D** objs, uint8_t numObjects, Vector3D center, Quaternion planeOrientation);
    void NormalizeObjectCenter(Object3D** objs, uint8_t numObjects, Vector3D center);

public:
    ObjectAlign(Vector2D camMin, Vector2D camMax, Quaternion targetOrientation = Quaternion());

    Vector3D GetCentroid(Object3D* obj);
    Vector3D GetCentroid(Object3D** objs, uint8_t numObjects);
    Vector3D GetObjectCenter(Object3D* obj);
    Vector3D GetObjectCenter(Object3D** objs, uint8_t numObjects);
    Vector3D GetObjectSize(Object3D* obj);
    Vector3D GetObjectSize(Object3D** objs, uint8_t numObjects);

    Quaternion GetPlaneNormal(Object3D* obj);
    Quaternion GetPlaneNormal(Object3D** objs, uint8_t numObjects);
    Quaternion GetPlaneOrientation(Object3D* obj, Vector3D centroid);
    Quaternion GetPlaneOrientation(Object3D** objs, uint8_t numObjects, Vector3D centroid);

    Transform GetTransform(Object3D* obj);
    Transform GetTransform(Object3D** objs, uint8_t numObjects);
    
    float GetObjectPlanarityRatio(Object3D* obj);
    float GetObjectPlanarityRatio(Object3D** objs, uint8_t numObjects);

    void SetPlaneOffsetAngle(float offsetPlaneAngle);
    void SetEdgeMargin(float edgeMargin);
    void SetForwardVector(Vector3D forwardVector);
    void SetCameraMin(Vector2D camMin);
    void SetCameraMax(Vector2D camMax);
    void SetMirrorX(bool mirrorX);
    void SetMirrorY(bool mirrorY);
    void SetJustification(Justification jst);
    void SetScale(float scaleX, float scaleY);


    void AlignObjectNoScale(Object3D* obj);
    void AlignObjectsNoScale(Object3D** objs, uint8_t numObjects);
    void AlignObject(Object3D* obj);
    void AlignObjects(Object3D** objs, uint8_t numObjects);
};
