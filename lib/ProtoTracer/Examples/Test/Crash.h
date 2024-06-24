#pragma once

#include "../Render/Object3D.h"
#include "../Render/ObjectDeformer.h"
#include "../Flash/CrashObjs.h"
#include "Animation.h"

class Crash : public Animation {
private:
    Light lights[6];
    Object3D* objects[7];
    Object3D protoDRV1Obj = Object3D(protoDRV1String, 150, 150);
    Object3D initObj = Object3D(initString, 100, 100);
    Object3D runningKernelObj = Object3D(runningKernelString, 260, 260);
    Object3D loadingModulesObj = Object3D(loadingModulesString, 260, 260);
    Object3D doneObj = Object3D(doneBootString, 200, 200);
    Object3D cursorObj = Object3D(cursorString, 10, 10);

    Object3D planeObj = Object3D(planeString, 150, 250);
    ObjectDeformer planeDeformer = ObjectDeformer(&planeObj);
    const int frames = 1260;

public:
    Crash(){
        lights[0].Set(Vector3D(1000, 0, 0), Vector3D(255, 0, 0), 1000.0f, 0.75f, 0.25f);//Set lights position, color intensity, falloff distance, and falloff curvature
        lights[1].Set(Vector3D(0, 1000, 0), Vector3D(0, 255, 0), 1000.0f, 0.75f, 0.25f);
        lights[2].Set(Vector3D(0, 0, 1000), Vector3D(0, 0, 255), 1000.0f, 0.75f, 0.25f);
        lights[3].Set(Vector3D(-2000, 0, 0), Vector3D(120, 0, 120), 1000.0f, 0.75f, 0.25f);
        lights[4].Set(Vector3D(0, -1000, 0), Vector3D(120, 120, 0), 1000.0f, 0.75f, 0.25f);
        lights[5].Set(Vector3D(0, 0, -1000), Vector3D(0, 120, 120), 1000.0f, 0.75f, 0.25f);
    
        objects[0] = &protoDRV1Obj;
        objects[1] = &initObj;
        objects[2] = &runningKernelObj;
        objects[3] = &loadingModulesObj;
        objects[4] = &doneObj;
        objects[5] = &cursorObj;
        objects[6] = &planeObj;
    
        scene = new Scene(objects, lights, 7, 6);
    }

    void FadeIn(float stepRatio){
        if (fade < 1.0f){
            fade += stepRatio;
            
            float ratio = Mathematics::CosineInterpolation(0.0f, 1.0f, fade);
            objects[0]->Scale(Vector3D(ratio, ratio, ratio), Vector3D(-40, 130, 0));
        }
    }

    void FadeOut(float stepRatio){
        if (fade > 0.0f){
            fade -= stepRatio;
            
            float ratio = Mathematics::CosineInterpolation(0.0f, 1.0f, fade);
            objects[0]->Scale(Vector3D(ratio, ratio, ratio), Vector3D(-40, 130, 0));
        }
    }

    void Update(float ratio){
        ratio = Mathematics::Constrain(ratio, 0.0f, 1.0f);
        int i = (int)(ratio * (float)frames);
        
        objects[0]->ResetVertices();
        objects[1]->ResetVertices();
        objects[2]->ResetVertices();
        objects[3]->ResetVertices();
        objects[4]->ResetVertices();
        objects[5]->ResetVertices();
        objects[6]->ResetVertices();
    }
};
