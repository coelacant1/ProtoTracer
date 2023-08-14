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

    Vector3D GetObjectCenter(Object3D** objs, uint8_t numObjects){
        Vector3D min = Vector3D(100000.0f, 100000.0f, 100000.0f), max = Vector3D(-100000.0f, -100000.0f, -100000.0f);

        for(uint8_t i = 0; i < numObjects; i++){
            // get size of object in origin orientation 
            for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
                Vector3D vertex = objs[i]->GetTriangleGroup()->GetVertices()[j];

                min = Vector3D::Min(min, vertex);
                max = Vector3D::Max(max, vertex);
            }
        }

        return (max + min) / 2.0f;
    }

    Vector3D GetObjectSize(Object3D** objs, uint8_t numObjects){
        Vector3D min = Vector3D(100000.0f, 100000.0f, 100000.0f), max = Vector3D(-100000.0f, -100000.0f, -100000.0f);

        for(uint8_t i = 0; i < numObjects; i++){
            // get size of object in origin orientation 
            for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
                Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];

                min = Vector3D::Min(min, modifiedVector);
                max = Vector3D::Max(max, modifiedVector);
                
                objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
            }
        }

        return max - min;
    }

    void NormalizeObjectPlane(Object3D** objs, uint8_t numObjects, Vector3D center, Quaternion planeOrientation){
        for(uint8_t i = 0; i < numObjects; i++){
            // get size of object in origin orientation 
            for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
                Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];

                modifiedVector = modifiedVector - center;// move to origin
                modifiedVector = planeOrientation.UnrotateVector(modifiedVector);// unrotate to align with base camera orientation
                
                objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
            }
        }
    }

    void NormalizeObjectCenter(Object3D** objs, uint8_t numObjects, Vector3D center){
        for(uint8_t i = 0; i < numObjects; i++){
            // get size of object in origin orientation 
            for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
                Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];

                modifiedVector = modifiedVector - center;// move to origin
                
                objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
            }
        }
    }

    Quaternion GetPlaneNormal(Object3D** objs, uint8_t numObjects){
        Vector3D normal;
        uint16_t count = 0;

        for(uint8_t i = 0; i < numObjects; i++){
            for(uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetTriangleCount(); j++){
                normal = normal + *(objs[i]->GetTriangleGroup()->GetTriangles()[j].Normal());

                count++;
            }
        }

        normal = normal / count;
        normal = normal.UnitSphere().Absolute();

        Quaternion rotation = Rotation(Vector3D(0.0f, 0.0f, 1.0f), normal).GetQuaternion();

        //rotation = rotation * Rotation(EulerAngles(Vector3D(90.0f, 0.0f, 0.0f), EulerConstants::EulerOrderXYZS)).GetQuaternion();
        rotation = rotation * Rotation(EulerAngles(Vector3D(0.0f, 0.0f, offsetPlaneAngle), EulerConstants::EulerOrderXYZS)).GetQuaternion();

        return rotation;
    }

    Quaternion GetPlaneOrientation(Object3D** objs, uint8_t numObjects, Vector3D centroid){
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

        dir = dir.UnitSphere();

        return Rotation(Vector3D(0.0f, 0.0f, 1.0f), dir).GetQuaternion() * Rotation(EulerAngles(Vector3D(0.0f, 0.0f, offsetPlaneAngle), EulerConstants::EulerOrderXYZS)).GetQuaternion();
    }

