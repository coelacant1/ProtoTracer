#include "Rasterizer.h"

Quaternion Rasterizer::rayDirection;
Quaternion Rasterizer::lookDirection;

RGBColor Rasterizer::CheckRasterPixelAccel(Triangle2D** triangles, int numTriangles, Vector2D pixelRay) {
    float zBuffer = 3.402823466e+38f;
    int triangle = 0;
    bool didIntersect = false;
    float u = 0.0f, v = 0.0f, w = 0.0f;
    Vector3D uvw;
    RGBColor color;

    #ifndef _ARM_MATH_H
    for (int t = 0; t < numTriangles; t++) {
        if (triangles[t]->averageDepth < zBuffer) {
            if (triangles[t]->DidIntersect(pixelRay.X, pixelRay.Y, u, v, w)) {
                uvw.X = u;
                uvw.Y = v;
                uvw.Z = w;
                zBuffer = triangles[t]->averageDepth;
                triangle = t;
                didIntersect = true;
            }
        }
    }
    #else
    //subtract for all triangles
    //float v2lX = x - p1X;
    //float v2lY = y - p1Y;
    float32_t subA[numTriangles * 2];
    float32_t subB[numTriangles * 2];
    float32_t subDst[numTriangles * 2];

    for (int i = 0; i < numTriangles; i++){
        subA[i * 2 + 0] = pixelRay.X;//x
        subA[i * 2 + 1] = pixelRay.Y;//y

        subB[i * 2 + 0] = triangles[i]->p1X;//p1x
        subB[i * 2 + 1] = triangles[i]->p1Y;//p1y
    }

    arm_sub_f32(subA, subB, subDst, numTriangles * 2);
    
    //v w multiplication
    // v2lX * v1Y | v1X * v2lY
    // v0X * v2lY | v2lX * v0Y
    float32_t multA[numTriangles * 4];
    float32_t multB[numTriangles * 4];
    float32_t multDst[numTriangles * 4];

    for (int i = 0; i < numTriangles; i++){
        multA[i * 4 + 0] = subDst[i * 2 + 0];//v2lx, from first set
        multA[i * 4 + 1] = triangles[i]->v1X;
        multA[i * 4 + 2] = triangles[i]->v0X;
        multA[i * 4 + 3] = subDst[i * 2 + 0];//v2lx, from first set
        
        multB[i * 4 + 0] = triangles[i]->v1Y;
        multB[i * 4 + 1] = subDst[i * 2 + 1];//v2ly, from first set
        multB[i * 4 + 2] = subDst[i * 2 + 1];//v2ly, from first set
        multB[i * 4 + 3] = triangles[i]->v0Y;
    }

    arm_mult_f32(multA, multB, multDst, numTriangles * 4);

    //v w subtraction (mult - mult)
    float32_t sub1A[numTriangles * 2];
    float32_t sub1B[numTriangles * 2];
    float32_t sub1Dst[numTriangles * 2];

    for (int i = 0; i < numTriangles; i++){
        sub1A[i * 2 + 0] = multDst[i * 4];//v2lX * v1Y
        sub1A[i * 2 + 1] = multDst[i * 4 + 2];//v0X * v2lY

        sub1B[i * 2 + 0] = multDst[i * 4 + 1];//v1X * v2lY
        sub1B[i * 2 + 1] = multDst[i * 4 + 3];//v2lX * v0Y
    }

    arm_sub_f32(sub1A, sub1B, sub1Dst, numTriangles * 2);

    //v w denominator multiplication
    float32_t mult1A[numTriangles * 2];
    float32_t mult1B[numTriangles * 2];
    float32_t mult1Dst[numTriangles * 2];

    for (int i = 0; i < numTriangles; i++){
        mult1A[i * 2 + 0] = sub1Dst[i * 2 + 0];//(v2lX * v1Y - v1X * v2lY)
        mult1A[i * 2 + 1] = sub1Dst[i * 2 + 1];//(v0X * v2lY - v2lX * v0Y)
        
        mult1B[i * 2 + 0] = triangles[i]->denominator;
        mult1B[i * 2 + 1] = triangles[i]->denominator;
    }

    arm_mult_f32(mult1A, mult1B, mult1Dst, numTriangles * 2);//provides v and w

    for (int i = 0; i < numTriangles; i++){
        v = mult1Dst[i * 2 + 0];
        w = mult1Dst[i * 2 + 1];
        u = 1.0f - v - w;

        if (triangles[i]->averageDepth < zBuffer) {
            bool intersect = !(v < 0.0f || w < 0.0f || v > 1.0f || w > 1.0f) && u > 0.0f;
            if (intersect){
                uvw.X = u;
                uvw.Y = v;
                uvw.Z = w;
                zBuffer = triangles[i]->averageDepth;
                triangle = i;
                didIntersect = true;
            }
        }
    }
    #endif
    
    if (didIntersect) {
        Vector3D intersect = (*triangles[triangle]->t3p1 * uvw.X) + (*triangles[triangle]->t3p2 * uvw.Y) + (*triangles[triangle]->t3p3 * uvw.Z);

        intersect = rayDirection.UnrotateVector(intersect);
        Vector2D uv;

        if (triangles[triangle]->hasUV) {
            uv = *triangles[triangle]->p1UV * uvw.X + *triangles[triangle]->p2UV * uvw.Y + *triangles[triangle]->p3UV * uvw.Z;
        }

        color = triangles[triangle]->GetMaterial()->GetRGB(intersect, *triangles[triangle]->normal, Vector3D(uv.X, uv.Y, 0.0f));
    }

    return color;
}

