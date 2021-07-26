#pragma once

#include "..\Materials\BMP.h"
#include "..\Math\Rotation.h"
#include "Pixel.h"
#include "PixelReader.h"
#include "Scene.h"
#include "Triangle2D.h"

class Camera {
private:
	Quaternion q;
	Vector3D p;
    Vector3D pictureCenter;
    unsigned int pixelCount;
    Pixel* pixelStorage;
    PixelReader pixelReader;
    bool antiAliasing = false;
    unsigned int antiAliasingSubdivisions = 2;
    float pixelPixelDistance = 1.0f;

    Vector3D CheckRasterPixel(Scene* scene, Triangle2D** triangles, int numTriangles, Vector2D pixelRay){
        float zBuffer = 3.402823466e+38f;
        int triangle = 0;
        bool didIntersect = false;
        Vector3D intersect;
        Vector3D color;
        
        for (int t = 0; t < numTriangles; t++) {
            float u = 0.0f, v = 0.0f, w = 0.0f;
            
            if (triangles[t]->DidIntersect(pixelRay, u, v, w)){
            intersect = *triangles[t]->t3p1 + (*triangles[t]->t3e2 * u) + (*triangles[t]->t3e1 * v);
            float rayDistanceToTriangle = Vector3D(pixelRay.X + p.X, pixelRay.Y + p.Y, p.Z).CalculateEuclideanDistance(intersect);
            
            if(rayDistanceToTriangle < zBuffer){
                zBuffer = rayDistanceToTriangle;
                intersect = *triangles[t]->t3p1 + (*triangles[t]->t3e2 * u) + (*triangles[t]->t3e1 * v);
                triangle = t;
            }

            didIntersect = true;
            }
        }

        if(didIntersect){
            if(triangles[triangle]->useMaterial){
                Vector3D rotateRay = q.RotateVector(Vector3D(pixelRay.X, pixelRay.Y, 0).Subtract(p));
                
                pixelRay = Vector2D(-rotateRay.X, rotateRay.Y);
                
                RGBColor rgbC = triangles[triangle]->GetMaterial()->GetRGB(pixelRay);
                color = Vector3D(rgbC.R, rgbC.G, rgbC.B);
            }
            else{
                for (int l = 0; l < scene->numLights; l++) {
                    Vector3D lVector = scene->lights[l].p;// - tempInt;
            
                    float angle = triangles[triangle]->normal.DotProduct(lVector.UnitSphere());
        
                    if (angle > 0) {
                        float lDistance = scene->lights[l].p.CalculateEuclideanDistance(intersect) / scene->lights[l].falloff;
                        float intensity = 1.0f / (1.0f + lDistance * scene->lights[l].a + powf(lDistance / scene->lights[l].falloff, 2.0f) * scene->lights[l].b);
                        
                        color = color + (scene->lights[l].intensity * angle * intensity);//add intensity drop with distance?
                    }
                }
            }
        }
        
        return color;
    }

    Vector3D CheckRasterPixelAntiAlias(int subdivisions, float pixelDistance, Scene* scene, Triangle2D** triangles, int numTriangles, Vector2D pixelRay){
        Vector3D color;
        float pixelHDistance = pixelDistance / 2.0f;
        float scanDistance = pixelDistance / (float)subdivisions;
        Vector2D startPoint = Vector2D(-pixelHDistance + (scanDistance / 2.0f), pixelHDistance - (scanDistance / 2.0f));

        for (int i = 0; i < subdivisions; i++){
            for (int j = 0; j < subdivisions; j++){
            color = color + CheckRasterPixel(scene, triangles, numTriangles, pixelRay + startPoint + Vector2D(scanDistance * subdivisions, scanDistance * subdivisions));
            }
        }

        return color / subdivisions;
    }

public:
    Camera(Vector3D q, Vector3D p, unsigned int pixelCount, const String* pixelData, bool flipX, bool flipY, bool flipOrder) {
        pixelStorage = new Pixel[pixelCount];
        Vector2D pictureCenter;
        pixelReader.GetPixels(pixelStorage, pixelCount, pixelData, pictureCenter, flipX, flipY, flipOrder);

        this->pictureCenter = Vector3D(pictureCenter.X, pictureCenter.Y, 0);
        
        pixelPixelDistance = fabs(pixelStorage[0].X - pixelStorage[1].X);

        this->pixelCount = pixelCount;
        
        this->q = Rotation(EulerAngles(q, EulerConstants::EulerOrderXYZR)).GetQuaternion();
        this->p = p;

        this->p.X = -p.X;
        this->p.Y = -p.Y;
    }
    
        Camera(Quaternion q, Vector3D p, unsigned int pixelCount, const String* pixelData, bool flipX, bool flipY, bool flipOrder) {
        pixelStorage = new Pixel[pixelCount];
        Vector2D pictureCenter;
        pixelReader.GetPixels(pixelStorage, pixelCount, pixelData, pictureCenter, flipX, flipY, flipOrder);
        
        this->pictureCenter = Vector3D(pictureCenter.X, pictureCenter.Y, 0);
        
        pixelPixelDistance = fabs(pixelStorage[0].X - pixelStorage[1].X);

        this->pixelCount = pixelCount;
        
            this->q = q;
            this->p = p;

            this->p.X = -p.X;
            this->p.Y = -p.Y;
        }
    
