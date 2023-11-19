#include "Rasterizer.h"

Quaternion Rasterizer::rayDirection;
Quaternion Rasterizer::lookDirection;

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

        BoundingBox2D transformedBounds;
        for (unsigned int i = 0; i < camera->GetPixelGroup()->GetPixelCount(); ++i) {
            Vector2D pixelRay = Vector2D(lookDirection.RotateVectorUnit(camera->GetPixelGroup()->GetCoordinate(i) * camera->GetTransform()->GetScale(), normLookDir));
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
            Vector2D pixelRay = Vector2D(lookDirection.RotateVectorUnit(camera->GetPixelGroup()->GetCoordinate(i) * camera->GetTransform()->GetScale(), normLookDir));
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
