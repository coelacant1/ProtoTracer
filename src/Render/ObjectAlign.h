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

    Quaternion GetPlaneNormal(Vector3D centroid, Object3D** objs, uint8_t numObjects){
        Vector3D normal;
        uint16_t count = 0;

        for(uint8_t i = 0; i < numObjects; i++){
            for(uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetTriangleCount(); j++){
                normal = normal + *objs[i]->GetTriangleGroup()->GetTriangles()[j].Normal();

                count++;
            }
        }

        normal = normal / count;
        normal = normal.UnitSphere();

        Quaternion rotation = Rotation(Vector3D(0.0f, 0.0f, 1.0f), normal).GetQuaternion();

        //rotation = rotation * Rotation(EulerAngles(Vector3D(90.0f, 0.0f, 0.0f), EulerConstants::EulerOrderXYZS)).GetQuaternion();
        rotation = rotation * Rotation(EulerAngles(Vector3D(0.0f, 0.0f, offsetPlaneAngle), EulerConstants::EulerOrderXYZS)).GetQuaternion();

        return rotation;
    }

    Quaternion GetPlaneOrientation(Vector3D centroid, Object3D** objs, uint8_t numObjects){
        //Calculate covariance matrix without symmetry
        float xx = 0.0f, xy = 0.0f, xz = 0.0f, yy = 0.0f, yz = 0.0f, zz = 0.0f;
        uint16_t count = 0;

        for(uint8_t i = 0; i < numObjects; i++){
            for(uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++){
                Vector3D off = objs[i]->GetTriangleGroup()->GetVertices()[j] - centroid;

                xx += off.X * off.X;
                xy += off.X * off.Y;
                xz += off.X * off.Z;
                yy += off.Y * off.Y;
                yz += off.Y * off.Z;
                zz += off.Z * off.Z;
                
                count++;
            }
        }

        xx /= count;
        xy /= count;
        xz /= count;
        yy /= count;
        yz /= count;
        zz /= count;

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

        //dir = dir.Normal();

        dir = dir.UnitSphere();

        return Rotation(Vector3D(0.0f, 0.0f, 1.0f), dir).GetQuaternion() * Rotation(EulerAngles(Vector3D(0.0f, 0.0f, offsetPlaneAngle), EulerConstants::EulerOrderXYZS)).GetQuaternion();
    }

public:
    ObjectAlign(Vector2D posMin, Vector2D posMax, Quaternion targetOrientation = Quaternion()){
        this->posMin = posMin;
        this->posMax = posMax;
        this->center = (posMin + posMax) / 2.0f;
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

    void SetMin(Vector2D posMin){
        this->posMin = posMin;
        this->center = (posMin + posMax) / 2.0f;
    }

    void SetMax(Vector2D posMax){
        this->posMax = posMax;
        this->center = (posMin + posMax) / 2.0f;
    }

    void AlignObjects(Object3D** objs, uint8_t numObjects, Justification jst = MiddleRight, bool mirror = false){
        // calculate planes, assume flat object (largest axes are axis), best fit plane i.e. centroid + direction/normal
        Vector3D centroid = GetCentroid(objs, numObjects);
        Quaternion cameraOrientation = targetOrientation;
        Quaternion planeOrientation = GetPlaneNormal(centroid, objs, numObjects);
        
        Vector3D min = Vector3D(100000.0f, 100000.0f, 100000.0f), max = Vector3D(-100000.0f, -100000.0f, -100000.0f), objectSize = Vector3D();
        Vector2D cameraSize = (posMax - posMin);

        for(uint8_t i = 0; i < numObjects; i++){
            // get size of object in origin orientation 
            for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
                Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];

                modifiedVector = modifiedVector - centroid;// move to origin
                modifiedVector = planeOrientation.UnrotateVector(modifiedVector);// unrotate to align with base camera orientation

                min = Vector3D::Min(min, modifiedVector);
                max = Vector3D::Max(max, modifiedVector);
                
                objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
            }
        }

        objectSize = max - min;//find offset in two min/max coordinates for size and add edge margin to normalize base on edge

        //scale to largest object size and smallest camera size
        //float maxObjectSize = Mathematics::Max(objectSize.X, objectSize.Y, objectSize.Z);
        //float minCameraSize = Mathematics::Min(cameraSize.X, cameraSize.Y);
        //float scaleRatio = (cameraSize.X  - edgeMargin) / objectSize.X;

        float xRatio = (cameraSize.X - edgeMargin) / objectSize.X;
        float yRatio = (cameraSize.Y - edgeMargin) / objectSize.Y;

        float scaleRatio = Mathematics::Min(xRatio, yRatio);

        //justification offset
        Vector2D offsetPosition;
        
        // calculate point 1000mm in front of camera
        Vector3D cameraTarget = cameraOrientation.RotateVector(Vector3D(forwardVector * 1000.0f) + Vector3D(center.X, center.Y, 0.0f) + Vector3D(offsetPosition.X, offsetPosition.Y, 0.0f));

        for(uint8_t i = 0; i < numObjects; i++){
            for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
                Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];
                
                // scaled object normalized in world origin
                modifiedVector = mirror ? modifiedVector * Vector3D(xRatio, yRatio, 1.0f) : modifiedVector * Vector3D(-xRatio, yRatio, 1.0f);

                // align object plane to camera plane
                modifiedVector = cameraOrientation.RotateVector(modifiedVector);

                // move object to 1000mm point in front of camera
                modifiedVector = modifiedVector + cameraTarget;//offset position
                
                objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
            }
        }
    }

};