RGBColor Rasterizer::CheckRasterPixel(Triangle2D** triangles, int numTriangles, Vector2D pixelRay) {
    float zBuffer = 3.402823466e+38f;
    int triangle = 0;
    bool didIntersect = false;
    float u = 0.0f, v = 0.0f, w = 0.0f;
    Vector3D uvw;
    RGBColor color;

    for (int t = 0; t < numTriangles; t++) {
        if (triangles[t]->averageDepth < zBuffer) {
            if (triangles[t]->DidIntersect(pixelRay.X, pixelRay.Y, u, v, w)) {
                uvw.X = u;
                uvw.Y = v;
                uvw.Z = w;
                zBuffer = triangles[t]->averageDepth;
                triangle = t;
                didIntersect = true;
            }
        }
    }
    
    if (didIntersect) {
        Vector3D intersect = (*triangles[triangle]->t3p1 * uvw.X) + (*triangles[triangle]->t3p2 * uvw.Y) + (*triangles[triangle]->t3p3 * uvw.Z);

        intersect = rayDirection.UnrotateVector(intersect);
        Vector2D uv;

        if (triangles[triangle]->hasUV) {
            uv = *triangles[triangle]->p1UV * uvw.X + *triangles[triangle]->p2UV * uvw.Y + *triangles[triangle]->p3UV * uvw.Z;
        }

        color = triangles[triangle]->GetMaterial()->GetRGB(intersect, *triangles[triangle]->normal, Vector3D(uv.X, uv.Y, 0.0f));
    }

    return color;
}

void Rasterizer::Rasterize(Scene* scene, CameraBase* camera) {
    if (camera->Is2D()) {
        for (unsigned int i = 0; i < camera->GetPixelGroup()->GetPixelCount(); i++) {
            Vector2D pixelRay = camera->GetPixelGroup()->GetCoordinate(i);
            Vector3D pixelRay3D = Vector3D(pixelRay.X, pixelRay.Y, 0) + camera->GetTransform()->GetPosition();

            RGBColor color = scene->GetObjects()[0]->GetMaterial()->GetRGB(pixelRay3D, Vector3D(), Vector3D());

            camera->GetPixelGroup()->GetColor(i)->R = color.R;
            camera->GetPixelGroup()->GetColor(i)->G = color.G;
            camera->GetPixelGroup()->GetColor(i)->B = color.B;
        }
    } else {
        camera->GetTransform()->SetBaseRotation(camera->GetCameraLayout()->GetRotation());

        lookDirection = camera->GetTransform()->GetRotation().Conjugate() * camera->GetLookOffset();
        Quaternion normLookDir = lookDirection.UnitQuaternion();
        rayDirection = camera->GetTransform()->GetRotation().Multiply(lookDirection);

        Vector2D pixelRay;
        BoundingBox2D transformedBounds;
        bool cameraScale = !(Mathematics::IsClose(camera->GetTransform()->GetScale().X, 1.0f, 0.01f) && Mathematics::IsClose(camera->GetTransform()->GetScale().Y, 1.0f, 0.01f) && Mathematics::IsClose(camera->GetTransform()->GetScale().Z, 1.0f, 0.01f));
        
        for (unsigned int i = 0; i < camera->GetPixelGroup()->GetPixelCount(); ++i) {
            if (cameraScale)
                pixelRay = Vector2D(lookDirection.RotateVectorUnit(camera->GetPixelGroup()->GetCoordinate(i) * camera->GetTransform()->GetScale(), normLookDir));
            else
                pixelRay = Vector2D(lookDirection.RotateVectorUnit(camera->GetPixelGroup()->GetCoordinate(i), normLookDir));

            transformedBounds.UpdateBounds(pixelRay);
        }

        QuadTree tree(transformedBounds);

        for (int i = 0; i < scene->GetObjectCount(); i++) {
            if (scene->GetObjects()[i]->IsEnabled()) {
                for (int j = 0; j < scene->GetObjects()[i]->GetTriangleGroup()->GetTriangleCount(); j++) {
                    tree.Insert(Triangle2D(lookDirection, camera->GetTransform(), &scene->GetObjects()[i]->GetTriangleGroup()->GetTriangles()[j], scene->GetObjects()[i]->GetMaterial()));
                }
            }
        }

        tree.Rebuild();

        for (unsigned int i = 0; i < camera->GetPixelGroup()->GetPixelCount(); i++) {
            if (cameraScale)
                pixelRay = Vector2D(lookDirection.RotateVectorUnit(camera->GetPixelGroup()->GetCoordinate(i) * camera->GetTransform()->GetScale(), normLookDir));
            else
                pixelRay = Vector2D(lookDirection.RotateVectorUnit(camera->GetPixelGroup()->GetCoordinate(i), normLookDir));

            Node* leafNode = tree.Intersect(pixelRay);

            if (!leafNode) {
                camera->GetPixelGroup()->GetColor(i)->R = 0;
                camera->GetPixelGroup()->GetColor(i)->G = 0;
                camera->GetPixelGroup()->GetColor(i)->B = 0;
                continue;
            }

            RGBColor color = CheckRasterPixel(leafNode->GetEntities(), leafNode->GetCount(), pixelRay);

            camera->GetPixelGroup()->GetColor(i)->R = color.R;
            camera->GetPixelGroup()->GetColor(i)->G = color.G;
            camera->GetPixelGroup()->GetColor(i)->B = color.B;
        }
    }
}
