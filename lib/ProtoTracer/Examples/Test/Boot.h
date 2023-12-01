#pragma once

#include "..\Templates\Project.h"
#include "..\..\Utils\Signals\FunctionGenerator.h"
#include "..\..\Assets\Models\OBJ\Spyro.h"
#include "..\..\Scene\Materials\Static\NormalMaterial.h"
#include "..\..\Scene\Objects\ObjectDeformer.h"
#include "..\..\Scene\Materials\CombineMaterial.h"
#include "..\..\Scene\Materials\Utils\MaterialAnimator.h"

#include "..\..\Scene\Materials\Static\LightMaterial.h"

#include "..\..\Assets\Models\OBJ\Cursor.h"
#include "..\..\Assets\Models\OBJ\DoneBoot.h"
#include "..\..\Assets\Models\OBJ\Init.h"
#include "..\..\Assets\Models\OBJ\LoadingModules.h"
#include "..\..\Assets\Models\OBJ\Plane.h"
#include "..\..\Assets\Models\OBJ\ProtoDRV1.h"
#include "..\..\Assets\Models\OBJ\RunningKernel.h"

#include "..\..\Camera\CameraManager\Implementations\HUB75DeltaCameras.h"
#include "..\..\Controller\HUB75Controller.h"

class Boot : public Project {
private:
    HUB75DeltaCameraManager cameras;
    HUB75Controller controller = HUB75Controller(&cameras, 100, 100);

    LightMaterial<6> lights = LightMaterial<6>();

    ProtoDRV1 protoDRV1O;
    Init initO;
    RunningKernel runningKernelO;
    LoadingModules loadingModulesO;
    DoneBoot doneO;
    Cursor cursorO;
    Plane planeO;

    ObjectDeformer planeDeformer = ObjectDeformer(planeO.GetObject());
    const int frames = 1500;

    FunctionGenerator square = FunctionGenerator(FunctionGenerator::Square, 0.0f, 1.0f, 0.5f);

    SimpleMaterial white = SimpleMaterial(RGBColor(255,255,255));
    SimpleMaterial blue = SimpleMaterial(RGBColor(0,75,255));
    SimpleMaterial black = SimpleMaterial(RGBColor(0,0,0));
    
    CombineMaterial<2> matCombine;
    CombineMaterial<2> textColor;

public:
    Boot() : Project(&cameras, &controller, 7){
        scene.AddObject(protoDRV1O.GetObject());
        scene.AddObject(initO.GetObject());
        scene.AddObject(runningKernelO.GetObject());
        scene.AddObject(loadingModulesO.GetObject());
        scene.AddObject(doneO.GetObject());
        scene.AddObject(cursorO.GetObject());
        scene.AddObject(planeO.GetObject());

        lights.GetLights()[0].Set(Vector3D(500, 0, 0), Vector3D(255, 0, 0), 1000.0f, 0.75f, 0.25f);//Set lights position, color intensity, falloff distance, and falloff curvature
        lights.GetLights()[1].Set(Vector3D(0, 500, 0), Vector3D(0, 255, 0), 1000.0f, 0.75f, 0.25f);
        lights.GetLights()[2].Set(Vector3D(0, 0, 500), Vector3D(0, 0, 255), 1000.0f, 0.75f, 0.25f);
        lights.GetLights()[3].Set(Vector3D(-500, 0, 0), Vector3D(120, 0, 120), 1000.0f, 0.75f, 0.25f);
        lights.GetLights()[4].Set(Vector3D(0, -500, 0), Vector3D(120, 120, 0), 1000.0f, 0.75f, 0.25f);
        lights.GetLights()[5].Set(Vector3D(0, 0, -500), Vector3D(0, 120, 120), 1000.0f, 0.75f, 0.25f);

        planeO.GetObject()->SetMaterial(&lights);
        cursorO.GetObject()->SetMaterial(&matCombine);


        textColor.AddMaterial(Material::Add, &white, 1.0f);
        textColor.AddMaterial(Material::Replace, &blue, 0.0f);

        matCombine.AddMaterial(Material::Add, &textColor, 1.0f);
        matCombine.AddMaterial(Material::Replace, &black, 0.0f);
    }

    void Initialize() override {
        controller.Initialize();
    }

