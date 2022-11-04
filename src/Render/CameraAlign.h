#pragma once

#include "CameraLayout.h"
#include "..\Math\Plane.h"
#include "Object3D.h"

class CameraAlign{
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
    CameraLayout* cameraLayout;
    Transform* cameraTransform;
    float offsetPlaneAngle = 0.0f;

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

        float maxDeterm = xD > yD ? (xD > zD ? xD : zD) : (yD > zD ? yD : zD);

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
    }

public:
    CameraAlign(CameraLayout* cameraLayout, Transform* cameraTransform, Vector2D cameraMinCoord, Vector2D cameraMaxCoord){
        this->cameraLayout = cameraLayout;
        this->cameraTransform = cameraTransform;
    }

    void SetPlaneOffsetAngle(float offsetPlaneAngle){
        this->offsetPlaneAngle = offsetPlaneAngle;
    }

    void AlignObjects(Object3D** objs, uint8_t numObjects, Justification jst, bool flipPlane = false){
        // calculate planes, assume flat object (largest axes are axis), best fit plane i.e. centroid + direction/normal
        Vector3D centroid = GetCentroid(objs, numObjects);
        Quaternion cameraOrientation = cameraTransform->GetRotation();
        Quaternion planeOrientation = GetPlaneOrientation(centroid, objs, numObjects);

        // get relative orientation between plane and camera
        Quaternion relativeOrientation = cameraOrientation / planeOrientation;

        // calculate point 1000mm in front of camera
        Vector3D cameraTarget = cameraOrientation.RotateVector(Vector3D(cameraLayout->GetForwardVector() * 1000.0f));

        for(uint8_t i = 0; i < numObjects; i++){
            // move object to 1000mm point in front of camera
            objs[i]->GetTransform()->Translate((cameraTarget - centroid) * -1.0f);

            // align object plane to camera plane
            objs[i]->GetTransform()->SetRotationOffset(centroid);
            objs[i]->GetTransform()->SetRotation(relativeOrientation.Conjugate());

        }




        // scale object to camera size


        // move to projection of edge
        
    }
    

};
