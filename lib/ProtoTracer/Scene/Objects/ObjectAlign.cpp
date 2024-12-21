#include "ObjectAlign.h"

Vector3D ObjectAlign::GetCentroid(Object3D* obj) {
    Object3D** objs = new Object3D*[1];
    objs[0] = obj;

    Vector3D output = GetCentroid(objs, 1);

    delete[] objs;

    return output;
}

Vector3D ObjectAlign::GetCentroid(Object3D** objs, uint8_t numObjects) {
    Vector3D centroid;
    uint16_t vertexCount = 0;

    for (uint8_t i = 0; i < numObjects; i++) {
        for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
            vertexCount++;
            centroid = centroid + objs[i]->GetTriangleGroup()->GetVertices()[j];
        }
    }

    centroid = centroid / float(vertexCount);

    return centroid;
}

Vector3D ObjectAlign::GetObjectCenter(Object3D* obj) {
    Object3D** objs = new Object3D*[1];
    objs[0] = obj;

    Vector3D output = GetObjectCenter(objs, 1);

    delete[] objs;

    return output;
}

Vector3D ObjectAlign::GetObjectCenter(Object3D** objs, uint8_t numObjects) {
    Vector3D min = Vector3D(100000.0f, 100000.0f, 100000.0f), max = Vector3D(-100000.0f, -100000.0f, -100000.0f);

    for (uint8_t i = 0; i < numObjects; i++) {
        for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
            Vector3D vertex = objs[i]->GetTriangleGroup()->GetVertices()[j];

            min = Vector3D::Min(min, vertex);
            max = Vector3D::Max(max, vertex);
        }
    }

    return (max + min) / 2.0f;
}

Vector3D ObjectAlign::GetObjectSize(Object3D* obj) {
    Object3D** objs = new Object3D*[1];
    objs[0] = obj;

    Vector3D output = GetObjectSize(objs, 1);

    delete[] objs;

    return output;
}

Vector3D ObjectAlign::GetObjectSize(Object3D** objs, uint8_t numObjects) {
    Vector3D min = Vector3D(100000.0f, 100000.0f, 100000.0f), max = Vector3D(-100000.0f, -100000.0f, -100000.0f);

    for (uint8_t i = 0; i < numObjects; i++) {
        for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
            Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];

            min = Vector3D::Min(min, modifiedVector);
            max = Vector3D::Max(max, modifiedVector);

            objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
        }
    }

    return max - min;
}

void ObjectAlign::NormalizeObjectPlane(Object3D** objs, uint8_t numObjects, Vector3D center, Quaternion planeOrientation) {
    for (uint8_t i = 0; i < numObjects; i++) {
        for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
            Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];

            modifiedVector = modifiedVector - center;
            modifiedVector = planeOrientation.UnrotateVector(modifiedVector);

            objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
        }
    }
}

void ObjectAlign::NormalizeObjectCenter(Object3D** objs, uint8_t numObjects, Vector3D center) {
    for (uint8_t i = 0; i < numObjects; i++) {
        for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
            Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];

            modifiedVector = modifiedVector - center;

            objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
        }
    }
}

float ObjectAlign::GetObjectPlanarityRatio(Object3D* obj) {
    Object3D** objs = new Object3D*[1];
    objs[0] = obj;

    float planarity = GetObjectPlanarityRatio(objs, 1);

    delete[] objs;

    return planarity;
}

// Main function to check planarity of objects
float ObjectAlign::GetObjectPlanarityRatio(Object3D** objs, uint8_t numObjects) {
    // Calculate centroid and plane orientation
    Vector3D centroid = GetCentroid(objs, numObjects);
    Quaternion planeOrientation = GetPlaneOrientation(objs, numObjects, centroid);

    uint16_t totalVertices = 0;
    Vector3D diffSum = Vector3D();

    for (uint8_t i = 0; i < numObjects; i++) {
        totalVertices += objs[i]->GetTriangleGroup()->GetVertexCount();// Determine total number of vertices

        for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
            Vector3D vertex = objs[i]->GetTriangleGroup()->GetVertices()[j];
            Vector3D diff = vertex - centroid;
            Vector3D diffRot = planeOrientation.RotateVector(diff);

            diffSum = diffSum + diffRot.Absolute();
        }
    }

    diffSum = diffSum / totalVertices;

    // Inverse of difference in scale of object in reference to best fit plane orientation. 0.0f for a sphere -> 1.0f for a plane
    return 1.0f - 1.0f / (diffSum / Mathematics::Min(diffSum.X, diffSum.Y, diffSum.Z)).AverageHighestTwoComponents();
}