    void Update(float ratio){
        ratio = Mathematics::Constrain(ratio, 0.0f, 1.0f);
        int i = (int)(ratio * (float)frames);
        
        protoDRV1O.GetObject()->ResetVertices();
        initO.GetObject()->ResetVertices();
        runningKernelO.GetObject()->ResetVertices();
        loadingModulesO.GetObject()->ResetVertices();
        doneO.GetObject()->ResetVertices();
        cursorO.GetObject()->ResetVertices();
        planeO.GetObject()->ResetVertices();
        
        lights.GetLights()[0].MoveTo(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f, 0, -cosf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f));
        lights.GetLights()[1].MoveTo(Vector3D(sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
        lights.GetLights()[2].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f, cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));
        lights.GetLights()[3].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f, 0, cosf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f));
        lights.GetLights()[4].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
        lights.GetLights()[5].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));
        
        protoDRV1O.GetObject()->Disable();
        initO.GetObject()->Disable();
        runningKernelO.GetObject()->Disable();
        loadingModulesO.GetObject()->Disable();
        doneO.GetObject()->Disable();
        cursorO.GetObject()->Disable();
        planeO.GetObject()->Disable();

        if(i < 180){//protodrv1
            protoDRV1O.GetObject()->Enable();
            
            protoDRV1O.GetObject()->GetTransform()->SetScale(Vector3D(-0.75f, 0.75f, 1));
            protoDRV1O.GetObject()->GetTransform()->SetPosition(Vector3D(180, 48, 0));
        } else if (i < 270){//init
            initO.GetObject()->Enable();

            initO.GetObject()->GetTransform()->SetScale(Vector3D(-0.75f, 0.75f, 1));
            initO.GetObject()->GetTransform()->SetPosition(Vector3D(180, 48, 0));
        } else if (i < 360){//done
            doneO.GetObject()->Enable();

            doneO.GetObject()->GetTransform()->SetScale(Vector3D(-0.75f, 0.75f, 1));
            doneO.GetObject()->GetTransform()->SetPosition(Vector3D(180, 48, 0));
        } else if (i < 540){//cursor blink and transform
            cursorO.GetObject()->Enable();

            if (square.Update() < 0.05f){
                matCombine.SetOpacity(1, 1.0f);
            }
            else{
                matCombine.SetOpacity(1, 0.0f);
            }

            cursorO.GetObject()->GetTransform()->SetScale(Vector3D(-0.75f, 0.75f, 1));
            cursorO.GetObject()->GetTransform()->SetPosition(Vector3D(180, 56, 0));
        } else if (i < 900){//cursor blink and transform

            cursorO.GetObject()->Enable();

            float transition = Mathematics::CosineInterpolation(0.0f, 1.0f, float(i - 540) / 360.0f);

            if (square.Update() < 0.05f){
                matCombine.SetOpacity(1, 1.0f - transition);
            }
            else{
                matCombine.SetOpacity(1, 0.0f);
            }

            Vector3D scale, pos;
            
            if (transition < 0.5f){
                scale = Vector3D::LERP(Vector3D(-0.75f, 0.75f, 1), Vector3D(-10, 5.0f, 1), Mathematics::Map(transition, 0.0f, 0.5f, 0.0f, 1.0f));
            }
            else{
                scale = Vector3D::LERP(Vector3D(-10, 5.0f, 1), Vector3D(-20, 0.0f, 1), Mathematics::Map(transition, 0.5f, 1.0f, 0.0f, 1.0f));
            }
            
            if (transition < 0.5f){
                pos = Vector3D::LERP(Vector3D(180, 56, 0), Vector3D(120, 180.0f, 0), Mathematics::Map(transition, 0.0f, 0.5f, 0.0f, 1.0f));
            }
            else{
                pos = Vector3D::LERP(Vector3D(120, 180, 0), Vector3D(-6.0f, 150.0f, 0), Mathematics::Map(transition, 0.5f, 1.0f, 0.0f, 1.0f));
            }

            Vector3D rotation = Vector3D::LERP(Vector3D(0, 0, 0), Vector3D(0, 0, 135), transition);

            Vector3D center = cursorO.GetObject()->GetCenterOffset();
            
            cursorO.GetObject()->GetTransform()->SetRotationOffset(center);
            //cursorO.GetObject()->GetTransform()->SetScaleOffset(center);
            cursorO.GetObject()->GetTransform()->SetScale(scale);
            cursorO.GetObject()->GetTransform()->SetRotation(rotation);
            
            cursorO.GetObject()->GetTransform()->SetPosition(pos);
            
            textColor.SetOpacity(1, transition);
        } else if (i < 1260){//plane
            planeO.GetObject()->Enable();

            int iO = i + 90;
            
            float def = sinf(iO * 3.14159f / 180.0f * 1.0f) * 0.009f;
            float freq = sinf(iO * 3.14159f / 180.0f * 1.0f) * 4000.0f;
            
            planeDeformer.SineWaveSurfaceDeform(Vector3D(-150, 100, 0), Mathematics::Constrain(sinf(iO * 3.14159f / 180.0f * 1.0f) * 300.0f + 150.0f, 0.0f, 200.0f), sinf(-iO * 3.14159f / 180.0f * 0.1f), 0.01f + def, 7000.0f - freq, ObjectDeformer::ZAxis);
        
            float s1 = 0.3f + sinf(iO * 3.14159f / 180.0f * 2.0f) * 0.1f;//0.3
            float s2 = 0.4f + sinf(iO * 3.14159f / 180.0f * 2.0f) * 0.1f;//0.4
            float s3 = 0.3f + sinf(iO * 3.14159f / 180.0f * 3.0f) * 0.1f;//0.3
            float zs = Mathematics::Constrain(sinf(iO * 3.14159f / 180.0f * 1.0f) * 360.0f + 180.0f, 180.0f, 360.0f + 90.0f);
            float cs = Mathematics::Constrain(sinf(iO * 3.14159f / 180.0f * 1.0f) * 90.0f + 45.0f, 0.0f, 90.0f);
            float xs = sinf(iO * 3.14159f / 180.0f * 1.0f) * 225.0f + 45.0f;
        
            planeO.GetObject()->GetTransform()->SetScaleOffset(Vector3D(0, 0, 0));
            planeO.GetObject()->GetTransform()->SetScale(Vector3D(s1, 1.0f - s2, s3));
            
            planeO.GetObject()->GetTransform()->SetRotationOffset(Vector3D(0, 100, 0));
            planeO.GetObject()->GetTransform()->SetRotation(Vector3D(cs + 45.0f, xs + 90.0f, zs));

            planeO.GetObject()->GetTransform()->SetPosition(Vector3D(96.0f, -48.0f, 0));
        }

        protoDRV1O.GetObject()->UpdateTransform();
        initO.GetObject()->UpdateTransform();
        runningKernelO.GetObject()->UpdateTransform();
        loadingModulesO.GetObject()->UpdateTransform();
        doneO.GetObject()->UpdateTransform();
        cursorO.GetObject()->UpdateTransform();
        planeO.GetObject()->UpdateTransform();
    }
};