    Camera(Quaternion q, Vector3D p, unsigned int horizontal, unsigned int vertical) {
        pixelStorage = new Pixel[horizontal * vertical];
        pixelReader.GetPixels(pixelStorage, false, false);
        
        pixelPixelDistance = fabs(pixelStorage[0].X - pixelStorage[1].X);
        
        this->q = q;
        this->p = p;

        this->p.X = -p.X;
        this->p.Y = -p.Y;
    }

    unsigned int GetPixelCount(){
        return pixelCount;
    }

    Pixel* GetPixels(){
        return pixelStorage;
    }

    Vector3D GetPictureCenter(){
        return q.RotateVector(pictureCenter) + p;
    }

        void Translate(Quaternion q, Vector3D p) {
            this->q = (this->q + q).UnitQuaternion();
            this->p = this->p + p.Multiply(-1.0f);
        }

        void MoveTo(Quaternion q, Vector3D p) {
            this->q = q;
            this->p = p;

            this->p.X = -p.X;
            this->p.Y = -p.Y;
        }

        void MoveTo(Vector3D qv, Vector3D p) {
            qv.Z = -qv.Z;
            this->q = Rotation(EulerAngles(qv, EulerConstants::EulerOrderXYZR)).GetQuaternion();
            this->p = p;

            this->p.X = -p.X;
            this->p.Y = -p.Y;
        }

    void EnableAntiAliasing(){
        antiAliasing = true;
    }
    
    void DisableAntiAliasing(){
        antiAliasing = false;
    }

    void SetAntiAliasingLevel(unsigned int level){
        antiAliasingSubdivisions = level;
    }

        void Rasterize(Scene* scene, float scale, float maxBrightness) {
        int numTriangles = 0;
    
        //for each object in the scene, get the triangles
        for(int i = 0; i < scene->numObjects; i++){
        if(scene->objects[i]->IsEnabled()){
            numTriangles += scene->objects[i]->GetTriangleAmount();
        }
        }
        
            Triangle2D** triangles = new Triangle2D*[numTriangles];
        int triangleCounter = 0;

        //for each object in the scene, get the triangles
        for(int i = 0; i < scene->numObjects; i++){
        if(scene->objects[i]->IsEnabled()){
            //for each triangle in object, project onto 2d surface, but pass material
            for (int j = 0; j < scene->objects[i]->GetTriangleAmount(); j++) {
            scene->objects[i]->GetTriangles()[j].Normal();
            
            if(scene->objects[i]->HasMaterial()){
                triangles[triangleCounter] = new Triangle2D(q, p, scene->objects[i]->GetTriangles()[j], scene->objects[i]->GetMaterial());
            }
            else{
                triangles[triangleCounter] = new Triangle2D(q, p, scene->objects[i]->GetTriangles()[j]);
            }
            
            triangleCounter++;
            }
        }
        }

            for (unsigned int i = 0; i < pixelCount; i++) {
        Vector2D pixelRay = Vector2D(pixelStorage[i].X * scale, pixelStorage[i].Y * scale);
        Vector3D color;

        if (antiAliasing){
            color = CheckRasterPixelAntiAlias(2, pixelPixelDistance * scale, scene, triangles, numTriangles, pixelRay);
        }
        else{
            color = CheckRasterPixel(scene, triangles, numTriangles, pixelRay);
        }

        color = color.Divide(255.0f / maxBrightness).Constrain(0.0f, maxBrightness);

        pixelStorage[i].Color.R = color.X;
        pixelStorage[i].Color.G = color.Y;
        pixelStorage[i].Color.B = color.Z;
            }

        for (int i = 0; i < triangleCounter; i++){
        delete triangles[i];
        }
        
            delete[] triangles;
        }
    
    float moveBMP = 0;

    void BMPRasterize(BMP *bmpImage, float scale, uint8_t maxBrightness){
        for (unsigned int i = 0; i < pixelCount; i++) {
        Vector3D camV = p;
        //camV.X = -camV.X;
        //camV.Y = -camV.Y;
        
        Quaternion temp = Rotation(EulerAngles(Vector3D(0, 0, -15), EulerConstants::EulerOrderXYZR)).GetQuaternion();

        float xpos, ypos, modifier = 1.0f;

        xpos = sinf(moveBMP * 3.14159f / 180.0f * 1.9f) * 10.0f;
        ypos = cosf(moveBMP * 3.14159f / 180.0f * 2.5f) * 10.0f;
        modifier = 1.0f;//0.9f + sinf(moveBMP * 3.14159f / 180.0f * 4.0f) * 0.1f;
        
        //Vector2D(camQ.UnrotateVector(Vector3D(*t.p1)) - camV);
        Vector3D rotateRay = q.RotateVector(Vector3D(pixelStorage[i].X, pixelStorage[i].Y, 0).Subtract(camV)).Add(Vector3D(-xpos, -ypos, 0));

        rotateRay = temp.RotateVector(rotateRay);
        
        Vector2D pixelRay = Vector2D(-rotateRay.X * scale, rotateRay.Y * scale) * modifier;

        pixelStorage[i].Color = bmpImage->GetRGB(pixelRay).Scale(maxBrightness);
        }
        
        moveBMP += 0.5f;

        if (moveBMP > 5000) moveBMP = 0;
    }
};