public:
    ObjectAlign(Vector2D camMin, Vector2D camMax, Quaternion targetOrientation = Quaternion()){
        this->camMin = camMin;
        this->camMax = camMax;
        this->cameraCenter = (camMin + camMax) / 2.0f;
        this->targetOrientation = targetOrientation;
    }

    void SetPlaneOffsetAngle(float offsetPlaneAngle){
        this->offsetPlaneAngle = offsetPlaneAngle;
    }

    void SetEdgeMargin(float edgeMargin){
        this->edgeMargin = edgeMargin * 2.0f;// for both sides
    }

    void SetForwardVector(Vector3D forwardVector){
        this->forwardVector = forwardVector;
    }

    void SetCameraMin(Vector2D camMin){
        this->camMin = camMin;
        this->cameraCenter = (camMin + camMax) / 2.0f;
    }

    void SetCameraMax(Vector2D camMax){
        this->camMax = camMax;
        this->cameraCenter = (camMin + camMax) / 2.0f;
    }

    void SetMirrorX(bool mirrorX){
        this->mirrorX = mirrorX;
    }

    void SetMirrorY(bool mirrorY){
        this->mirrorY = mirrorY;
    }

    void SetJustification(Justification jst){
        this->jst = jst;
    }

    void SetScale(float scaleX, float scaleY){
        this->scaleX = scaleX;
        this->scaleY = scaleY;
    }

    void AlignObjectNoScale(Object3D* obj){
        Object3D** objs = new Object3D*[1];

		objs[0] = obj;

        AlignObjectsNoScale(objs, 1);

		delete[] objs;
    }
    
    void AlignObjectsNoScale(Object3D** objs, uint8_t numObjects){
        // calculate planes, assume flat object (largest axes are axis), best fit plane i.e. centroid + direction/normal
        Vector3D centroid = GetCentroid(objs, numObjects);
        Quaternion planeOrientation = GetPlaneNormal(objs, numObjects);
        //Quaternion planeOrientation = GetPlaneOrientation(objs, numObjects, centroid);
        Vector3D objectCenter = GetObjectCenter(objs, numObjects);//Get cameraCenter of objects
        
        //Normalize objects to plane orientation and cameraCenter of object
        NormalizeObjectPlane(objs, numObjects, centroid, planeOrientation);

        objectCenter = GetObjectCenter(objs, numObjects);//Get cameraCenter of objects

        NormalizeObjectCenter(objs, numObjects, objectCenter);//Shift object back to center of view
        
        // calculate point 1000mm in front of camera
        Vector3D cameraTarget = targetOrientation.RotateVector(Vector3D(forwardVector * 1000.0f) + Vector3D(cameraCenter.X, cameraCenter.Y, 0.0f));

        for(uint8_t i = 0; i < numObjects; i++){
            for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
                Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];

                // mirror object normalized in default camera space
                modifiedVector = modifiedVector * Vector3D(mirrorX ? -1.0f : 1.0f, mirrorY ? -1.0f : 1.0f, 1.0f);

                // align object plane to camera plane
                modifiedVector = targetOrientation.RotateVector(modifiedVector);

                // move object to 1000mm point in front of camera
                modifiedVector = modifiedVector + cameraTarget;//offset position
                
                objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
            }
        }
    }

    void AlignObject(Object3D* obj){
        Object3D** objs = new Object3D*[1];

		objs[0] = obj;

        AlignObjects(objs, 1);

		delete[] objs;
    }

    void AlignObjects(Object3D** objs, uint8_t numObjects){
        // calculate planes, assume flat object (largest axes are axis), best fit plane i.e. centroid + direction/normal
        Vector3D centroid = GetCentroid(objs, numObjects);
        //Quaternion planeOrientation = GetPlaneNormal(objs, numObjects);
        Quaternion planeOrientation = GetPlaneOrientation(objs, numObjects, centroid);
        Vector2D cameraSize = (camMax - camMin);
        Vector3D objectCenter = GetObjectCenter(objs, numObjects);//Get cameraCenter of objects
        
        //Normalize objects to plane orientation and cameraCenter of object
        NormalizeObjectPlane(objs, numObjects, centroid, planeOrientation);

        objectCenter = GetObjectCenter(objs, numObjects);//Get cameraCenter of objects

        NormalizeObjectCenter(objs, numObjects, objectCenter);//Shift object back to center of view

        //Get new size of objects after normalization
        Vector3D objectSize = GetObjectSize(objs, numObjects);

        float xRatio = (cameraSize.X - edgeMargin) / objectSize.X;
        float yRatio = (cameraSize.Y - edgeMargin) / objectSize.Y;

        if(jst != Stretch){
            //Uniform object scaling with modifier
            xRatio = Mathematics::Min(xRatio, yRatio) * scaleX;
            yRatio = Mathematics::Min(xRatio, yRatio) * scaleY;
        }

        float xOffset = ((cameraSize.X - edgeMargin) - (xRatio * objectSize.X)) / 2.0f;//get left over space between camera edge and object in X-axis view
        float yOffset = ((cameraSize.Y - edgeMargin) - (yRatio * objectSize.Y)) / 2.0f;//get left over space between camera edge and object in Y-axis view

        //xOffset = xOffset < 0.0f ? 0.0f : xOffset;//stay within bounds, do not move outside if object is larger than camera
        //yOffset = yOffset < 0.0f ? 0.0f : yOffset;

        switch (jst){
            case UpperLeft:
                //No Change
                break;
            case UpperMiddle:
                xOffset = 0.0f;
                break;
            case UpperRight:
                xOffset = -xOffset;
                break;
            case MiddleLeft:
                yOffset = 0.0f;
                break;
            case MiddleRight:
                xOffset = -xOffset;
                yOffset = 0.0f;
                break;
            case LowerLeft:
                yOffset = -yOffset;
                break;
            case LowerMiddle:
                xOffset = 0.0f;
                yOffset = -yOffset;
                break;
            case LowerRight:
                xOffset = -xOffset;
                yOffset = -yOffset;
                break;
            default://Middle
                xOffset = 0.0f;
                yOffset = 0.0f;
                break;
        }
        
        // calculate point 1000mm in front of camera
        Vector3D cameraTarget = targetOrientation.RotateVector(Vector3D(forwardVector * 1000.0f) + Vector3D(cameraCenter.X, cameraCenter.Y, 0.0f));

        for(uint8_t i = 0; i < numObjects; i++){
            for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
                Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];

                // scaled object normalized in default camera space
                modifiedVector = modifiedVector * Vector3D(xRatio, yRatio, 1.0f) * Vector3D(mirrorX ? -1.0f : 1.0f, mirrorY ? -1.0f : 1.0f, 1.0f);
                
                // move object in default camera space before rotation
                modifiedVector = modifiedVector + Vector3D(xOffset, yOffset, 0.0f);

                // align object plane to camera plane
                modifiedVector = targetOrientation.RotateVector(modifiedVector);

                // move object to 1000mm point in front of camera
                modifiedVector = modifiedVector + cameraTarget;//offset position
                
                objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
            }
        }
    }

};
