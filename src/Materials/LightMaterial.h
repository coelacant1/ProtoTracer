#pragma once

#include "Material.h"
#include "..\Math\Vector2D.h"
#include "..\Render\Light.h"

//Converts gif to RGB XY pixel matrix
class LightMaterial : public Material {
private:
    Light lights[6];
    int numLights = 6;
  
public:
    LightMaterial(){
        lights[0].Set(Vector3D(1000, 0, 0), Vector3D(255, 0, 0), 1000.0f, 0.5f, 0.5f);//Set lights position, color intensity, falloff distance, and falloff curvature
        lights[1].Set(Vector3D(0, 1000, 0), Vector3D(0, 255, 0), 1000.0f, 0.5f, 0.5f);
        lights[2].Set(Vector3D(0, 1000, 1000), Vector3D(0, 0, 255), 1000.0f, 0.5f, 0.5f);
        lights[3].Set(Vector3D(-1000, 0, 0), Vector3D(120, 0, 120), 1000.0f, 0.5f, 0.5f);
        lights[4].Set(Vector3D(0, -1000, 0), Vector3D(120, 120, 0), 1000.0f, 0.5f, 0.5f);
        lights[5].Set(Vector3D(0, 0, -1000), Vector3D(0, 120, 120), 1000.0f, 0.5f, 0.5f);
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override {
        Vector3D color;

        for (int l = 0; l < numLights; l++) {
            Vector3D lVector = lights[l].p;// - tempInt;

            float angle = normal.DotProduct(lVector.UnitSphere());

            if (angle > 0) {
                float lDistance = lights[l].p.CalculateEuclideanDistance(position) / lights[l].falloff;
                float intensity = 1.0f / (1.0f + lDistance * lights[l].a + powf(lDistance / lights[l].falloff, 2.0f) * lights[l].b);
                
                color = color + (lights[l].intensity * angle * intensity);//add intensity drop with distance?
            }
        }

        return RGBColor(color);
    }
};