Quaternion ObjectAlign::GetPlaneNormal(Object3D* obj) {
    Object3D** objs = new Object3D*[1];
    objs[0] = obj;

    Quaternion output = GetPlaneNormal(objs, 1);

    delete[] objs;

    return output;
}

Quaternion ObjectAlign::GetPlaneNormal(Object3D** objs, uint8_t numObjects) {
    Vector3D normal;
    uint16_t count = 0;

    for (uint8_t i = 0; i < numObjects; i++) {
        for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetTriangleCount(); j++) {
            normal = normal + *(objs[i]->GetTriangleGroup()->GetTriangles()[j].Normal());

            count++;
        }
    }

    normal = normal / count;
    normal = normal.UnitSphere().Absolute();

    Quaternion rotation = Rotation(Vector3D(0.0f, 0.0f, 1.0f), normal).GetQuaternion();

    rotation = rotation * Rotation(EulerAngles(Vector3D(0.0f, 0.0f, offsetPlaneAngle), EulerConstants::EulerOrderXYZS)).GetQuaternion();

    return rotation;
}

Quaternion ObjectAlign::GetPlaneOrientation(Object3D* obj, Vector3D centroid) {
    Object3D** objs = new Object3D*[1];
    objs[0] = obj;

    Quaternion output = GetPlaneOrientation(objs, 1, centroid);

    delete[] objs;

    return output;
}

