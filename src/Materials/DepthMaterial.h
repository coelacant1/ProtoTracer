#pragma once

#include "Material.h"
#include "..\Math\Vector2D.h"
#include "GradientMaterial.h"

//Converts gif to RGB XY pixel matrix
class DepthMaterial : public Material {
public:
    enum Axis{
        X,
        Y,
        Z
    };

private:
    RGBColor spectrum[4] = {RGBColor(0, 255, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
    GradientMaterial gNoiseMat = GradientMaterial(4, spectrum, 2.0f, false);
    Axis axis;
    float depth = 0.0f;
    float zOffset = 0.0f;
  
public:
    DepthMaterial(Axis axis, float depth, float zOffset){
        this->axis = axis;
        this->depth = depth;
        this->zOffset = zOffset;
    }
    
    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        float axisValue = 0.0f;

        switch(axis){
            case X:
                axisValue = position.X;
                break;
            case Y:
                axisValue = position.Y;
                break;
            case Z:
                axisValue = position.Z;
                break;
            default:
                break;
        }

        float pos = Mathematics::Map(axisValue, -depth / 2.0f + zOffset, depth / 2.0f + zOffset, 0.0f, 1.0f);
        
        return gNoiseMat.GetRGB(Vector3D(pos, 0, 0), Vector3D(), Vector3D());
    }
};
