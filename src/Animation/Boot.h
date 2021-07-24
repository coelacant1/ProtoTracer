#pragma once

#include "..\Render\Object3D.h"
#include "..\Render\ObjectDeformer.h"
#include "..\Flash\BootObjs.h"
#include "Animation.h"

class Boot : public Animation {
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
    Boot(){
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
        
        objects[0]->Rotate(Vector3D(3 + sinf(i * 3.14159f / 180.0f * 4.0f) * 2.0f, sinf(i * 3.14159f / 180.0f * 2.0f) * 2.0f, 0), Vector3D(0, 100, 0));
        objects[1]->Rotate(Vector3D(3 + sinf(i * 3.14159f / 180.0f * 4.0f) * 2.0f, sinf(i * 3.14159f / 180.0f * 2.0f) * 2.0f, 0), Vector3D(0, 100, 0));
        objects[2]->Rotate(Vector3D(3 + sinf(i * 3.14159f / 180.0f * 4.0f) * 2.0f, sinf(i * 3.14159f / 180.0f * 2.0f) * 2.0f, 0), Vector3D(0, 100, 0));
        objects[3]->Rotate(Vector3D(3 + sinf(i * 3.14159f / 180.0f * 4.0f) * 2.0f, sinf(i * 3.14159f / 180.0f * 2.0f) * 2.0f, 0), Vector3D(0, 100, 0));
        objects[4]->Rotate(Vector3D(3 + sinf(i * 3.14159f / 180.0f * 4.0f) * 2.0f, sinf(i * 3.14159f / 180.0f * 2.0f) * 2.0f, 0), Vector3D(0, 100, 0));
        objects[5]->Rotate(Vector3D(3 + sinf(i * 3.14159f / 180.0f * 4.0f) * 2.0f, sinf(i * 3.14159f / 180.0f * 2.0f) * 2.0f, 0), Vector3D(0, 100, 0));
        
        objects[0]->Scale(Vector3D(1.0f + sinf(i * 3.14159f / 180.0f * 1.0f) * 0.025f, 1.0f + sinf(i * 3.14159f / 180.0f * 10.0f) * 0.025f, 1.0f), Vector3D(0, 0, 0));
        objects[1]->Scale(Vector3D(1.0f + sinf(i * 3.14159f / 180.0f * 1.0f) * 0.025f, 1.0f + sinf(i * 3.14159f / 180.0f * 10.0f) * 0.025f, 1.0f), Vector3D(0, 0, 0));
        objects[2]->Scale(Vector3D(1.0f + sinf(i * 3.14159f / 180.0f * 1.0f) * 0.025f, 1.0f + sinf(i * 3.14159f / 180.0f * 10.0f) * 0.025f, 1.0f), Vector3D(0, 0, 0));
        objects[3]->Scale(Vector3D(1.0f + sinf(i * 3.14159f / 180.0f * 1.0f) * 0.025f, 1.0f + sinf(i * 3.14159f / 180.0f * 10.0f) * 0.025f, 1.0f), Vector3D(0, 0, 0));
        objects[4]->Scale(Vector3D(1.0f + sinf(i * 3.14159f / 180.0f * 1.0f) * 0.025f, 1.0f + sinf(i * 3.14159f / 180.0f * 10.0f) * 0.025f, 1.0f), Vector3D(0, 0, 0));
        objects[5]->Scale(Vector3D(1.0f + sinf(i * 3.14159f / 180.0f * 1.0f) * 0.025f, 1.0f + sinf(i * 3.14159f / 180.0f * 10.0f) * 0.025f, 1.0f), Vector3D(0, 0, 0));
        
        lights[0].MoveTo(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f, 0, -cosf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f));
        lights[1].MoveTo(Vector3D(sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
        lights[2].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f, cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));
        lights[3].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f, 0, cosf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f));
        lights[4].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
        lights[5].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));
        
        if(i < 180){//protodrv1
        objects[0]->Enable();
        objects[1]->Disable();
        objects[2]->Disable();
        objects[3]->Disable();
        objects[4]->Disable();
        objects[5]->Disable();
        objects[6]->Disable();
        
        objects[0]->Scale(Vector3D(-1, 1, 1));
        objects[0]->MoveRelative(Vector3D(120, 70, 0));
        } else if (i < 270){//init
        objects[0]->Disable();
        objects[1]->Enable();
        objects[2]->Disable();
        objects[3]->Disable();
        objects[4]->Disable();
        objects[5]->Disable();
        objects[6]->Disable();

        objects[1]->Scale(Vector3D(-1, 1, 1));
        objects[1]->MoveRelative(Vector3D(120, 70, 0));
        } else if (i < 360){//done
        objects[0]->Disable();
        objects[1]->Disable();
        objects[2]->Disable();
        objects[3]->Disable();
        objects[4]->Enable();
        objects[5]->Disable();
        objects[6]->Disable();

        objects[4]->Scale(Vector3D(-1, 1, 1));
        objects[4]->MoveRelative(Vector3D(120, 70, 0));
        } else if (i < 540){//cursor blink and transform
        objects[0]->Disable();
        objects[1]->Disable();
        objects[2]->Disable();
        objects[3]->Disable();
        objects[4]->Disable();
        objects[5]->Enable();
        objects[6]->Disable();

        objects[5]->Scale(Vector3D(-1, 1, 1));
        objects[5]->MoveRelative(Vector3D(120, 82, 0));
        } else if (i < 900){//cursor blink and transform
        float ratio = Mathematics::CosineInterpolation(0.0f, 1.0f, ((float)(i - 540)) / 360.0f);
        
        Vector3D scale = Vector3D::LERP(Vector3D(-1, 1, 1), Vector3D(-10, 28, 1), ratio);
        Vector3D pos = Vector3D::LERP(Vector3D(120, 82, 0), Vector3D(-55, 120, 0), ratio);
        Vector3D rotation = Vector3D::LERP(Vector3D(0, 0, 0), Vector3D(0, 90, 0), ratio);
        
        objects[5]->ScaleCenter(scale);
        objects[5]->MoveRelative(pos);
        objects[5]->RotateCenter(rotation);
        } else if (i < 1260){//plane
        objects[0]->Disable();
        objects[1]->Disable();
        objects[2]->Disable();
        objects[3]->Disable();
        objects[4]->Disable();
        objects[5]->Disable();
        objects[6]->Enable();

        int iO = i + 90;
        
        float def = sinf(iO * 3.14159f / 180.0f * 1.0f) * 0.009f;
        float freq = sinf(iO * 3.14159f / 180.0f * 1.0f) * 4000.0f;
        
        planeDeformer.SineWaveSurfaceDeform(Vector3D(-150, 100, 0), Mathematics::Constrain(sinf(iO * 3.14159f / 180.0f * 1.0f) * 300.0f + 150.0f, 0.0f, 200.0f), sinf(-iO * 3.14159f / 180.0f * 0.1f), 0.01f + def, 7000.0f - freq, ObjectDeformer::ZAxis);
    
        float s1 = 0.3f + sinf(iO * 3.14159f / 180.0f * 2.0f) * 0.1f;
        float s2 = 0.4f + sinf(iO * 3.14159f / 180.0f * 2.0f) * 0.1f;
        float s3 = 0.3f + sinf(iO * 3.14159f / 180.0f * 3.0f) * 0.1f;
        float zs = Mathematics::Constrain(sinf(iO * 3.14159f / 180.0f * 1.0f) * 360.0f + 180.0f, 180.0f, 360.0f + 90.0f);
        float cs = Mathematics::Constrain(sinf(iO * 3.14159f / 180.0f * 1.0f) * 90.0f + 45.0f, 0, 90);
        float xs = sinf(iO * 3.14159f / 180.0f * 1.0f) * 225.0f + 45.0f;
    
        objects[6]->Scale(Vector3D(s1, 1.0f - s2, s3), Vector3D(0, 0, 0));
        objects[6]->Rotate(Vector3D(cs + 45.0f, xs + 90.0f, zs), Vector3D(0, 100, 0));
        objects[6]->MoveRelative(Vector3D(-40, 10, 0));
        }
    }
};