Quaternion ObjectAlign::GetPlaneOrientation(Object3D** objs, uint8_t numObjects, Vector3D centroid) {
    float xx = 0.0f, xy = 0.0f, xz = 0.0f, yy = 0.0f, yz = 0.0f, zz = 0.0f;
    uint16_t count = 0;

    for (uint8_t i = 0; i < numObjects; i++) {
        for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
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

    float xD = yy * zz - yz * yz;
    float yD = xx * zz - xz * xz;
    float zD = xx * yy - xy * xy;

    float maxDeterm = Mathematics::Max(xD, yD, zD);

    if (maxDeterm <= 0.0f) return Quaternion();

    Vector3D dir;

    if (Mathematics::IsClose(maxDeterm, xD, 0.001f)) {
        dir.X = xD;
        dir.Y = xz * yz - xy * zz;
        dir.Z = xy * yz - xz * yy;
    } else if (Mathematics::IsClose(maxDeterm, yD, 0.001f)) {
        dir.X = xz * yz - xy * zz;
        dir.Y = yD;
        dir.Z = xy * xz - yz * xx;
    } else {
        dir.X = xy * yz - xz * yy;
        dir.Y = xy * xz - yz * xx;
        dir.Z = xD;
    }

    dir = dir.UnitSphere();

    Serial.print(dir.ToString()); Serial.print('\t');
    Serial.print(xD); Serial.print('\t');
    Serial.print(yD); Serial.print('\t');
    Serial.print(zD); Serial.print('\t');
    Serial.print(Rotation(Vector3D(0.0f, 0.0f, 1.0f), dir).GetEulerAngles(EulerConstants::EulerOrderXYZS).Angles.ToString()); Serial.print('\n'); Serial.print('\n');

    return Rotation(Vector3D(0.0f, 0.0f, 1.0f), dir).GetQuaternion() * Rotation(EulerAngles(Vector3D(0.0f, 0.0f, offsetPlaneAngle), EulerConstants::EulerOrderXYZS)).GetQuaternion();
}

ObjectAlign::ObjectAlign(Vector2D camMin, Vector2D camMax, Quaternion targetOrientation) {
    this->camMin = camMin;
    this->camMax = camMax;
    this->cameraCenter = (camMin + camMax) / 2.0f;
    this->targetOrientation = targetOrientation;
}

void ObjectAlign::SetPlaneOffsetAngle(float offsetPlaneAngle) {
    this->offsetPlaneAngle = offsetPlaneAngle;
}

void ObjectAlign::SetEdgeMargin(float edgeMargin) {
    this->edgeMargin = edgeMargin * 2.0f;
}

void ObjectAlign::SetForwardVector(Vector3D forwardVector) {
    this->forwardVector = forwardVector;
}

void ObjectAlign::SetCameraMin(Vector2D camMin) {
    this->camMin = camMin;
    this->cameraCenter = (camMin + camMax) / 2.0f;
}

void ObjectAlign::SetCameraMax(Vector2D camMax) {
    this->camMax = camMax;
    this->cameraCenter = (camMin + camMax) / 2.0f;
}

void ObjectAlign::SetMirrorX(bool mirrorX) {
    this->mirrorX = mirrorX;
}

void ObjectAlign::SetMirrorY(bool mirrorY) {
    this->mirrorY = mirrorY;
}

void ObjectAlign::SetJustification(Justification jst) {
    this->jst = jst;
}

void ObjectAlign::SetScale(float scaleX, float scaleY) {
    this->scaleX = scaleX;
    this->scaleY = scaleY;
}

//Aligns object, does not move or scale object
Transform ObjectAlign::GetTransform(Object3D* obj){
    Object3D** objs = new Object3D*[1];
    objs[0] = obj;
    Transform objectCenter = GetTransform(objs, 1);
    delete[] objs;

    return objectCenter;
}

Transform ObjectAlign::GetTransform(Object3D** objs, uint8_t numObjects){
    Transform newTransform;
    // calculate planes, assume flat object (largest axes are axis), best fit plane i.e. centroid + direction/normal
    Vector3D centroid = GetCentroid(objs, numObjects);
    Quaternion planeOrientation = GetPlaneOrientation(objs, numObjects, centroid);
    Vector2D cameraSize = (camMax - camMin);
    Vector3D objectCenter = GetObjectCenter(objs, numObjects); // Get cameraCenter of objects

    // Get new size of objects after normalization
    Vector3D objectSize = GetObjectSize(objs, numObjects);

    float xRatio = (cameraSize.X - edgeMargin) / objectSize.X;
    float yRatio = (cameraSize.Y - edgeMargin) / objectSize.Y;

    if (jst != Stretch) {
        // Uniform object scaling with modifier
        xRatio = Mathematics::Min(xRatio, yRatio) * scaleX;
        yRatio = Mathematics::Min(xRatio, yRatio) * scaleY;
    }

    float xOffset = ((cameraSize.X - edgeMargin) - (xRatio * objectSize.X)) / 2.0f; // get left over space between camera edge and object in X-axis view
    float yOffset = ((cameraSize.Y - edgeMargin) - (yRatio * objectSize.Y)) / 2.0f; // get left over space between camera edge and object in Y-axis view

    switch (jst) {
        case UpperLeft:
            // No Change
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
        default: // Middle
            xOffset = 0.0f;
            yOffset = 0.0f;
            break;
    }

    // calculate point 250mm in front of camera
    Vector3D cameraTarget = targetOrientation.RotateVector(Vector3D(forwardVector * 250.0f) + Vector3D(cameraCenter.X, cameraCenter.Y, 0.0f));
    Quaternion outputQuaternion = planeOrientation.Conjugate().Multiply(targetOrientation);

    newTransform.SetPosition(Vector3D(xOffset, yOffset, 0.0f) + cameraTarget - objectCenter);
    newTransform.SetRotation(outputQuaternion);
    newTransform.SetRotationOffset(objectCenter);
    newTransform.SetScale(Vector3D(xRatio, yRatio, 1.0f) * Vector3D(mirrorX ? -1.0f : 1.0f, mirrorY ? -1.0f : 1.0f, 1.0f));

    return newTransform;
}

void ObjectAlign::AlignObjectNoScale(Object3D* obj) {
    Object3D** objs = new Object3D*[1];
    objs[0] = obj;
    AlignObjectsNoScale(objs, 1);
    delete[] objs;
}

void ObjectAlign::AlignObjectsNoScale(Object3D** objs, uint8_t numObjects) {
    Vector3D centroid = GetCentroid(objs, numObjects);
    Quaternion planeOrientation = GetPlaneNormal(objs, numObjects);
    Vector3D objectCenter = GetObjectCenter(objs, numObjects);
    NormalizeObjectPlane(objs, numObjects, centroid, planeOrientation);
    objectCenter = GetObjectCenter(objs, numObjects);
    NormalizeObjectCenter(objs, numObjects, objectCenter);
    Vector3D cameraTarget = targetOrientation.RotateVector(Vector3D(forwardVector * 250.0f) + Vector3D(cameraCenter.X, cameraCenter.Y, 0.0f));
    for (uint8_t i = 0; i < numObjects; i++) {
        for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
            Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];
            modifiedVector = modifiedVector * Vector3D(mirrorX ? -1.0f : 1.0f, mirrorY ? -1.0f : 1.0f, 1.0f);
            modifiedVector = targetOrientation.RotateVector(modifiedVector);
            modifiedVector = modifiedVector + cameraTarget;
            objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
        }
    }
}

