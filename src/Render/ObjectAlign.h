#pragma once

#include "..\Math\Plane.h"
#include "Object3D.h"

class ObjectAlign{
public:
    enum Justification{
        UpperLeft,
        UpperMiddle,
        UpperRight,
        MiddleLeft,
        Center,
        MiddleRight,
        LowerLeft,
        LowerMiddle,
        LowerRight
    };

private:
    Quaternion targetOrientation;
    Vector3D forwardVector = Vector3D(0.0f, 0.0f, 1.0f);
    Vector2D center;
    Vector2D posMin;
    Vector2D posMax;
    float offsetPlaneAngle = 0.0f;
    float edgeMargin = 10.0f;

    Vector3D GetCentroid(Object3D** objs, uint8_t numObjects){
        //Calculate plane centroid
        Vector3D centroid;
        uint16_t vertexCount = 0;

        for(uint8_t i = 0; i < numObjects; i++){
            for(uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++){
                vertexCount++;
                centroid = centroid + objs[i]->GetTriangleGroup()->GetVertices()[j];
            }
        }

        centroid = centroid / float(vertexCount);

        return centroid;
    }

    Quaternion GetPlaneOrientation(Vector3D centroid, Object3D** objs, uint8_t numObjects){
        //Calculate covariance matrix without symmetry
        float xx = 0.0f, xy = 0.0f, xz = 0.0f, yy = 0.0f, yz = 0.0f, zz = 0.0f;

        for(uint8_t i = 0; i < numObjects; i++){
            for(uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++){
                Vector3D off = objs[i]->GetTriangleGroup()->GetVertices()[j] - centroid;
                xx += off.X * off.X;
                xy += off.X * off.Y;
                xz += off.X * off.Z;
                yy += off.Y * off.Y;
                yz += off.Y * off.Z;
                zz += off.Z * off.Z;
            }
        }

        //Calculate determinants
        float xD = yy * zz - yz * yz;
        float yD = xx * zz - xz * xz;
        float zD = xx * yy - xy * xy;

        float maxDeterm = Mathematics::Max(xD, yD, zD);

        if (maxDeterm <= 0.0f) return Quaternion();//not a plane, do not rotate

        Vector3D dir;

        if (Mathematics::IsClose(maxDeterm, xD, 0.001f)){//X path best fit
            dir.X = xD;
            dir.Y = xz * yz - xy * zz;
            dir.Z = xy * yz - xz * yy;
        }
        else if (Mathematics::IsClose(maxDeterm, yD, 0.001f)){//Y path best fit
            dir.X = xz * yz - xy * zz;
            dir.Y = yD;
            dir.Z = xy * xz - yz * xx;
        }
        else{//Z path best fit
            dir.X = xy * yz - xz * yy;
            dir.Y = xy * xz - yz * xx;
            dir.Z = xD;
        }

        dir = dir.Normal();

        Rotation rotation = Rotation(DirectionAngle(offsetPlaneAngle, dir));

        return rotation.GetQuaternion() * Rotation(EulerAngles(Vector3D(90.0f, 0.0f, 0.0f), EulerConstants::EulerOrderXYZS)).GetQuaternion();
    }

public:
    ObjectAlign(Vector2D min, Vector2D max, Quaternion targetOrientation = Quaternion()){
        this->posMin = min;
        this->posMax = max;
        this->center = (min + max) / 2.0f;
        this->targetOrientation = targetOrientation;
    }

    void SetPlaneOffsetAngle(float offsetPlaneAngle){
        this->offsetPlaneAngle = offsetPlaneAngle;
    }

    void SetEdgeMargin(float edgeMargin){
        this->edgeMargin = edgeMargin;
    }

    void SetForwardVector(Vector3D forwardVector){
        this->forwardVector = forwardVector;
    }

    void SetMin(Vector3D min){
        this->posMin = min;
    }

    void SetMax(Vector3D max){
        this->posMax = max;
    }

    void AlignObjects(Object3D** objs, uint8_t numObjects, Justification jst = MiddleRight, bool mirror = false){
        // calculate planes, assume flat object (largest axes are axis), best fit plane i.e. centroid + direction/normal
        Vector3D centroid = GetCentroid(objs, numObjects);
        Quaternion cameraOrientation = targetOrientation;
        Quaternion baseCameraOrientation = Rotation(DirectionAngle(0.0f, forwardVector)).GetQuaternion();
        Quaternion planeOrientation = GetPlaneOrientation(centroid, objs, numObjects);

        // get relative orientation between plane and camera
        Quaternion relativeOriginOrientation = baseCameraOrientation / planeOrientation;//Rotation to unrotated camera
        
        Vector3D min, max, objectSize;
        Vector2D cameraSize = (posMax - posMin);

        for(uint8_t i = 0; i < numObjects; i++){
            // get size of object in origin orientation 
            for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
                Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];

                modifiedVector = planeOrientation.UnrotateVector(modifiedVector - centroid);// move to center, unrotate to align with base camera orientation

                min = Vector3D::Min(min, modifiedVector);
                max = Vector3D::Max(max, modifiedVector);
                
                objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
            }
        }

        objectSize = (max - min);//find offset in two min/max coordinates for size and add edge margin to normalize base on edge

        //scale to largest object size and smallest camera size
        float maxObjectSize = Mathematics::Max(objectSize.X, objectSize.Y, objectSize.Z);
        float minCameraSize = Mathematics::Min(cameraSize.X, cameraSize.Y);
        float scaleRatio = (cameraSize.X  - edgeMargin) / objectSize.X;

        //justification offset
        Vector2D offsetPosition;

        // calculate point 1000mm in front of camera
        Vector3D cameraTarget = cameraOrientation.RotateVector(Vector3D(forwardVector * 1000.0f) + Vector3D(center.X, center.Y, 0.0f) + Vector3D(offsetPosition.X, offsetPosition.Y, 0.0f));

        for(uint8_t i = 0; i < numObjects; i++){
            for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
                Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];
                
                // scaled object normalized in world origin
                modifiedVector = mirror ? modifiedVector * Vector3D(-scaleRatio, scaleRatio, scaleRatio) : modifiedVector * scaleRatio;

                // align object plane to camera plane
                modifiedVector = cameraOrientation.RotateVector(modifiedVector);

                // move object to 1000mm point in front of camera
                modifiedVector = modifiedVector + cameraTarget;//offset position
                
                objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
            }
        }
    }

};