void ObjectAlign::AlignObject(Object3D* obj) {
    Object3D** objs = new Object3D*[1];
    objs[0] = obj;
    AlignObjects(objs, 1);
    delete[] objs;
}

void ObjectAlign::AlignObjects(Object3D** objs, uint8_t numObjects) {
    // calculate planes, assume flat object (largest axes are axis), best fit plane i.e. centroid + direction/normal
    Vector3D centroid = GetCentroid(objs, numObjects);
    Quaternion planeOrientation = GetPlaneOrientation(objs, numObjects, centroid);
    Vector2D cameraSize = (camMax - camMin);
    Vector3D objectCenter = GetObjectCenter(objs, numObjects); // Get cameraCenter of objects

    // Normalize objects to plane orientation and cameraCenter of object
    NormalizeObjectPlane(objs, numObjects, centroid, planeOrientation);

    objectCenter = GetObjectCenter(objs, numObjects); // Get cameraCenter of objects

    NormalizeObjectCenter(objs, numObjects, objectCenter); // Shift object back to center of view

    // Get new size of objects after normalization
    Vector3D objectSize = GetObjectSize(objs, numObjects);

    float xRatio = (cameraSize.X - edgeMargin) / objectSize.X;
    float yRatio = (cameraSize.Y - edgeMargin) / objectSize.Y;

    if (jst != Stretch) {
        // Uniform object scaling with modifier
        xRatio = Mathematics::Min(xRatio, yRatio) * scaleX;
        yRatio = Mathematics::Min(xRatio, yRatio) * scaleY;
    }

    float xOffset = ((cameraSize.X - edgeMargin) - (xRatio * objectSize.X)) / 2.0f; // get left over space between camera edge and object in X-axis view
    float yOffset = ((cameraSize.Y - edgeMargin) - (yRatio * objectSize.Y)) / 2.0f; // get left over space between camera edge and object in Y-axis view

    switch (jst) {
        case UpperLeft:
            // No Change
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
        default: // Middle
            xOffset = 0.0f;
            yOffset = 0.0f;
            break;
    }

    // calculate point 250mm in front of camera
    Vector3D cameraTarget = targetOrientation.RotateVector(Vector3D(forwardVector * 250.0f) + Vector3D(cameraCenter.X, cameraCenter.Y, 0.0f));

    for (uint8_t i = 0; i < numObjects; i++) {
        for (uint16_t j = 0; j < objs[i]->GetTriangleGroup()->GetVertexCount(); j++) {
            Vector3D modifiedVector = objs[i]->GetTriangleGroup()->GetVertices()[j];

            // scaled object normalized in default camera space
            modifiedVector = modifiedVector * Vector3D(xRatio, yRatio, 1.0f) * Vector3D(mirrorX ? -1.0f : 1.0f, mirrorY ? -1.0f : 1.0f, 1.0f);

            // move object in default camera space before rotation
            modifiedVector = modifiedVector + Vector3D(xOffset, yOffset, 0.0f);

            // align object plane to camera plane
            modifiedVector = targetOrientation.RotateVector(modifiedVector);

            // move object to 250mm point in front of camera
            modifiedVector = modifiedVector + cameraTarget; // offset position

            objs[i]->GetTriangleGroup()->GetVertices()[j] = modifiedVector;
        }
    }
}
